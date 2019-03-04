#include<cassert>
#include<type_traits>
#include<boost/numeric/conversion/cast.hpp>

#include<onerut_normal_operator/to_mat.hpp>

namespace onerut_normal_operator {

    template<class T>
    T _to_mat(const AbstractOperator& op) {
        static_assert(std::is_same<T, arma::mat>::value ||
                std::is_same<T, arma::sp_mat>::value);
        const auto spad_dim = boost::numeric_cast<arma::uword>(op.get_domain()->size());
        T result(spad_dim, spad_dim);
        result.zeros();
        for (AbstractOperator::BraKetT ket = 0; ket < spad_dim; ket++) {
            auto it_ptr = op.begin_itptr(ket);
            while (!it_ptr->is_end()) {
                const auto& val_bra = it_ptr->get_val_bra();
                const double& value = val_bra.first;
                const auto& bra = val_bra.second;
                if (bra < spad_dim) {
                    result(bra, ket) += value;
                }
                // The we need to check (bra < spad_dim)
                // as the operator may go out of the space.
                // As an example:
                // The oscillator creation operator may be implemented to
                // retrun bra=ket+1 for every ket.
                it_ptr->next();
            }
        }
        return result;
    }

}

namespace onerut_normal_operator {

    arma::mat to_mat(const AbstractOperator& op) {
        return _to_mat<arma::mat>(op);
    }

    arma::sp_mat to_sp_mat(const AbstractOperator& op) {
        return _to_mat<arma::sp_mat>(op);
    }

}