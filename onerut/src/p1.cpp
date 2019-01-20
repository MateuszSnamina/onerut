#include<onerut_parser/gramma_parser.hpp>
#include<iostream>

int main() {
    //std::string input = "  _alg(_67j, foo(  7  , 8 ) , (xx2s) ) kota* 56.8 ";
    //std::string input  = "  $ ";
    std::string input = "  3.0+_alg((5-7/foo(6)), 8.9*ala) ";
    //std::string input = "(9*2+3)*7.0";
    const auto parsed = onerut_parser::parse(input);
    print(parsed);
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
