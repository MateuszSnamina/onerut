#include<onerut_parser/gramma_parser.hpp>
#include<iostream>
///////////////////////////////////////////////////////////////////////

int main() { 
    //std::wstring s;
    //std::getline(std::cin, s);
    ///std::wcout << "input size: " << ws.size() << std::endl;
    //std::wcout << "input     : " << ws << std::endl;    

    //std::string s = "  _alg(_67j, foo(7, 8 ) , xx2s) kota* 56.8 ";
    std::string s = "  $ ";
    onerut_parser::parse(s);
    
}

///////////////////////////////////////////////////////////////////////////
//#include<string_view>
//std::string_view make_string_view(boost::iterator_range<std::string::const_iterator> r) {
//    return std::string_view(&*r.begin(), r.end() - r.begin());
//}

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
