#ifndef ONERUT_PARSER_BUILD_RESULT_UTILITY
#define ONERUT_PARSER_BUILD_RESULT_UTILITY

#include<vector>

#include<onerut_parser/compile_result.hpp>
#include<onerut_scalar/scalar.hpp>

// *************************************************************************
// ********************** HELPER FUNCTIONS   *******************************
// *************************************************************************

namespace onerut_parser::utility {

    // -------------------------------------------------------------------------
    // ------------------ COMPILE RESULTS --------------------------------------
    // -------------------------------------------------------------------------

    bool
    is_not_const_ref(const onerut_parser::CompileResult& result);

    bool
    is_const_ref(const onerut_parser::CompileResult& result);

    bool
    is_identifier_not_found_error(const onerut_parser::CompileResultDeref& result);

    std::shared_ptr<onerut_parser::CompileResultNotConstRef>
    to_not_const_ref(const onerut_parser::CompileResult& compile_result);
    
    std::string
    name_of_identifier_not_found(const onerut_parser::CompileResultDeref& result);

    // -------------------------------------------------------------------------

    std::vector<onerut_parser::CompileResultDeref>
    many_dereference(const std::vector<onerut_parser::CompileResult> compile_result_argv);

    // -------------------------------------------------------------------------
    // ------------------ COMPILE RESULTS DEREF --------------------------------
    // -------------------------------------------------------------------------

    bool
    is_integer(const onerut_parser::CompileResultDeref& result);

    bool
    is_real_or_integer(const onerut_parser::CompileResultDeref& result);

    // -------------------------------------------------------------------------

    std::shared_ptr<onerut_scalar::Integer>
    to_integer(const onerut_parser::CompileResultDeref& arg_result);

    std::shared_ptr<onerut_scalar::Real>
    to_real(const onerut_parser::CompileResultDeref& arg_result);

    // -------------------------------------------------------------------------

    std::vector<std::shared_ptr < onerut_scalar::Integer >>
    many_to_integer(std::vector<onerut_parser::CompileResultDeref> argv_compile_result_deref);

    std::vector<std::shared_ptr < onerut_scalar::Real >>
    many_to_real(std::vector<onerut_parser::CompileResultDeref> argv_compile_result_deref);

}

#endif