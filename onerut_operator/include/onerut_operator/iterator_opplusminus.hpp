#ifndef ONERUT_ITERATOR_OPPLUSMINUS
#define ONERUT_ITERATOR_OPPLUSMINUS

#include<any>
#include<memory>
#include<algorithm>
#include<iterator>
#include<vector>
#include<optional>

#include<onerut_operator/operator_abstract.hpp>
#include<type_traits>

namespace onerut_typed_operator {

    // -------------------------------------------------------------------------
    // ------------------ PlusMinus OPERATOR  ----------------------------------
    // -------------------------------------------------------------------------    

    //template<typename _BraKetT>
    //class OpPlusMinusOperator; //TODO do we need this forward decl ??

    template<typename _BraKetT, typename _StoredAbstractOpT>
    class OpPlusMinusOperatorIterator : public AbstractResultIterator<_BraKetT> {
    public:
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using StoredAbstractOpT = _StoredAbstractOpT;
        using StoredAbstractOpPtrT = std::shared_ptr<const StoredAbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = OpPlusMinusOperatorIterator<BraKetT, StoredAbstractOpT>;
        static_assert(std::is_base_of<AbstractOpT, StoredAbstractOpT>::value);
        static_assert(std::is_same<typename StoredAbstractOpT::BraKetT, BraKetT>::value); // remove _BraKetT from the Iterator template parameter list!
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

    // -------------------------------------------------------------------------
    // ------------------ PlusMinus OPERATOR - implementation  -----------------
    // -------------------------------------------------------------------------    

    template<typename _BraKetT, typename _StoredAbstractOpT>
    OpPlusMinusOperatorIterator<_BraKetT, _StoredAbstractOpT>::OpPlusMinusOperatorIterator(
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

    template<typename _BraKetT, typename _StoredAbstractOpT>
    typename AbstractResultIterator<_BraKetT>::value_type
    OpPlusMinusOperatorIterator<_BraKetT, _StoredAbstractOpT>::get_val_bra() const {
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

    template<typename _BraKetT, typename _StoredAbstractOpT>
    void
    OpPlusMinusOperatorIterator<_BraKetT, _StoredAbstractOpT>::next() {
        assert(!is_end());
        _base_itptr->next();
        _goto_next_arg_if_base_itptr_is_end();
    }

    template<typename _BraKetT, typename _StoredAbstractOpT>
    bool
    OpPlusMinusOperatorIterator<_BraKetT, _StoredAbstractOpT>::is_end() const {
        return (_other_argv_it == _other_argv_end) && _base_itptr->is_end();
    }

    template<typename _BraKetT, typename _StoredAbstractOpT>
    void
    OpPlusMinusOperatorIterator<_BraKetT, _StoredAbstractOpT>::_goto_next_arg_if_base_itptr_is_end() {
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

}

#endif
