#ifndef ONERUT_PARSER_EXEC_REQUEST
#define ONERUT_PARSER_EXEC_REQUEST

#include<cassert>
#include<memory>
#include<string>
#include<iostream>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_parser {

    struct ExecRequest {
        virtual void exec(std::ostream& stream, std::string line_prefix = "") const = 0;
    };

    template<class T>
    struct ExecRequestTyped : public ExecRequest {
        ExecRequestTyped(std::shared_ptr<T> asset);
        void exec(std::ostream& stream, std::string line_prefix = "") const final;
        const std::shared_ptr<T> asset;
    };

    template<class T>
    void ExecRequestTyped<T>::exec(std::ostream& stream, std::string line_prefix) const {
        asset->exec(stream, line_prefix);
    }

    template<class T>
    ExecRequestTyped<T>::ExecRequestTyped(std::shared_ptr<T> asset) :
    asset(asset) {
        assert(asset);
    }

}

#endif
