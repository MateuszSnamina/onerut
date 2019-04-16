#include<onerut_parser_exec/ast_x3_to_ast_source.hpp>

namespace onerut_parser_exec::onerut_ast {

    // -------------------------------------------------------------------------
    // ------------- VISITOR ---------------------------------------------------
    // -------------------------------------------------------------------------

    struct ToAstSourceVisitor {
        ToAstSourceVisitor(
                std::shared_ptr<const std::string> input,
                const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions);
        typedef std::shared_ptr<source::SourceNode> result_type;
        template<typename T>
        result_type operator()(const T & info) const;
        const std::shared_ptr<const std::string> input;
        const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions;
    };

    ToAstSourceVisitor::ToAstSourceVisitor(
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) :
    input(input),
    positions(positions) {
    }

    template<typename T>
    ToAstSourceVisitor::result_type ToAstSourceVisitor::operator()(const T & info) const {
        return to_ast_source(info, input, positions);
    }

    // -------------------------------------------------------------------------
    // -------------- FUNCTIONS FOR CONCRETE AST TYPES -------------------------
    // -------------------------------------------------------------------------

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::ExpressionInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        return to_ast_source(info.assign, input, positions);
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::OpAssignInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        const std::shared_ptr<source::SourceNode> second_arg = to_ast_source(info.sum, input, positions);
        if (!info.bit)
            return second_arg;
        const std::shared_ptr<source::SourceNode> first_arg = to_ast_source((*info.bit).identifier, input, positions);
        const string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <= span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<source::OpAssignNode>(input, span, first_arg, second_arg, (*info.bit).new_flag, (*info.bit).const_flag);
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::OpPlusMinusInfo& info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        const std::shared_ptr<source::SourceNode> first_arg = to_ast_source(info.first_arg, input, positions);
        if (info.other_argv.empty())
            return first_arg;
        std::vector<std::shared_ptr < source::SourceNode>> other_argv;
        std::vector<char> opv;
        other_argv.reserve(info.other_argv.size());
        opv.reserve(info.other_argv.size());
        for (const x3::OpPlusMinusBitInfo& arg_info : info.other_argv) {
            assert(arg_info.op == '+' || arg_info.op == '-');
            const std::shared_ptr<source::SourceNode> other_arg = to_ast_source(arg_info.arg, input, positions);
            other_argv.push_back(other_arg);
            opv.push_back(arg_info.op);
        }
        const string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <= span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<source::OpPlusMinusNode>(input, span, first_arg, other_argv, opv);
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::OpProdDivInfo & info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        const std::shared_ptr<source::SourceNode> first_arg = to_ast_source(info.first_arg, input, positions);
        if (info.other_argv.empty())
            return first_arg;
        std::vector<std::shared_ptr < source::SourceNode>> other_argv;
        std::vector<char> opv;
        other_argv.reserve(info.other_argv.size());
        opv.reserve(info.other_argv.size());
        for (const x3::OpProdDivBitInfo& arg_info : info.other_argv) {
            assert(arg_info.op == '*' || arg_info.op == '/');
            const std::shared_ptr<source::SourceNode> other_arg = to_ast_source(arg_info.arg, input, positions);
            other_argv.push_back(other_arg);
            opv.push_back(arg_info.op);
        }
        const string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <= span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<source::OpProdDivNode>(input, span, first_arg, other_argv, opv);
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::OpPowInfo & info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        const std::shared_ptr<source::SourceNode> first_arg = to_ast_source(info.first_arg, input, positions);
        if (!info.other_arg)
            return first_arg;
        const std::shared_ptr<source::SourceNode> other_arg = to_ast_source(*info.other_arg, input, positions);
        const string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <= span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<source::OpPowNode>(input, span, first_arg, other_arg);
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::OpAtInfo & info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        const std::shared_ptr<source::SourceNode> first_arg = to_ast_source(info.first_arg, input, positions);
        if (!info.other_arg)
            return first_arg;
        const std::shared_ptr<source::SourceNode> other_arg = to_ast_source(*info.other_arg, input, positions);
        const string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <= span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<source::OpAtNode>(input, span, first_arg, other_arg);
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::OpArrowInfo & info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        const std::shared_ptr<source::SourceNode> first_arg = to_ast_source(info.first_arg, input, positions);
        if (!info.other_arg)
            return first_arg;
        const std::shared_ptr<source::SourceNode> other_arg = to_ast_source(*info.other_arg, input, positions);
        const string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <= span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<source::OpArrowNode>(input, span, first_arg, other_arg);
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::OpGlueInfo & info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        const std::shared_ptr<source::SourceNode> first_arg = to_ast_source(info.first_arg, input, positions);
        if (!info.other_arg)
            return first_arg;
        const std::shared_ptr<source::SourceNode> other_arg = to_ast_source(*info.other_arg, input, positions);
        const string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <= span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<source::OpGlueNode>(input, span, first_arg, other_arg);
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::Value1Info & info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        const auto visitor = ToAstSourceVisitor(input, positions);
        return boost::apply_visitor(visitor, info);
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::LitDoubleInfo & info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        const string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <= span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<source::LitDoubleNode>(input, span, info.value);
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::LitPureComplexDoubleInfo & info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        const string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <= span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<source::LitPureComplexDoubleNode>(input, span, info.value);
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::LitLongInfo & info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        const string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <= span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<source::LitLongNode>(input, span, info.value);
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::OpUnaryPlusMinusInfo & info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        const std::shared_ptr<source::SourceNode> expression = to_ast_source(info.expression, input, positions);
        if (!info.op)
            return expression;
        const string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <= span.begin());
        assert(span.end() <= input->cend());
        assert(*info.op == '+' || *info.op == '-');
        return std::make_shared<source::UnaryPlusMinusNode>(input, span, *info.op, expression);
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::Value2Info & info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        const auto visitor = ToAstSourceVisitor(input, positions);
        return boost::apply_visitor(visitor, info);
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::FunctionInfo & info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        const std::string name = info.name.name();
        std::vector<std::shared_ptr < source::SourceNode>> argv;
        argv.reserve(info.argv.size());
        for (const x3::ExpressionInfo& arg_info : info.argv) {
            const std::shared_ptr<source::SourceNode> arg = to_ast_source(arg_info, input, positions);
            argv.push_back(arg);
        }
        const string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <= span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<source::FunctionNode>(input, span, name, argv);
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::EmptyFunctionInfo & info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        const std::string name = info.name.name();
        const std::vector<std::shared_ptr < source::SourceNode >> argv;
        const string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <= span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<source::FunctionNode>(input, span, name, argv);
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::IdentifierInfo & info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        const string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <= span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<source::IdentifierNode>(input, span, info.name());
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::NestedExpression1Info & info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        return to_ast_source(info.expression, input, positions);
    }

    std::shared_ptr<source::SourceNode> to_ast_source(
            const x3::NestedExpression2Info & info,
            std::shared_ptr<const std::string> input,
            const boost::spirit::x3::position_cache<std::vector < std::string::const_iterator >>&positions) {
        return to_ast_source(info.expression, input, positions);
    }

}