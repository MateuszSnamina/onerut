#ifndef ONERUT_TYPED_OPERATOR_ITERATOR_OPPROD
#define ONERUT_TYPED_OPERATOR_ITERATOR_OPPROD

#include<memory>
#include<vector>
#include<optional>
#include<numeric> // std::accumulate
#include<functional> // std::multiplies

#include<onerut_typed_operator/operator_abstract.hpp>

namespace onerut_typed_operator {

    // -------------------------------------------------------------------------
    // ------------------ OpProd OPERATOR  -------------------------------------
    // -------------------------------------------------------------------------    

    template<typename _ScalarT, typename _BraKetT, typename _StoredAbstractOpT>
    class OpProdOperatorIterator : public AbstractResultIterator<_ScalarT, _BraKetT> {
    public:
        using ScalarT = _ScalarT;        
        using BraKetT = _BraKetT;
        using AbstractOpT = AbstractOperator<ScalarT, BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using StoredAbstractOpT = _StoredAbstractOpT;        
        using StoredAbstractOpPtrT = std::shared_ptr<const StoredAbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = OpProdOperatorIterator<ScalarT, BraKetT, StoredAbstractOpT>;
        static_assert(std::is_base_of<AbstractOpT, StoredAbstractOpT>::value);
        static_assert(std::is_same<typename StoredAbstractOpT::BraKetT, BraKetT>::value); // remove _BraKetT from the Iterator template parameter list!
        OpProdOperatorIterator(
                const std::vector<StoredAbstractOpPtrT>& argv, const BraKetT& ket);
        typename AbstractResultIterator<ScalarT, BraKetT>::value_type get_val_bra() const override;
        void next() override;
        virtual bool is_end() const override;
    private:
        const std::vector<StoredAbstractOpPtrT>& _argv; //TODO reference
        std::vector<AbstractIteratorPtrT> _base_itptr;
        std::vector<ScalarT> _factor;
        std::optional<BraKetT> _bra;
        std::optional<BraKetT> _init(unsigned arg_number, BraKetT);
        std::optional<BraKetT> _next(unsigned arg_number);
    };

    // -------------------------------------------------------------------------

    template<typename _ScalarT, typename _BraKetT, typename _StoredAbstractOpT>
    OpProdOperatorIterator<_ScalarT, _BraKetT, _StoredAbstractOpT>::OpProdOperatorIterator(
            const std::vector<StoredAbstractOpPtrT>& argv, const BraKetT& ket) :
    _argv(argv),
    _base_itptr(argv.size()),
    _factor(argv.size()),
    _bra(std::nullopt) {
        if (_argv.empty()) {
            _bra = ket;
        } else {
            _bra = _init(_argv.size() - 1, ket);
        }
    }

    template<typename _ScalarT, typename _BraKetT, typename _StoredAbstractOpT>
    std::optional<_BraKetT>
    OpProdOperatorIterator<_ScalarT, _BraKetT, _StoredAbstractOpT>::_init(unsigned arg_number, BraKetT ket) {
        assert(_base_itptr.size() == _argv.size());
        assert(_base_itptr.size() == _factor.size());
        assert(arg_number < _argv.size());
        _base_itptr[arg_number] = std::static_pointer_cast<const AbstractOpT>(_argv[arg_number])->begin_itptr(ket);
        while (!_base_itptr[arg_number]->is_end()) {
            const auto& val_bra = _base_itptr[arg_number]->get_val_bra();
            const auto& val = val_bra.first;
            const BraKetT& bra1 = val_bra.second;
            _factor[arg_number] = val;
            if (arg_number == 0) {
                return bra1;
            }
            if (const auto& bra2 = _init(arg_number - 1, bra1)) {
                return bra2;
            } else {
                _base_itptr[arg_number]->next();
            }
        }
        return std::nullopt;
    }

    template<typename _ScalarT, typename _BraKetT, typename _StoredAbstractOpT>
    typename AbstractResultIterator<_ScalarT, _BraKetT>::value_type
    OpProdOperatorIterator<_ScalarT, _BraKetT, _StoredAbstractOpT>::get_val_bra() const {
        assert(!is_end());
        const auto value = std::accumulate(begin(_factor), end(_factor), 1.0, std::multiplies<ScalarT>());
        return std::make_pair(value, *_bra);
    }

    template<typename _ScalarT, typename _BraKetT, typename _StoredAbstractOpT>
    void
    OpProdOperatorIterator<_ScalarT, _BraKetT, _StoredAbstractOpT>::next() {
        assert(!is_end());
        if (_argv.empty())
            _bra.reset();
        else
            _bra = _next(0);
    }

    template<typename _ScalarT, typename _BraKetT, typename _StoredAbstractOpT>
    std::optional<_BraKetT>
    OpProdOperatorIterator<_ScalarT, _BraKetT, _StoredAbstractOpT>::_next(unsigned arg_number) {
        assert(_base_itptr.size() == _argv.size());
        assert(_base_itptr.size() == _factor.size());
        assert(arg_number < _argv.size());
        assert(!is_end());
        _base_itptr[arg_number]->next();
        while (_base_itptr[arg_number]->is_end()) {
            if (arg_number == _argv.size() - 1) {
                return std::nullopt;
            } else {
                if (const auto& intermediate = _next(arg_number + 1)) {
                    _base_itptr[arg_number] = std::static_pointer_cast<const AbstractOpT>(_argv[arg_number])->begin_itptr(*intermediate);
                } else {
                    return std::nullopt;
                }
            }
        }
        assert(!_base_itptr[arg_number]->is_end());
        const auto& val_bra = _base_itptr[arg_number]->get_val_bra();
        const auto& val = val_bra.first;
        const BraKetT& bra = val_bra.second;
        _factor[arg_number] = val;
        return bra;
    }

    template<typename _ScalarT, typename _BraKetT, typename _StoredAbstractOpT>
    bool
    OpProdOperatorIterator<_ScalarT, _BraKetT, _StoredAbstractOpT>::is_end() const {
        return !_bra.has_value();
    }

}

#endif
