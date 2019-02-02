#include<algorithm>
#include<iterator>

#include<onerut_parser/ast_source.hpp>
#include<onerut_parser/identifier_global.hpp>
#include<onerut_parser/function_global.hpp>
#include<onerut_scalar/scalar.hpp>
#include<onerut_parser/ast_compile_result.hpp>
#include<onerut_parser/share_from.hpp>

namespace {

    bool is_plus_munis_char(char32_t op) {
        return op == L'+' || op == L'-';
    }

    bool is_prod_div_char(char32_t op) {
        return op == L'*' || op == L'/';
    }

    bool is_integer(const onerut_parser::CompileResult& result) {
        assert(!result.is_empty());
        assert(!result.is_compile_error());
        return result.is_given_type<onerut_scalar::Long>();
    }

    bool is_real(const onerut_parser::CompileResult& result) {
        assert(!result.is_empty());
        assert(!result.is_compile_error());
        return result.is_given_type<onerut_scalar::Long>() || result.is_given_type<onerut_scalar::Double>();
    }

    bool is_ref(const onerut_parser::CompileResult& result) {
        return result.is_given_type<onerut_parser::CompileResultRef>();
    }

    bool is_const_ref(const onerut_parser::CompileResult& result) {
        return result.is_given_type<onerut_parser::ConstCompileResultRef>();
    }

    bool is_identifier_not_found_error(const onerut_parser::CompileResult& result) {
        if (const auto& error = result.compile_error_or_empty())
            if (std::dynamic_pointer_cast<const onerut_parser::IdentifierNotFoundError>(*error))
                return true;
        return false;
    }

    std::shared_ptr<onerut_scalar::Long> to_long(const onerut_parser::CompileResult& arg_result) {
        assert(is_integer(arg_result));
        std::shared_ptr<onerut_scalar::Long> arg_long;
        arg_long = *arg_result.typed_value_or_empty<onerut_scalar::Long>();
        assert(arg_long);
        return arg_long;
    }

    std::shared_ptr<onerut_scalar::Double> to_double(const onerut_parser::CompileResult& arg_result) {
        assert(is_real(arg_result));
        std::shared_ptr<onerut_scalar::Double> arg_double;
        if (auto temp = arg_result.typed_value_or_empty<onerut_scalar::Long>()) {
            arg_double = *temp;
        } else {
            arg_double = *arg_result.typed_value_or_empty<onerut_scalar::Double>();
        }
        assert(arg_double);
        return arg_double;
    }

    bool is_either_value_or_type(onerut_parser::CompileResult first_arg_compile_result, onerut_parser::CompileResult second_arg_compile_result) {
        return first_arg_compile_result.is_either_value_or_type() &&
                second_arg_compile_result.is_either_value_or_type();
    }

    bool is_either_value_or_type(onerut_parser::CompileResult first_arg_compile_result, std::vector<onerut_parser::CompileResult> other_argv_compile_result) {
        return first_arg_compile_result.is_either_value_or_type() &&
                std::all_of(other_argv_compile_result.cbegin(), other_argv_compile_result.cend(),
                [](const onerut_parser::CompileResult & compile_result) {
                    return compile_result.is_either_value_or_type();
                });
    }

    bool is_either_value_or_type(std::vector<onerut_parser::CompileResult> argv_compile_result) {
        return std::all_of(argv_compile_result.cbegin(), argv_compile_result.cend(),
                [](const onerut_parser::CompileResult & compile_result) {
                    return compile_result.is_either_value_or_type();
                });
    }

    //    bool is_compile_error(onerut_parser::CompileResult first_arg_compile_result, onerut_parser::CompileResult second_arg_compile_result) {
    //        return first_arg_compile_result.is_compile_error() ||
    //                second_arg_compile_result.is_compile_error();
    //    }

    //    bool is_compile_error(onerut_parser::CompileResult first_arg_compile_result, std::vector<onerut_parser::CompileResult> other_argv_compile_result) {
    //        return first_arg_compile_result.is_compile_error() ||
    //                std::any_of(other_argv_compile_result.cbegin(), other_argv_compile_result.cend(),
    //                [](const onerut_parser::CompileResult & compile_result) {
    //                    return compile_result.is_compile_error();
    //                });
    //    }

    //    bool is_compile_error(std::vector<onerut_parser::CompileResult> argv_compile_result) {
    //        return std::any_of(argv_compile_result.cbegin(), argv_compile_result.cend(),
    //                [](const onerut_parser::CompileResult & compile_result) {
    //                    return compile_result.is_compile_error();
    //                });
    //    }

    std::vector<std::shared_ptr < onerut_parser::onerut_ast::compile_result::CompileResultNode>>
    many_compile(const std::vector<std::shared_ptr<onerut_parser::onerut_ast::source::SourceNode>> argv) {
        std::vector<std::shared_ptr < onerut_parser::onerut_ast::compile_result::CompileResultNode>> argv_node;
        argv_node.reserve(argv.size());
        std::transform(cbegin(argv), cend(argv), back_inserter(argv_node),
                [](const std::shared_ptr<onerut_parser::onerut_ast::source::SourceNode> & arg) {
                    return arg->compile();
                });
        return argv_node;
    }

    std::vector<onerut_parser::CompileResult>
    many_extract_compile_result(std::vector<std::shared_ptr < onerut_parser::onerut_ast::compile_result::CompileResultNode>> argv_node) {
        std::vector<onerut_parser::CompileResult> argv_compile_result;
        argv_compile_result.reserve(argv_node.size());
        std::transform(cbegin(argv_node), cend(argv_node), back_inserter(argv_compile_result),
                [](const std::shared_ptr < onerut_parser::onerut_ast::compile_result::CompileResultNode> &arg) {
                    return arg->compile_result;
                });
        return argv_compile_result;
    }

}

namespace onerut_parser::onerut_ast::source {

    // *************************************************************************
    // ***********************    Abstract baseclasses   ***********************
    // *************************************************************************

    std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode>
    WithNoSubsourcesNode::compile() const {
        const auto compile_result = basic_compile();

        return std::make_shared<onerut_parser::onerut_ast::compile_result::CompileResultNode>(
                shared_from(this), compile_result);
    }

    std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode>
    WithOneSubsourceNode::compile() const {
        std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> arg_node = arg->compile();
        const auto arg_compile_result = arg_node->compile_result;
        const auto compile_result = basic_compile(arg_compile_result);

        return std::make_shared<onerut_parser::onerut_ast::compile_result::CompileResultNode>(
                shared_from(this), arg_node, compile_result);
    }

    std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode>
    WithTwoSubsourcesNode::compile() const {
        std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> first_arg_node = first_arg->compile();
        std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> second_arg_node = second_arg->compile();
        const auto first_arg_compile_result = first_arg_node->compile_result;
        const auto second_arg_compile_result = second_arg_node->compile_result;
        const auto compile_result = basic_compile(first_arg_compile_result, second_arg_compile_result);

        return std::make_shared<onerut_parser::onerut_ast::compile_result::CompileResultNode>(
                shared_from(this), first_arg_node, second_arg_node, compile_result);
    }

    std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode>
    WithOneOrMoreSubsourcesNode::compile() const {
        const auto first_arg_node = first_arg->compile();
        const auto other_argv_node = many_compile(other_argv);
        const auto first_arg_compile_result = first_arg_node->compile_result;
        const auto other_argv_compile_result = many_extract_compile_result(other_argv_node);
        const auto compile_result = basic_compile(first_arg_compile_result, other_argv_compile_result);
        return std::make_shared<onerut_parser::onerut_ast::compile_result::CompileResultNode>(
                shared_from(this), first_arg_node, other_argv_node, compile_result);
    }

    std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode>
    WithAnyNumberOfSubsourcesNode::compile() const {
        const auto argv_node = many_compile(argv);
        const auto argv_compile_result = many_extract_compile_result(argv_node);
        const auto compile_result = basic_compile(argv_compile_result);
        return std::make_shared<onerut_parser::onerut_ast::compile_result::CompileResultNode>(
                shared_from(this), argv_node, compile_result);
    }

    // *************************************************************************
    // ***********************      Concrete classes     ***********************
    // *************************************************************************

    CompileResult
    IdentifierNode::basic_compile() const {
        if (auto builder = GlobalIdentifiers::instance().get_or_empty(name)) {
            return (*builder)->get_compile_result();
        }
        return CompileResult::from_compile_error(std::make_shared<IdentifierNotFoundError>(name));
    }

    // -------------------------------------------------------------------------

    CompileResult
    OpAssignNode::basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const {
        //        const TwoSubsourcesCompileResult arg_results = compile_args();
        //        if (!arg_results.is_either_value_or_type())
        //            const CompileResult compile_result = CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        //
        //        const CompileResult compile_result = CompileResult::from_compile_error(std::make_shared<CompilerNotImplementedError>());

    }

    // -------------------------------------------------------------------------

    CompileResult
    OpPlusMinusNode::basic_compile(CompileResult first_arg_compile_result, std::vector<CompileResult> other_argv_compile_result) const {
        assert(std::all_of(opv.cbegin(), opv.cend(), is_plus_munis_char));
        if (!is_either_value_or_type(first_arg_compile_result, other_argv_compile_result))
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (is_integer(first_arg_compile_result) && std::all_of(other_argv_compile_result.cbegin(), other_argv_compile_result.cend(), is_integer)) {
            std::shared_ptr<onerut_scalar::Long> first_arg_long;
            std::vector<std::shared_ptr < onerut_scalar::Long >> other_argv_long;
            other_argv_long.reserve(other_argv.size());
            first_arg_long = to_long(first_arg_compile_result);
            std::transform(other_argv_compile_result.cbegin(), other_argv_compile_result.cend(), std::back_inserter(other_argv_long), to_long);
            return CompileResult::from_value<onerut_scalar::Long>(std::make_shared<onerut_scalar::OpPlusMinusLong>(first_arg_long, other_argv_long, opv));
        }
        if (is_real(first_arg_compile_result) && std::all_of(other_argv_compile_result.cbegin(), other_argv_compile_result.cend(), is_real)) {
            std::shared_ptr<onerut_scalar::Double> first_arg_double;
            std::vector<std::shared_ptr < onerut_scalar::Double >> other_argv_double;
            other_argv_double.reserve(other_argv.size());
            first_arg_double = to_double(first_arg_compile_result);
            std::transform(other_argv_compile_result.cbegin(), other_argv_compile_result.cend(), std::back_inserter(other_argv_double), to_double);

            return CompileResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::OpPlusMinusDouble>(first_arg_double, other_argv_double, opv));
        }
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    CompileResult
    OpProdDivNode::basic_compile(CompileResult first_arg_compile_result, std::vector<CompileResult> other_argv_compile_result) const {
        assert(std::all_of(opv.cbegin(), opv.cend(), is_prod_div_char));
        if (!is_either_value_or_type(first_arg_compile_result, other_argv_compile_result))
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (is_integer(first_arg_compile_result) && std::all_of(other_argv_compile_result.cbegin(), other_argv_compile_result.cend(), is_integer)) {
            std::shared_ptr<onerut_scalar::Long> first_arg_long;
            std::vector<std::shared_ptr < onerut_scalar::Long >> other_argv_long;
            other_argv_long.reserve(other_argv.size());
            first_arg_long = to_long(first_arg_compile_result);
            std::transform(other_argv_compile_result.cbegin(), other_argv_compile_result.cend(), std::back_inserter(other_argv_long), to_long);
            return CompileResult::from_value<onerut_scalar::Long>(std::make_shared<onerut_scalar::OpProdDivLong>(first_arg_long, other_argv_long, opv));
        }
        if (is_real(first_arg_compile_result) && std::all_of(other_argv_compile_result.cbegin(), other_argv_compile_result.cend(), is_real)) {
            std::shared_ptr<onerut_scalar::Double> first_arg_double;
            std::vector<std::shared_ptr < onerut_scalar::Double >> other_argv_double;
            other_argv_double.reserve(other_argv.size());
            first_arg_double = to_double(first_arg_compile_result);
            std::transform(other_argv_compile_result.cbegin(), other_argv_compile_result.cend(), std::back_inserter(other_argv_double), to_double);

            return CompileResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::OpProdDivDouble>(first_arg_double, other_argv_double, opv));
        }
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    CompileResult
    OpPowNode::basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const {
        if (!is_either_value_or_type(first_arg_compile_result, second_arg_compile_result))
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());

        return CompileResult::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    // -------------------------------------------------------------------------

    CompileResult
    OpAtNode::basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const {
        if (!is_either_value_or_type(first_arg_compile_result, second_arg_compile_result))
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());

        return CompileResult::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    // -------------------------------------------------------------------------

    CompileResult
    OpArrowNode::basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const {
        if (!is_either_value_or_type(first_arg_compile_result, second_arg_compile_result))
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());

        return CompileResult::from_compile_error(std::make_shared<CompilerNotImplementedError>());

    }

    // -------------------------------------------------------------------------

    CompileResult
    OpGlueNode::basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const {
        if (!is_either_value_or_type(first_arg_compile_result, second_arg_compile_result))
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());

        return CompileResult::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    // -------------------------------------------------------------------------

    CompileResult
    UnaryPlusMinusNode::basic_compile(CompileResult arg_compile_result) const {
        assert(is_plus_munis_char(op));
        assert(!arg_compile_result.is_empty());
        if (!arg_compile_result.is_either_value_or_type())
            const CompileResult compile_result = CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (is_integer(arg_compile_result)) {
            const std::shared_ptr<onerut_scalar::Long> arg_long = to_long(arg_compile_result);
            return CompileResult::from_value<onerut_scalar::Long>(std::make_shared<onerut_scalar::OpUnaryPlusMinusLong>(arg_long, op));
        }
        if (is_real(arg_compile_result)) {
            const std::shared_ptr<onerut_scalar::Double> arg_double = to_double(arg_compile_result);

            return CompileResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::OpUnaryPlusMinusDouble>(arg_double, op));
        }
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    CompileResult
    LitLongNode::basic_compile() const {

        return CompileResult::from_value<onerut_scalar::Long>(std::make_shared<onerut_scalar::LitLong>(value));
    }

    // -------------------------------------------------------------------------

    CompileResult
    LitDoubleNode::basic_compile() const {

        return CompileResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::LitDouble>(value));
    }

    // -------------------------------------------------------------------------

    CompileResult
    FunctionNode::basic_compile(std::vector<CompileResult> argv_compile_result) const {
        if (!is_either_value_or_type(argv_compile_result))
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        return CompileResult::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

}
