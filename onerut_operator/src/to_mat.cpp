#include<onerut_operator/to_mat.hpp>

namespace onerut_operator {

    arma::mat to_mat(const AbstractOperator<unsigned>& op, unsigned spad_dim) {
        arma::mat result(spad_dim, spad_dim, arma::fill::zeros);
        for (unsigned ket = 0; ket < spad_dim; ket++) {
            auto it_ptr = op.begin_itptr(ket);
            while (!it_ptr->is_end()) {
                const std::pair<double, unsigned>& val_bra = it_ptr->get_val_bra();
                const double& value = val_bra.first;
                const unsigned& bra = val_bra.second;
                result(bra, ket) += value;
                it_ptr->next();
            }
        }
        return result;
    }

}