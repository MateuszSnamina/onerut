#include<cassert>
#include<boost/algorithm/string.hpp>

#include<onerut_parser_exec/ast_source.hpp>

namespace {

    std::string _to_string(const std::string& name, const std::vector<std::string> argv) {
        std::string result;        
        result += name;
        result += "(";
        result += boost::join(argv, ",");
        result += ")";
        return result;
    }
}

namespace onerut_parser_exec::onerut_ast::source {

    std::string IdentifierNode::to_oneliner() const {
        const std::string name = "Identifier";
        const std::vector<std::string> _argv{};
        return _to_string(name, _argv);
    }

    std::string OpAssignNode::to_oneliner() const {
        const std::string name = "OpAssign";
        const std::string _new_flag = (new_flag ? "+NEW" : "-NEW");
        const std::string _const_flag = (new_flag ? "+CONST" : "-CONST");
        const std::vector<std::string> _argv{_new_flag, _const_flag, first_arg->to_oneliner(), second_arg->to_oneliner()};
        return _to_string(name, _argv);
    }

    std::string OpPlusMinusNode::to_oneliner() const {
        const std::string name = "OpPlusMinus";
        const std::string _opv(begin(opv), end(opv));
        std::vector<std::string> _argv;
        _argv.push_back(_opv);
        _argv.push_back(first_arg->to_oneliner());
        for (const auto other_arg : other_argv)
            _argv.push_back(other_arg->to_oneliner());
        return _to_string(name, _argv);
    }

    std::string OpProdDivNode::to_oneliner() const {
        const std::string name = "OpProdDiv";
        const std::string _opv(begin(opv), end(opv));
        std::vector<std::string> _argv;
        _argv.push_back(_opv);
        _argv.push_back(first_arg->to_oneliner());
        for (const auto other_arg : other_argv)
            _argv.push_back(other_arg->to_oneliner());
        return _to_string(name, _argv);
    }

    std::string OpPowNode::to_oneliner() const {
        const std::string name = "OpPow";
        return _to_string(name,{first_arg->to_oneliner(), second_arg->to_oneliner()});
    }

    std::string OpAtNode::to_oneliner() const {
        const std::string name = "OpAt";
        return _to_string(name,{first_arg->to_oneliner(), second_arg->to_oneliner()});
    }

    std::string OpArrowNode::to_oneliner() const {
        const std::string name = "OpArrow";
        return _to_string(name,{first_arg->to_oneliner(), second_arg->to_oneliner()});
    }

    std::string OpGlueNode::to_oneliner() const {
        const std::string name = "OpGlue";
        return _to_string(name,{first_arg->to_oneliner(), second_arg->to_oneliner()});
    }

    std::string UnaryPlusMinusNode::to_oneliner() const {
        const std::string name = "OpUnaryPlusMinus";
        return _to_string(name,{std::string(1, op), arg->to_oneliner()});
    }

    std::string LitLongNode::to_oneliner() const {
        const std::string name = "LitLong";
        return _to_string(name,{std::to_string(value)});
    }

    std::string LitDoubleNode::to_oneliner() const {
        const std::string name = "LitDouble";
        return _to_string(name,{std::to_string(value)});
    }

    std::string LitPureComplexDoubleNode::to_oneliner() const {
        const std::string name = "LitPureComplexDouble";
        return _to_string(name,{std::to_string(value)});
    }

    std::string FunctionNode::to_oneliner() const {
        const std::string name = "Function";
        std::vector<std::string> _argv;
        _argv.push_back(FunctionNode::name);
        for (const auto arg : argv)
            _argv.push_back(arg->to_oneliner());
        return _to_string(name, _argv);
    }

}
