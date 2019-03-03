#include<cassert>

#include<onerut_normal_operator/operator_kron.hpp>

#include<iostream> //debug TODO delete

namespace {

    //    unsigned _get_site_intex(
    //            unsigned my_weight,
    //            unsigned next_weight,
    //            unsigned ket) {
    //        return (ket % next_weight) / my_weight;
    //    }
    //
    //    unsigned _get_site_intex(
    //            const std::vector<unsigned>& weights,
    //            unsigned site,
    //            unsigned ket) {
    //        assert(site < weights.size() - 1);
    //        return _get_site_intex(weights[site +1], weights[site], ket);
    //    }

}

namespace onerut_normal_operator {

    /*
        // -------------------------------------------------------------------------

        KronAtOperator::SpinZetOperator(std::shared_ptr<const SpinDomain> domain) :
        domain(domain) {
            assert(domain);
        }

        std::shared_ptr<const Domain> KronAtOperator::get_domain() const {
            return domain;
        }

        typename KronAtOperator::AbstractIteratorPtrT
        SpinZetOperator::begin_itptr(const unsigned& ket) const {          
            return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(value, ket)));
        }
   
     */
}

