#ifndef ONERUT_PARSER_COMMON_VISITORS
#define ONERUT_PARSER_COMMON_VISITORS

#include<optional>

namespace {

    // -------------------------------------------------------------------------

    template<typename VariantContentType>
    struct ContentOrEmptyVisitor {
        using ResultType = std::optional<VariantContentType>;
        ResultType operator()(const VariantContentType& x) const;
        template<typename U>
        ResultType operator()(const U& x) const;
    };

    template<typename VariantContentType>
    typename ContentOrEmptyVisitor<VariantContentType>::ResultType
    ContentOrEmptyVisitor<VariantContentType>::operator()(const VariantContentType& x) const {
        return x;
    }

    template<typename VariantContentType>
    template<typename U>
    typename ContentOrEmptyVisitor<VariantContentType>::ResultType
    ContentOrEmptyVisitor<VariantContentType>::operator()(const U& x) const {
        return std::nullopt;
    }

    // -------------------------------------------------------------------------

    template<typename VariantContentType>
    struct IsContentVisitor {
        bool operator()(const VariantContentType& x) const;
        template<typename U>
        bool operator()(const U& x) const;
    };

    template<typename VariantContentType>
    bool
    IsContentVisitor<VariantContentType>::operator()(const VariantContentType& x) const {
        return true;
    }

    template<typename VariantContentType>
    template<typename U>
    bool
    IsContentVisitor<VariantContentType>::operator()(const U& x) const {
        return false;
    }

    // -------------------------------------------------------------------------
    
}

#endif