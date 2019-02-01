#include<algorithm>
#include<iterator>

#include<onerut_parser/ast_dyn.hpp>
#include<onerut_parser/identifier_global.hpp>
#include<onerut_parser/function_global.hpp>
#include<onerut_scalar/scalar.hpp>

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

}

namespace onerut_parser::onerut_ast::dyn {

    // *************************************************************************
    // ***********************    Abstract baseclasses   ***********************
    // *************************************************************************

    bool TwoSubexpressionsCompileResult::is_compile_error() const {
        return first_arg.is_compile_error() || second_arg.is_compile_error();
    }

    bool TwoSubexpressionsCompileResult::is_either_value_or_type() const {
        return first_arg.is_either_value_or_type() && second_arg.is_either_value_or_type();
    }

    TwoSubexpressionsCompileResult
    WithTwoSubexpressionsNode::compile_args() const {
        TwoSubexpressionsCompileResult result;
        result.first_arg = first_arg->compile();
        result.second_arg = second_arg->compile();
        return result;
    }

    bool OneOrMoreSubexpressionsCompileResult::is_compile_error() const {
        return first_arg.is_compile_error() || std::any_of(other_argv.cbegin(), other_argv.cend(), [](const CompileResult & r) {
            return r.is_compile_error();
        });
    }

    bool OneOrMoreSubexpressionsCompileResult::is_either_value_or_type() const {
        return first_arg.is_either_value_or_type() && std::all_of(other_argv.cbegin(), other_argv.cend(), [](const CompileResult & r) {
            return r.is_either_value_or_type();
        });
    }

    OneOrMoreSubexpressionsCompileResult
    WithOneOrMoreSubexpressionsNode::compile_args() const {
        OneOrMoreSubexpressionsCompileResult result;
        result.first_arg = first_arg->compile();
        result.other_argv.resize(other_argv.size());
        std::transform(other_argv.cbegin(), other_argv.cend(), result.other_argv.begin(),
                [](const std::shared_ptr<ExpressionNode> & arg) {
                    return arg->compile();
                });
        return result;
    }

    bool AnyNumberOfSubexpressionsCompileResult::is_compile_error() const {
        return std::any_of(argv.cbegin(), argv.cend(), [](const CompileResult & r) {
            return r.is_compile_error();
        });
    }

    bool AnyNumberOfSubexpressionsCompileResult::is_either_value_or_type() const {
        return std::all_of(argv.cbegin(), argv.cend(), [](const CompileResult & r) {
            return r.is_either_value_or_type();
        });
    }

    AnyNumberOfSubexpressionsCompileResult
    WithAnyNumberOfSubexpressionsNode::compile_args() const {
        AnyNumberOfSubexpressionsCompileResult result;
        result.argv.resize(argv.size());
        std::transform(argv.cbegin(), argv.cend(), result.argv.begin(),
                [](const std::shared_ptr<ExpressionNode> & arg) {
                    return arg->compile();
                });
        return result;
    }

    // *************************************************************************
    // ***********************      Concrete classes     ***********************
    // *************************************************************************

    CompileResult IdentifierNode::compile() const {
        if (auto builder = GlobalIdentifiers::instance().get_or_empty(name)) {
            return (*builder)->build();
         }
        return CompileResult::from_compile_error(std::make_shared<IdentifierNotFoundError>(name));
    }

    // -------------------------------------------------------------------------

    CompileResult OpAssignNode::compile() const {
        const TwoSubexpressionsCompileResult arg_results = compile_args();
        if (!arg_results.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());

        return CompileResult::from_compile_error(std::make_shared<CompilerNotImplementedError>());

    }

    // -------------------------------------------------------------------------

    CompileResult OpPlusMinusNode::compile() const {
        assert(std::all_of(opv.cbegin(), opv.cend(), is_plus_munis_char));
        const OneOrMoreSubexpressionsCompileResult arg_results = compile_args();
        if (!arg_results.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (is_integer(arg_results.first_arg) && std::all_of(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), is_integer)) {
            std::shared_ptr<onerut_scalar::Long> first_arg_long;
            std::vector<std::shared_ptr < onerut_scalar::Long >> other_argv_long;
            other_argv_long.reserve(other_argv.size());
            first_arg_long = to_long(arg_results.first_arg);
            std::transform(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), std::back_inserter(other_argv_long), to_long);
            return CompileResult::from_value<onerut_scalar::Long>(std::make_shared<onerut_scalar::OpPlusMinusLong>(first_arg_long, other_argv_long, opv));
        }
        if (is_real(arg_results.first_arg) && std::all_of(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), is_real)) {
            std::shared_ptr<onerut_scalar::Double> first_arg_double;
            std::vector<std::shared_ptr < onerut_scalar::Double >> other_argv_double;
            other_argv_double.reserve(other_argv.size());
            first_arg_double = to_double(arg_results.first_arg);
            std::transform(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), std::back_inserter(other_argv_double), to_double);

            return CompileResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::OpPlusMinusDouble>(first_arg_double, other_argv_double, opv));
        }

        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    CompileResult OpProdDivNode::compile() const {
        assert(std::all_of(opv.cbegin(), opv.cend(), is_prod_div_char));
        const OneOrMoreSubexpressionsCompileResult arg_results = compile_args();
        if (!arg_results.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (is_integer(arg_results.first_arg) && std::all_of(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), is_integer)) {
            std::shared_ptr<onerut_scalar::Long> first_arg_long;
            std::vector<std::shared_ptr < onerut_scalar::Long >> other_argv_long;
            other_argv_long.reserve(other_argv.size());
            first_arg_long = to_long(arg_results.first_arg);
            std::transform(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), std::back_inserter(other_argv_long), to_long);
            return CompileResult::from_value<onerut_scalar::Long>(std::make_shared<onerut_scalar::OpProdDivLong>(first_arg_long, other_argv_long, opv));
        }
        if (is_real(arg_results.first_arg) && std::all_of(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), is_real)) {
            std::shared_ptr<onerut_scalar::Double> first_arg_double;
            std::vector<std::shared_ptr < onerut_scalar::Double >> other_argv_double;
            other_argv_double.reserve(other_argv.size());
            first_arg_double = to_double(arg_results.first_arg);
            std::transform(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), std::back_inserter(other_argv_double), to_double);

            return CompileResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::OpProdDivDouble>(first_arg_double, other_argv_double, opv));
        }
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    CompileResult OpPowNode::compile() const {
        const TwoSubexpressionsCompileResult arg_results = compile_args();
        if (!arg_results.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());

        return CompileResult::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    // -------------------------------------------------------------------------

    CompileResult OpAtNode::compile() const {
        const TwoSubexpressionsCompileResult arg_results = compile_args();
        if (!arg_results.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());

        return CompileResult::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    // -------------------------------------------------------------------------

    CompileResult OpArrowNode::compile() const {
        const TwoSubexpressionsCompileResult arg_results = compile_args();
        if (!arg_results.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());

        return CompileResult::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    // -------------------------------------------------------------------------

    CompileResult OpGlueNode::compile() const {
        const TwoSubexpressionsCompileResult arg_results = compile_args();
        if (!arg_results.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());

        return CompileResult::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    // -------------------------------------------------------------------------

    CompileResult UnaryPlusMinusNode::compile() const {
        assert(is_plus_munis_char(op));
        const CompileResult arg_result = expression->compile();
        assert(!arg_result.is_empty());
        if (!arg_result.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (is_integer(arg_result)) {
            const std::shared_ptr<onerut_scalar::Long> arg_long = to_long(arg_result);
            return CompileResult::from_value<onerut_scalar::Long>(std::make_shared<onerut_scalar::OpUnaryPlusMinusLong>(arg_long, op));
        }
        if (is_real(arg_result)) {
            const std::shared_ptr<onerut_scalar::Double> arg_double = to_double(arg_result);

            return CompileResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::OpUnaryPlusMinusDouble>(arg_double, op));
        }
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    CompileResult LitLongNode::compile() const {

        return CompileResult::from_value<onerut_scalar::Long>(std::make_shared<onerut_scalar::LitLong>(value));
    }

    // -------------------------------------------------------------------------

    CompileResult LitDoubleNode::compile() const {

        return CompileResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::LitDouble>(value));
    }

    // -------------------------------------------------------------------------

    CompileResult FunctionNode::compile() const {
        const AnyNumberOfSubexpressionsCompileResult arg_results = compile_args();
        if (!arg_results.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        return CompileResult::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

}
