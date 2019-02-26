#include<onerut_parser/exec_request.hpp>

namespace onerut_parser {

    ExecRequest::ExecRequest(std::shared_ptr<const onerut_normal_operator::AbstractOperator> hamiltonian) :
    hamiltonian(hamiltonian) {
    }

}
