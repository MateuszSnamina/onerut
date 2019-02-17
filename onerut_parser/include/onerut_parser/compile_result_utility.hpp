#ifndef ONERUT_PARSER_BUILD_RESULT_UTILITY
#define ONERUT_PARSER_BUILD_RESULT_UTILITY

#include<vector>

#include<onerut_parser/compile_result.hpp>
#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_operator/operator_abstract.hpp>

namespace onerut_parser::utility {

    // -------------------------------------------------------------------------
    // ------------------ COMPILE RESULTS --------------------------------------
    // -------------------------------------------------------------------------

    bool
    is_not_const_ref(const onerut_parser::CompileResult&);

    bool
    is_const_ref(const onerut_parser::CompileResult&);

    bool
    is_identifier_not_found_error(const onerut_parser::CompileResultDeref&);

    std::shared_ptr<onerut_parser::CompileResultNotConstRef>
    to_not_const_ref(const onerut_parser::CompileResult&);

    std::string
    name_of_identifier_not_found(const onerut_parser::CompileResultDeref&);

    // -------------------------------------------------------------------------

    std::vector<onerut_parser::CompileResultDeref>
    many_dereference(const std::vector<onerut_parser::CompileResult>);

    // -------------------------------------------------------------------------
    // ------------------ COMPILE RESULTS DEREF --------------------------------
    // -------------------------------------------------------------------------

    bool
    is_integer(const onerut_parser::CompileResultDeref&);

    bool
    is_real_or_integer(const onerut_parser::CompileResultDeref&);

    bool
    is_real_or_integer_or_complex(const onerut_parser::CompileResultDeref&);

    bool
    is_normal_operator(const onerut_parser::CompileResultDeref&);

    //bool
    //is_fermion_operator(const onerut_parser::CompileResultDeref&);

    //bool
    //is_boson_operator(const onerut_parser::CompileResultDeref&);

    // -------------------------------------------------------------------------

    std::shared_ptr<onerut_scalar::Integer>
    to_integer(const onerut_parser::CompileResultDeref&);

    std::shared_ptr<onerut_scalar::Real>
    to_real(const onerut_parser::CompileResultDeref&);

    std::shared_ptr<onerut_scalar::Complex>
    to_complex(const onerut_parser::CompileResultDeref&);

    std::shared_ptr<onerut_operator::AbstractOperator<unsigned> >
    to_normal_operator(const onerut_parser::CompileResultDeref&);

    //    std::shared_ptr<onerut_operator::AbstractOperator<FERMION_KET_T> >
    //    to_fermion_operator(const onerut_parser::CompileResultDeref&);

    //    std::shared_ptr<onerut_operator::AbstractOperator<BOSON_KET_T> >
    //    to_boson_operator(const onerut_parser::CompileResultDeref&);

    // -------------------------------------------------------------------------

    std::vector<std::shared_ptr < onerut_scalar::Integer >>
    many_to_integer(std::vector<onerut_parser::CompileResultDeref>);

    std::vector<std::shared_ptr < onerut_scalar::Real >>
    many_to_real(std::vector<onerut_parser::CompileResultDeref>);

    std::vector<std::shared_ptr < onerut_scalar::Complex >>
    many_to_complex(std::vector<onerut_parser::CompileResultDeref>);

}

#endif