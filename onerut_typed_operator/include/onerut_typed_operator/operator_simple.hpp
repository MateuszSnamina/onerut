#ifndef ONERUT_TYPED_OPERATOR_OPERATOR_SIMPLE
#define ONERUT_TYPED_OPERATOR_OPERATOR_SIMPLE

#include<utility>
#include<optional>

#include<onerut_typed_operator/operator_abstract.hpp>
#include<onerut_typed_operator/iterator_simple.hpp>

namespace onerut_typed_operator {

    // -------------------------------------------------------------------------
    // ------------------ SIMPLE OPERATOR --------------------------------------
    // -------------------------------------------------------------------------        

    template<typename _ScalarT, typename _BraKetT>
    class HopOperator : public AbstractOperator<_ScalarT, _BraKetT> {
    public:
        using ScalarT = _ScalarT;
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<ScalarT, BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = SimpleOperatorIterator<ScalarT, BraKetT>;
        HopOperator(ScalarT value, const BraKetT &site_1, const BraKetT &site_2);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
    private:
        const ScalarT value;
        const BraKetT site_1;
        const BraKetT site_2;
    };

    template<typename _ScalarT, typename _BraKetT>
    class DiagOperator : public AbstractOperator<_ScalarT, _BraKetT> {
    public:
        using ScalarT = _ScalarT;
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<ScalarT, BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = SimpleOperatorIterator<ScalarT, BraKetT>;
        DiagOperator(ScalarT value, const BraKetT &site);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
    private:
        const ScalarT value;
        const BraKetT site;
    };

    // -------------------------------------------------------------------------
    // ------------------ SIMPLE OPERATOR - IMPLEMENTATION ---------------------
    // -------------------------------------------------------------------------     

    template<typename _ScalarT, typename _BraKetT>
    HopOperator<_ScalarT, _BraKetT>::HopOperator(ScalarT value, const BraKetT& site_1, const BraKetT& site_2) :
    value(value),
    site_1(site_1),
    site_2(site_2) {
        assert(site_1 != site_2);
    }

    template<typename _ScalarT, typename _BraKetT>
    typename HopOperator<_ScalarT, _BraKetT>::AbstractIteratorPtrT
    HopOperator<_ScalarT, _BraKetT>::begin_itptr(const BraKetT& ket) const {
        if (ket == site_1) {
            return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(value, site_2)));
        } else if (ket == site_2) {
            return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(value, site_1)));
        }
        return std::make_unique<IteratorT>(IteratorT::create_end_iterator());
    }

    // -------------------------------------------------------------------------        

    template<typename _ScalarT, typename _BraKetT>
    DiagOperator<_ScalarT, _BraKetT>::DiagOperator(ScalarT value, const BraKetT &site) :
    value(value),
    site(site) {
    }

    template<typename _ScalarT, typename _BraKetT>
    typename DiagOperator<_ScalarT, _BraKetT>::AbstractIteratorPtrT
    DiagOperator<_ScalarT, _BraKetT>::begin_itptr(const BraKetT& ket) const {
        if (ket == site) {
            return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(value, site)));
        }
        return std::make_unique<IteratorT>(IteratorT::create_end_iterator());
    }

}

#endif
