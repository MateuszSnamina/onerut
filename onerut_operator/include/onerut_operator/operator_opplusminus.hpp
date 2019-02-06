#ifndef ONERUT_OPERATOR_OPPLUSMINUS
#define ONERUT_OPERATOR_OPPLUSMINUS

#include<any>
#include<memory>
#include<algorithm>
#include<iterator>
#include<vector>
#include<optional>

#include<onerut_operator/operator_abstract.hpp>

namespace onerut_operator {

    // -------------------------------------------------------------------------
    // ------------------ PlusMinus OPERATOR  ----------------------------------
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

}

#endif
