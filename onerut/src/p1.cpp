#include<iostream>

#include<onerut_parser/gramma_parser.hpp>
#include<onerut_parser/ast_x3_to_ast_dyn.hpp>
#include<onerut_parser/print_chart.hpp>

int main() {
    //std::string input = "  _alg(_67j, foo(  7  , 8 ) , (xx2s) ) kota* 56.8 ";
    //std::string input  = "  $ ";
    std::string input = "  3.0^6@t+_alg((5->4-7/foo(6)), 8.9*ola::ala,-z+9,-7+9) ";
    //std::string input = "(9*2+3)*7.0";
    const auto parsed_x3_info = onerut_parser::parse(input);
    print(parsed_x3_info);

    const auto ast_dyn_head = onerut_parser::onerut_ast::to_ast_dyn(
            parsed_x3_info.ast_head,
            parsed_x3_info.input,
            parsed_x3_info.positions);

    const auto ast_dyn_chart = ast_dyn_head->to_chart();
    onerut_parser::print_chart(parsed_x3_info.input, ast_dyn_chart);
    
    /*
                const x3::ExpressionInfo& info,
            std::shared_ptr<const std::u32string> input,                        
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions
                
                
                    struct ParseResultInfo {
        std::shared_ptr<const std::u32string> input;
        const bool match;
        const bool hit_end;
        const bool succes;
        const onerut_parser::onerut_ast::x3::ExpressionInfo ast_head;
        const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >> positions;
     */
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

        int i2 = boost::convert<int>(sv).value();
        std::cout << i2 << std::endl;

        //boost::cnv::lexical_cast
        //using boost::convert;
        //boost::cnv::cstream cnv;

        //std::cout <<
        //      boost::convert<int>("66", cnv).value();

        //std::string_view sw(s.data(), 3);
        //if (sw.cbegin() == s.cbegin()){
        //    std::cout << "OK" << std::endl;
        // }
    }

}
 */
