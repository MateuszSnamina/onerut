#include<onerut_parser/diag_request.hpp>

namespace onerut_parser {

    DiagRequest::DiagRequest(std::shared_ptr<const onerut_normal_operator::AbstractOperator> hamiltonian) :
    hamiltonian(hamiltonian) {
    }

}
