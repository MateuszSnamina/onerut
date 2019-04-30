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

    KronDomain::KronDomain(const std::vector<std::shared_ptr<const Domain> > & domains) :
    subdomains(domains),
    subdomain_sizes(domains_2_domain_sizes(domains)),
    weights(domain_sizes_2_weights(subdomain_sizes)) {
    }

    uint32_t KronDomain::size() const {
        return weights.front();
    }

    std::string KronDomain::state_name(uint32_t index) const {
        assert(index < size());
        std::vector<std::string> site_state_names;
        for (uint32_t place = 0; place < subdomains.size(); ++place) {
            const uint32_t index_on_site = utility::get_sub_index(*this, place, index);
            site_state_names.push_back(subdomains[place]->state_name(index_on_site));
        }
        return boost::join(site_state_names, ":");
    }

    std::unique_ptr<KronPlaceholder> KronDomain::crate_placeholder(uint32_t place) const {
        assert(place < subdomains.size());
        return std::unique_ptr<KronPlaceholder>(new KronPlaceholder{shared_from(this), place});
    }

    uint32_t KronDomain::get_place_weight(unsigned place) const {
        assert(place < subdomains.size());
        return weights[place + 1];
    }

    uint32_t KronDomain::get_next_place_weight(unsigned place) const {
        assert(place < subdomains.size());
        return weights[place];
    }

    // -------------------------------------------------------------------------
    // --------------  Placeholder  --------------------------------------------
    // -------------------------------------------------------------------------

    KronPlaceholder::KronPlaceholder(std::shared_ptr<const KronDomain> domain, uint32_t place) :
    domain(domain),
    place(place) {
        assert(place < domain->subdomains.size());
    }

    std::shared_ptr<const Domain> KronPlaceholder::fetch_subdomain() const {
        return domain->subdomains[place];
    }

}

