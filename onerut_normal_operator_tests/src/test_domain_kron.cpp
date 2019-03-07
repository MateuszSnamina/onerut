#include<gtest/gtest.h>

#include<onerut_normal_operator/domain_custom.hpp>

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(testDomainCustom, test0) {
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    EXPECT_EQ(4, domain->size());
    EXPECT_EQ("CC", domain->state_name(2));
    const auto created_state = domain->crate_state(2);
    ASSERT_TRUE(created_state);
    EXPECT_EQ(2, created_state->index);
    const auto created_state_domain = created_state->domain;
    ASSERT_TRUE(created_state_domain);
    EXPECT_EQ("CC", created_state->fetch_name());
    EXPECT_EQ(domain.get(), created_state_domain.get());
    EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(*domain, *created_state_domain));
}

TEST(testDomainCustom, test1) {
    using DomainT = onerut_normal_operator::CustomDomain;
    const auto domain0 = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto domain1 = std::make_shared<DomainT>(std::vector<std::string>{"AA", "BB", "CC", "DD"});
    const auto created_state0 = domain0->crate_state(2);
    const auto created_state1 = domain1->crate_state(2);
    ASSERT_TRUE(created_state0);
    ASSERT_TRUE(created_state1);
    const auto created_state_domain0 = created_state0->domain;
    const auto created_state_domain1 = created_state1->domain;
    ASSERT_TRUE(created_state_domain0);
    ASSERT_TRUE(created_state_domain1);
    EXPECT_FALSE(onerut_normal_operator::are_the_same_domains(*created_state_domain0, *created_state_domain1));
}

