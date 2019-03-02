#include<iomanip>

#include<log_utils/fancy_log_mat.hpp>

#include<onerut_normal_operator/to_mat.hpp>
#include<onerut_normal_operator/to_string.hpp>

namespace onerut_normal_operator {

    std::string to_string(const Domain& domain) {
        std::string result;
        for (unsigned index = 0; index < domain.size(); ++index)
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

    std::string to_string(const Eigs& eigs, std::string line_prefix) {
        std::ostringstream sstream;
        const auto eigs_results = eigs.value();
        eigs_results.log(sstream, line_prefix);
        return sstream.str();
    }
    
}
