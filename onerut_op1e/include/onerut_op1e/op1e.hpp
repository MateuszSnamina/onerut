#ifndef ONERUT_OP1E
#define ONERUT_OP1E

#include<any>
#include<memory>
#include<algorithm>
#include<iterator>
#include<vector>
#include<optional>
#include<functional>

#include<armadillo>

namespace onerut_op1e {

    // -------------------------------------------------------------------------
    // ------------------  ABSTRACT OPERATOR  ----------------------------------
    // -------------------------------------------------------------------------

    template<typename BraKetT>
    class AbstractResultIterator
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
        assert(!base_itptr->is_end());
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
    // ------------------ PlusMinus OPERATOR  -------------------------------------
    // -------------------------------------------------------------------------    

    template<typename BraKetT>
    class OpPlusMinusOperator;

    template<typename BraKetT>
    class OpPlusMinusOperatorIterator : public AbstractResultIterator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIterator = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::shared_ptr<AbstractIterator>;
        using Iterator = OpPlusMinusOperatorIterator<BraKetT>;
        OpPlusMinusOperatorIterator(
                const AbstractOpPtrT& first_arg,
                const std::vector<AbstractOpPtrT>& other_argv,
                const std::vector<char>& opv,
                const BraKetT& ket);
        typename AbstractResultIterator<BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        void _goto_next_arg_if_base_itptr_is_end();
        AbstractIteratorPtrT _base_itptr;
        typename std::vector<AbstractOpPtrT>::const_iterator _other_argv_it;
        const typename std::vector<AbstractOpPtrT>::const_iterator _other_argv_end;
        std::vector<char>::const_iterator _opv_it;
        const BraKetT _ket;
        bool _process_first;
        bool _is_end;
    };

    template<typename BraKetT>
    class OpPlusMinusOperator : public AbstractOperator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using Iterator = OpPlusMinusOperatorIterator<BraKetT>;
        OpPlusMinusOperator(
                const AbstractOpPtrT& first_arg,
                const std::vector<AbstractOpPtrT>& other_argv,
                const std::vector<char>& opv);
        std::shared_ptr<AbstractResultIterator<BraKetT>> begin_itptr(const BraKetT& ket) const override;
    private:
        const AbstractOpPtrT first_arg;
        const std::vector<AbstractOpPtrT> other_argv;
        const std::vector<char> opv;
    };

    // -------------------------------------------------------------------------
    // ------------------ PlusMinus OPERATOR - implementation  -----------------
    // -------------------------------------------------------------------------    

    template<typename BraKetT>
    OpPlusMinusOperatorIterator<BraKetT>::OpPlusMinusOperatorIterator(
            const AbstractOpPtrT& first_arg,
            const std::vector<AbstractOpPtrT>& other_argv,
            const std::vector<char>& opv,
            const BraKetT& ket) :
    _base_itptr(first_arg->begin_itptr(ket)),
    _other_argv_it(std::cbegin(other_argv)),
    _other_argv_end(std::cend(other_argv)),
    _opv_it(std::cbegin(opv)),
    _ket(ket),
    _process_first(true),
    _is_end(false) {
        _goto_next_arg_if_base_itptr_is_end();
    }

    template<typename BraKetT>
    typename AbstractResultIterator<BraKetT>::value_type
    OpPlusMinusOperatorIterator<BraKetT>::get_val_bra() const {
        assert(!_is_end);
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
            if (_other_argv_it != _other_argv_end)
                _base_itptr = (*_other_argv_it)->begin_itptr(_ket);
            else
                _is_end = true;
        }
    }

    // -------------------------------------------------------------------------

    template<typename BraKetT>
    OpPlusMinusOperator<BraKetT>::OpPlusMinusOperator(
            const AbstractOpPtrT& first_arg,
            const std::vector<AbstractOpPtrT>& other_argv,
            const std::vector<char>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
    }

    template<typename BraKetT>
    std::shared_ptr<AbstractResultIterator<BraKetT>>
    OpPlusMinusOperator<BraKetT>::begin_itptr(const BraKetT& ket) const {
        return std::make_shared<Iterator>(first_arg, other_argv, opv, ket);
    }

    // -------------------------------------------------------------------------
    // ------------------ OpProd OPERATOR  -------------------------------------
    // -------------------------------------------------------------------------    

    template<typename BraKetT>
    class OpProdOperatorIterator : public AbstractResultIterator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIterator = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::shared_ptr<const AbstractIterator>;
        using Iterator = OpProdOperatorIterator<BraKetT>;
        OpProdOperatorIterator(
                const std::vector<AbstractOpPtrT>& argv, const BraKetT& ket);
        typename AbstractResultIterator<BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        //void _goto_next_arg_if_base_itptr_is_end();
        std::vector<AbstractOpPtrT> _argv;
        std::vector<AbstractIteratorPtrT> _base_itptr;
        std::vector<double> _factor;
        std::optional<BraKetT> _bra;
    };

    template<typename BraKetT>
    class OpProdOperator : public AbstractOperator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using Iterator = OpProdOperatorIterator<BraKetT>;
        OpProdOperator(std::vector<AbstractOpPtrT> argv);
        std::shared_ptr<AbstractResultIterator<BraKetT>> begin_itptr(const BraKetT& ket) const override;
    private:
        std::vector<AbstractOpPtrT> argv;
    };

    // -------------------------------------------------------------------------

    template<typename BraKetT>
    OpProdOperatorIterator<BraKetT>::OpProdOperatorIterator(
            const std::vector<AbstractOpPtrT>& argv, const BraKetT& ket) :
    _argv(argv),
    _base_itptr(argv.size()),
    _factor(argv.size()),
    _bra(std::nullopt) {
        BraKetT& temp = ket;
        auto base_itptr_rit = _base_itptr.rbegin();
        for (auto arg_rit = _argv.rbegin(); arg_rit != _argv.rend(); arg_rit) {
            *base_itptr_rit = (*arg_rit)->begin_itptr(temp);
            if ((*base_itptr_rit)->is_end())
                return;
            const auto& val_bra = (*base_itptr_rit)->get_val_bra();
            const double& val = val_bra.first;
            const BraKetT& bra = val_bra.second;
            temp = bra;
        }
        _bra = temp;
    }

    template<typename BraKetT>
    typename AbstractResultIterator<BraKetT>::value_type
    OpProdOperatorIterator<BraKetT>::get_val_bra() const {
        assert(!is_end());
        double value = std::accumulate(begin(_factor), end(_factor), 1, std::multiplies<double>());
        return std::make_pair(value, _bra);
    }

    template<typename BraKetT>
    void
    OpProdOperatorIterator<BraKetT>::next() {
        assert(!is_end());
        //TODO
    }

    template<typename BraKetT>
    bool
    OpProdOperatorIterator<BraKetT>::is_end() const {
        return _bra.has_value();
    }

    template<typename BraKetT>
    OpProdOperator<BraKetT>::OpProdOperator(std::vector<AbstractOpPtrT> argv) :
    argv(argv) {
    }

    template<typename BraKetT>
    std::shared_ptr<AbstractResultIterator<BraKetT>>
    OpProdOperator<BraKetT>::begin_itptr(const BraKetT& ket) const {
        return std::make_shared<Iterator>(argv, ket);
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