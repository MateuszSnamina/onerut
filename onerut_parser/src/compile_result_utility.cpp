#include<algorithm>

#include<onerut_parser/compile_result_utility.hpp>

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
    is_integer(const onerut_parser::CompileResultDeref& arg) {
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<onerut_scalar::Integer>();
    }

    bool
    is_real_or_integer(const onerut_parser::CompileResultDeref& arg) {
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<onerut_scalar::Integer>() ||
                arg.is_given_type<onerut_scalar::Real>();
    }

    bool
    is_real_or_integer_or_complex(const onerut_parser::CompileResultDeref& arg) {
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<onerut_scalar::Integer>() ||
                arg.is_given_type<onerut_scalar::Real>() ||
                arg.is_given_type<onerut_scalar::Complex>();
    }
    // -------------------------------------------------------------------------

    std::shared_ptr<onerut_scalar::Integer>
    to_integer(const onerut_parser::CompileResultDeref& arg) {
        assert(is_integer(arg));
        const auto& arg_integer = *arg.typed_value_or_empty<onerut_scalar::Integer>();
        assert(arg_integer);
        return arg_integer;
    }

    std::shared_ptr<onerut_scalar::Real>
    to_real(const onerut_parser::CompileResultDeref& arg) {
        assert(is_real_or_integer(arg));
        std::shared_ptr<onerut_scalar::Real> arg_real;
        if (auto temp = arg.typed_value_or_empty<onerut_scalar::Integer>()) {
            arg_real = *temp;
        } else {
            arg_real = *arg.typed_value_or_empty<onerut_scalar::Real>();
        }
        assert(arg_real);
        return arg_real;
    }

    std::shared_ptr<onerut_scalar::Complex>
    to_complex(const onerut_parser::CompileResultDeref& arg) {
        assert(is_real_or_integer_or_complex(arg));
        std::shared_ptr<onerut_scalar::Complex> arg_complex;
        if (auto temp = arg.typed_value_or_empty<onerut_scalar::Integer>()) {
            arg_complex = *temp;
        } else if (auto temp = arg.typed_value_or_empty<onerut_scalar::Real>()) {
            arg_complex = *temp;
        } else {
            arg_complex = *arg.typed_value_or_empty<onerut_scalar::Complex>();
        }
        assert(arg_complex);
        return arg_complex;
    }

    // -------------------------------------------------------------------------

    std::vector<std::shared_ptr < onerut_scalar::Integer >>
    many_to_integer(std::vector<onerut_parser::CompileResultDeref> argv_compile_result_deref) {
        std::vector<std::shared_ptr < onerut_scalar::Integer >> argv_integer;
        argv_integer.reserve(argv_compile_result_deref.size());
        std::transform(argv_compile_result_deref.cbegin(), argv_compile_result_deref.cend(),
                std::back_inserter(argv_integer), to_integer);
        return argv_integer;
    }

    std::vector<std::shared_ptr < onerut_scalar::Real >>
    many_to_real(std::vector<onerut_parser::CompileResultDeref> argv_compile_result_deref) {
        std::vector<std::shared_ptr < onerut_scalar::Real >> argv_real;
        argv_real.reserve(argv_compile_result_deref.size());
        std::transform(argv_compile_result_deref.cbegin(), argv_compile_result_deref.cend(),
                std::back_inserter(argv_real), to_real);
        return argv_real;
    }

    std::vector<std::shared_ptr < onerut_scalar::Complex >>
    many_to_complex(std::vector<onerut_parser::CompileResultDeref> argv_compile_result_deref) {
        std::vector<std::shared_ptr < onerut_scalar::Complex >> argv_complex;
        argv_complex.reserve(argv_compile_result_deref.size());
        std::transform(argv_compile_result_deref.cbegin(), argv_compile_result_deref.cend(),
                std::back_inserter(argv_complex), to_complex);
        return argv_complex;
    }

}