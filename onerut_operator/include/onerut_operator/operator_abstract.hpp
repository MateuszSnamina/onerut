#ifndef ONERUT_OPERATOR_ABSTRACT
#define ONERUT_OPERATOR_ABSTRACT

#include<memory>
#include<utility>

namespace onerut_operator {

    // -------------------------------------------------------------------------
    // ------------------  ABSTRACT OPERATOR  ----------------------------------
    // -------------------------------------------------------------------------
    
    template<typename _BraKetT>
    class AbstractOperator;

    template<typename _BraKetT>
    class AbstractResultIterator {
    public:
        using BraKetT = _BraKetT;
        using value_type = std::pair<double, BraKetT>;
        using pointer = value_type*;
        using reference = value_type&;
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        virtual value_type get_val_bra() const = 0;
        virtual void next() = 0;
        virtual bool is_end() const = 0;
        virtual ~AbstractResultIterator() = default;
    };

    template<typename _BraKetT>
    class AbstractOperator {
    public:
        using BraKetT = _BraKetT;        
        using AbstractOpT = AbstractOperator<BraKetT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;        
        virtual AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const = 0;
    };

}

#endif
