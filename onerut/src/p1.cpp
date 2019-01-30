#include<iostream>
#include<iomanip>

#include<onerut_parser/gramma_parser.hpp>
#include<onerut_parser/ast_x3_to_ast_dyn.hpp>
#include<onerut_parser/print_chart.hpp>
#include<onerut_scalar/scalar.hpp>

#include<esc/esc_manip.hpp>

int main() {


    //std::string input = "  _alg(_67j, foo(  7  , 8 ) , (xx2s) ) kota* 56.8 ";
    //std::string input  = "  $ ";
    const std::string input = "  3.0^6@t+_alg((5->4-7/foo(6)), 8.9*ola::ala,-z+9,-7+9)*(-(9))+(-(9.0)+1) ";
    //std::string input = "(9/2+3)*7.0";
    //std::cout << (9 / 2 + 3)*7.0 << std::endl;
    //long i = 10000000000000000l;
    //std::cout << i + 1 << std::endl;
    //std::cout << std::setprecision(20) << 10000000000000000 + 1. << std::endl;
    //return 1;
    //std::string input = " (13/2*0.5+ (-(7.8*(5+5*7)) + 8. + -.8) /9) ";
    //std::cout << (13 / 2 * 0.5 + (-(7.8 * (5 + 5 * 7)) + 8. + -.8) / 9) << std::endl;
    //std::string input = "10000000 + 1.";
    //std::string input = "1000000000000000000000+1.";

    // -------------------------------------------------------------------------
    const auto parsed_x3_info = onerut_parser::parse(input);
    std::cout << "Parsed info: (onerut_ast::x3):" << std::endl;
    print(parsed_x3_info);
    if (!parsed_x3_info.succes())
        return 1;

    // -------------------------------------------------------------------------
    const auto ast_dyn_head = onerut_parser::onerut_ast::to_ast_dyn(
            parsed_x3_info.ast_head,
            parsed_x3_info.input,
            parsed_x3_info.positions);

    const auto ast_dyn_chart = ast_dyn_head->to_chart();
    // -------------------------------------------------------------------------

    std::cout << "Parsed info: (onerut_ast::dyn):" << std::endl;
    onerut_parser::print_chart(parsed_x3_info.input, ast_dyn_chart);

    // -------------------------------------------------------------------------

    onerut_parser::BuildResult result = ast_dyn_head->build();
    if (result.is_error()) {
        std::cout << "ERROR" << std::endl;
        std::cout << (*result.build_error_or_empty())->what() << std::endl;
    } else if (result.is_given_type<onerut_scalar::Long>()) {
        std::cout << "RESULT IS AN INT" << std::endl;
        std::shared_ptr<onerut_scalar::Long> result_long = *(result.typed_value_or_empty<onerut_scalar::Long>());
        std::cout << "VALUE = " << result_long->value_long() << std::endl;
    } else if (result.is_given_type<onerut_scalar::Double>()) {
        std::cout << "RESULT IS AN DOUBLE" << std::endl;
        std::shared_ptr<onerut_scalar::Double> result_double = *(result.typed_value_or_empty<onerut_scalar::Double>());
        std::cout << "VALUE = " << std::endl;
        std::cout << std::setprecision(20) << result_double->value_double() << std::endl;
    } else {
        std::cout << "NOT INT NOR DOUBLE" << std::endl;
    }
    // -------------------------------------------------------------------------

}


///////////////////////////////////////////////////////////////////////
//#include<boost/convert.hpp>
//#include<boost/convert/lexical_cast.hpp>

//using boost::convert;
//using boost::lexical_cast;

//struct boost::cnv::by_default : public boost::cnv::lexical_cast {
//};
/*
int main() {
    {
        std::string s = "654x";
        boost::iterator_range<std::string::const_iterator> r;
        r = {s.cbegin(), s.cend()};
        auto sv = make_string_view(r);

        long i2 = boost::convert<long>(sv).value();
        std::cout << i2 << std::endl;

        //boost::cnv::lexical_cast
        //using boost::convert;
        //boost::cnv::cstream cnv;

        //std::cout <<
        //      boost::convert<long>("66", cnv).value();

        //std::string_view sw(s.data(), 3);
        //if (sw.cbegin() == s.cbegin()){
        //    std::cout << "OK" << std::endl;
        // }
    }

}
 */
