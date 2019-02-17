#ifndef ONERUT_NORMAL_OPERATOR_ABSTRACT
#define ONERUT_NORMAL_OPERATOR_ABSTRACT

#include<memory>
#include<utility>

#include<onerut_operator/operator_abstract.hpp>

namespace onerut_nornal_operator {

    struct Domain {
        unsigned size;
    };

    struct State {
        const std::shared_ptr<Domain> domain;
        const unsigned index;
    };

//    class NormalOperator
//    public:
//        NormalOperator
//        const std::shared_ptr<Domain> domain;
//
//    };

    /*
        // -------------------------------------------------------------------------
        // ------------------  ABSTRACT OPERATOR  ----------------------------------
        // -------------------------------------------------------------------------
    
        template<typename BraKetT>
        class AbstractOperator;

        template<typename BraKetT>
        class AbstractResultIterator {
        public:
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

        template<typename BraKetT>
        class AbstractOperator {
        public:
            using AbstractOpT = AbstractOperator<BraKetT>;
            using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
            using AbstractIteratorT = AbstractResultIterator<BraKetT>;
            using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;        
            virtual AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const = 0;
        };
     */
}

#endif
