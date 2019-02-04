#include<algorithm>

#include<onerut_parser/compile_result_utility.hpp>

// *************************************************************************
// ********************** HELPER FUNCTIONS   *******************************
// *************************************************************************

namespace onerut_parser::utility {

    // -------------------------------------------------------------------------
    // ------------------ COMPILE RESULTS --------------------------------------
    // -------------------------------------------------------------------------

    bool
    is_not_const_ref(const onerut_parser::CompileResult& result) {
        if (const auto & reference = result.reference_or_empty())
            if (std::dynamic_pointer_cast<const onerut_parser::CompileResultNotConstRef>(*reference))
                return true;
        return false;
    }

    bool
    is_const_ref(const onerut_parser::CompileResult& result) {
        if (const auto & reference = result.reference_or_empty())
            if (std::dynamic_pointer_cast<const onerut_parser::CompileResultConstRef>(*reference))
                return true;
        return false;
    }

    bool
    is_identifier_not_found_error(const onerut_parser::CompileResultDeref& result) {
        if (const auto& error = result.compile_error_or_empty())
            if (std::dynamic_pointer_cast<const onerut_parser::IdentifierNotFoundError>(*error))
                return true;
        return false;
    }

    std::shared_ptr<onerut_parser::CompileResultNotConstRef>
    to_not_const_ref(const onerut_parser::CompileResult& compile_result) {
        assert(is_not_const_ref(compile_result));
        const auto & reference = compile_result.reference_or_empty();
        const auto & no_const_reference = std::dynamic_pointer_cast<onerut_parser::CompileResultNotConstRef>(*reference);
        assert(no_const_reference);
        return no_const_reference;
    }

    std::string
    name_of_identifier_not_found(const onerut_parser::CompileResultDeref& result) {
        const auto& error = result.compile_error_or_empty();
        assert(error);
        const auto& identifier_not_found_error = std::dynamic_pointer_cast<const onerut_parser::IdentifierNotFoundError>(*error);
        assert(identifier_not_found_error);
        return identifier_not_found_error->identifier_name;
    }

    // -------------------------------------------------------------------------

    std::vector<onerut_parser::CompileResultDeref>
    many_dereference(
            const std::vector<onerut_parser::CompileResult> compile_result_argv) {
        std::vector<onerut_parser::CompileResultDeref> argv_compile_result_deref;
        argv_compile_result_deref.reserve(compile_result_argv.size());
        std::transform(cbegin(compile_result_argv), cend(compile_result_argv), back_inserter(argv_compile_result_deref),
                [](const onerut_parser::CompileResult & compile_result) {
                    return compile_result.dereference();
                });
        return argv_compile_result_deref;
    }

    // -------------------------------------------------------------------------
    // ------------------ COMPILE RESULTS DEREF --------------------------------
    // -------------------------------------------------------------------------    

    bool
    is_integer(const onerut_parser::CompileResultDeref& result) {
        assert(!result.is_empty());
        assert(!result.is_compile_error());
        return result.is_given_type<onerut_scalar::Long>();
    }

    bool
    is_real(const onerut_parser::CompileResultDeref& result) {
        assert(!result.is_empty());
        assert(!result.is_compile_error());
        return result.is_given_type<onerut_scalar::Long>() || result.is_given_type<onerut_scalar::Double>();
    }

    // -------------------------------------------------------------------------

    std::shared_ptr<onerut_scalar::Long>
    to_long(const onerut_parser::CompileResultDeref& arg_result) {
        assert(is_integer(arg_result));
        const auto& arg_long = *arg_result.typed_value_or_empty<onerut_scalar::Long>();
        assert(arg_long);
        return arg_long;
    }

    std::shared_ptr<onerut_scalar::Double>
    to_double(const onerut_parser::CompileResultDeref& arg_result) {
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

    // -------------------------------------------------------------------------

    std::vector<std::shared_ptr < onerut_scalar::Long >>
    many_to_long(std::vector<onerut_parser::CompileResultDeref> argv_compile_result_deref) {
        std::vector<std::shared_ptr < onerut_scalar::Long >> argv_long;
        argv_long.reserve(argv_compile_result_deref.size());
        std::transform(argv_compile_result_deref.cbegin(), argv_compile_result_deref.cend(),
                std::back_inserter(argv_long), to_long);
        return argv_long;
    }

    std::vector<std::shared_ptr < onerut_scalar::Double >>
    many_to_double(std::vector<onerut_parser::CompileResultDeref> argv_compile_result_deref) {
        std::vector<std::shared_ptr < onerut_scalar::Double >> argv_long;
        argv_long.reserve(argv_compile_result_deref.size());
        std::transform(argv_compile_result_deref.cbegin(), argv_compile_result_deref.cend(),
                std::back_inserter(argv_long), to_double);
        return argv_long;
    }

}