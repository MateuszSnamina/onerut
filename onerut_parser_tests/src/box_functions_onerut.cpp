#include<gtest/gtest.h>
#include<onerut_normal_operator/domain_abstract.hpp>
#include<onerut_normal_operator/domain_custom.hpp>
#include<onerut_normal_operator/domain_oscillator.hpp>
#include<onerut_normal_operator/domain_spin.hpp>
#include<onerut_normal_operator/domain_kron.hpp>
#include<onerut_parser/asset_ref_container.hpp>
#include<onerut_parser/function_factory_container.hpp>
#include<onerut_parser_tests/box_common.hpp>

#include "onerut_normal_operator/operator_simple.hpp"

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

TEST(boxFunctionsOnerut, customDomainTest0) {
    onerut_parser::FunctionFactoryContainer::global_instance().clear();
    onerut_parser::FunctionFactoryContainer::global_instance().put_all();
    onerut_parser::AssetRefContainer::global_instance().clear();
    // -------
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, custom_domain(5, 6));
    // -------
    const auto domain_asset = inuput_2_asset("custom_domain(xxx, yyy)");
    ASSERT_TRUE(domain_asset);
    const auto domain_asset_deref = domain_asset->deref();
    ASSERT_TRUE(domain_asset_deref.is_either_value_or_type());
    const auto domain = domain_asset_deref.typed_value_or_empty<onerut_normal_operator::CustomDomain>();
    ASSERT_TRUE(domain);
    ASSERT_EQ(2, (*domain)->size());
    EXPECT_EQ("xxx", (*domain)->state_name(0));
    EXPECT_EQ("yyy", (*domain)->state_name(1));
    // -------
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, custom_domain(xxx, yyy));
    // -------
    {
        const auto state_index_0_asset = inuput_2_asset("xxx");
        ASSERT_TRUE(state_index_0_asset);
        const auto state_index_0_asset_deref = state_index_0_asset->deref();
        ASSERT_TRUE(state_index_0_asset_deref.is_either_value_or_type());
        const auto state_index_0 = state_index_0_asset_deref.typed_value_or_empty<onerut_normal_operator::StateIndex>();
        ASSERT_TRUE(state_index_0);
        EXPECT_EQ(0, (*state_index_0)->index);
        EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(**domain, *(*state_index_0)->domain));
        EXPECT_EQ("xxx", (*state_index_0)->fetch_name());
    }
    // -------
    {
        const auto state_index_1_asset = inuput_2_asset("yyy");
        ASSERT_TRUE(state_index_1_asset);
        const auto state_index_1_asset_deref = state_index_1_asset->deref();
        ASSERT_TRUE(state_index_1_asset_deref.is_either_value_or_type());
        const auto state_index_1 = state_index_1_asset_deref.typed_value_or_empty<onerut_normal_operator::StateIndex>();
        ASSERT_TRUE(state_index_1);
        EXPECT_EQ(1, (*state_index_1)->index);
        EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(**domain, *(*state_index_1)->domain));
        ASSERT_EQ("yyy", (*state_index_1)->fetch_name());
    }
    // -------
    {
        const auto state_index_1_asset = inuput_2_asset("yyy");
        ASSERT_TRUE(state_index_1_asset);
        const auto state_index_1_asset_deref = state_index_1_asset->deref();
        ASSERT_TRUE(state_index_1_asset_deref.is_either_value_or_type());
        const auto state_index_1 = state_index_1_asset_deref.typed_value_or_empty<onerut_normal_operator::StateIndex>();
        ASSERT_TRUE(state_index_1);
        EXPECT_EQ(1, (*state_index_1)->index);
        EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(**domain, *(*state_index_1)->domain));
        ASSERT_EQ("yyy", (*state_index_1)->fetch_name());
    }
}

TEST(boxFunctionsOnerut, customDomainTest1) {
    onerut_parser::FunctionFactoryContainer::global_instance().clear();
    onerut_parser::FunctionFactoryContainer::global_instance().put_all();
    onerut_parser::AssetRefContainer::global_instance().clear();
    // -------
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, custom_domain(5, 6));
    // -------
    const auto domain_asset = inuput_2_asset("dom := custom_domain(xxx, yyy)");
    ASSERT_TRUE(domain_asset);
    const auto domain_asset_deref = domain_asset->deref();
    ASSERT_TRUE(domain_asset_deref.is_either_value_or_type());
    const auto domain = domain_asset_deref.typed_value_or_empty<onerut_normal_operator::CustomDomain>();
    ASSERT_TRUE(domain);
    ASSERT_EQ(2, (*domain)->size());
    EXPECT_EQ("xxx", (*domain)->state_name(0));
    EXPECT_EQ("yyy", (*domain)->state_name(1));
    // -------
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, custom_domain(xxx, yyy));
    // -------
    {
        const auto state_index_0_asset = inuput_2_asset("xxx");
        ASSERT_TRUE(state_index_0_asset);
        const auto state_index_0_asset_deref = state_index_0_asset->deref();
        ASSERT_TRUE(state_index_0_asset_deref.is_either_value_or_type());
        const auto state_index_0 = state_index_0_asset_deref.typed_value_or_empty<onerut_normal_operator::StateIndex>();
        ASSERT_TRUE(state_index_0);
        EXPECT_EQ(0, (*state_index_0)->index);
        EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(**domain, *(*state_index_0)->domain));
        EXPECT_EQ("xxx", (*state_index_0)->fetch_name());
    }
    // -------
    {
        const auto state_index_1_asset = inuput_2_asset("yyy");
        ASSERT_TRUE(state_index_1_asset);
        const auto state_index_1_asset_deref = state_index_1_asset->deref();
        ASSERT_TRUE(state_index_1_asset_deref.is_either_value_or_type());
        const auto state_index_1 = state_index_1_asset_deref.typed_value_or_empty<onerut_normal_operator::StateIndex>();
        ASSERT_TRUE(state_index_1);
        EXPECT_EQ(1, (*state_index_1)->index);
        EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(**domain, *(*state_index_1)->domain));
        ASSERT_EQ("yyy", (*state_index_1)->fetch_name());
    }
    // -------
    {
        const auto re_dom_asset = inuput_2_asset("dom");
        ASSERT_TRUE(re_dom_asset);
        const auto re_dom_asset_deref = re_dom_asset->deref();
        ASSERT_TRUE(re_dom_asset_deref.is_either_value_or_type());
        const auto re_dom = re_dom_asset_deref.typed_value_or_empty<onerut_normal_operator::CustomDomain>();
        ASSERT_TRUE(re_dom);
        EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(**domain, **re_dom));
    }
    // -------
    {
        const auto re_state_index_0_asset = inuput_2_asset("state_index(dom,0)");
        ASSERT_TRUE(re_state_index_0_asset);
        const auto re_state_index_0_asset_deref = re_state_index_0_asset->deref();
        ASSERT_TRUE(re_state_index_0_asset_deref.is_either_value_or_type());
        const auto re_state_index_0 = re_state_index_0_asset_deref.typed_value_or_empty<onerut_normal_operator::StateIndex>();
        ASSERT_TRUE(re_state_index_0);
        EXPECT_EQ(0, (*re_state_index_0)->index);
        EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(**domain, *(*re_state_index_0)->domain));
        EXPECT_EQ("xxx", (*re_state_index_0)->fetch_name());
    }
    // -------
    ONERUT_BOX_ERROR_TEST(ArgumentDomainError, state_index(dom, -1));
    ONERUT_BOX_ERROR_TEST(ArgumentDomainError, state_index(dom, 2));
}

TEST(boxFunctionsOnerut, oscillatorDomainTest0) {
    onerut_parser::FunctionFactoryContainer::global_instance().clear();
    onerut_parser::FunctionFactoryContainer::global_instance().put_all();
    onerut_parser::AssetRefContainer::global_instance().clear();
    // -------
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, oscillator_domain(2.6));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, oscillator_domain(2.6, 45));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, oscillator_domain());
    ONERUT_BOX_ERROR_TEST(ArgumentDomainError, oscillator_domain(0));
    ONERUT_BOX_ERROR_TEST(ArgumentDomainError, oscillator_domain(-1));
    // -------
    const auto domain_asset = inuput_2_asset("dom := oscillator_domain(2)");
    ASSERT_TRUE(domain_asset);
    const auto domain_asset_deref = domain_asset->deref();
    ASSERT_TRUE(domain_asset_deref.is_either_value_or_type());
    const auto domain = domain_asset_deref.typed_value_or_empty<onerut_normal_operator::OscillatorDomain>();
    ASSERT_TRUE(domain);
    ASSERT_EQ(2, (*domain)->size());
    // -------
    {
        const auto re_dom_asset = inuput_2_asset("dom");
        ASSERT_TRUE(re_dom_asset);
        const auto re_dom_asset_deref = re_dom_asset->deref();
        ASSERT_TRUE(re_dom_asset_deref.is_either_value_or_type());
        const auto re_dom = re_dom_asset_deref.typed_value_or_empty<onerut_normal_operator::OscillatorDomain>();
        ASSERT_TRUE(re_dom);
        EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(**domain, **re_dom));
    }
    // -------
    {
        const auto re_state_index_0_asset = inuput_2_asset("state_index(dom,0)");
        ASSERT_TRUE(re_state_index_0_asset);
        const auto re_state_index_0_asset_deref = re_state_index_0_asset->deref();
        ASSERT_TRUE(re_state_index_0_asset_deref.is_either_value_or_type());
        const auto re_state_index_0 = re_state_index_0_asset_deref.typed_value_or_empty<onerut_normal_operator::StateIndex>();
        ASSERT_TRUE(re_state_index_0);
        EXPECT_EQ(0, (*re_state_index_0)->index);
        EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(**domain, *(*re_state_index_0)->domain));
        EXPECT_EQ("nu_0", (*re_state_index_0)->fetch_name());
    }
    // -------
    {
        const auto re_state_index_1_asset = inuput_2_asset("state_index(dom,1)");
        ASSERT_TRUE(re_state_index_1_asset);
        const auto re_state_index_1_asset_deref = re_state_index_1_asset->deref();
        ASSERT_TRUE(re_state_index_1_asset_deref.is_either_value_or_type());
        const auto re_state_index_1 = re_state_index_1_asset_deref.typed_value_or_empty<onerut_normal_operator::StateIndex>();
        ASSERT_TRUE(re_state_index_1);
        EXPECT_EQ(1, (*re_state_index_1)->index);
        EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(**domain, *(*re_state_index_1)->domain));
        EXPECT_EQ("nu_1", (*re_state_index_1)->fetch_name());
    }
}

TEST(boxFunctionsOnerut, spinDomainTest0) {
    onerut_parser::FunctionFactoryContainer::global_instance().clear();
    onerut_parser::FunctionFactoryContainer::global_instance().put_all();
    onerut_parser::AssetRefContainer::global_instance().clear();
    // -------
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, spin_domain(2.6));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, spin_domain(2.6, 45));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, spin_domain());
    ONERUT_BOX_ERROR_TEST(ArgumentDomainError, spin_domain(0));
    ONERUT_BOX_ERROR_TEST(ArgumentDomainError, spin_domain(-1));
    // -------
    const auto domain_asset = inuput_2_asset("dom := spin_domain(2)");
    ASSERT_TRUE(domain_asset);
    const auto domain_asset_deref = domain_asset->deref();
    ASSERT_TRUE(domain_asset_deref.is_either_value_or_type());
    const auto domain = domain_asset_deref.typed_value_or_empty<onerut_normal_operator::SpinDomain>();
    ASSERT_TRUE(domain);
    ASSERT_EQ(2, (*domain)->size());
    // -------
    {
        const auto re_dom_asset = inuput_2_asset("dom");
        ASSERT_TRUE(re_dom_asset);
        const auto re_dom_asset_deref = re_dom_asset->deref();
        ASSERT_TRUE(re_dom_asset_deref.is_either_value_or_type());
        const auto re_dom = re_dom_asset_deref.typed_value_or_empty<onerut_normal_operator::SpinDomain>();
        ASSERT_TRUE(re_dom);
        EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(**domain, **re_dom));
    }
    // -------
    {
        const auto re_state_index_0_asset = inuput_2_asset("state_index(dom,0)");
        ASSERT_TRUE(re_state_index_0_asset);
        const auto re_state_index_0_asset_deref = re_state_index_0_asset->deref();
        ASSERT_TRUE(re_state_index_0_asset_deref.is_either_value_or_type());
        const auto re_state_index_0 = re_state_index_0_asset_deref.typed_value_or_empty<onerut_normal_operator::StateIndex>();
        ASSERT_TRUE(re_state_index_0);
        EXPECT_EQ(0, (*re_state_index_0)->index);
        EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(**domain, *(*re_state_index_0)->domain));
        EXPECT_EQ("UUp", (*re_state_index_0)->fetch_name());
    }
    // -------
    {
        const auto re_state_index_1_asset = inuput_2_asset("state_index(dom,1)");
        ASSERT_TRUE(re_state_index_1_asset);
        const auto re_state_index_1_asset_deref = re_state_index_1_asset->deref();
        ASSERT_TRUE(re_state_index_1_asset_deref.is_either_value_or_type());
        const auto re_state_index_1 = re_state_index_1_asset_deref.typed_value_or_empty<onerut_normal_operator::StateIndex>();
        ASSERT_TRUE(re_state_index_1);
        EXPECT_EQ(1, (*re_state_index_1)->index);
        EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(**domain, *(*re_state_index_1)->domain));
        EXPECT_EQ("DDown", (*re_state_index_1)->fetch_name());
    }
}

TEST(boxFunctionsOnerut, kronDomainTest0) {
    onerut_parser::FunctionFactoryContainer::global_instance().clear();
    onerut_parser::FunctionFactoryContainer::global_instance().put_all();
    onerut_parser::AssetRefContainer::global_instance().clear();
    // -------
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, kron_domain(2.6));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, kron_domain(2.6, 45));
    // -------
    const auto subdomain_0_asset = inuput_2_asset("subdom_0 := spin_domain(3)");
    ASSERT_TRUE(subdomain_0_asset);
    const auto subdomain_0_asset_deref = subdomain_0_asset->deref();
    ASSERT_TRUE(subdomain_0_asset_deref.is_either_value_or_type());
    const auto subdomain_0 = subdomain_0_asset_deref.typed_value_or_empty<onerut_normal_operator::SpinDomain>();
    ASSERT_TRUE(subdomain_0);
    ASSERT_EQ(3, (*subdomain_0)->size());
    // -------
    const auto subdomain_1_asset = inuput_2_asset("subdom_1 := custom_domain(xx, yy)");
    ASSERT_TRUE(subdomain_1_asset);
    const auto subdomain_1_asset_deref = subdomain_1_asset->deref();
    ASSERT_TRUE(subdomain_1_asset_deref.is_either_value_or_type());
    const auto subdomain_1 = subdomain_1_asset_deref.typed_value_or_empty<onerut_normal_operator::CustomDomain>();
    ASSERT_TRUE(subdomain_1);
    ASSERT_EQ(2, (*subdomain_1)->size());
    // -------
    const auto domain_asset = inuput_2_asset("dom := kron_domain(subdom_0, subdom_1)");
    ASSERT_TRUE(domain_asset);
    const auto domain_asset_deref = domain_asset->deref();
    ASSERT_TRUE(domain_asset_deref.is_either_value_or_type());
    const auto domain = domain_asset_deref.typed_value_or_empty<onerut_normal_operator::KronDomain>();
    ASSERT_TRUE(domain);
    ASSERT_EQ(3 * 2, (*domain)->size());
    ASSERT_EQ(2, (*domain)->subdomains.size());
    EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(**subdomain_0, *(*domain)->subdomains[0]));
    EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(**subdomain_1, *(*domain)->subdomains[1]));
    // -------
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, kron_placeholders(2.6, 45));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, kron_placeholders(dom, 45));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, kron_placeholders(dom, _0));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, kron_placeholders(dom, _0, _1, _2));
    // -------
    const auto kron_placeholders_asset = inuput_2_asset("kron_placeholders(dom, _0, _1)");
    ASSERT_TRUE(kron_placeholders_asset);
    const auto kron_placeholders_asset_deref = domain_asset->deref();
    ASSERT_TRUE(kron_placeholders_asset_deref.is_either_value_or_type());
    // -------
    {
        const auto placeholders_0_asset = inuput_2_asset("_0");
        ASSERT_TRUE(placeholders_0_asset);
        const auto placeholders_0_asset_deref = placeholders_0_asset->deref();
        ASSERT_TRUE(placeholders_0_asset_deref.is_either_value_or_type());
        const auto placeholders_0 = placeholders_0_asset_deref.typed_value_or_empty<onerut_normal_operator::KronPlaceholder>();
        ASSERT_TRUE(placeholders_0);
        EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(**domain, *(*placeholders_0)->domain));
        EXPECT_EQ(0, (*placeholders_0)->place);
    }
    // -------
    {
        const auto placeholders_1_asset = inuput_2_asset("_1");
        ASSERT_TRUE(placeholders_1_asset);
        const auto placeholders_1_asset_deref = placeholders_1_asset->deref();
        ASSERT_TRUE(placeholders_1_asset_deref.is_either_value_or_type());
        const auto placeholders_1 = placeholders_1_asset_deref.typed_value_or_empty<onerut_normal_operator::KronPlaceholder>();
        ASSERT_TRUE(placeholders_1);
        EXPECT_TRUE(onerut_normal_operator::are_the_same_domains(**domain, *(*placeholders_1)->domain));
        EXPECT_EQ(1, (*placeholders_1)->place);
    }
}

TEST(boxFunctionsOnerut, diagOperatorTest0) {
    onerut_parser::FunctionFactoryContainer::global_instance().clear();
    onerut_parser::FunctionFactoryContainer::global_instance().put_all();
    onerut_parser::AssetRefContainer::global_instance().clear();
    // -------
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, diag(3));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, diag(3, 7, 8));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, diag(xxx, state_index(custom_domain(xx0, yy0), 0)));
    // -------
    const auto domain_asset = inuput_2_asset("dom := custom_domain(xx1, yy1)");
    ASSERT_TRUE(domain_asset);
    const auto domain_asset_deref = domain_asset->deref();
    ASSERT_TRUE(domain_asset_deref.is_either_value_or_type());
    const auto domain = domain_asset_deref.typed_value_or_empty<onerut_normal_operator::CustomDomain>();
    ASSERT_TRUE(domain);
    ASSERT_EQ(2, (*domain)->size());
    // -------
    const auto operator_diag_asset = inuput_2_asset("diag(4.0, state_index(dom,1))");
    ASSERT_TRUE(operator_diag_asset);
    const auto operator_diag_asset_deref = operator_diag_asset->deref();
    ASSERT_TRUE(operator_diag_asset_deref.is_either_value_or_type());
    const auto operator_diag = operator_diag_asset_deref.typed_value_or_empty<onerut_normal_operator::AbstractOperator>();
    ASSERT_TRUE(operator_diag);
    ASSERT_TRUE(onerut_normal_operator::are_the_same_domains(**domain, *(*operator_diag)->get_domain()));
    const auto operator_diag_typed = std::dynamic_pointer_cast<const onerut_normal_operator::DiagOperator>(*operator_diag);
    ASSERT_TRUE(operator_diag_typed);
}

TEST(boxFunctionsOnerut, hopOperatorTest0) {
    onerut_parser::FunctionFactoryContainer::global_instance().clear();
    onerut_parser::FunctionFactoryContainer::global_instance().put_all();
    onerut_parser::AssetRefContainer::global_instance().clear();
    // -------
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, hop(3, 7));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, hop(3, 7, 8, 9));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, hop(xxx, state_index(custom_domain(xx0), 0), state_index(custom_domain(xx1), 0)));
    ONERUT_BOX_ERROR_TEST(ArgumentDomainError, hop(4.0, state_index(custom_domain(xx2), 0), state_index(custom_domain(xx3), 0)));
    // -------
    const auto domain_asset = inuput_2_asset("dom := custom_domain(xx, yy)");
    ASSERT_TRUE(domain_asset);
    const auto domain_asset_deref = domain_asset->deref();
    ASSERT_TRUE(domain_asset_deref.is_either_value_or_type());
    const auto domain = domain_asset_deref.typed_value_or_empty<onerut_normal_operator::CustomDomain>();
    ASSERT_TRUE(domain);
    ASSERT_EQ(2, (*domain)->size());
    // -------
    //////  ONERUT_BOX_ERROR_TEST(ArgumentDomainError, hop(4.0, state_index(dom, 0), state_index(dom, 0))); // TODO make the code so that test passes and uncomment the test
    // -------
    const auto operator_hop_asset = inuput_2_asset("hop(4.0, state_index(dom,0), state_index(dom,1))");
    ASSERT_TRUE(operator_hop_asset);
    const auto operator_hop_asset_deref = operator_hop_asset->deref();
    ASSERT_TRUE(operator_hop_asset_deref.is_either_value_or_type());
    const auto operator_hop = operator_hop_asset_deref.typed_value_or_empty<onerut_normal_operator::AbstractOperator>();
    ASSERT_TRUE(operator_hop);
    ASSERT_TRUE(onerut_normal_operator::are_the_same_domains(**domain, *(*operator_hop)->get_domain()));
    const auto operator_hop_typed = std::dynamic_pointer_cast<const onerut_normal_operator::HopOperator>(*operator_hop);
    ASSERT_TRUE(operator_hop_typed);
}

TEST(boxFunctionsOnerut, oscillatorOperatorTest0) {
    onerut_parser::FunctionFactoryContainer::global_instance().clear();
    onerut_parser::FunctionFactoryContainer::global_instance().put_all();
    onerut_parser::AssetRefContainer::global_instance().clear();
    // -------
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cr());
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, cr(3, 5.));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, cr(3));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, cr(custom_domain(xx0, yy0)));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, an());
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, an(3, 5.));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, an(3));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, an(custom_domain(xx1, yy1)));
}

TEST(boxFunctionsOnerut, spinOperatorTest0) {
    onerut_parser::FunctionFactoryContainer::global_instance().clear();
    onerut_parser::FunctionFactoryContainer::global_instance().put_all();
    onerut_parser::AssetRefContainer::global_instance().clear();
    // -------
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, Sp());
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, Sp(3, 5.));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, Sp(3));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, Sp(custom_domain(xx0, yy0)));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, Sm());
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, Sm(3, 5.));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, Sm(3));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, Sm(custom_domain(xx1, yy1)));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, Sz());
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, Sz(3, 5.));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, Sz(3));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, Sz(custom_domain(xx2, yy2)));
}

TEST(boxFunctionsOnerut, opPlusMinusTest0) {
    onerut_parser::FunctionFactoryContainer::global_instance().clear();
    onerut_parser::FunctionFactoryContainer::global_instance().put_all();
    onerut_parser::AssetRefContainer::global_instance().clear();
    // -------
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, eye(custom_domain(xx0, yy0)) + 4);
    ONERUT_BOX_ERROR_TEST(ArgumentDomainError, eye(custom_domain(xx1, yy1)) + eye(custom_domain(xx2, yy2)));
    ONERUT_BOX_ERROR_TEST(ArgumentDomainError, eye(custom_domain(xx3, yy3)) - eye(custom_domain(xx4, yy4)));
}

TEST(boxFunctionsOnerut, opProdTest0) {
    onerut_parser::FunctionFactoryContainer::global_instance().clear();
    onerut_parser::FunctionFactoryContainer::global_instance().put_all();
    onerut_parser::AssetRefContainer::global_instance().clear();
    // -------
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, eye(custom_domain(xx0, yy0)) * 4);
    ONERUT_BOX_ERROR_TEST(ArgumentDomainError, eye(custom_domain(xx1, yy1)) * eye(custom_domain(xx2, yy2)));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, eye(custom_domain(xx3, yy3)) / eye(custom_domain(xx4, yy4)));
}

TEST(boxFunctionsOnerut, eigdTest0) {
    onerut_parser::FunctionFactoryContainer::global_instance().clear();
    onerut_parser::FunctionFactoryContainer::global_instance().put_all();
    onerut_parser::AssetRefContainer::global_instance().clear();
    // -------
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, eigd());
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, eigd(2.6, 7, 8, 8));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, eigd(2.6));
}

TEST(boxFunctionsOnerut, eigsTest0) {
    onerut_parser::FunctionFactoryContainer::global_instance().clear();
    onerut_parser::FunctionFactoryContainer::global_instance().put_all();
    onerut_parser::AssetRefContainer::global_instance().clear();
    // -------
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, eigs(2.6));
    ONERUT_BOX_ERROR_TEST(WrongNumberOfArgumentsError, eigs(2.6, 7, 8, 8));
    ONERUT_BOX_ERROR_TEST(ArgumentMismatchError, eigs(2.6, 7.5));
    ONERUT_BOX_ERROR_TEST(ArgumentDomainError, eigs(eye(custom_domain(xx0, yy0)), 5));
    ONERUT_BOX_ERROR_TEST(ArgumentDomainError, eigs(eye(custom_domain(xx1, yy1)), 2));
    ONERUT_BOX_ERROR_TEST(ArgumentDomainError, eigs(eye(custom_domain(xx2, yy2)), 0));
    ONERUT_BOX_ERROR_TEST(ArgumentDomainError, eigs(eye(custom_domain(xx3, yy3)), -1));
}
