#ifndef ONERUT_PARSER_EXEC_REQUEST
#define ONERUT_PARSER_EXEC_REQUEST

#include<memory>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_parser {

    struct ExecRequest {
        ExecRequest(std::shared_ptr<const onerut_normal_operator::AbstractOperator> hamiltonian);
        std::shared_ptr<const onerut_normal_operator::AbstractOperator> hamiltonian;
    };

}

#endif
