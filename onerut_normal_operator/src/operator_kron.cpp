#include<cassert>
#include<iterator>
#include<algorithm>
#include<numeric> // std::accumulate, std::partial_sum
#include<functional> // std::multiplies
#include<cmath>
#include<string>
#include<boost/algorithm/string.hpp>

#include<onerut_normal_operator/operator_kron.hpp>

#include<iostream> //debug TODO delete

namespace {

    void print_vector(std::vector<unsigned> v) {
        for (unsigned i = 0; i < v.size(); ++i) {
            std::cout << v[i] << " ";
        }
        std::cout << std::endl;

    }
}

namespace {

    std::vector<unsigned> domains_2_domain_sizes(
            const std::vector<std::shared_ptr<const onerut_normal_operator::Domain> > & domains) {
        std::vector<unsigned> domain_sizes;
        std::transform(
                cbegin(domains), cend(domains),
                std::back_inserter(domain_sizes),
                [](const auto & domain) {
                    return domain->size();
                }
        );
        return domain_sizes;
    }

    std::vector<unsigned> domain_sizes_2_weights(
            const std::vector<unsigned> & domain_sizes) {
        std::vector<unsigned> weights(domain_sizes.size() + 1);
        weights.back() = 1;
        std::partial_sum(
                crbegin(domain_sizes), crend(domain_sizes),
                rbegin(weights) + 1, std::multiplies<unsigned>());
        return weights;
    }

    unsigned _get_site_intex(
            unsigned my_weight,
            unsigned next_weight,
            unsigned ket) {
        return (ket % next_weight) / my_weight;
    }

    unsigned _get_site_intex(
            const std::vector<unsigned>& weights,
            unsigned site,
            unsigned ket) {
        assert(site < weights.size() - 1);
        return _get_site_intex(weights[site +1], weights[site], ket);
    }

}


namespace onerut_normal_operator {

    KronDomain::KronDomain(std::vector<std::shared_ptr<const Domain> > domains) :
    domains(domains),
    domain_sizes(domains_2_domain_sizes(domains)),
    weights(domain_sizes_2_weights(domain_sizes)) {
        print_vector(domain_sizes); //debug TODO delete
        print_vector(weights); //debug
    }

    unsigned KronDomain::size() const {
        return weights.front();
    }

    std::string KronDomain::state_name(unsigned index) const {
        std::string result;
        std::vector<std::string> site_state_names;
        for (unsigned site = 0; site < domains.size(); ++site) {
            const unsigned index_on_site = _get_site_intex(weights, site, index);
            site_state_names.push_back(domains[site]->state_name(index_on_site));
        }
        return boost::join(site_state_names, "x");
    }

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

