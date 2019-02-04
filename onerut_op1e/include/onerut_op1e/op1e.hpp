#ifndef ONERUT_OP1E
#define ONERUT_OP1E

#include<any>
#include<memory>
#include<algorithm>
#include<iterator>
#include<vector>
#include<optional>

#include<boost/operators.hpp>

#include<armadillo>

namespace onerut_op1e {

    // -------------------------------------------------------------------------
    // ------------------  ABSTRACT OPERATOR  ----------------------------------
    // -------------------------------------------------------------------------

    template<typename BraKetT>
    class AbstractResultIterator : boost::equality_comparable<AbstractResultIterator<BraKetT>>
    {
        public:
        using iterator_category = std::input_iterator_tag;
        using value_type = std::pair<double, BraKetT>;
        using difference_type = unsigned;
        using pointer = value_type*;
        using reference = value_type&;
        virtual value_type get_val_bra() const = 0;
        virtual AbstractResultIterator & next() = 0;
        virtual bool is_end() const = 0;
        virtual ~AbstractResultIterator() = default;
    };

    template<typename BraKetT>
    class AbstractOperator {
    public:
        virtual std::shared_ptr<AbstractResultIterator<BraKetT>> begin_itptr(const BraKetT arg) const = 0;
    };

    // -------------------------------------------------------------------------
    // ------------------ SIMPLE OPERATOR --------------------------------------
    // -------------------------------------------------------------------------        

    template<typename BraKetT>
    class SimpleOperatorIterator : public AbstractResultIterator<BraKetT> {
    public:
        static SimpleOperatorIterator create_the_one_valid_iterator(typename AbstractResultIterator<BraKetT>::value_type);
        static SimpleOperatorIterator create_end_iterator();
        typename AbstractResultIterator<BraKetT>::value_type get_val_bra() const override;
        SimpleOperatorIterator& next() override;
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
        std::shared_ptr<AbstractResultIterator<BraKetT>> begin_itptr(const BraKetT arg) const override;
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
        std::shared_ptr<AbstractResultIterator<BraKetT>> begin_itptr(const BraKetT arg) const override;
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
    SimpleOperatorIterator<BraKetT>&
    SimpleOperatorIterator<BraKetT>::next() {
        assert(result);
        result.reset();
        return *this;
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
    HopOperator<BraKetT>::begin_itptr(const BraKetT arg) const {
        if (arg == site_1) {
            return std::make_shared<Iterator>(Iterator::create_the_one_valid_iterator(std::make_pair(value, site_2)));
        } else if (arg == site_2) {
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
    DiagOperator<BraKetT>::begin_itptr(const BraKetT arg) const {
        if (arg == site) {
            return std::make_shared<Iterator>(Iterator::create_the_one_valid_iterator(std::make_pair(value, site)));
        }
        return std::make_shared<Iterator>(Iterator::create_end_iterator());
    }

    // -------------------------------------------------------------------------
    // ------------------ SIMPLE OPERATOR - IMPLEMENTATION ---------------------
    // -------------------------------------------------------------------------    

    // -------------------------------------------------------------------------
    // ------------------ ANY OPERATOR INTERFACE -------------------------------
    // ------------------------------------------------------------------------- 

    //    class Op1e {
    //    public:
    //        virtual std::vector<std::pair<double, std::any>> call(const std::any& arg) const = 0;
    //        virtual ~Op1e() = default;
    //    };


    // -------------------------------------------------------------------------

    arma::mat to_mat(const AbstractOperator<unsigned>& op, unsigned spad_dim) {
        arma::mat result(spad_dim, spad_dim, arma::fill::zeros);
        for (unsigned ket = 0; ket < spad_dim; ket++) {
            auto it1 = op.begin_itptr(ket);
            while (!it1->is_end()) {
                const std::pair<double, unsigned>& val_bra = it1->get_val_bra();
                const double& value = val_bra.first;
                const unsigned& bra = val_bra.second;
                result(bra, ket) += value;
                it1->next();
            }
        }
        return result;
    }

}

#endif