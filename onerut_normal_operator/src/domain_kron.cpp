#include<cassert>
#include<algorithm>
#include<numeric> // std::partial_sum
#include<functional> // std::multiplies
#include<boost/algorithm/string.hpp>

#include<onerut_normal_operator/share_from.hpp>
#include<onerut_normal_operator/utility_kron.hpp>
#include<onerut_normal_operator/domain_kron.hpp>

namespace {

    std::vector<uint32_t> domains_2_domain_sizes(
            const std::vector<std::shared_ptr<const onerut_normal_operator::Domain> > & domains) {
        std::vector<uint32_t> domain_sizes;
        std::transform(
                cbegin(domains), cend(domains),
                std::back_inserter(domain_sizes),
                [](const auto & domain) {
                    return domain->size();
                }
        );
        return domain_sizes;
    }

    std::vector<uint32_t> domain_sizes_2_weights(
            const std::vector<uint32_t> & domain_sizes) {
        std::vector<uint32_t> weights(domain_sizes.size() + 1);
        weights.back() = 1;
        std::partial_sum(
                crbegin(domain_sizes), crend(domain_sizes),
                rbegin(weights) + 1, std::multiplies<uint32_t>());
        return weights;
    }

}

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // --------------  Domain  -------------------------------------------------
    // -------------------------------------------------------------------------

    KronDomain::KronDomain(std::vector<std::shared_ptr<const Domain> > domains) :
    domains(domains),
    domain_sizes(domains_2_domain_sizes(domains)),
    weights(domain_sizes_2_weights(domain_sizes)) {
    }

    uint32_t KronDomain::size() const {
        return weights.front();
    }

    std::string KronDomain::state_name(uint32_t index) const {
        assert(index <= size());
        std::string result;
        std::vector<std::string> site_state_names;
        for (uint32_t site = 0; site < domains.size(); ++site) {
            const uint32_t index_on_site = utility::_get_site_intex(weights, site, index);
            site_state_names.push_back(domains[site]->state_name(index_on_site));
        }
        return boost::join(site_state_names, ":");
    }

    std::unique_ptr<KronPlaceholder> KronDomain::crate_placeholder(uint32_t place) const {
        assert(place <= domains.size());
        return std::unique_ptr<KronPlaceholder>(new KronPlaceholder{shared_from(this), place});
    }

    // -------------------------------------------------------------------------
    // --------------  Placeholder  --------------------------------------------
    // -------------------------------------------------------------------------

    KronPlaceholder::KronPlaceholder(std::shared_ptr<const KronDomain> domain, uint32_t place) :
    domain(domain),
    place(place) {
        assert(place <= domain->domains.size());
    }

    std::shared_ptr<const Domain> KronPlaceholder::fetch_domain() const {
        return domain->domains[place];
    }

}

