#include<algorithm>

#include<onerut_parser/ast_dyn.hpp>
#include<onerut_scalar/scalar.hpp>

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
    WithTwoSubexpressionsNode::build_dry_run_args() const {
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
                [](const std::shared_ptr<ExpressionNode> & e) {
                    return e->build();
                });
        return result;
    }

    OneOrMoreSubexpressionsBuildResult
    WithOneOrMoreSubexpressionsNode::build_dry_run_args() const {
        OneOrMoreSubexpressionsBuildResult result;
        result.first_arg = first_arg->build_dry_run();
        result.other_argv.resize(other_argv.size());
        std::transform(other_argv.cbegin(), other_argv.cend(), result.other_argv.begin(),
                [](const std::shared_ptr<ExpressionNode> & e) {
                    return e->build_dry_run();
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
                [](const std::shared_ptr<ExpressionNode> & e) {
                    return e->build();
                });
        return result;
    }

    AnyNumberOfSubexpressionsBuildResult
    WithAnyNumberOfSubexpressionsNode::build_dry_run_args() const {
        AnyNumberOfSubexpressionsBuildResult result;
        result.argv.resize(argv.size());
        std::transform(argv.cbegin(), argv.cend(), result.argv.begin(),
                [](const std::shared_ptr<ExpressionNode> & e) {
                    return e->build_dry_run();
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
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult OpPlusMinusNode::build() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult OpProdDivNode::build_dry_run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult OpProdDivNode::build() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
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
        BuildResult result;
        //assert(op == L'+' || op == L'-');
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult UnaryPlusMinusNode::build() const {
        BuildResult result;
        //assert(op == L'+' || op == L'-');
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult LitIntNode::build_dry_run() const {
        BuildResult result;
        result = BuildResult::from_type<onerut_scalar::Int>();
        return result;
    }

    BuildResult LitIntNode::build() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult LitDoubleNode::build_dry_run() const {
        BuildResult result;
        result = BuildResult::from_type<onerut_scalar::Double>();
        return result;
    }

    BuildResult LitDoubleNode::build() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
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
