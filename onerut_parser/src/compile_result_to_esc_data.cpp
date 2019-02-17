#include<onerut_parser/compile_result_to_esc_data.hpp>
#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_operator/operator_abstract.hpp>
namespace onerut_parser {

    esc::EscData compile_result_to_esc_data(const CompileResult& compile_result) {
        if (compile_result.dereference().is_empty())
            return esc::EscDataBuilder() << esc::manip::bg_magenta << esc::manip::build_esc_data;
        if (compile_result.dereference().is_compile_error()) {
            if (std::dynamic_pointer_cast<CompileArgumentsError>(*compile_result.dereference().compile_error_or_empty()))
                return esc::EscDataBuilder() << esc::manip::bg_yellow << esc::manip::build_esc_data;
            if (std::dynamic_pointer_cast<CompilerNotImplementedError>(*compile_result.dereference().compile_error_or_empty()))
                return esc::EscDataBuilder() << esc::manip::bg_magenta << esc::manip::build_esc_data;
            return esc::EscDataBuilder() << esc::manip::bg_red << esc::manip::build_esc_data;
        }
        if (compile_result.dereference().is_given_type<onerut_scalar::Integer>())
            return esc::EscDataBuilder() << esc::manip::blue << esc::manip::build_esc_data;
        if (compile_result.dereference().is_given_type<onerut_scalar::Real>())
            return esc::EscDataBuilder() << esc::manip::cyan << esc::manip::build_esc_data;
        if (compile_result.dereference().is_given_type<onerut_scalar::Complex>())
            return esc::EscDataBuilder() << esc::manip::green << esc::manip::build_esc_data;        
        if (compile_result.dereference().is_given_type<onerut_operator::AbstractOperator<unsigned> >())
            return esc::EscDataBuilder() << esc::manip::bold << esc::manip::yellow << esc::manip::build_esc_data;                
        return esc::EscDataBuilder() << esc::manip::build_esc_data;
    }

}