#include<algorithm>
#include<iterator>

#include<onerut_parser/ast_dyn.hpp>
#include<onerut_parser/identifier_global.hpp>
#include<onerut_parser/function_global.hpp>
#include<onerut_scalar/scalar.hpp>
#include<onerut_parser/ast_compile_result.hpp>

#include<iostream> //debug! TODO



// https://stackoverflow.com/questions/657155/how-to-enable-shared-from-this-of-both-parent-and-derived:

template <typename Base>
inline std::shared_ptr<Base>
shared_from_base(std::enable_shared_from_this<Base>* base) {
    return base->shared_from_this();
}

template <typename Base>
inline std::shared_ptr<const Base>
shared_from_base(std::enable_shared_from_this<Base> const* base) {
    return base->shared_from_this();
}

template <typename That>
inline std::shared_ptr<That>
shared_from(That* that) {
    return std::static_pointer_cast<That>(shared_from_base(that));
}



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

    bool is_compile_error(onerut_parser::CompileResult first_arg_compile_result, onerut_parser::CompileResult second_arg_compile_result) {
        return first_arg_compile_result.is_compile_error() ||
                second_arg_compile_result.is_compile_error();
    }

    bool is_either_value_or_type(onerut_parser::CompileResult first_arg_compile_result, onerut_parser::CompileResult second_arg_compile_result) {
        return first_arg_compile_result.is_either_value_or_type() &&
                second_arg_compile_result.is_either_value_or_type();
    }

    bool is_compile_error(onerut_parser::CompileResult first_arg_compile_result, std::vector<onerut_parser::CompileResult> other_argv_compile_result) {
        return first_arg_compile_result.is_compile_error() ||
                std::any_of(other_argv_compile_result.cbegin(), other_argv_compile_result.cend(),
                [](const onerut_parser::CompileResult & compile_result) {
                    return compile_result.is_compile_error();
                });
    }

    bool is_either_value_or_type(onerut_parser::CompileResult first_arg_compile_result, std::vector<onerut_parser::CompileResult> other_argv_compile_result) {
        return first_arg_compile_result.is_either_value_or_type() &&
                std::all_of(other_argv_compile_result.cbegin(), other_argv_compile_result.cend(),
                [](const onerut_parser::CompileResult & compile_result) {
                    return compile_result.is_either_value_or_type();
                });
    }

    bool is_compile_error(std::vector<onerut_parser::CompileResult> argv_compile_result) {
        return std::any_of(argv_compile_result.cbegin(), argv_compile_result.cend(),
                [](const onerut_parser::CompileResult & compile_result) {
                    return compile_result.is_compile_error();
                });
    }

    bool is_either_value_or_type(std::vector<onerut_parser::CompileResult> argv_compile_result) {
        return std::all_of(argv_compile_result.cbegin(), argv_compile_result.cend(),
                [](const onerut_parser::CompileResult & compile_result) {
                    return compile_result.is_either_value_or_type();
                });
    }

}

namespace onerut_parser::onerut_ast::dyn {

    // *************************************************************************
    // ***********************    Abstract baseclasses   ***********************
    // *************************************************************************

    std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode>
    WithNoSubexpressionsNode::compile() const {
        const CompileResult compile_result = basic_compile();
        return std::make_shared<onerut_parser::onerut_ast::compile_result::CompileResultNode>(
                shared_from(this), compile_result);
    }

    std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode>
    WithOneSubexpressionNode::compile() const {
        std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> arg_node = expression->compile();
        const CompileResult arg_compile_result = arg_node->compile_result;
        const CompileResult compile_result = basic_compile(arg_compile_result);
        return std::make_shared<onerut_parser::onerut_ast::compile_result::CompileResultNode>(
                shared_from(this), arg_node, compile_result);
    }

    std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode>
    WithTwoSubexpressionsNode::compile() const {
        std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> first_arg_node = first_arg->compile();
        std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> second_arg_node = second_arg->compile();
        const CompileResult first_arg_compile_result = first_arg_node->compile_result;
        const CompileResult second_arg_compile_result = second_arg_node->compile_result;
        const CompileResult compile_result = basic_compile(first_arg_compile_result, second_arg_compile_result);
        return std::make_shared<onerut_parser::onerut_ast::compile_result::CompileResultNode>(
                shared_from(this), first_arg_node, second_arg_node, compile_result);
    }

    std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode>
    WithOneOrMoreSubexpressionsNode::compile() const {
        std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> first_arg_node = first_arg->compile();
        std::vector<std::shared_ptr < onerut_parser::onerut_ast::compile_result::CompileResultNode>> other_argv_node;
        other_argv_node.resize(other_argv.size());
        std::transform(other_argv.cbegin(), other_argv.cend(), other_argv_node.begin(),
                [](const std::shared_ptr<ExpressionNode> & arg) {
                    return arg->compile();
                }); // TODO zrobic back inserter!!!!!! Zrobic osobna funkcje!!
        const CompileResult first_arg_compile_result = first_arg_node->compile_result;
        std::vector<CompileResult> other_argv_compile_result;
        other_argv_compile_result.resize(other_argv.size());
        std::transform(other_argv_node.cbegin(), other_argv_node.cend(), other_argv_compile_result.begin(),
                [](const std::shared_ptr < onerut_parser::onerut_ast::compile_result::CompileResultNode> &arg) {
                    return arg->compile_result;
                }); // TODO zrobic back inserter!!!!!! Zrobic osobna funkcje!!
        const CompileResult compile_result = basic_compile(first_arg_compile_result, other_argv_compile_result);
        return std::make_shared<onerut_parser::onerut_ast::compile_result::CompileResultNode>(
                shared_from(this), first_arg_node, other_argv_node, compile_result);
    }

    std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode>
    WithAnyNumberOfSubexpressionsNode::compile() const {
        std::vector<std::shared_ptr < onerut_parser::onerut_ast::compile_result::CompileResultNode>> argv_node;
        argv_node.resize(argv.size());
        std::transform(argv.cbegin(), argv.cend(), argv_node.begin(),
                [](const std::shared_ptr<ExpressionNode> & arg) {
                    return arg->compile();
                }); // TODO zrobic back inserter!!!!!! Zrobic osobna funkcje!!
        std::vector<CompileResult> argv_compile_result;
        argv_compile_result.resize(argv.size());
        std::transform(argv_node.cbegin(), argv_node.cend(), argv_compile_result.begin(),
                [](const std::shared_ptr < onerut_parser::onerut_ast::compile_result::CompileResultNode> &arg) {
                    return arg->compile_result;
                }); // TODO zrobic back inserter!!!!!! Zrobic osobna funkcje!!
        const CompileResult compile_result = basic_compile(argv_compile_result);
        return std::make_shared<onerut_parser::onerut_ast::compile_result::CompileResultNode>(
                shared_from(this), argv_node, compile_result);
    }

    // *************************************************************************
    // ***********************      Concrete classes     ***********************
    // *************************************************************************

    CompileResult
    IdentifierNode::basic_compile() const {
        if (auto builder = GlobalIdentifiers::instance().get_or_empty(name)) {
            return (*builder)->build();
        }
        return CompileResult::from_compile_error(std::make_shared<IdentifierNotFoundError>(name));
    }

    // -------------------------------------------------------------------------

    CompileResult
    OpAssignNode::basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const {
        //        const TwoSubexpressionsCompileResult arg_results = compile_args();
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
