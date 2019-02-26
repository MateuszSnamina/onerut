#ifndef ONERUT_PARSER_EXEC_REQUEST
#define ONERUT_PARSER_EXEC_REQUEST

#include<cassert>
#include<memory>

namespace onerut_parser {

    struct ExecRequest {
        virtual void exec() const = 0;
    };

    template<class T>
    struct ExecRequestTyped : public ExecRequest {
        ExecRequestTyped(std::shared_ptr<T> asset);
        void exec() const final;
        const std::shared_ptr<T> asset;
    };

    template<class T>
    void ExecRequestTyped<T>::exec() const {
        asset->exec();
    }

    template<class T>
    ExecRequestTyped<T>::ExecRequestTyped(std::shared_ptr<T> asset) :
    asset(asset) {
        assert(asset);
    }

}

#endif
