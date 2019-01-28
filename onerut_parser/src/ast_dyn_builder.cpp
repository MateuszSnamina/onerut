#include<algorithm>

#include<onerut_parser/ast_dyn.hpp>
#include<onerut_scalar/scalar.hpp>

namespace {

    bool is_plus_munis_char(char32_t op) {
        return op == L'+' || op == L'-';
    }

    bool is_prod_div_char(char32_t op) {
        return op == L'*' || op == L'/';
    }

    bool is_integer(const onerut_parser::BuildResult& result) {
        assert(!result.is_empty());
        assert(!result.is_error());
        return result.is_given_type<onerut_scalar::Int>();
    }

    bool is_real(const onerut_parser::BuildResult& result) {
        assert(!result.is_empty());
        assert(!result.is_error());
        return result.is_given_type<onerut_scalar::Int>() || result.is_given_type<onerut_scalar::Double>();
    }

    std::shared_ptr<onerut_scalar::Int> to_int(const onerut_parser::BuildResult& arg_result) {
        assert(is_integer(arg_result));
        std::shared_ptr<onerut_scalar::Int> arg_int;
        arg_int = *arg_result.typed_value_or_empty<onerut_scalar::Int>();
        assert(arg_int);
        return arg_int;
    }

    std::shared_ptr<onerut_scalar::Double> to_real(const onerut_parser::BuildResult& arg_result) {
        assert(is_real(arg_result));
        std::shared_ptr<onerut_scalar::Double> arg_double;
        if (auto temp = arg_result.typed_value_or_empty<onerut_scalar::Int>()) {
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

    bool TwoSubexpressionsBuildResult::is_error() const {
        return first_arg.is_error() || second_arg.is_error();
    }

    TwoSubexpressionsBuildResult
    WithTwoSubexpressionsNode::build_args() const {
        TwoSubexpressionsBuildResult result;
        result.first_arg = first_arg->build();
        result.second_arg = second_arg->build();
        return result;
    }

    TwoSubexpressionsBuildResult
    WithTwoSubexpressionsNode::build_args_dry_run() const {
        TwoSubexpressionsBuildResult result;
        result.first_arg = first_arg->build_dry_run();
        result.second_arg = second_arg->build_dry_run();
        return result;
    }

    bool OneOrMoreSubexpressionsBuildResult::is_error() const {
        return first_arg.is_error() || std::any_of(other_argv.cbegin(), other_argv.cend(), [](const BuildResult & r) {
            return r.is_error();
        });
    }

    OneOrMoreSubexpressionsBuildResult
    WithOneOrMoreSubexpressionsNode::build_args() const {
        OneOrMoreSubexpressionsBuildResult result;
        result.first_arg = first_arg->build();
        result.other_argv.resize(other_argv.size());
        std::transform(other_argv.cbegin(), other_argv.cend(), result.other_argv.begin(),
                [](const std::shared_ptr<ExpressionNode> & arg) {
                    return arg->build();
                });
        return result;
    }

    OneOrMoreSubexpressionsBuildResult
    WithOneOrMoreSubexpressionsNode::build_args_dry_run() const {
        OneOrMoreSubexpressionsBuildResult result;
        result.first_arg = first_arg->build_dry_run();
        result.other_argv.resize(other_argv.size());
        std::transform(other_argv.cbegin(), other_argv.cend(), result.other_argv.begin(),
                [](const std::shared_ptr<ExpressionNode> & arg) {
                    return arg->build_dry_run();
                });
        return result;
    }

    bool AnyNumberOfSubexpressionsBuildResult::is_error() const {
        return std::any_of(argv.cbegin(), argv.cend(), [](const BuildResult & r) {
            return r.is_error();
        });
    }

    AnyNumberOfSubexpressionsBuildResult
    WithAnyNumberOfSubexpressionsNode::build_args() const {
        AnyNumberOfSubexpressionsBuildResult result;
        result.argv.resize(argv.size());
        std::transform(argv.cbegin(), argv.cend(), result.argv.begin(),
                [](const std::shared_ptr<ExpressionNode> & arg) {
                    return arg->build();
                });
        return result;
    }

    AnyNumberOfSubexpressionsBuildResult
    WithAnyNumberOfSubexpressionsNode::build_args_dry_run() const {
        AnyNumberOfSubexpressionsBuildResult result;
        result.argv.resize(argv.size());
        std::transform(argv.cbegin(), argv.cend(), result.argv.begin(),
                [](const std::shared_ptr<ExpressionNode> & arg) {
                    return arg->build_dry_run();
                });
        return result;
    }

    // *************************************************************************
    // ***********************      Concrete classes     ***********************
    // *************************************************************************

    BuildResult IdentifierNode::build_dry_run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult IdentifierNode::build() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult OpPlusMinusNode::build_dry_run() const {
        assert(std::all_of(opv.cbegin(), opv.cend(), is_plus_munis_char));
        const OneOrMoreSubexpressionsBuildResult arg_results = build_args_dry_run();
        if (arg_results.is_error())
            return BuildResult::from_build_error(std::make_shared<BuildArgumentsError>());
        if (is_integer(arg_results.first_arg) && std::all_of(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), is_integer))
            return BuildResult::from_type<onerut_scalar::Int>();
        if (is_real(arg_results.first_arg) && std::all_of(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), is_real))
            return BuildResult::from_type<onerut_scalar::Double>();
        return BuildResult::from_build_error(std::make_shared<ArgumentMismatchError>());
    }

    BuildResult OpPlusMinusNode::build() const {
        assert(std::all_of(opv.cbegin(), opv.cend(), is_plus_munis_char));
        const OneOrMoreSubexpressionsBuildResult arg_results = build_args();
        if (arg_results.is_error())
            return BuildResult::from_build_error(std::make_shared<BuildArgumentsError>());
        if (is_integer(arg_results.first_arg) && std::all_of(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), is_integer)) {
            std::shared_ptr<onerut_scalar::Int> first_arg_int;
            std::vector<std::shared_ptr < onerut_scalar::Int >> other_argv_int(other_argv.size());
            first_arg_int = to_int(arg_results.first_arg);
            std::transform(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), other_argv_int.begin(), to_int);
            return BuildResult::from_value<onerut_scalar::Int>(std::make_shared<onerut_scalar::OpPlusMinusInt>(first_arg_int, other_argv_int, opv));
        }
        if (is_real(arg_results.first_arg) && std::all_of(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), is_real)) {
            std::shared_ptr<onerut_scalar::Double> first_arg_double;
            std::vector<std::shared_ptr < onerut_scalar::Double >> other_argv_double(other_argv.size());
            first_arg_double = to_real(arg_results.first_arg);
            std::transform(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), other_argv_double.begin(), to_real);
            return BuildResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::OpPlusMinusDouble>(first_arg_double, other_argv_double, opv));
        }

        return BuildResult::from_build_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    BuildResult OpProdDivNode::build_dry_run() const {
        assert(std::all_of(opv.cbegin(), opv.cend(), is_prod_div_char));
        const OneOrMoreSubexpressionsBuildResult arg_results = build_args_dry_run();
        if (arg_results.is_error())
            return BuildResult::from_build_error(std::make_shared<BuildArgumentsError>());
        if (is_integer(arg_results.first_arg) && std::all_of(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), is_integer))
            return BuildResult::from_type<onerut_scalar::Int>();
        if (is_real(arg_results.first_arg) && std::all_of(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), is_real))
            return BuildResult::from_type<onerut_scalar::Double>();
        return BuildResult::from_build_error(std::make_shared<ArgumentMismatchError>());
    }

    BuildResult OpProdDivNode::build() const {
        assert(std::all_of(opv.cbegin(), opv.cend(), is_prod_div_char));
        const OneOrMoreSubexpressionsBuildResult arg_results = build_args();
        if (arg_results.is_error())
            return BuildResult::from_build_error(std::make_shared<BuildArgumentsError>());
        if (is_integer(arg_results.first_arg) && std::all_of(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), is_integer)) {
            std::shared_ptr<onerut_scalar::Int> first_arg_int;
            std::vector<std::shared_ptr < onerut_scalar::Int >> other_argv_int(other_argv.size());
            first_arg_int = to_int(arg_results.first_arg);
            std::transform(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), other_argv_int.begin(), to_int);
            return BuildResult::from_value<onerut_scalar::Int>(std::make_shared<onerut_scalar::OpProdDivInt>(first_arg_int, other_argv_int, opv));
        }
        if (is_real(arg_results.first_arg) && std::all_of(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), is_real)) {
            std::shared_ptr<onerut_scalar::Double> first_arg_double;
            std::vector<std::shared_ptr < onerut_scalar::Double >> other_argv_double(other_argv.size());
            first_arg_double = to_real(arg_results.first_arg);
            std::transform(arg_results.other_argv.cbegin(), arg_results.other_argv.cend(), other_argv_double.begin(), to_real);
            return BuildResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::OpProdDivDouble>(first_arg_double, other_argv_double, opv));
        }
        return BuildResult::from_build_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    BuildResult OpPowNode::build_dry_run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult OpPowNode::build() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult OpAtNode::build_dry_run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult OpAtNode::build() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult OpArrowNode::build_dry_run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult OpArrowNode::build() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult OpGlueNode::build_dry_run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult OpGlueNode::build() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult UnaryPlusMinusNode::build_dry_run() const {
        assert(is_plus_munis_char(op));
        const BuildResult arg_result = expression->build_dry_run();
        assert(!arg_result.is_empty());
        if (arg_result.is_error())
            return BuildResult::from_build_error(std::make_shared<BuildArgumentsError>());
        if (is_integer(arg_result))
            return BuildResult::from_type<onerut_scalar::Int>();
        if (is_real(arg_result))
            return BuildResult::from_type<onerut_scalar::Double>();
        return BuildResult::from_build_error(std::make_shared<ArgumentMismatchError>());
    }

    BuildResult UnaryPlusMinusNode::build() const {
        assert(is_plus_munis_char(op));
        const BuildResult arg_result = expression->build();
        assert(!arg_result.is_empty());
        if (arg_result.is_error())
            return BuildResult::from_build_error(std::make_shared<BuildArgumentsError>());
        if (is_integer(arg_result)) {
            const std::shared_ptr<onerut_scalar::Int> arg_int = to_int(arg_result);
            return BuildResult::from_value<onerut_scalar::Int>(std::make_shared<onerut_scalar::OpUnaryPlusMinusInt>(arg_int, op));
        }
        if (is_real(arg_result)) {
            const std::shared_ptr<onerut_scalar::Double> arg_double = to_real(arg_result);
            return BuildResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::OpUnaryPlusMinusDouble>(arg_double, op));
        }
        return BuildResult::from_build_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    BuildResult LitIntNode::build_dry_run() const {
        return BuildResult::from_type<onerut_scalar::Int>();
    }

    BuildResult LitIntNode::build() const {
        return BuildResult::from_value<onerut_scalar::Int>(std::make_shared<onerut_scalar::LitInt>(value));
    }

    // -------------------------------------------------------------------------

    BuildResult LitDoubleNode::build_dry_run() const {
        return BuildResult::from_type<onerut_scalar::Double>();
    }

    BuildResult LitDoubleNode::build() const {
        return BuildResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::LitDouble>(value));
    }

    // -------------------------------------------------------------------------

    BuildResult FunctionNode::build_dry_run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult FunctionNode::build() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

}
