#include<onerut_parser/ast_x3_to_ast_dyn.hpp>

namespace onerut_parser::onerut_ast {

    // -------------------------------------------------------------------------
    // ------------- VISITOR ---------------------------------------------------
    // -------------------------------------------------------------------------

    struct to_ast_dyn_visitor {
        to_ast_dyn_visitor(
                std::shared_ptr<const std::u32string> input,
                const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions);
        typedef std::shared_ptr<dyn::ExpressionNode> result_type;
        template<typename T>
        result_type operator()(const T & info) const;
        const std::shared_ptr<const std::u32string> input;
        const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions;
    };

    to_ast_dyn_visitor::to_ast_dyn_visitor(
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) :
    input(input),
    positions(positions) {
    }

    template<typename T>
    to_ast_dyn_visitor::result_type to_ast_dyn_visitor::operator()(const T & info) const {
        return to_ast_dyn(info, input, positions);
    }

    // -------------------------------------------------------------------------
    // -------------- FUNCTIONS FOR CONCRETE AST TYPES -------------------------
    // -------------------------------------------------------------------------

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::ExpressionInfo& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        return to_ast_dyn(info.sum, input, positions);
    }

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::OpPlusMinusInfo& info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        const std::shared_ptr<dyn::ExpressionNode> first_arg = to_ast_dyn(info.first_arg, input, positions);
        if (info.other_argv.empty())
            return first_arg;
        std::vector<std::shared_ptr < dyn::ExpressionNode>> other_argv;
        std::vector<char32_t> opv;
        other_argv.reserve(info.other_argv.size());
        opv.reserve(info.other_argv.size());
        for (const x3::OpPlusMinusBitInfo& arg_info : info.other_argv) {
            assert(arg_info.op == U'+' || arg_info.op == U'-');
            const std::shared_ptr<dyn::ExpressionNode> other_arg = to_ast_dyn(arg_info.arg, input, positions);
            other_argv.push_back(other_arg);
            opv.push_back(arg_info.op);
        }
        const u32string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <=span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<dyn::OpPlusMinusNode>(input, span, first_arg, other_argv, opv);
    }

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::OpProdDivInfo & info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        const std::shared_ptr<dyn::ExpressionNode> first_arg = to_ast_dyn(info.first_arg, input, positions);
        if (info.other_argv.empty())
            return first_arg;
        std::vector<std::shared_ptr < dyn::ExpressionNode>> other_argv;
        std::vector<char32_t> opv;
        other_argv.reserve(info.other_argv.size());
        opv.reserve(info.other_argv.size());
        for (const x3::OpProdDivBitInfo& arg_info : info.other_argv) {
            assert(arg_info.op == U'*' || arg_info.op == U'/');
            const std::shared_ptr<dyn::ExpressionNode> other_arg = to_ast_dyn(arg_info.arg, input, positions);
            other_argv.push_back(other_arg);
            opv.push_back(arg_info.op);
        }
        const u32string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <=span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<dyn::OpProdDivNode>(input, span, first_arg, other_argv, opv);
    }

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::OpPowInfo & info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        const std::shared_ptr<dyn::ExpressionNode> first_arg = to_ast_dyn(info.first_arg, input, positions);
        if (!info.other_arg)
            return first_arg;
        const std::shared_ptr<dyn::ExpressionNode> other_arg = to_ast_dyn(*info.other_arg, input, positions);
        const u32string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <=span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<dyn::OpPowNode>(input, span, first_arg, other_arg);
    }

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::OpAtInfo & info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        const std::shared_ptr<dyn::ExpressionNode> first_arg = to_ast_dyn(info.first_arg, input, positions);
        if (!info.other_arg)
            return first_arg;
        const std::shared_ptr<dyn::ExpressionNode> other_arg = to_ast_dyn(*info.other_arg, input, positions);
        const u32string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <=span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<dyn::OpAtNode>(input, span, first_arg, other_arg);
    }

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::OpArrowInfo & info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        const std::shared_ptr<dyn::ExpressionNode> first_arg = to_ast_dyn(info.first_arg, input, positions);
        if (!info.other_arg)
            return first_arg;
        const std::shared_ptr<dyn::ExpressionNode> other_arg = to_ast_dyn(*info.other_arg, input, positions);
        const u32string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <=span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<dyn::OpArrowNode>(input, span, first_arg, other_arg);
    }

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::OpGlueInfo & info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        const std::shared_ptr<dyn::ExpressionNode> first_arg = to_ast_dyn(info.first_arg, input, positions);
        if (!info.other_arg)
            return first_arg;
        const std::shared_ptr<dyn::ExpressionNode> other_arg = to_ast_dyn(*info.other_arg, input, positions);
        const u32string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <=span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<dyn::OpGlueNode>(input, span, first_arg, other_arg);
    }

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::Value1Info & info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        const auto visitor = to_ast_dyn_visitor(input, positions);
        return boost::apply_visitor(visitor, info);
    }

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::LitDoubleInfo & info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        const u32string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <=span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<dyn::LitDoubleNode>(input, span, info.value);
    }

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::LitIntInfo & info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        const u32string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <=span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<dyn::LitIntNode>(input, span, info.value);
    }

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::OpUnaryPlusMinusInfo & info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        const std::shared_ptr<dyn::ExpressionNode> expression = to_ast_dyn(info.expression, input, positions);
        if (!info.op)
            return expression;
        const u32string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <=span.begin());
        assert(span.end() <= input->cend());
        assert(*info.op == U'+' || *info.op == U'-');
        return std::make_shared<dyn::UnaryPlusMinusNode>(input, span, *info.op, expression);
    }

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::Value2Info & info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        const auto visitor = to_ast_dyn_visitor(input, positions);
        return boost::apply_visitor(visitor, info);
    }

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::FunctionInfo & info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        const std::u32string name = info.name.name();
        std::vector<std::shared_ptr < dyn::ExpressionNode>> argv;
        argv.reserve(info.argv.size());
        for (const x3::ExpressionInfo& arg_info : info.argv) {
            const std::shared_ptr<dyn::ExpressionNode> arg = to_ast_dyn(arg_info, input, positions);
            argv.push_back(arg);
        }
        const u32string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <=span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<dyn::FunctionNode>(input, span, name, argv);
    }

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::IdentifierInfo & info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        const u32string_const_span span = {positions.position_of(info).begin(), positions.position_of(info).end()};
        assert(input);
        assert(input->cbegin() <=span.begin());
        assert(span.end() <= input->cend());
        return std::make_shared<dyn::IdentifierNode>(input, span, info.name());
    }

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::NestedExpression1Info & info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        return to_ast_dyn(info.expression, input, positions);
    }

    std::shared_ptr<dyn::ExpressionNode> to_ast_dyn(
            const x3::NestedExpression2Info & info,
            std::shared_ptr<const std::u32string> input,
            const boost::spirit::x3::position_cache<std::vector < std::u32string::const_iterator >>&positions) {
        return to_ast_dyn(info.expression, input, positions);
    }

}