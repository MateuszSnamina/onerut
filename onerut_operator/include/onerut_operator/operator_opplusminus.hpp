#ifndef ONERUT_OPERATOR_OPPLUSMINUS
#define ONERUT_OPERATOR_OPPLUSMINUS

#include<any>
#include<memory>
#include<algorithm>
#include<iterator>
#include<vector>
#include<optional>

#include<onerut_operator/operator_abstract.hpp>
#include<type_traits>

namespace onerut_operator {

    // -------------------------------------------------------------------------
    // ------------------ PlusMinus OPERATOR  ----------------------------------
    // -------------------------------------------------------------------------    

    template<typename BraKetT>
    class OpPlusMinusOperator;

    template<typename BraKetT, typename StoredAbstractOpT>
    class OpPlusMinusOperatorIterator : public AbstractResultIterator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using StoredAbstractOpPtrT = std::shared_ptr<const StoredAbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = OpPlusMinusOperatorIterator<BraKetT, StoredAbstractOpT>;
        static_assert(std::is_base_of<AbstractOpT, StoredAbstractOpT>::value);
        OpPlusMinusOperatorIterator(
                const StoredAbstractOpPtrT& first_arg,
                const std::vector<StoredAbstractOpPtrT>& other_argv,
                const std::vector<char>& opv,
                const BraKetT& ket);
        typename AbstractResultIterator<BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        AbstractIteratorPtrT _base_itptr;
        typename std::vector<StoredAbstractOpPtrT>::const_iterator _other_argv_it;
        const typename std::vector<StoredAbstractOpPtrT>::const_iterator _other_argv_end;
        std::vector<char>::const_iterator _opv_it;
        const BraKetT _ket;
        bool _process_first;
        void _goto_next_arg_if_base_itptr_is_end();
    };

    template<typename BraKetT>
    class OpPlusMinusOperator : public AbstractOperator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = OpPlusMinusOperatorIterator<BraKetT, AbstractOpT>;
        OpPlusMinusOperator(
                const AbstractOpPtrT& first_arg,
                const std::vector<AbstractOpPtrT>& other_argv,
                const std::vector<char>& opv);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
    private:
        const AbstractOpPtrT first_arg;
        const std::vector<AbstractOpPtrT> other_argv;
        const std::vector<char> opv;
    };

    // -------------------------------------------------------------------------
    // ------------------ PlusMinus OPERATOR - implementation  -----------------
    // -------------------------------------------------------------------------    

    template<typename BraKetT, typename StoredAbstractOpPtrT>
    OpPlusMinusOperatorIterator<BraKetT, StoredAbstractOpPtrT>::OpPlusMinusOperatorIterator(
            const StoredAbstractOpPtrT& first_arg,
            const std::vector<StoredAbstractOpPtrT>& other_argv,
            const std::vector<char>& opv,
            const BraKetT& ket) :
    _base_itptr(std::static_pointer_cast<const AbstractOpT>(first_arg)->begin_itptr(ket)),
    _other_argv_it(std::cbegin(other_argv)),
    _other_argv_end(std::cend(other_argv)),
    _opv_it(std::cbegin(opv)),
    _ket(ket),
    _process_first(true) {
        _goto_next_arg_if_base_itptr_is_end();
    }

    template<typename BraKetT, typename StoredAbstractOpPtrT>
    typename AbstractResultIterator<BraKetT>::value_type
    OpPlusMinusOperatorIterator<BraKetT, StoredAbstractOpPtrT>::get_val_bra() const {
        assert(!is_end());
        assert(!_base_itptr->is_end());
        if (_process_first || *_opv_it == '+') {
            return _base_itptr->get_val_bra();
        } else {
            assert(*_opv_it == '-');
            const auto& val_bra = _base_itptr->get_val_bra();
            const double& value = val_bra.first;
            const BraKetT& bra = val_bra.second;
            return std::make_pair(-value, bra);
        }
    }

    template<typename BraKetT, typename StoredAbstractOpPtrT>
    void
    OpPlusMinusOperatorIterator<BraKetT, StoredAbstractOpPtrT>::next() {
        assert(!is_end());
        _base_itptr->next();
        _goto_next_arg_if_base_itptr_is_end();
    }

    template<typename BraKetT, typename StoredAbstractOpPtrT>
    bool
    OpPlusMinusOperatorIterator<BraKetT, StoredAbstractOpPtrT>::is_end() const {
        return (_other_argv_it == _other_argv_end) && _base_itptr->is_end();
    }

    template<typename BraKetT, typename StoredAbstractOpPtrT>
    void
    OpPlusMinusOperatorIterator<BraKetT, StoredAbstractOpPtrT>::_goto_next_arg_if_base_itptr_is_end() {
        if (_base_itptr->is_end() && _process_first) {
            _process_first = false;
            if (_other_argv_it != _other_argv_end)
                _base_itptr = std::static_pointer_cast<const AbstractOpT>((*_other_argv_it))->begin_itptr(_ket);
        }
        while (_base_itptr->is_end() && (_other_argv_it != _other_argv_end)) {
            _other_argv_it++;
            _opv_it++;
            if (_other_argv_it != _other_argv_end)
                _base_itptr = std::static_pointer_cast<const AbstractOpT>((*_other_argv_it))->begin_itptr(_ket);
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
    typename OpPlusMinusOperator<BraKetT>::AbstractIteratorPtrT
    OpPlusMinusOperator<BraKetT>::begin_itptr(const BraKetT& ket) const {
        return std::make_unique<Iterator>(first_arg, other_argv, opv, ket);
    }

}

#endif
