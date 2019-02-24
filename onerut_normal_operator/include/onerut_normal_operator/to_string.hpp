#ifndef ONERUT_NORMAL_OPERATOR_TO_STRING
#define ONERUT_NORMAL_OPERATOR_TO_STRING

#include<string>
#include<onerut_normal_operator/operator_abstract.hpp>

namespace onerut_normal_operator {

    std::string to_string(const Domain& domain);
    std::string to_string(const AbstractOperator& op, std::string line_prefix = "");

}

#endif
