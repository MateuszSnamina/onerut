#include<cassert>
//#include<algorithm>//TODO delete
#include<boost/numeric/conversion/cast.hpp>
#include<boost/algorithm/string.hpp>

#include<onerut_normal_operator/share_from.hpp>
#include<onerut_normal_operator/utility_fock.hpp>
#include<onerut_normal_operator/domain_fock.hpp>

namespace {
    //
    //    std::vector<uint32_t> domains_2_domain_sizes(
    //            const std::vector<std::shared_ptr<const onerut_normal_operator::Domain> > & domains) {
    //        std::vector<uint32_t> domain_sizes;
    //        std::transform(
    //                cbegin(domains), cend(domains),
    //                std::back_inserter(domain_sizes),
    //                [](const auto & domain) {
    //                    return domain->size();
    //                }
    //        );
    //        return domain_sizes;
    //    }
    //
    //    std::vector<uint32_t> domain_sizes_2_weights(
    //            const std::vector<uint32_t> & domain_sizes) {
    //        std::vector<uint32_t> weights(domain_sizes.size() + 1);
    //        weights.back() = 1;
    //        std::partial_sum(
    //                crbegin(domain_sizes), crend(domain_sizes),
    //                rbegin(weights) + 1, std::multiplies<uint32_t>());
    //        return weights;
    //    }

}

namespace onerut_normal_operator {

    // -------------------------------------------------------------------------
    // --------------  Domain  -------------------------------------------------
    // -------------------------------------------------------------------------

    FockDomain::FockDomain(uint32_t n_particles, const std::vector<std::string> & orbital_names) :
    n_particles(n_particles),
    orbital_names(orbital_names) {
        assert(n_particles > 0);
        assert(n_particles <= boost::numeric_cast<uint32_t>(orbital_names.size()));
    }

    uint32_t FockDomain::size() const {
        return utility::binomial_coefficient(orbital_names.size(), n_particles);
    }

    std::string FockDomain::state_name(uint32_t index) const {
        assert(index < size());
        std::vector<std::string> occupied_orbital_names;
        //        for (uint32_t place = 0; place < subdomains.size(); ++place) {
        //            const uint32_t index_on_site = utility::get_sub_index(*this, place, index);
        //            site_state_names.push_back(subdomains[place]->state_name(index_on_site));
        //        }
        const auto n_orbitals = boost::numeric_cast<uint32_t>(orbital_names.size());
        const auto decoded = utility::decode(n_particles, n_orbitals, index);
        return utility::vector_of_bool_to_string(decoded);
        //+ std::to_string(utility::encode(decoded, n_particles));
        //boost::join(occupied_orbital_names, "&"); //TODO
    }

    std::unique_ptr<OrbitalIndex> FockDomain::crate_orbital_index(uint32_t index) const {
        assert(index < orbital_names.size());

        return std::unique_ptr<OrbitalIndex>(new OrbitalIndex{shared_from(this), index});
    }

    // -------------------------------------------------------------------------
    // --------------  OrbitalIndex  -------------------------------------------
    // -------------------------------------------------------------------------

    OrbitalIndex::OrbitalIndex(std::shared_ptr<const FockDomain> domain, uint32_t index) :
    domain(domain),
    index(index) {

        assert(index < domain->orbital_names.size());
    }

    std::string OrbitalIndex::fetch_name() const {
        return domain->orbital_names[index];
    }
}