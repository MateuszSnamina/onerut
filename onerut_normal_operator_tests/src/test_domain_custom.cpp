#include<gtest/gtest.h>

#include<onerut_normal_operator/domain_custom.hpp>
#include<onerut_normal_operator/domain_kron.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(testDomainKron, test0) {
    using DomainT = onerut_normal_operator::Domain;
    using DomainPtrT = std::shared_ptr<const DomainT>;
    using CustomDomainT = onerut_normal_operator::CustomDomain;
    using KronDomainT = onerut_normal_operator::KronDomain;
    const auto subdomain0 = std::make_shared<CustomDomainT>(std::vector<std::string>{"AA", "BB"});
    const auto subdomain1 = std::make_shared<CustomDomainT>(std::vector<std::string>{"aaa", "bb", "c"});
    const auto subdomain2 = std::make_shared<CustomDomainT>(std::vector<std::string>{"alpha"});
    const auto domain = std::make_shared<KronDomainT>(std::vector<DomainPtrT>{subdomain0, subdomain1, subdomain2});
    EXPECT_EQ(2 * 3 * 1, domain->size());
    std::vector<std::string> expected_names{
        "AA:aaa:alpha",
        "AA:bb:alpha",
        "AA:c:alpha",
        "BB:aaa:alpha",
        "BB:bb:alpha",
        "BB:c:alpha"};
    EXPECT_EQ(expected_names[0], domain->state_name(0));
    EXPECT_EQ(expected_names[1], domain->state_name(1));
    EXPECT_EQ(expected_names[2], domain->state_name(2));
    EXPECT_EQ(expected_names[3], domain->state_name(3));
    EXPECT_EQ(expected_names[4], domain->state_name(4));
    EXPECT_EQ(expected_names[5], domain->state_name(5));
    EXPECT_EQ(expected_names, domain->state_names());
}

TEST(testDomainKron, test1) {
    using DomainT = onerut_normal_operator::Domain;
    using DomainPtrT = std::shared_ptr<const DomainT>;
    using CustomDomainT = onerut_normal_operator::CustomDomain;
    using KronDomainT = onerut_normal_operator::KronDomain;
    const auto subdomain0 = std::make_shared<CustomDomainT>(std::vector<std::string>{"AA", "BB"});
    const auto subdomain1 = std::make_shared<CustomDomainT>(std::vector<std::string>{});
    const auto subdomain2 = std::make_shared<CustomDomainT>(std::vector<std::string>{"aaa", "bb", "c"});
    const auto subdomain3 = std::make_shared<CustomDomainT>(std::vector<std::string>{"alpha"});
    const auto domain = std::make_shared<KronDomainT>(std::vector<DomainPtrT>{subdomain0, subdomain1, subdomain2, subdomain3});
    EXPECT_EQ(0, subdomain1->size());
    EXPECT_EQ(2 * 0 * 3 * 1, domain->size());
}