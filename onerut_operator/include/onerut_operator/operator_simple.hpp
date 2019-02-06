#ifndef ONERUT_OPERATOR_SIMPLE
#define ONERUT_OPERATOR_SIMPLE

#include<onerut_operator/operator_abstract.hpp>

namespace onerut_operator {

    // -------------------------------------------------------------------------
    // ------------------ SIMPLE OPERATOR --------------------------------------
    // -------------------------------------------------------------------------        

    template<typename BraKetT>
    class SimpleOperatorIterator : public AbstractResultIterator<BraKetT> {
    public:
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

    template<typename BraKetT>
    class HopOperator : public AbstractOperator<BraKetT> {
    public:
        using Iterator = SimpleOperatorIterator<BraKetT>;
        HopOperator(double value, const BraKetT &site_1, const BraKetT &site_2);
        std::shared_ptr<AbstractResultIterator<BraKetT>> begin_itptr(const BraKetT& ket) const override;
    private:
        const double value;
        const BraKetT site_1;
        const BraKetT site_2;
    };

    template<typename BraKetT>
    class DiagOperator : public AbstractOperator<BraKetT> {
    public:
        using Iterator = SimpleOperatorIterator<BraKetT>;
        DiagOperator(double value, const BraKetT &site);
        std::shared_ptr<AbstractResultIterator<BraKetT>> begin_itptr(const BraKetT& ket) const override;
    private:
        const double value;
        const BraKetT site;
    };
    // -------------------------------------------------------------------------
    // ------------------ SIMPLE OPERATOR - IMPLEMENTATION ---------------------
    // -------------------------------------------------------------------------     

    template<typename BraKetT>
    SimpleOperatorIterator<BraKetT>::SimpleOperatorIterator(typename AbstractResultIterator<BraKetT>::value_type result) :
    result(result) {
    }

    template<typename BraKetT>
    SimpleOperatorIterator<BraKetT>
    SimpleOperatorIterator<BraKetT>::create_end_iterator() {
        return SimpleOperatorIterator<BraKetT>();
    }

    template<typename BraKetT>
    SimpleOperatorIterator<BraKetT>
    SimpleOperatorIterator<BraKetT>::create_the_one_valid_iterator(typename AbstractResultIterator<BraKetT>::value_type result) {
        return SimpleOperatorIterator<BraKetT>(result);
    }

    template<typename BraKetT>
    typename AbstractResultIterator<BraKetT>::value_type
    SimpleOperatorIterator<BraKetT>::get_val_bra() const {
        assert(result);
        return *result;
    }

    template<typename BraKetT>
    void
    SimpleOperatorIterator<BraKetT>::next() {
        assert(result);
        result.reset();
    }

    template<typename BraKetT>
    bool
    SimpleOperatorIterator<BraKetT>::is_end() const {
        return !result.has_value();
    }

    // -------------------------------------------------------------------------    

    template<typename BraKetT>
    HopOperator<BraKetT>::HopOperator(double value, const BraKetT &site_1, const BraKetT &site_2) :
    value(value),
    site_1(site_1),
    site_2(site_2) {
        assert(site_1 != site_2);
    }

    template<typename BraKetT>
    std::shared_ptr<AbstractResultIterator<BraKetT>>
    HopOperator<BraKetT>::begin_itptr(const BraKetT& ket) const {
        if (ket == site_1) {
            return std::make_shared<Iterator>(Iterator::create_the_one_valid_iterator(std::make_pair(value, site_2)));
        } else if (ket == site_2) {
            return std::make_shared<Iterator>(Iterator::create_the_one_valid_iterator(std::make_pair(value, site_1)));
        }
        return std::make_shared<Iterator>(Iterator::create_end_iterator());
    }

    // -------------------------------------------------------------------------        

    template<typename BraKetT>
    DiagOperator<BraKetT>::DiagOperator(double value, const BraKetT &site) :
    value(value),
    site(site) {
    }

    template<typename BraKetT>
    std::shared_ptr<AbstractResultIterator<BraKetT>>
    DiagOperator<BraKetT>::begin_itptr(const BraKetT& ket) const {
        if (ket == site) {
            return std::make_shared<Iterator>(Iterator::create_the_one_valid_iterator(std::make_pair(value, site)));
        }
        return std::make_shared<Iterator>(Iterator::create_end_iterator());
    }

}

#endif
