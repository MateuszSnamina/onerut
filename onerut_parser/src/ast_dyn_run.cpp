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
    WithTwoSubexpressionsNode::run_args() const {
        TwoSubexpressionsBuildResult result;
        result.first_arg = first_arg->run();
        result.second_arg = second_arg->run();
        return result;
    }

    TwoSubexpressionsBuildResult
    WithTwoSubexpressionsNode::dry_run_args() const {
        TwoSubexpressionsBuildResult result;
        result.first_arg = first_arg->dry_run();
        result.second_arg = second_arg->dry_run();
        return result;
    }

    bool OneOrMoreSubexpressionsBuildResult::is_error() const {
        return first_arg.is_error() || std::any_of(other_argv.cbegin(), other_argv.cend(), [](const BuildResult & r) {
            return r.is_error();
        });
    }

    OneOrMoreSubexpressionsBuildResult
    WithOneOrMoreSubexpressionsNode::run_args() const {
        OneOrMoreSubexpressionsBuildResult result;
        result.first_arg = first_arg->run();
        result.other_argv.resize(other_argv.size());
        std::transform(other_argv.cbegin(), other_argv.cend(), result.other_argv.begin(),
                [](const std::shared_ptr<ExpressionNode> & e) {
                    return e->run();
                });
        return result;
    }

    OneOrMoreSubexpressionsBuildResult
    WithOneOrMoreSubexpressionsNode::dry_run_args() const {
        OneOrMoreSubexpressionsBuildResult result;
        result.first_arg = first_arg->dry_run();
        result.other_argv.resize(other_argv.size());
        std::transform(other_argv.cbegin(), other_argv.cend(), result.other_argv.begin(),
                [](const std::shared_ptr<ExpressionNode> & e) {
                    return e->dry_run();
                });
        return result;
    }

    bool AnyNumberOfSubexpressionsBuildResult::is_error() const {
        return std::any_of(argv.cbegin(), argv.cend(), [](const BuildResult & r) {
            return r.is_error();
        });
    }

    AnyNumberOfSubexpressionsBuildResult
    WithAnyNumberOfSubexpressionsNode::run_args() const {
        AnyNumberOfSubexpressionsBuildResult result;
        result.argv.resize(argv.size());
        std::transform(argv.cbegin(), argv.cend(), result.argv.begin(),
                [](const std::shared_ptr<ExpressionNode> & e) {
                    return e->run();
                });
        return result;
    }

    AnyNumberOfSubexpressionsBuildResult
    WithAnyNumberOfSubexpressionsNode::dry_run_args() const {
        AnyNumberOfSubexpressionsBuildResult result;
        result.argv.resize(argv.size());
        std::transform(argv.cbegin(), argv.cend(), result.argv.begin(),
                [](const std::shared_ptr<ExpressionNode> & e) {
                    return e->dry_run();
                });
        return result;
    }

    // *************************************************************************
    // ***********************      Concrete classes     ***********************
    // *************************************************************************

    BuildResult IdentifierNode::dry_run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult IdentifierNode::run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult OpPlusMinusNode::dry_run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult OpPlusMinusNode::run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult OpProdDivNode::dry_run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult OpProdDivNode::run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult OpPowNode::dry_run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult OpPowNode::run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult OpAtNode::dry_run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult OpAtNode::run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult OpArrowNode::dry_run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult OpArrowNode::run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult OpGlueNode::dry_run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult OpGlueNode::run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult UnaryPlusMinusNode::dry_run() const {
        BuildResult result;
        //assert(op == L'+' || op == L'-');
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult UnaryPlusMinusNode::run() const {
        BuildResult result;
        //assert(op == L'+' || op == L'-');
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult LitIntNode::dry_run() const {
        BuildResult result;
        result = BuildResult::from_type<onerut_scalar::Int>();
        return result;
    }

    BuildResult LitIntNode::run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult LitDoubleNode::dry_run() const {
        BuildResult result;
        result = BuildResult::from_type<onerut_scalar::Double>();
        return result;
    }

    BuildResult LitDoubleNode::run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    // -------------------------------------------------------------------------

    BuildResult FunctionNode::dry_run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

    BuildResult FunctionNode::run() const {
        BuildResult result;
        result = BuildResult::from_build_error(std::make_shared<BuildNotImplementedError>());
        return result;
    }

}
