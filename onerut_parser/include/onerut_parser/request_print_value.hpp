#ifndef ONERUT_PARSER_REQUEST_PRINT_VALUE
#define ONERUT_PARSER_REQUEST_PRINT_VALUE

#include<cassert>
#include<memory>

#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/operator_oscillator.hpp>
#include<onerut_normal_operator/operator_spin.hpp>
#include<onerut_normal_operator/diagonalizator.hpp>
#include<onerut_parser/asset_error.hpp>

namespace onerut_parser {

    struct PrintValueRequest {
        virtual void print(std::ostream& stream, std::string line_prefix) const = 0;
    };

    template<class T>
    struct PrintValueRequestTyped : public PrintValueRequest {
    };

    template<>
    struct PrintValueRequestTyped<onerut_parser::CompileError> : public PrintValueRequest {
        using Type = onerut_parser::CompileError;
        PrintValueRequestTyped(std::shared_ptr<Type> instance);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_scalar::Integer> : public PrintValueRequest {
        using Type = onerut_scalar::Integer;
        PrintValueRequestTyped(std::shared_ptr<Type> instance);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_scalar::Real> : public PrintValueRequest {
        using Type = onerut_scalar::Real;
        PrintValueRequestTyped(std::shared_ptr<Type> instance);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_scalar::Complex> : public PrintValueRequest {
        using Type = onerut_scalar::Complex;
        PrintValueRequestTyped(std::shared_ptr<Type> instance);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::CustomDomain> : public PrintValueRequest {
        using Type = onerut_normal_operator::CustomDomain;
        PrintValueRequestTyped(std::shared_ptr<Type> instance);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::OscillatorDomain> : public PrintValueRequest {
        using Type = onerut_normal_operator::OscillatorDomain;
        PrintValueRequestTyped(std::shared_ptr<Type> instance);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::SpinDomain> : public PrintValueRequest {
        using Type = onerut_normal_operator::SpinDomain;
        PrintValueRequestTyped(std::shared_ptr<Type> instance);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::StateIndex> : public PrintValueRequest {
        using Type = onerut_normal_operator::StateIndex;
        PrintValueRequestTyped(std::shared_ptr<Type> instance);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::AbstractOperator> : public PrintValueRequest {
        using Type = onerut_normal_operator::AbstractOperator;
        PrintValueRequestTyped(std::shared_ptr<Type> instance);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::Eigs> : public PrintValueRequest {
        using Type = onerut_normal_operator::Eigs;
        PrintValueRequestTyped(std::shared_ptr<Type> instance);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::Mean> : public PrintValueRequest {
        using Type = onerut_normal_operator::Mean;
        PrintValueRequestTyped(std::shared_ptr<Type> instance);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

}

#endif
