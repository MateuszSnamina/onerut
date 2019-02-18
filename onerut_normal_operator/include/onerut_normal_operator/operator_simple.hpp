#ifndef ONERUT_NORMAL_OPERATOR_SIMPLE
#define ONERUT_NORMAL_OPERATOR_SIMPLE

#include<onerut_scalar/scalar_abstract_integer.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/operator_simple.hpp>

namespace onerut_normal_operator {

    using BraKetT = unsigned; // TODO put into class as a literal.

    AbstractOperator* x;

    class HopOperator : public AbstractOperator {
    public:
        using AbstractOpT = AbstractOperator;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_operator::AbstractResultIterator<BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using Iterator = onerut_operator::SimpleOperatorIterator<BraKetT>;
        HopOperator(double value, const onerut_scalar::Integer& site_1, const onerut_scalar::Integer&site_2);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
        std::shared_ptr<const Domain> get_domain() const override;
    private:
        const double value;
        const onerut_scalar::Integer& site_1;
        const onerut_scalar::Integer& site_2;
    };

    /*
        // -------------------------------------------------------------------------
        // ------------------ SIMPLE OPERATOR --------------------------------------
        // -------------------------------------------------------------------------        

        template<typename BraKetT>
        class SimpleOperatorIterator : public AbstractResultIterator<BraKetT> {
        public:
            using AbstractOpT = AbstractOperator<BraKetT>;
            using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
            using AbstractIteratorT = AbstractResultIterator<BraKetT>;
            using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;        
            using Iterator = SimpleOperatorIterator<BraKetT>;        
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
            using AbstractOpT = AbstractOperator<BraKetT>;
            using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
            using AbstractIteratorT = AbstractResultIterator<BraKetT>;
            using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;       
            using Iterator = SimpleOperatorIterator<BraKetT>;
            HopOperator(double value, const BraKetT &site_1, const BraKetT &site_2);
            AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
        private:
            const double value;
            const BraKetT site_1;
            const BraKetT site_2;
        };

        template<typename BraKetT>
        class DiagOperator : public AbstractOperator<BraKetT> {
        public:
            using AbstractOpT = AbstractOperator<BraKetT>;
            using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
            using AbstractIteratorT = AbstractResultIterator<BraKetT>;
            using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;        
            using Iterator = SimpleOperatorIterator<BraKetT>;
            DiagOperator(double value, const BraKetT &site);
            AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const override;
        private:
            const double value;
            const BraKetT site;
        };
     */
}

#endif
