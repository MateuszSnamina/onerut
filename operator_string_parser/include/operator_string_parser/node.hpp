#ifndef OPERATR_STRING_PARSER_NODE_HPP
#define OPERATR_STRING_PARSER_NODE_HPP

#include<operator_string_parser/span.hpp>
#include<memory>

namespace operator_string_parser {

    class Node {        
        string_const_span;
        std::vector<std::shared_ptr<Node>> childs;
        enum class Type {unrevealed, expression, one_electon_operator, many_electon_operator};
        Type type;        
    };
    
    std::shared_ptr<Node> string_to_tree();
}


#endif