//#include<armadillo>

#include<onerut/parser.hpp>

///////////////////////////////////////////////////////////////////////
#include<string_view>
#include<boost/convert.hpp>
#include<boost/convert/lexical_cast.hpp>

//using boost::convert;
//using boost::lexical_cast;

struct boost::cnv::by_default : public boost::cnv::lexical_cast {
};

std::string_view make_string_view(boost::iterator_range<std::string::const_iterator> r) {
    return std::string_view(&*r.begin(), r.end() - r.begin());
}
///////////////////////////////////////////////////////////////////////

int main() {
    std::string s = "  _alg(_67j,foo(7,8),xx2s) kota* 56.8 ";
    onerut_parse(s);
}

///////////////////////////////////////////////////////////////////////////

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

    {
        std::string s = "  foo((3.), bar(6, x ), baz(-9))";
        auto root = operator_string_parser::span_to_node({s.cbegin(), s.cend()});
        std::cout << s << std::endl;
        std::cout << root->str() << std::endl;
    }
    {
        std::string s = "  3+ 5";
        auto root = operator_string_parser::span_to_node({s.cbegin(), s.cend()});
        std::cout << s << std::endl;
        std::cout << root->str() << std::endl;
    }
    {
        std::string s = "( ( x +  3+ (5) + foo(x,y)))";
        auto root = operator_string_parser::span_to_node({s.cbegin(), s.cend()});
        std::cout << s << std::endl;
        std::cout << root->str() << std::endl;
    }
    {
        std::string s = "( ( x +  5 * 9 * y + d * (7+4)))";
        auto root = operator_string_parser::span_to_node({s.cbegin(), s.cend()});
        std::cout << s << std::endl;
        std::cout << root->str() << std::endl;
    }
}
 */

/*
int main() {
  arma::mat X = {{0,1},{1,0}};
  X = X * X;
  arma::mat beta;
  arma::vec epsilon;
  arma::eig_sym(epsilon, beta , X);
  arma::sp_mat Y(5000, 5000);
  Y(0,0) = -5;
  Y(1,1) = -8;
  Y(20,20) = -54;
  Y(3,3) = -2;
  Y(4,4) = -3;
  //arma::eigs_sym(epsilon, beta , Y, 7, "sa");
  //std::cout << epsilon << std::endl;
  //std::cout << beta << std::endl;
}
 */
