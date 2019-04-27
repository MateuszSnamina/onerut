#include<cassert>
#include<type_traits>
#include<boost/cast.hpp>

#include<onerut_normal_operator/calculate_mean.hpp>

namespace cpp20 {

    template< class T >
    struct remove_cvref {
        typedef std::remove_cv_t<std::remove_reference_t<T> > type;
    };

}

namespace onerut_normal_operator {

    double calculate_mean(
            const AbstractRealOperator& op, const arma::vec& col) {
        const auto space_dim = op.get_domain()->size();
        assert(boost::numeric_cast<arma::uword>(space_dim) == col.n_elem);
        using BraKetT = typename cpp20::remove_cvref<decltype(space_dim)>::type;
        double result = 0.0;
        for (BraKetT ket = 0; ket < space_dim; ket++) {
            auto it_ptr = op.begin_itptr(ket);
            while (!it_ptr->is_end()) {
                const auto& val_bra = it_ptr->get_val_bra();
                const auto& value = val_bra.first;
                const auto& bra = val_bra.second;
                if (bra < space_dim) {
                    result += col(bra) * value * col(ket);
                }
                it_ptr->next();
            }
        }
        return result;
    }

    arma::vec many_calculate_mean(
            const AbstractRealOperator& op, const arma::mat& cols) {
        const auto space_dim = op.get_domain()->size();
        assert(boost::numeric_cast<arma::uword>(space_dim) == cols.n_rows);
        using BraKetT = typename cpp20::remove_cvref<decltype(space_dim)>::type;
        arma::vec result(cols.n_cols, arma::fill::zeros);
        for (BraKetT ket = 0; ket < space_dim; ket++) {
            auto it_ptr = op.begin_itptr(ket);
            while (!it_ptr->is_end()) {
                const auto& val_bra = it_ptr->get_val_bra();
                const auto& value = val_bra.first;
                const auto& bra = val_bra.second;
                for (arma::uword i_col = 0; i_col < cols.n_cols; ++i_col) {
                    if (bra < space_dim) {
                        result(i_col) += cols(bra, i_col) * value * cols(ket, i_col);
                    }
                }
                it_ptr->next();
            }
        }
        return result;
    }

    arma::vec calculate_thermal_weights(
            arma::vec energies, double temperature) {
        if (energies.n_elem == 0)
            assert(false);
        if (temperature != 0) {
            const double ref_energy = energies(0);
            energies -= ref_energy;
            energies *= -1 / temperature;
            energies = arma::exp(energies);
            //energies.for_each(
            //        [&ref_energy, &temperature](double& val) {
            //            val = std::exp(-(val - ref_energy) / temperature);
            //        }
            //);
            const double Z = arma::sum(energies);
            energies /= Z;
        } else {
            const auto index = energies.index_min();
            energies.zeros();
            energies[index] = 1.0;
        }
        return energies;
    }

    double calculate_thermal_mean(
            const AbstractRealOperator& op, const arma::mat& cols,
            const arma::vec& energies, double temperature) {
        assert(energies.n_elem == cols.n_cols);
        const auto weights = calculate_thermal_weights(energies, temperature);
        const auto means = many_calculate_mean(op, cols);
        return arma::dot(weights, means);
    }

}


