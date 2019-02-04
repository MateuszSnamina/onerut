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
    is_real(const onerut_parser::CompileResultDeref& result);

    // -------------------------------------------------------------------------

    std::shared_ptr<onerut_scalar::Long>
    to_long(const onerut_parser::CompileResultDeref& arg_result);

    std::shared_ptr<onerut_scalar::Double>
    to_double(const onerut_parser::CompileResultDeref& arg_result);

    // -------------------------------------------------------------------------

    std::vector<std::shared_ptr < onerut_scalar::Long >>
    many_to_long(std::vector<onerut_parser::CompileResultDeref> argv_compile_result_deref);

    std::vector<std::shared_ptr < onerut_scalar::Double >>
    many_to_double(std::vector<onerut_parser::CompileResultDeref> argv_compile_result_deref);

}

#endif