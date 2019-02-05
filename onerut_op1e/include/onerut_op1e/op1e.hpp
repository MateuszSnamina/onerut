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
        virtual void next() = 0;
        virtual bool is_end() const = 0;
        virtual ~AbstractResultIterator() = default;
    };

    template<typename BraKetT>
    class AbstractOperator {
    public:
        virtual std::shared_ptr<AbstractResultIterator<BraKetT>> begin_itptr(const BraKetT& ket) const = 0;
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

    // -------------------------------------------------------------------------
    // ------------------ SCALLED OPERATOR  -------------------------------------
    // -------------------------------------------------------------------------    

    template<typename BraKetT>
    class ScalledOperatorIterator : public AbstractResultIterator<BraKetT> {
    public:
        ScalledOperatorIterator(double factor, std::shared_ptr<AbstractResultIterator<BraKetT>> base_itptr);
        typename AbstractResultIterator<BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        const double factor;
        const std::shared_ptr<AbstractResultIterator<BraKetT>> base_itptr;
    };

    template<typename BraKetT>
    class ScalledOperator : public AbstractOperator<BraKetT> {
    public:
        using Iterator = ScalledOperatorIterator<BraKetT>;
        ScalledOperator(double factor, std::shared_ptr<const AbstractOperator<BraKetT>> arg);
        std::shared_ptr<AbstractResultIterator<BraKetT>> begin_itptr(const BraKetT& ket) const override;
    private:
        const double factor;
        const std::shared_ptr<const AbstractOperator<BraKetT>> arg;
    };


    // -------------------------------------------------------------------------
    // ------------------ SCALLED OPERATOR - IMPLEMENTATION ---------------------
    // -------------------------------------------------------------------------    

    template<typename BraKetT>
    ScalledOperatorIterator<BraKetT>::ScalledOperatorIterator(
            double factor,
            std::shared_ptr<AbstractResultIterator<BraKetT>> base_itptr) :
    factor(factor),
    base_itptr(base_itptr) {
    }

    template<typename BraKetT>
    typename AbstractResultIterator<BraKetT>::value_type
    ScalledOperatorIterator<BraKetT>::get_val_bra() const {
        assert(!base_itptr->is_end());
        const typename AbstractResultIterator<BraKetT>::value_type& val_bra = base_itptr->get_val_bra();
        const double& value = val_bra.first;
        const BraKetT& bra = val_bra.second;
        return std::make_pair(factor*value, bra);
    }

    template<typename BraKetT>
    void
    ScalledOperatorIterator<BraKetT>::next() {
        base_itptr->next();
    }

    template<typename BraKetT>
    bool
    ScalledOperatorIterator<BraKetT>::is_end() const {
        return base_itptr->is_end();
    }

    // -------------------------------------------------------------------------

    template<typename BraKetT>
    ScalledOperator<BraKetT>::ScalledOperator(
            double factor,
            std::shared_ptr<const AbstractOperator<BraKetT>> arg) :
    factor(factor),
    arg(arg) {
    }

    template<typename BraKetT>
    std::shared_ptr<AbstractResultIterator<BraKetT>>
    ScalledOperator<BraKetT>::begin_itptr(const BraKetT& ket) const {
        return std::make_shared<Iterator>(factor, arg->begin_itptr(ket));
    }

    // -------------------------------------------------------------------------
    // ------------------ SCALLED OPERATOR  -------------------------------------
    // -------------------------------------------------------------------------    

    template<typename BraKetT>
    class OpPlusMinusOperator;

    template<typename BraKetT>
    class OpPlusMinusOperatorIterator : public AbstractResultIterator<BraKetT> {
    public:
        using OpT = AbstractOperator<BraKetT>;
        using OpPtrT = std::shared_ptr<const OpT>;
        using Iterator = OpPlusMinusOperatorIterator<BraKetT>;
        OpPlusMinusOperatorIterator(
                const BraKetT& ket,
                const OpPtrT& first_arg,
                const std::vector<OpPtrT>& other_argv,
                const std::vector<char>& opv);
        typename AbstractResultIterator<BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        void _goto_next_arg_if_base_itptr_is_end();
        const BraKetT _ket;
        std::shared_ptr<AbstractResultIterator<BraKetT>> _base_itptr;
        typename std::vector<OpPtrT>::const_iterator _other_argv_it;
        const typename std::vector<OpPtrT>::const_iterator _other_argv_end;
        std::vector<char>::const_iterator _opv_it;
        bool _process_first;
        bool _is_end;
    };

    template<typename BraKetT>
    class OpPlusMinusOperator : public AbstractOperator<BraKetT> {
    public:
        using OpT = AbstractOperator<BraKetT>;
        using OpPtrT = std::shared_ptr<const OpT>;
        using Iterator = OpPlusMinusOperatorIterator<BraKetT>;
        OpPlusMinusOperator(
                const OpPtrT& first_arg,
                const std::vector<OpPtrT>& other_argv,
                const std::vector<char>& opv);
        std::shared_ptr<AbstractResultIterator<BraKetT>> begin_itptr(const BraKetT& ket) const override;
    private:
        const OpPtrT first_arg;
        const std::vector<OpPtrT> other_argv;
        const std::vector<char> opv;
    };

    // -------------------------------------------------------------------------

    template<typename BraKetT>
    OpPlusMinusOperatorIterator<BraKetT>::OpPlusMinusOperatorIterator(
            const BraKetT& ket,
            const OpPtrT& first_arg,
            const std::vector<OpPtrT>& other_argv,
            const std::vector<char>& opv) :
    _ket(ket),
    _base_itptr(first_arg->begin_itptr(ket)),
    _other_argv_it(std::cbegin(other_argv)),
    _other_argv_end(std::cend(other_argv)),
    _opv_it(std::cbegin(opv)),
    _process_first(true),
    _is_end(false) {
        _goto_next_arg_if_base_itptr_is_end();
    }

    template<typename BraKetT>
    typename AbstractResultIterator<BraKetT>::value_type
    OpPlusMinusOperatorIterator<BraKetT>::get_val_bra() const {
        assert(!_base_itptr->is_end());
        if (_process_first || *_opv_it == '+') {
            return _base_itptr->get_val_bra();
        } else {
            assert(*_opv_it == '-');
            const typename AbstractResultIterator<BraKetT>::value_type& val_bra = _base_itptr->get_val_bra();
            const double& value = val_bra.first;
            const BraKetT& bra = val_bra.second;
            return std::make_pair(-value, bra);
        }
    }

    template<typename BraKetT>
    void
    OpPlusMinusOperatorIterator<BraKetT>::next() {
        assert(!_is_end);
        _base_itptr->next();
        _goto_next_arg_if_base_itptr_is_end();
    }

    template<typename BraKetT>
    bool
    OpPlusMinusOperatorIterator<BraKetT>::is_end() const {
        return _is_end;
    }

    template<typename BraKetT>
    void
    OpPlusMinusOperatorIterator<BraKetT>::_goto_next_arg_if_base_itptr_is_end() {
        if (_process_first && _base_itptr->is_end()) {
            _process_first = false;
            _base_itptr = (*_other_argv_it)->begin_itptr(_ket);
        }
        while (_base_itptr->is_end() && !_is_end) {
            _other_argv_it++;
            _opv_it++;
            if (_other_argv_it != _other_argv_end) {
                _base_itptr = (*_other_argv_it)->begin_itptr(_ket);
            } else {
                _is_end = true;
            }
        }
    }

    // -------------------------------------------------------------------------

    template<typename BraKetT>
    OpPlusMinusOperator<BraKetT>::OpPlusMinusOperator(
            const OpPtrT& first_arg,
            const std::vector<OpPtrT>& other_argv,
            const std::vector<char>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
    }

    template<typename BraKetT>
    std::shared_ptr<AbstractResultIterator<BraKetT>>
    OpPlusMinusOperator<BraKetT>::begin_itptr(const BraKetT& ket) const {
        return std::make_shared<Iterator>(ket, first_arg, other_argv, opv);
    }

    // -------------------------------------------------------------------------
    // ------------------ ANY OPERATOR INTERFACE -------------------------------
    // ------------------------------------------------------------------------- 

    //    class Op1e {
    //    public:
    //        virtual std::vector<std::pair<double, std::any>> call(const std::any& arg) const = 0;
    //        virtual ~Op1e() = default;
    //    };


    // -------------------------------------------------------------------------
    // -----------------------  TO MAT -----------------------------------------
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