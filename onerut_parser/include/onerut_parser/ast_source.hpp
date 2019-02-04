#ifndef ONERUT_PARSER_AST_DYN
#define ONERUT_PARSER_AST_DYN

#include<string>
#include<vector>
#include<memory>

#include<string_utils/string_span.hpp>
#include<onerut_parser/compile_result.hpp>
#include<onerut_parser/print_chart.hpp>

namespace onerut_parser::onerut_ast::compile_result {
    class CompileResultNode;
}

namespace onerut_parser::onerut_ast::source {

    // *************************************************************************
    // ***********************    Abstract baseclasses   ***********************
    // *************************************************************************

    class SourceNode : public std::enable_shared_from_this<SourceNode> {
    public:
        SourceNode(
                std::shared_ptr<const std::string> input,
                string_const_span span);
        const std::shared_ptr<const std::string> input;
        const string_const_span span;
        virtual ~SourceNode() = 0;
        virtual std::string to_oneliner() const = 0;
        virtual std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> compile() const = 0;
        LinesStyledChartInfo to_chart() const;
        virtual void to_chart(
                unsigned deepness,
                LinesStyledChartInfo& chart) const = 0;
        virtual void to_chart_disregard_subsource(
                unsigned deepness,
                LinesStyledChartInfo& chart) const;
    };

    // -------------------------------------------------------------------------

    class WithNoSubsourcesNode : public SourceNode {
    public:
        WithNoSubsourcesNode(
                std::shared_ptr<const std::string> input,
                string_const_span span);
        void to_chart(
                unsigned deepness,
                LinesStyledChartInfo& chart) const final;
        virtual std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> compile() const final;
        virtual CompileResult basic_compile() const = 0;
    };

    class WithOneSubsourceNode : public SourceNode {
    public:
        WithOneSubsourceNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                const std::shared_ptr<SourceNode> arg);
        void to_chart(
                unsigned deepness,
                LinesStyledChartInfo& chart) const final;
        virtual std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> compile() const final;
        virtual CompileResult basic_compile(CompileResult arg_compile_result) const = 0;
        const std::shared_ptr<SourceNode> arg;
    };

    class WithTwoSubsourcesNode : public SourceNode {
    public:
        WithTwoSubsourcesNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::shared_ptr<SourceNode> second_arg);
        void to_chart(
                unsigned deepness,
                LinesStyledChartInfo& chart) const final;
        virtual std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> compile() const final;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const = 0;
        const std::shared_ptr<SourceNode> first_arg;
        const std::shared_ptr<SourceNode> second_arg;
    };

    class WithOneOrMoreSubsourcesNode : public SourceNode {
    public:
        WithOneOrMoreSubsourcesNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::vector<std::shared_ptr<SourceNode>> other_argv);
        void to_chart(
                unsigned deepness,
                LinesStyledChartInfo& chart) const final;
        virtual std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> compile() const final;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, std::vector<CompileResult> other_argv_compile_result) const = 0;
        const std::shared_ptr<SourceNode> first_arg;
        const std::vector<std::shared_ptr<SourceNode>> other_argv;
    };

    class WithAnyNumberOfSubsourcesNode : public SourceNode {
    public:
        WithAnyNumberOfSubsourcesNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                std::vector<std::shared_ptr<SourceNode>> argv);
        void to_chart(
                unsigned deepness,
                LinesStyledChartInfo& chart) const final;
        virtual std::shared_ptr<onerut_parser::onerut_ast::compile_result::CompileResultNode> compile() const final;
        virtual CompileResult basic_compile(std::vector<CompileResult> argv_compile_result) const = 0;
        const std::vector<std::shared_ptr<SourceNode>> argv;
    };

    // *************************************************************************
    // ***********************      Concrete classes     ***********************
    // *************************************************************************

    class IdentifierNode : public WithNoSubsourcesNode {
    public:
        IdentifierNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                std::string name);
        std::string to_oneliner() const override;
        CompileResult basic_compile() const override;
        const std::string name;
    };

    class LitLongNode : public WithNoSubsourcesNode {
    public:
        LitLongNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                long value);
        std::string to_oneliner() const override;
        CompileResult basic_compile() const override;
        const long value;
    };

    class LitDoubleNode : public WithNoSubsourcesNode {
    public:
        LitDoubleNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                double value);
        std::string to_oneliner() const override;
        CompileResult basic_compile() const override;
        const double value;
    };

    class OpAssignNode : public WithTwoSubsourcesNode {
    public:
        OpAssignNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::shared_ptr<SourceNode> second_arg,
                bool new_flag,
                bool const_flag);
        std::string to_oneliner() const override;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const override;
        const bool new_flag;
        const bool const_flag;
    };

    class OpPlusMinusNode : public WithOneOrMoreSubsourcesNode {
    public:
        OpPlusMinusNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::vector<std::shared_ptr<SourceNode>> other_argv,
                std::vector<char> opv);
        std::string to_oneliner() const override;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, std::vector<CompileResult> other_argv_compile_result) const override;
        const std::vector<char> opv;
    };

    class OpProdDivNode : public WithOneOrMoreSubsourcesNode {
    public:
        OpProdDivNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::vector<std::shared_ptr<SourceNode>> other_argv,
                std::vector<char> opv);
        std::string to_oneliner() const override;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, std::vector<CompileResult> other_argv_compile_result) const override;
        const std::vector<char> opv;
    };

    class OpPowNode : public WithTwoSubsourcesNode {
    public:
        OpPowNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::shared_ptr<SourceNode> second_arg);
        std::string to_oneliner() const override;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const override;
    };

    class OpAtNode : public WithTwoSubsourcesNode {
    public:
        OpAtNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::shared_ptr<SourceNode> second_arg);
        std::string to_oneliner() const override;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const override;
    };

    class OpArrowNode : public WithTwoSubsourcesNode {
    public:
        OpArrowNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::shared_ptr<SourceNode> second_arg);
        std::string to_oneliner() const override;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const override;
    };

    class OpGlueNode : public WithTwoSubsourcesNode {
    public:
        OpGlueNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::shared_ptr<SourceNode> second_arg);
        std::string to_oneliner() const override;
        virtual CompileResult basic_compile(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const override;
    };

    class UnaryPlusMinusNode : public WithOneSubsourceNode {
    public:
        UnaryPlusMinusNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                char op,
                std::shared_ptr<SourceNode> arg);
        std::string to_oneliner() const override;
        virtual CompileResult basic_compile(CompileResult arg_compile_result) const override;
        const char op;
    };

    class FunctionNode : public WithAnyNumberOfSubsourcesNode {
    public:
        FunctionNode(
                std::shared_ptr<const std::string> input,
                string_const_span span,
                std::string name,
                std::vector<std::shared_ptr<SourceNode>> argv);
        std::string to_oneliner() const override;
        virtual CompileResult basic_compile(std::vector<CompileResult> argv_compile_result) const override;
        const std::string name;
    };

}

#endif
