#include<onerut_typed_operator/to_mat.hpp>

namespace onerut_typed_operator {

    arma::mat to_mat(const AbstractOperator<double, unsigned>& op, unsigned spad_dim) {
        using ScalarT = double;
        arma::mat result(spad_dim, spad_dim, arma::fill::zeros);
        for (unsigned ket = 0; ket < spad_dim; ket++) {
            auto it_ptr = op.begin_itptr(ket);
            while (!it_ptr->is_end()) {
                const std::pair<ScalarT, unsigned>& val_bra = it_ptr->get_val_bra();
                const ScalarT& value = val_bra.first;
                const unsigned& bra = val_bra.second;
                result(bra, ket) += value;
                it_ptr->next();
            }
        }
        return result;
    }

    arma::cx_mat to_mat(const AbstractOperator<std::complex<double>, unsigned>& op, unsigned spad_dim) {
        using ScalarT = std::complex<double>;
        arma::cx_mat result(spad_dim, spad_dim, arma::fill::zeros);
        for (unsigned ket = 0; ket < spad_dim; ket++) {
            auto it_ptr = op.begin_itptr(ket);
            while (!it_ptr->is_end()) {
                const std::pair<ScalarT, unsigned>& val_bra = it_ptr->get_val_bra();
                const ScalarT& value = val_bra.first;
                const unsigned& bra = val_bra.second;
                result(bra, ket) += value;
                it_ptr->next();
            }
        }
        return result;
    }

}