#ifndef ONERUT_PRESENTER_DEPENDABLE_HPP
#define ONERUT_PRESENTER_DEPENDABLE_HPP

#include<onerut_dependence/dependence.hpp>
#include<onerut_convergence_parameter/convergence_parameter.hpp>
#include<onerut_normal_operator/eig.hpp>
#include<onerut_normal_operator/mean.hpp>
#include<onerut_request/request_print_value.hpp>
#include<onerut/presenter.hpp>

//TODO move to  cpp file!!!!

struct DependablePresenter;

struct DependablePresenterFrame {
    DependablePresenterFrame(
            const DependablePresenter & presenter,
            const std::shared_ptr<const onerut_dependence::Dependable>& dependable);
    const DependablePresenter & _presenter;
    const std::shared_ptr<const onerut_dependence::Dependable>& _dependable;
};

DependablePresenterFrame::DependablePresenterFrame(
        const DependablePresenter & presenter,
        const std::shared_ptr<const onerut_dependence::Dependable>& dependable) :
_presenter(presenter),
_dependable(dependable) {
}

struct DependablePresenter {
    DependablePresenter(
            const Presenter< onerut_convergence_parameter::ConvergenceParameter>& presenter_for_convergence_parameter_objects,
            const Presenter< onerut_normal_operator::Eig>& presenter_for_eig_objects,
            const Presenter< onerut_normal_operator::Mean>& presenter_for_mean_objects,
            const Presenter< onerut_request::PrintValueRequest>& presenter_for_print_value_request_objects);
    DependablePresenterFrame operator()(std::shared_ptr<const onerut_dependence::Dependable> dependable) const;
    const Presenter< onerut_convergence_parameter::ConvergenceParameter>& _presenter_for_convergence_parameter_objects;
    const Presenter< onerut_normal_operator::Eig>& _presenter_for_eig_objects;
    const Presenter< onerut_normal_operator::Mean>& _presenter_for_mean_objects;
    const Presenter< onerut_request::PrintValueRequest>& _presenter_for_print_value_request_objects;
};

std::ostream& operator<<(std::ostream& stream, const DependablePresenterFrame& frame) {
    if (const auto& casted = std::dynamic_pointer_cast<const onerut_convergence_parameter::ConvergenceParameter>(frame._dependable)) {
        stream << "[CONVERGENCE PARAMETER] "
                << frame._presenter._presenter_for_convergence_parameter_objects(casted);
    }
    if (const auto& casted = std::dynamic_pointer_cast<const onerut_normal_operator::Eig>(frame._dependable)) {
        stream << "[EIG] "
                << frame._presenter._presenter_for_eig_objects(casted);
    }
    if (const auto& casted = std::dynamic_pointer_cast<const onerut_normal_operator::Mean>(frame._dependable)) {
        stream << "[MEAN] "
                << frame._presenter._presenter_for_mean_objects(casted);
    }
    if (const auto& casted = std::dynamic_pointer_cast<const onerut_request::PrintValueRequest>(frame._dependable)) {
        stream << "[REQUEST] "
                << frame._presenter._presenter_for_print_value_request_objects(casted);
    }
    return stream;
}

DependablePresenter::DependablePresenter(
        const Presenter<onerut_convergence_parameter::ConvergenceParameter>& presenter_for_convergence_parameter_objects,
        const Presenter<onerut_normal_operator::Eig>& presenter_for_eig_objects,
        const Presenter<onerut_normal_operator::Mean>& presenter_for_mean_objects,
        const Presenter<onerut_request::PrintValueRequest>& presenter_for_print_value_request_objects) :
_presenter_for_convergence_parameter_objects(presenter_for_convergence_parameter_objects),
_presenter_for_eig_objects(presenter_for_eig_objects),
_presenter_for_mean_objects(presenter_for_mean_objects),
_presenter_for_print_value_request_objects(presenter_for_print_value_request_objects) {
}

DependablePresenterFrame
DependablePresenter::operator()(std::shared_ptr<const onerut_dependence::Dependable> dependable) const {
    return DependablePresenterFrame(*this, dependable);
}

#endif