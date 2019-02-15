#include<algorithm>
#include<iterator>

#include<onerut_parser/share_from.hpp>
#include<onerut_parser/ast_compile_result.hpp>
#include<onerut_parser/compile_result_utility.hpp>
#include<onerut_parser/ast_source.hpp>
#include<onerut_parser/identifier_global.hpp>
#include<onerut_parser/function_factory_global.hpp>
#include<onerut_scalar/scalar.hpp>

namespace {

    bool
    is_plus_munis_char(char op) {
        return op == L'+' || op == L'-';
    }

    bool
    is_prod_div_char(char op) {
        return op == L'*' || op == L'/';
    }

    std::vector<std::shared_ptr < onerut_parser::onerut_ast::compile_result::CompileResultNode>>
    many_compile(
            const std::vector<std::shared_ptr<onerut_parser::onerut_ast::source::SourceNode>> argv) {
        std::vector<std::shared_ptr < onerut_parser::onerut_ast::compile_result::CompileResultNode>> argv_node;
        argv_node.reserve(argv.size());
        std::transform(cbegin(argv), cend(argv), back_inserter(argv_node),
                [](const std::shared_ptr<onerut_parser::onerut_ast::source::SourceNode> & arg) {
                    return arg->compile();
                });
        return argv_node;
    }

    std::vector<onerut_parser::CompileResult>
    many_extract_compile_result(
            std::vector<std::shared_ptr < onerut_parser::onerut_ast::compile_result::CompileResultNode>> argv_node) {
        std::vector<onerut_parser::CompileResult> argv_compile_result;
        argv_compile_result.reserve(argv_node.size());
        std::transform(cbegin(argv_node), cend(argv_node), back_inserter(argv_compile_result),
                [](const std::shared_ptr < onerut_parser::onerut_ast::compile_result::CompileResultNode> &arg) {
                    return arg->compile_result;
                });
        return argv_compile_result;
    }

    //    bool
    //    many_is_either_value_or_type(
    //            onerut_parser::CompileResultDeref first_arg_compile_result,
    //            onerut_parser::CompileResultDeref second_arg_compile_result) {
    //        return first_arg_compile_result.is_either_value_or_type() &&
    //                second_arg_compile_result.is_either_value_or_type();
    //    }

    bool
    many_is_either_value_or_type(
            onerut_parser::CompileResultDeref first_arg_compile_result,
            std::vector<onerut_parser::CompileResultDeref> other_argv_compile_result) {
        return first_arg_compile_result.is_either_value_or_type() &&
                std::all_of(other_argv_compile_result.cbegin(), other_argv_compile_result.cend(),
                [](const onerut_parser::CompileResultDeref & compile_result) {
                    return compile_result.is_either_value_or_type();
                });
    }

    //    bool
    //    many_is_either_value_or_type(std::vector<onerut_parser::CompileResultDeref> argv_compile_result) {
    //        return std::all_of(argv_compile_result.cbegin(), argv_compile_result.cend(),
    //                [](const onerut_parser::CompileResultDeref & compile_result) {
    //                    return compile_result.is_either_value_or_type();
    //                });
    //    }

    onerut_parser::CompileResult
    behave_like_a_binary_function(
            const std::string function_name,
            onerut_parser::CompileResult first_arg_compile_result,
            onerut_parser::CompileResult second_arg_compile_result) {
        const auto first_arg_compile_result_deref = first_arg_compile_result.dereference();
        const auto second_arg_compile_result_deref = second_arg_compile_result.dereference();
        if (auto function_factory = onerut_parser::GlobalFunctionFactories::instance().get_or_empty(function_name))
            return (*function_factory)->make_function_otherwise_make_error({first_arg_compile_result, second_arg_compile_result});
        return onerut_parser::CompileResult::from_compile_error(std::make_shared<onerut_parser::FunctionNotFoundError>(function_name));
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
        if (auto holder = GlobalIdentifiers::instance().get_or_empty(name))
            return CompileResult::from_reference(*holder);
        return CompileResult::from_compile_error(std::make_shared<IdentifierNotFoundError>(name));
    }

    // -------------------------------------------------------------------------

    CompileResult
    OpAssignNode::basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const {
        const auto second_arg_compile_result_deref = second_arg_compile_result.dereference();
        const auto first_arg_compile_result_deref = first_arg_compile_result.dereference();
        const bool first_arg_is_not_const_ref = utility::is_not_const_ref(first_arg_compile_result);
        const bool first_arg_is_const_ref = utility::is_const_ref(first_arg_compile_result);
        const bool first_arg_is_identifier_not_found_error = utility::is_identifier_not_found_error(first_arg_compile_result_deref);
        const bool first_arg_type_match = first_arg_is_not_const_ref || first_arg_is_const_ref || first_arg_is_identifier_not_found_error;
        const bool second_argument_match = second_arg_compile_result_deref.is_either_value_or_type();
        if (!second_argument_match)
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!first_arg_type_match)
            return CompileResult::from_compile_error(std::make_shared<IllegalAssignAttemptToRValueError>());
        if (first_arg_is_const_ref)
            return CompileResult::from_compile_error(std::make_shared<IllegalAssignAttemptToConstReferenceError>());
        if (new_flag && !first_arg_is_identifier_not_found_error)
            return CompileResult::from_compile_error(std::make_shared<IllegalAssignAttemptToReferenceError>());
        if (first_arg_is_identifier_not_found_error) {
            const auto name = utility::name_of_identifier_not_found(first_arg_compile_result_deref);
            const std::shared_ptr<AbstractCompileResultRef> created_ref = const_flag ?
                    std::static_pointer_cast<AbstractCompileResultRef>(std::make_shared<CompileResultConstRef>(name, second_arg_compile_result_deref)) :
                    std::static_pointer_cast<AbstractCompileResultRef>(std::make_shared<CompileResultNotConstRef>(name, second_arg_compile_result_deref));
            if (!GlobalIdentifiers::instance().put(name, created_ref)) {
                return CompileResult::from_compile_error(std::make_shared<IllegalSecondAssignError>());
            }
            return second_arg_compile_result;
        }
        if (first_arg_is_not_const_ref) {
            auto ref = utility::to_not_const_ref(first_arg_compile_result);
            if (!const_flag) {
                ref->set_compile_result(second_arg_compile_result_deref);
            } else {
                const auto name = ref->get_name();
                const auto created_ref = std::make_shared<CompileResultConstRef>(name, second_arg_compile_result_deref);
                GlobalIdentifiers::instance().force_put(name, created_ref);
            }
            return second_arg_compile_result;
        }
        return CompileResult::from_compile_error(std::make_shared<CompilerNotImplementedError>());
    }

    // -------------------------------------------------------------------------

    CompileResult
    OpPlusMinusNode::basic_compile(CompileResult first_arg_compile_result, std::vector<CompileResult> other_argv_compile_result) const {
        assert(std::all_of(opv.cbegin(), opv.cend(), is_plus_munis_char));
        const auto & first_arg_compile_result_deref = first_arg_compile_result.dereference();
        const auto & other_argv_compile_result_deref = utility::many_dereference(other_argv_compile_result);
        if (!many_is_either_value_or_type(first_arg_compile_result_deref, other_argv_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (utility::is_integer(first_arg_compile_result_deref) &&
                std::all_of(cbegin(other_argv_compile_result_deref), cend(other_argv_compile_result_deref), utility::is_integer)) {
            const auto & first_arg_integer = utility::to_integer(first_arg_compile_result_deref);
            const auto & other_argv_integer = utility::many_to_integer(other_argv_compile_result_deref);
            return CompileResult::from_value<onerut_scalar::Integer>(std::make_shared<onerut_scalar::OpPlusMinusInteger>(first_arg_integer, other_argv_integer, opv));
        }
        if (utility::is_real_or_integer(first_arg_compile_result_deref) &&
                std::all_of(cbegin(other_argv_compile_result_deref), cend(other_argv_compile_result_deref), utility::is_real_or_integer)) {
            const auto & first_arg_real = utility::to_real(first_arg_compile_result_deref);
            const auto & other_argv_real = utility::many_to_real(other_argv_compile_result_deref);
            return CompileResult::from_value<onerut_scalar::Real>(std::make_shared<onerut_scalar::OpPlusMinusReal>(first_arg_real, other_argv_real, opv));
        }
        if (utility::is_real_or_integer_or_complex(first_arg_compile_result_deref) &&
                std::all_of(cbegin(other_argv_compile_result_deref), cend(other_argv_compile_result_deref), utility::is_real_or_integer_or_complex)) {
            const auto & first_arg_complex = utility::to_complex(first_arg_compile_result_deref);
            const auto & other_argv_complex = utility::many_to_complex(other_argv_compile_result_deref);
            return CompileResult::from_value<onerut_scalar::Complex>(std::make_shared<onerut_scalar::OpPlusMinusComplex>(first_arg_complex, other_argv_complex, opv));
        }
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    CompileResult
    OpProdDivNode::basic_compile(CompileResult first_arg_compile_result, std::vector<CompileResult> other_argv_compile_result) const {
        assert(std::all_of(opv.cbegin(), opv.cend(), is_prod_div_char));
        const auto & first_deref_arg_compile_result = first_arg_compile_result.dereference();
        const auto & other_argv_compile_result_deref = utility::many_dereference(other_argv_compile_result);
        if (!many_is_either_value_or_type(first_deref_arg_compile_result, other_argv_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (utility::is_integer(first_deref_arg_compile_result) &&
                std::all_of(cbegin(other_argv_compile_result_deref), cend(other_argv_compile_result_deref), utility::is_integer)) {
            const auto & first_arg_integer = utility::to_integer(first_deref_arg_compile_result);
            const auto & other_argv_integer = utility::many_to_integer(other_argv_compile_result_deref);
            return CompileResult::from_value<onerut_scalar::Integer>(std::make_shared<onerut_scalar::OpProdDivInteger>(first_arg_integer, other_argv_integer, opv));
        }
        if (utility::is_real_or_integer(first_deref_arg_compile_result) &&
                std::all_of(cbegin(other_argv_compile_result_deref), cend(other_argv_compile_result_deref), utility::is_real_or_integer)) {
            const auto & first_arg_real = utility::to_real(first_deref_arg_compile_result);
            const auto & other_argv_real = utility::many_to_real(other_argv_compile_result_deref);
            return CompileResult::from_value<onerut_scalar::Real>(std::make_shared<onerut_scalar::OpProdDivReal>(first_arg_real, other_argv_real, opv));
        }
        if (utility::is_real_or_integer_or_complex(first_deref_arg_compile_result) &&
                std::all_of(cbegin(other_argv_compile_result_deref), cend(other_argv_compile_result_deref), utility::is_real_or_integer_or_complex)) {
            const auto & first_arg_complex = utility::to_complex(first_deref_arg_compile_result);
            const auto & other_argv_complex = utility::many_to_complex(other_argv_compile_result_deref);
            return CompileResult::from_value<onerut_scalar::Complex>(std::make_shared<onerut_scalar::OpProdDivComplex>(first_arg_complex, other_argv_complex, opv));
        }
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    CompileResult
    OpPowNode::basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const {
        return behave_like_a_binary_function("pow", first_arg_compile_result, second_arg_compile_result);
    }

    // -------------------------------------------------------------------------

    CompileResult
    OpAtNode::basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const {
        return behave_like_a_binary_function("at", first_arg_compile_result, second_arg_compile_result);

    }

    // -------------------------------------------------------------------------

    CompileResult
    OpArrowNode::basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const {
        return behave_like_a_binary_function("arrow", first_arg_compile_result, second_arg_compile_result);

    }

    // -------------------------------------------------------------------------

    CompileResult
    OpGlueNode::basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const {
        return behave_like_a_binary_function("glue", first_arg_compile_result, second_arg_compile_result);
    }

    // -------------------------------------------------------------------------

    CompileResult
    UnaryPlusMinusNode::basic_compile(CompileResult arg_compile_result) const {
        const auto arg_compile_result_deref = arg_compile_result.dereference();
        assert(is_plus_munis_char(op));
        assert(!arg_compile_result_deref.is_empty());
        if (!arg_compile_result_deref.is_either_value_or_type())
            const CompileResult compile_result = CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (utility::is_integer(arg_compile_result_deref)) {
            const auto & arg_integer = utility::to_integer(arg_compile_result_deref);
            return CompileResult::from_value<onerut_scalar::Integer>(std::make_shared<onerut_scalar::OpUnaryPlusMinusInteger>(arg_integer, op));
        }
        if (utility::is_real_or_integer(arg_compile_result_deref)) {
            const auto & arg_real = utility::to_real(arg_compile_result_deref);
            return CompileResult::from_value<onerut_scalar::Real>(std::make_shared<onerut_scalar::OpUnaryPlusMinusReal>(arg_real, op));
        }
        if (utility::is_real_or_integer_or_complex(arg_compile_result_deref)) {
            const auto & arg_complex = utility::to_complex(arg_compile_result_deref);
            return CompileResult::from_value<onerut_scalar::Complex>(std::make_shared<onerut_scalar::OpUnaryPlusMinusComplex>(arg_complex, op));
        }
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    CompileResult
    LitLongNode::basic_compile() const {
        return CompileResult::from_value<onerut_scalar::Integer>(std::make_shared<onerut_scalar::LitInteger>(value));
    }

    // -------------------------------------------------------------------------

    CompileResult
    LitDoubleNode::basic_compile() const {
        return CompileResult::from_value<onerut_scalar::Real>(std::make_shared<onerut_scalar::LitReal>(value));
    }

    // -------------------------------------------------------------------------

    CompileResult
    LitPureComplexDoubleNode::basic_compile() const {
        return CompileResult::from_value<onerut_scalar::Complex>(std::make_shared<onerut_scalar::LitComplex>(std::complex(0.0, value)));
    }
    
    // -------------------------------------------------------------------------

    CompileResult
    FunctionNode::basic_compile(std::vector<CompileResult> argv_compile_result) const {
        if (auto function = GlobalFunctionFactories::instance().get_or_empty(name))
            return (*function)->make_function_otherwise_make_error(argv_compile_result);
        return CompileResult::from_compile_error(std::make_shared<FunctionNotFoundError>(name));
    }

}
