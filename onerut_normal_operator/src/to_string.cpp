#include<iomanip>
#include<type_traits>

#include<log_utils/fancy_log_mat.hpp>

#include<onerut_normal_operator/to_mat.hpp>
#include<onerut_normal_operator/to_string.hpp>

namespace cpp20 {

    template< class T >
    struct remove_cvref {
        typedef std::remove_cv_t<std::remove_reference_t<T> > type;
    };

}

namespace onerut_normal_operator {

    std::string to_string(const Domain& domain) {
        std::string result;
        const auto domain_size = domain.size();
        using BraKetT = typename cpp20::remove_cvref<decltype(domain_size)>::type;
        for (BraKetT index = 0; index < domain_size; ++index)
            result += "【#" + std::to_string(index) + "»" + domain.state_name(index) + "】";
        return result;
    }

    std::string to_string(const AbstractOperator& op, std::string line_prefix) {
        std::ostringstream sstream;
        sstream << std::fixed;
        sstream << std::showpos;
        sstream << std::setprecision(6);
        const arma::mat matrix = to_mat(op);
        fancy_logging::log(sstream,
                op.get_domain()->state_names(),
                op.get_domain()->state_names(),
                matrix,
                line_prefix);
        return sstream.str();
    }

    std::string to_string(const Eig& eigs, std::string line_prefix) {
        std::ostringstream sstream;
        const auto eigs_results = eigs.value();
        eigs_results.log(sstream, line_prefix);
        return sstream.str();
    }

}
