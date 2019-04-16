#ifndef ONERUT_PARSER_REQUEST_IMPERATIVE
#define ONERUT_PARSER_REQUEST_IMPERATIVE

#include<cassert>
#include<memory>

#include<onerut_parser_exec/asset_utility.hpp>

namespace onerut_parser {

    struct ImperativeRequest {
        virtual void exec() const = 0;
    };

    // -------------------------------------------------------------------------

    template<class T>
    struct LatchRequestTyped : public ImperativeRequest {
        LatchRequestTyped(std::shared_ptr<T> instance);
        void exec() const final;
        const std::shared_ptr<T> instance;
    };

    template<class T>
    LatchRequestTyped<T>::LatchRequestTyped(std::shared_ptr<T> instance) :
    instance(instance) {
        assert(instance);
    }

    template<class T>
    void LatchRequestTyped<T>::exec() const {
        instance->latch();
    }

    // -------------------------------------------------------------------------

    template<class T>
    struct ResetRequestTyped : public ImperativeRequest {
        ResetRequestTyped(std::shared_ptr<T> instance);
        void exec() const final;
        const std::shared_ptr<T> instance;
    };

    template<class T>
    ResetRequestTyped<T>::ResetRequestTyped(std::shared_ptr<T> instance) :
    instance(instance) {
        assert(instance);
    }

    template<class T>
    void ResetRequestTyped<T>::exec() const {
        instance->reset();
    }

    // -------------------------------------------------------------------------

}
#endif
