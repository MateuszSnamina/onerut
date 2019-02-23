#ifndef ONERUT_OPERATOR_SIMPLE
#define ONERUT_OPERATOR_SIMPLE

#include<utility>
#include<optional>

#include<onerut_operator/operator_abstract.hpp>

namespace onerut_operator {

    // -------------------------------------------------------------------------
    // ------------------ SIMPLE OPERATOR --------------------------------------
    // -------------------------------------------------------------------------        

    template<typename _BraKetT>
    class SimpleOperatorIterator : public AbstractResultIterator<_BraKetT> {
    public:
        using BraKetT = _BraKetT;        
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;        
        using Iterator = SimpleOperatorIterator<BraKetT>;        
        static SimpleOperatorIterator create_the_one_valid_iterator(typename AbstractResultIterator<BraKetT>::value_type);
        static SimpleOperatorIterator create_end_iterator();
        typename AbstractResultIterator<BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        SimpleOperatorIterator() = default;
        SimpleOperatorIterator(typename AbstractResultIterator<BraKetT>::value_type result);
        std::optional<std::pair<double, BraKetT>> result; // no value for the end iterator.
    };

    template<typename _BraKetT>
    class HopOperator : public AbstractOperator<_BraKetT> {
    public:
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;     
        using Iterator = SimpleOperatorIterator<BraKetT>;
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
        using Iterator = SimpleOperatorIterator<BraKetT>;
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
    SimpleOperatorIterator<_BraKetT>::SimpleOperatorIterator(typename AbstractResultIterator<BraKetT>::value_type result) :
    result(result) {
    }

    template<typename _BraKetT>
    SimpleOperatorIterator<_BraKetT>
    SimpleOperatorIterator<_BraKetT>::create_end_iterator() {
        return SimpleOperatorIterator<BraKetT>();
    }

    template<typename _BraKetT>
    SimpleOperatorIterator<_BraKetT>
    SimpleOperatorIterator<_BraKetT>::create_the_one_valid_iterator(typename AbstractResultIterator<BraKetT>::value_type result) {
        return SimpleOperatorIterator<BraKetT>(result);
    }

    template<typename _BraKetT>
    typename AbstractResultIterator<_BraKetT>::value_type
    SimpleOperatorIterator<_BraKetT>::get_val_bra() const {
        assert(result);
        return *result;
    }

    template<typename _BraKetT>
    void
    SimpleOperatorIterator<_BraKetT>::next() {
        assert(result);
        result.reset();
    }

    template<typename _BraKetT>
    bool
    SimpleOperatorIterator<_BraKetT>::is_end() const {
        return !result.has_value();
    }

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
            return std::make_unique<Iterator>(Iterator::create_the_one_valid_iterator(std::make_pair(value, site_2)));
        } else if (ket == site_2) {
            return std::make_unique<Iterator>(Iterator::create_the_one_valid_iterator(std::make_pair(value, site_1)));
        }
        return std::make_unique<Iterator>(Iterator::create_end_iterator());
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
            return std::make_unique<Iterator>(Iterator::create_the_one_valid_iterator(std::make_pair(value, site)));
        }
        return std::make_unique<Iterator>(Iterator::create_end_iterator());
    }

}

#endif
