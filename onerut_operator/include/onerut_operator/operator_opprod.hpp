#ifndef ONERUT_OPERATOR_OPPROD
#define ONERUT_OPERATOR_OPPROD

#include<memory>
#include<algorithm>
#include<iterator>
#include<vector>
#include<optional>
#include<numeric>
#include<functional>

#include<onerut_operator/operator_abstract.hpp>

namespace onerut_operator {

    // -------------------------------------------------------------------------
    // ------------------ OpProd OPERATOR  -------------------------------------
    // -------------------------------------------------------------------------    

    template<typename BraKetT>
    class OpProdOperatorIterator : public AbstractResultIterator<BraKetT> {
    public:
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIterator = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::shared_ptr<AbstractIterator>;
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
        std::optional<BraKetT> init(unsigned arg_number, BraKetT);
        std::optional<BraKetT> next(unsigned arg_number);
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
        _bra = init(_argv.size() - 1, ket);
    }

    template<typename BraKetT>
    std::optional<BraKetT>
    OpProdOperatorIterator<BraKetT>::init(unsigned arg_number, BraKetT ket) {
        _base_itptr[arg_number] = _argv[arg_number]->begin_itptr(ket);
        while (!_base_itptr[arg_number]->is_end()) {
            const auto& val_bra = _base_itptr[arg_number]->get_val_bra();
            const double& val = val_bra.first;
            const BraKetT& bra1 = val_bra.second;
            _factor[arg_number] = val;
            if (arg_number == 0) {
                return bra1;
            }
            std::optional<BraKetT> bra2 = init(arg_number - 1, bra1);
            if (bra2) {
                return bra2;
            } else {
                _base_itptr[arg_number]->next();
            }
        }
        return std::nullopt;
    }

    template<typename BraKetT>
    typename AbstractResultIterator<BraKetT>::value_type
    OpProdOperatorIterator<BraKetT>::get_val_bra() const {
        assert(!is_end());
        double value = std::accumulate(begin(_factor), end(_factor), 1.0, std::multiplies<double>());
        return std::make_pair(value, *_bra);
    }

    template<typename BraKetT>
    void
    OpProdOperatorIterator<BraKetT>::next() {
        assert(!is_end());
        _bra = next(0);
    }

    template<typename BraKetT >
    std::optional<BraKetT>
    OpProdOperatorIterator<BraKetT>::next(unsigned arg_number) {
        assert(arg_number < _argv.size());
        assert(!is_end());
        _base_itptr[arg_number]->next();
        while (_base_itptr[arg_number]->is_end()) {
            if (arg_number == _argv.size() - 1) {
                return std::nullopt;
            } else {
                if (auto intermediate = next(arg_number + 1)) {
                    _base_itptr[arg_number] = _argv[arg_number]->begin_itptr(*intermediate);
                } else {
                    return std::nullopt;
                }
            }
        }
        assert(!_base_itptr[arg_number]->is_end());
        const auto& val_bra = _base_itptr[arg_number]->get_val_bra();
        const double& val = val_bra.first;
        const BraKetT& bra = val_bra.second;
        _factor[arg_number] = val;
        return bra;
    }

    template<typename BraKetT>
    bool
    OpProdOperatorIterator<BraKetT>::is_end() const {
        return !_bra.has_value();
    }

    template<typename BraKetT >
    OpProdOperator<BraKetT>::OpProdOperator(std::vector<AbstractOpPtrT> argv) :
    argv(argv) {
    }

    template<typename BraKetT >
    std::shared_ptr<AbstractResultIterator < BraKetT >>
    OpProdOperator<BraKetT>::begin_itptr(const BraKetT & ket) const {
        return std::make_shared<Iterator>(argv, ket);
    }

}

#endif
