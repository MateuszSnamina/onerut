#include<cassert>
#include<type_traits>

#include<onerut_normal_operator/calculate_mean.hpp>

namespace cpp20 {

    template< class T >
    struct remove_cvref {
        typedef std::remove_cv_t<std::remove_reference_t<T> > type;
    };
    
}

namespace onerut_normal_operator {

    double calculate_mean(const AbstractOperator& op, const arma::vec& vec) {
        assert(op.get_domain()->size() == vec.n_elem);
        const auto spad_dim = op.get_domain()->size();
        using BraKetT = typename cpp20::remove_cvref<decltype(spad_dim)>::type;        
        double result = 0.0;
        for (BraKetT ket = 0; ket < spad_dim; ket++) {
            auto it_ptr = op.begin_itptr(ket);
            while (!it_ptr->is_end()) {
                const auto& val_bra = it_ptr->get_val_bra();
                const auto& value = val_bra.first;
                const auto& bra = val_bra.second;
                if (bra < spad_dim) {
                    result += vec(bra) * value * vec(ket);
                }
                it_ptr->next();
            }
        }
        return result;
    }

}


