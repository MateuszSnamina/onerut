#ifndef ONERUT_REQUEST_PARSER_REQUEST_PRINT_VALUE
#define ONERUT_REQUEST_PARSER_REQUEST_PRINT_VALUE

#include<cassert>
#include<memory>

#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_env/env.hpp>
#include<onerut_convergence_parameter/convergence_parameter.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/domain_custom.hpp>
#include<onerut_normal_operator/domain_oscillator.hpp>
#include<onerut_normal_operator/domain_spin.hpp>
#include<onerut_normal_operator/domain_eg.hpp>
#include<onerut_normal_operator/domain_fock.hpp>
#include<onerut_normal_operator/domain_kron.hpp>
#include<onerut_normal_operator/eig.hpp>
#include<onerut_normal_operator/mean.hpp>

namespace onerut_request {

    struct PrintValueRequest {
        PrintValueRequest(bool print_only_in_summary = false);
        virtual void print(std::ostream& stream, std::string line_prefix) const = 0;
        bool print_only_in_summary() const;
    private:
        const bool _print_only_in_summary;
    };

    template<class T>
    struct PrintValueRequestTyped : public PrintValueRequest {
    };

    //    template<>
    //    struct PrintValueRequestTyped<onerut_parser_exec::CompileError> : public PrintValueRequest {
    //        using Type =onerut_parser_exec::CompileError;
    //        PrintValueRequestTyped(std::shared_ptr<Type> instance);
    //        void print(std::ostream& stream, std::string line_prefix) const override;
    //        const std::shared_ptr<Type> instance;
    //    };

    template<>
    struct PrintValueRequestTyped<onerut_scalar::Integer> : public PrintValueRequest {
        using Type = onerut_scalar::Integer;
        PrintValueRequestTyped(std::shared_ptr<Type> instance, bool print_only_in_summary = false);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_scalar::Real> : public PrintValueRequest {
        using Type = onerut_scalar::Real;
        PrintValueRequestTyped(std::shared_ptr<Type> instance, bool print_only_in_summary = false);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_scalar::Complex> : public PrintValueRequest {
        using Type = onerut_scalar::Complex;
        PrintValueRequestTyped(std::shared_ptr<Type> instance, bool print_only_in_summary = false);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_env::Env> : public PrintValueRequest {
        using Type = onerut_env::Env;
        PrintValueRequestTyped(std::shared_ptr<Type> instance, bool print_only_in_summary = false);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_convergence_parameter::ConvergenceParameter> : public PrintValueRequest {
        using Type = onerut_convergence_parameter::ConvergenceParameter;
        PrintValueRequestTyped(std::shared_ptr<Type> instance, bool print_only_in_summary = false);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::CustomDomain> : public PrintValueRequest {
        using Type = onerut_normal_operator::CustomDomain;
        PrintValueRequestTyped(std::shared_ptr<Type> instance, bool print_only_in_summary = false);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::OscillatorDomain> : public PrintValueRequest {
        using Type = onerut_normal_operator::OscillatorDomain;
        PrintValueRequestTyped(std::shared_ptr<Type> instance, bool print_only_in_summary = false);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::SpinDomain> : public PrintValueRequest {
        using Type = onerut_normal_operator::SpinDomain;
        PrintValueRequestTyped(std::shared_ptr<Type> instance, bool print_only_in_summary = false);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::EgDomain> : public PrintValueRequest {
        using Type = onerut_normal_operator::EgDomain;
        PrintValueRequestTyped(std::shared_ptr<Type> instance, bool print_only_in_summary = false);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::FockDomain> : public PrintValueRequest {
        using Type = onerut_normal_operator::FockDomain;
        PrintValueRequestTyped(std::shared_ptr<Type> instance, bool print_only_in_summary = false);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::KronDomain> : public PrintValueRequest {
        using Type = onerut_normal_operator::KronDomain;
        PrintValueRequestTyped(std::shared_ptr<Type> instance, bool print_only_in_summary = false);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::StateIndex> : public PrintValueRequest {
        using Type = onerut_normal_operator::StateIndex;
        PrintValueRequestTyped(std::shared_ptr<Type> instance, bool print_only_in_summary = false);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::OrbitalIndex> : public PrintValueRequest {
        using Type = onerut_normal_operator::OrbitalIndex;
        PrintValueRequestTyped(std::shared_ptr<Type> instance, bool print_only_in_summary = false);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::KronPlaceholder> : public PrintValueRequest {
        using Type = onerut_normal_operator::KronPlaceholder;
        PrintValueRequestTyped(std::shared_ptr<Type> instance, bool print_only_in_summary = false);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::AbstractRealOperator> : public PrintValueRequest {
        using Type = onerut_normal_operator::AbstractRealOperator;
        PrintValueRequestTyped(std::shared_ptr<Type> instance, bool print_only_in_summary = false);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::Eig> : public PrintValueRequest {
        using Type = onerut_normal_operator::Eig;
        PrintValueRequestTyped(std::shared_ptr<Type> instance, bool print_only_in_summary = false);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

    template<>
    struct PrintValueRequestTyped<onerut_normal_operator::Mean> : public PrintValueRequest {
        using Type = onerut_normal_operator::Mean;
        PrintValueRequestTyped(std::shared_ptr<Type> instance, bool print_only_in_summary = false);
        void print(std::ostream& stream, std::string line_prefix) const override;
        const std::shared_ptr<Type> instance;
    };

}

#endif
