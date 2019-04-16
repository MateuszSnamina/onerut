#ifndef ONERUT_PARSER_AST_DYN
#define ONERUT_PARSER_AST_DYN

#include<string>
#include<vector>
#include<memory>

#include<string_utils/string_span.hpp>
#include<onerut_parser_exec/asset.hpp>
#include<onerut_parser_exec/print_chart.hpp>
#include<onerut_parser_exec/compiler_rules.hpp>

namespace onerut_parser_exec::onerut_ast::asset {
    class AssetNode;
}

namespace onerut_parser_exec::onerut_ast::source {

    // *************************************************************************
    // ***********************    Abstract baseclasses   ***********************
    // *************************************************************************

    class SourceNode : public std::enable_shared_from_this<SourceNode> {
    public:
        SourceNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span);
        const std::shared_ptr<const std::string> input;
        const string_utils::string_const_span span;
        virtual ~SourceNode() = 0;
        virtual std::string to_oneliner() const = 0;
        virtual std::shared_ptr<asset::AssetNode> compile(std::shared_ptr<CompilerRules> compiler_rules) const = 0;
        LinesStyledChartInfo to_ast_chart() const;
        virtual void to_ast_chart(
                unsigned deepness,
                LinesStyledChartInfo& ast_chart) const = 0;
        virtual void to_ast_chart_disregard_subsource(
                unsigned deepness,
                LinesStyledChartInfo& ast_chart) const;
    };

    // -------------------------------------------------------------------------

    class WithNoSubsourcesNode : public SourceNode {
    public:
        WithNoSubsourcesNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span);
        void to_ast_chart(
                unsigned deepness,
                LinesStyledChartInfo& ast_chart) const final;
        virtual std::shared_ptr<asset::AssetNode> compile(std::shared_ptr<CompilerRules> compiler_rules) const final;
        virtual Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules) const = 0;
    };

    class WithOneSubsourceNode : public SourceNode {
    public:
        WithOneSubsourceNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span,
                const std::shared_ptr<SourceNode> arg);
        void to_ast_chart(
                unsigned deepness,
                LinesStyledChartInfo& ast_chart) const final;
        virtual std::shared_ptr<asset::AssetNode> compile(std::shared_ptr<CompilerRules> compiler_rules) const final;
        virtual Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset arg_asset) const = 0;
        const std::shared_ptr<SourceNode> arg;
    };

    class WithTwoSubsourcesNode : public SourceNode {
    public:
        WithTwoSubsourcesNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::shared_ptr<SourceNode> second_arg);
        void to_ast_chart(
                unsigned deepness,
                LinesStyledChartInfo& ast_chart) const final;
        virtual std::shared_ptr<asset::AssetNode> compile(std::shared_ptr<CompilerRules> compiler_rules) const final;
        virtual Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset first_arg_asset, Asset second_arg_asset) const = 0;
        const std::shared_ptr<SourceNode> first_arg;
        const std::shared_ptr<SourceNode> second_arg;
    };

    class WithOneOrMoreSubsourcesNode : public SourceNode {
    public:
        WithOneOrMoreSubsourcesNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::vector<std::shared_ptr<SourceNode>> other_argv);
        void to_ast_chart(
                unsigned deepness,
                LinesStyledChartInfo& ast_chart) const final;
        virtual std::shared_ptr<asset::AssetNode> compile(std::shared_ptr<CompilerRules> compiler_rules) const final;
        virtual Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset first_arg_asset, std::vector<Asset> other_argv_asset) const = 0;
        const std::shared_ptr<SourceNode> first_arg;
        const std::vector<std::shared_ptr<SourceNode>> other_argv;
    };

    class WithAnyNumberOfSubsourcesNode : public SourceNode {
    public:
        WithAnyNumberOfSubsourcesNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span,
                std::vector<std::shared_ptr<SourceNode>> argv);
        void to_ast_chart(
                unsigned deepness,
                LinesStyledChartInfo& ast_chart) const final;
        virtual std::shared_ptr<asset::AssetNode> compile(std::shared_ptr<CompilerRules> compiler_rules) const final;
        virtual Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules, std::vector<Asset> argv_asset) const = 0;
        const std::vector<std::shared_ptr<SourceNode>> argv;
    };

    // *************************************************************************
    // ***********************      Concrete classes     ***********************
    // *************************************************************************

    class IdentifierNode : public WithNoSubsourcesNode {
    public:
        IdentifierNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span,
                std::string name);
        std::string to_oneliner() const override;
        Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules) const override;
        const std::string name;
    };

    class LitLongNode : public WithNoSubsourcesNode {
    public:
        LitLongNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span,
                long value);
        std::string to_oneliner() const override;
        Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules) const override;
        const long value;
    };

    class LitDoubleNode : public WithNoSubsourcesNode {
    public:
        LitDoubleNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span,
                double value);
        std::string to_oneliner() const override;
        Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules) const override;
        const double value;
    };

    class LitPureComplexDoubleNode : public WithNoSubsourcesNode {
    public:
        LitPureComplexDoubleNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span,
                double value);
        std::string to_oneliner() const override;
        Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules) const override;
        const double value; // the complex part
    };

    class OpAssignNode : public WithTwoSubsourcesNode {
    public:
        OpAssignNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::shared_ptr<SourceNode> second_arg,
                bool new_flag,
                bool const_flag);
        std::string to_oneliner() const override;
        virtual Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset first_arg_asset, Asset second_arg_asset) const override;
        const bool new_flag;
        const bool const_flag;
    };

    class OpPlusMinusNode : public WithOneOrMoreSubsourcesNode {
    public:
        OpPlusMinusNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::vector<std::shared_ptr<SourceNode>> other_argv,
                std::vector<char> opv);
        std::string to_oneliner() const override;
        virtual Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset first_arg_asset, std::vector<Asset> other_argv_asset) const override;
        const std::vector<char> opv;
    };

    class OpProdDivNode : public WithOneOrMoreSubsourcesNode {
    public:
        OpProdDivNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::vector<std::shared_ptr<SourceNode>> other_argv,
                std::vector<char> opv);
        std::string to_oneliner() const override;
        virtual Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset first_arg_asset, std::vector<Asset> other_argv_asset) const override;
        const std::vector<char> opv;
    };

    class OpPowNode : public WithTwoSubsourcesNode {
    public:
        OpPowNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::shared_ptr<SourceNode> second_arg);
        std::string to_oneliner() const override;
        virtual Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset first_arg_asset, Asset second_arg_asset) const override;
    };

    class OpAtNode : public WithTwoSubsourcesNode {
    public:
        OpAtNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::shared_ptr<SourceNode> second_arg);
        std::string to_oneliner() const override;
        virtual Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset first_arg_asset, Asset second_arg_asset) const override;
    };

    class OpArrowNode : public WithTwoSubsourcesNode {
    public:
        OpArrowNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::shared_ptr<SourceNode> second_arg);
        std::string to_oneliner() const override;
        virtual Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset first_arg_asset, Asset second_arg_asset) const override;
    };

    class OpGlueNode : public WithTwoSubsourcesNode {
    public:
        OpGlueNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span,
                std::shared_ptr<SourceNode> first_arg,
                std::shared_ptr<SourceNode> second_arg);
        std::string to_oneliner() const override;
        virtual Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset first_arg_asset, Asset second_arg_asset) const override;
    };

    class UnaryPlusMinusNode : public WithOneSubsourceNode {
    public:
        UnaryPlusMinusNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span,
                char op,
                std::shared_ptr<SourceNode> arg);
        std::string to_oneliner() const override;
        virtual Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules, Asset arg_asset) const override;
        const char op;
    };

    class FunctionNode : public WithAnyNumberOfSubsourcesNode {
    public:
        FunctionNode(
                std::shared_ptr<const std::string> input,
                string_utils::string_const_span span,
                std::string name,
                std::vector<std::shared_ptr<SourceNode>> argv);
        std::string to_oneliner() const override;
        virtual Asset basic_compile(std::shared_ptr<CompilerRules> compiler_rules, std::vector<Asset> argv_asset) const override;
        const std::string name;
    };

}

#endif
