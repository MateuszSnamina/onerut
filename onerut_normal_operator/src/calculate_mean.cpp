#include<cassert>
#include<onerut_normal_operator/calculate_mean.hpp>

namespace onerut_normal_operator {

    double calculate_mean(const AbstractOperator& op, const arma::vec& vec) {
        assert(op.get_domain()->size() == vec.n_elem);
        const unsigned spad_dim = op.get_domain()->size();
        double result = 0.0;
        for (unsigned ket = 0; ket < spad_dim; ket++) {
            auto it_ptr = op.begin_itptr(ket);
            while (!it_ptr->is_end()) {
                const std::pair<double, unsigned>& val_bra = it_ptr->get_val_bra();
                const double& value = val_bra.first;
                const unsigned& bra = val_bra.second;
                if (bra < spad_dim) {
                    result += vec(bra) * value * vec(ket);
                }
                it_ptr->next();
            }
        }
        return result;
    }

}


