#ifndef ONERUT_PARSER_DIAG_REQUEST
#define ONERUT_PARSER_DIAG_REQUEST

#include<memory>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_parser {

    struct DiagRequest {
        DiagRequest(std::shared_ptr<const onerut_normal_operator::AbstractOperator> hamiltonian);
        std::shared_ptr<const onerut_normal_operator::AbstractOperator> hamiltonian;
    };

}

#endif
