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

    template<typename _BraKetT>
    class HopOperator : public AbstractOperator<_BraKetT> {
    public:
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;     
        using IteratorT = SimpleOperatorIterator<BraKetT>;
        HopOperator(double value, const BraKetT &site_1, const BraKetT &site_2);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
    private:
        const double value;
        const BraKetT site_1;
        const BraKetT site_2;
    };

    template<typename _BraKetT>
    class DiagOperator : public AbstractOperator<_BraKetT> {
    public:
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;  
        using IteratorT = SimpleOperatorIterator<BraKetT>;
        DiagOperator(double value, const BraKetT &site);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
    private:
        const double value;
        const BraKetT site;
    };
       
    // -------------------------------------------------------------------------
    // ------------------ SIMPLE OPERATOR - IMPLEMENTATION ---------------------
    // -------------------------------------------------------------------------     

    template<typename _BraKetT>
    HopOperator<_BraKetT>::HopOperator(double value, const BraKetT& site_1, const BraKetT& site_2) :
    value(value),
    site_1(site_1),
    site_2(site_2) {
        assert(site_1 != site_2);
    }

    template<typename _BraKetT>
    typename HopOperator<_BraKetT>::AbstractIteratorPtrT
    HopOperator<_BraKetT>::begin_itptr(const BraKetT& ket) const {
        if (ket == site_1) {
            return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(value, site_2)));
        } else if (ket == site_2) {
            return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(value, site_1)));
        }
        return std::make_unique<IteratorT>(IteratorT::create_end_iterator());
    }

    // -------------------------------------------------------------------------        

    template<typename _BraKetT>
    DiagOperator<_BraKetT>::DiagOperator(double value, const BraKetT &site) :
    value(value),
    site(site) {
    }

    template<typename _BraKetT>
    typename DiagOperator<_BraKetT>::AbstractIteratorPtrT
    DiagOperator<_BraKetT>::begin_itptr(const BraKetT& ket) const {
        if (ket == site) {
            return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(value, site)));
        }
        return std::make_unique<IteratorT>(IteratorT::create_end_iterator());
    }

}

#endif
