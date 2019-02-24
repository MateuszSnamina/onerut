#include<onerut_normal_operator/to_mat.hpp>

namespace onerut_normal_operator {

    arma::mat to_mat(const AbstractOperator& op) {
        const unsigned spad_dim = op.get_domain()->size();
        arma::mat result(spad_dim, spad_dim, arma::fill::zeros);
        for (unsigned ket = 0; ket < spad_dim; ket++) {
            auto it_ptr = op.begin_itptr(ket);
            while (!it_ptr->is_end()) {
                const std::pair<double, unsigned>& val_bra = it_ptr->get_val_bra();
                const double& value = val_bra.first;
                const unsigned& bra = val_bra.second;
                if (bra < spad_dim) {
                    result(bra, ket) += value;
                }
                // The we need to check (bra < spad_dim)
                // as the operator may go out of the space.
                // As an example:
                // The oscilator creation operator may be implemented to
                // retrun bra=ket+1 for every ket.
                it_ptr->next();
            }
        }
        return result;
    }

}