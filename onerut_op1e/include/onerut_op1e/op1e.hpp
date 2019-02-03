#ifndef ONERUT_OP1E
#define ONERUT_OP1E

#include<any>
#include<memory>
#include<iterator>
#include<vector>
#include<optional>

#include<boost/operators.hpp>

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
        virtual value_type operator*() const = 0;
        virtual AbstractResultIterator& operator++() = 0;
        virtual AbstractResultIterator& operator++(int) = 0;
        virtual bool operator==(const AbstractResultIterator & other) const = 0;
        virtual ~AbstractResultIterator() = default;
    };

    template<typename BraKetT>
    class AbstractOperator {
    public:
        virtual std::shared_ptr<AbstractResultIterator<BraKetT>> begin_itptr(const BraKetT arg) const;
        virtual std::shared_ptr<AbstractResultIterator<BraKetT>> end_itptr() const;
    };

    // -------------------------------------------------------------------------
    // ------------------ SIMPLE OPERATOR --------------------------------------
    // -------------------------------------------------------------------------        

    template<typename BraKetT>
    class SimpleOperator : AbstractOperator<BraKetT> {
    public:
        std::shared_ptr<AbstractResultIterator<BraKetT>> begin_itptr(const BraKetT arg) const override;
        std::shared_ptr<AbstractResultIterator<BraKetT>> end_itptr() const override;
        struct SimpleOperatorIterator;
    };

    template<typename BraKetT>
    class SimpleOperator<BraKetT>::SimpleOperatorIterator : public AbstractResultIterator<BraKetT> {
    public:
        static SimpleOperatorIterator create_the_one_valid_iterator(std::pair<double, BraKetT>);
        static SimpleOperatorIterator create_end_iterator();
        typename AbstractResultIterator<BraKetT>::value_type operator*() const override;
        SimpleOperatorIterator& operator++() override;
        SimpleOperatorIterator& operator++(int) override;
        bool operator==(const AbstractResultIterator<BraKetT> & other) const override;
    private:
        SimpleOperatorIterator(std::pair<double, BraKetT> result);
        SimpleOperatorIterator() = default;
        std::optional<std::pair<double, BraKetT>> result; // no value for the end iterator.
    };

    // -------------------------------------------------------------------------
    // ------------------ SIMPLE OPERATOR - IMPLEMENTATION ---------------------
    // -------------------------------------------------------------------------     

    template<typename BraKetT>
    SimpleOperator<BraKetT>::SimpleOperatorIterator::SimpleOperatorIterator(std::pair<double, BraKetT> result) :
    result(result) {
    }

    template<typename BraKetT>
    typename SimpleOperator<BraKetT>::SimpleOperatorIterator
    SimpleOperator<BraKetT>::SimpleOperatorIterator::create_end_iterator() {
        return SimpleOperator<BraKetT>::SimpleOperatorIterator();
    }

    template<typename BraKetT>
    typename SimpleOperator<BraKetT>::SimpleOperatorIterator
    SimpleOperator<BraKetT>::SimpleOperatorIterator::create_the_one_valid_iterator(std::pair<double, BraKetT> result) {
        return SimpleOperator<BraKetT>::SimpleOperatorIterator(result);
    }

    template<typename BraKetT>
    typename AbstractResultIterator<BraKetT>::value_type 
    SimpleOperator<BraKetT>::SimpleOperatorIterator::operator*() const {
        assert(result);
        return *result;
    }

    template<typename BraKetT>
    typename SimpleOperator<BraKetT>::SimpleOperatorIterator&
    SimpleOperator<BraKetT>::SimpleOperatorIterator::operator++() {
        assert(result);
        result.reset();
        return *this;
    }

    template<typename BraKetT>
    typename SimpleOperator<BraKetT>::SimpleOperatorIterator&
    SimpleOperator<BraKetT>::SimpleOperatorIterator::operator++(int) {
        SimpleOperatorIterator result(*this);
        ++(*this);
        return result;
    }

    template<typename BraKetT>
    bool
    SimpleOperator<BraKetT>::SimpleOperatorIterator::operator==(const AbstractResultIterator<BraKetT>& other) const {
        assert(dynamic_cast<SimpleOperatorIterator*> (&other));
        const SimpleOperatorIterator& other_casted = static_cast<SimpleOperatorIterator&> (other);
        return result == other_casted.result;
    }

    // -------------------------------------------------------------------------
    // ------------------ SIMPLE OPERATOR - IMPLEMENTATION ---------------------
    // -------------------------------------------------------------------------    

    // -------------------------------------------------------------------------
    // ------------------ ANY OPERATOR INTERFACE -------------------------------
    // ------------------------------------------------------------------------- 

    //    class Op1e {
    //    public:
    //        virtual std::vector<std::pair<double, std::any>> call(const std::any& arg) const = 0;
    //        virtual ~Op1e() = default;
    //    };

}

#endif