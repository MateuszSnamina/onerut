#include<iostream>
#include<iomanip>

#include<onerut_parser/gramma_parser.hpp>
#include<onerut_parser/ast_x3_to_ast_source.hpp>
#include<onerut_parser/ast_compile_result.hpp>
#include<onerut_parser/print_chart.hpp>
#include<onerut_parser/identifier_global.hpp>
#include<onerut_parser/function_global.hpp>
#include<onerut_scalar/scalar.hpp>

#include<esc/esc_manip.hpp>

bool execute_line(std::shared_ptr<std::u32string> line) {
    // #########################################################################
    const auto parsed_x3_info = onerut_parser::parse(line);
    // -------------------------------------------------------------------------
    std::cout << "Parsed info: (onerut_ast::x3):" << std::endl;
    //    print(parsed_x3_info);
    if (!parsed_x3_info.succes())
        return false;
    // #########################################################################
    const auto ast_source_head = onerut_parser::onerut_ast::to_ast_source(
            parsed_x3_info.ast_head,
            parsed_x3_info.input,
            parsed_x3_info.positions);
    // -------------------------------------------------------------------------
    //    const auto ast_source_chart = ast_source_head->to_chart();
    //    std::cout << "Parsed info: (onerut_ast::source):" << std::endl;
    //    onerut_parser::print_chart(parsed_x3_info.input, ast_source_chart);
    // #########################################################################
    const auto ast_compile_result_head = ast_source_head->compile();
    // -------------------------------------------------------------------------
    const auto ast_compile_result_chart = ast_compile_result_head->to_chart();
    std::cout << "Parsed info: (onerut_ast::compile_result):" << std::endl;
    onerut_parser::print_chart(parsed_x3_info.input, ast_compile_result_chart);
    // -------------------------------------------------------------------------
    onerut_parser::CompileResult compile_result = ast_compile_result_head->compile_result;
    if (compile_result.dereference().is_compile_error()) {
        std::cout << "RESULT IS AN ERROR" << std::endl;
        std::cout << (*compile_result.dereference().compile_error_or_empty())->what() << std::endl;
    } else if (compile_result.dereference().is_given_type<onerut_scalar::Long>()) {
        std::cout << "RESULT IS AN INT" << std::endl;
        std::shared_ptr<onerut_scalar::Long> result_long = *(compile_result.dereference().typed_value_or_empty<onerut_scalar::Long>());
        std::cout << "VALUE = " << result_long->value_long() << std::endl;
    } else if (compile_result.dereference().is_given_type<onerut_scalar::Double>()) {
        std::cout << "RESULT IS AN DOUBLE" << std::endl;
        std::shared_ptr<onerut_scalar::Double> result_double = *(compile_result.dereference().typed_value_or_empty<onerut_scalar::Double>());
        std::cout << "VALUE = " << std::setprecision(20) << result_double->value_double() << std::endl;
        //    } else if (compile_result.dereference().is_given_type<onerut_scalar::Double>()) {
        //        std::cout << "RESULT IS AN DOUBLE" << std::endl;
        //        std::shared_ptr<onerut_scalar::Double> result_double = *(compile_result.dereference().typed_value_or_empty<onerut_scalar::Double>());
        //        std::cout << "VALUE = " << std::setprecision(20) << result_double->value_double() << std::endl;
    } else {
        std::cout << "RESULT IS NOT INT NOR DOUBLE NOR ERROR." << std::endl;
    }
    return true;
}

bool execute_script(std::vector<std::shared_ptr<std::u32string>> lines) {
    return std::all_of(cbegin(lines), cend(lines),
            [](const std::shared_ptr<std::u32string> &line) {
                return execute_line(line);
            });
}

int main() {

    //std::make_shared<const std::u32string>(unicode_from_utf8(input)));

    onerut_parser::GlobalIdentifiers::instance().put_e();
    onerut_parser::GlobalIdentifiers::instance().put_pi();
    onerut_parser::GlobalFunctions::instance().put_sqrt();
    onerut_parser::GlobalFunctions::instance().put_pow();

    //std::string input = "  _alg(_67j, foo(  7  , 8 ) , (xx2s) ) kota* 56.8 ";
    //std::string input  = "  $ ";
    //const std::string input = "  3.0^6@t+_alg((5->4-7/foo(6)), 8.9*ola::ala,-pi+9,-7+9)*(-(9))+(-(9.0)+1) ";
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

    //const std::string input = "  10+pi/2 ";
    //const std::string input = "new x := 10 ";

    std::vector<std::shared_ptr < std::u32string>> lines;
    //    lines.push_back(std::make_shared < std::u32string>(U"(2+4*3)+pi/2"));
    lines.push_back(std::make_shared < std::u32string>(U"x:=(2+4*3)+pi/2"));
    lines.push_back(std::make_shared < std::u32string>(U"x+7"));
    lines.push_back(std::make_shared < std::u32string>(U"x:=40"));
    lines.push_back(std::make_shared < std::u32string>(U"x+4"));
    lines.push_back(std::make_shared < std::u32string>(U"sqrt(4.0)"));
    lines.push_back(std::make_shared < std::u32string>(U"pow(3,2)"));
    execute_script(lines);
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
