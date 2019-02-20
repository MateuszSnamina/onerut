#include<onerut_parser/common_visitors.hpp>
#include<onerut_parser/asset_deref.hpp>

namespace onerut_parser {

    // *************************************************************************
    // ********************** HELPER FUNCTIONS   *******************************
    // *************************************************************************

    namespace {

        // ---------------------------------------------------------------------

        struct ValueOrThrowVisitor {
            std::any operator()(const std::monostate&) const;
            std::any operator()(const std::any& x) const;
            std::any operator()(std::shared_ptr<CompileError> error) const;
        };

        std::any
        ValueOrThrowVisitor::operator()(const std::monostate&) const {
            throw std::runtime_error("DereferencedAsset: Empty result type has no value.");
        }

        std::any
        ValueOrThrowVisitor::operator()(const std::any& x) const {
            return x;
        }

        std::any
        ValueOrThrowVisitor::operator()(std::shared_ptr<CompileError> error) const {
            assert(error);
            throw *error;
        }

        // ---------------------------------------------------------------------
        
    }

    // *************************************************************************
    // ********************** DEREFERENCED COMPILE RESULT **********************
    // *************************************************************************    

    AssetDeref::AssetDeref(const VariantType content, FromContentT) :
    _content(content) {
    }

    AssetDeref
    AssetDeref::from_compile_error(std::shared_ptr<CompileError> error) {
        assert(error);
        AssetDeref::VariantType content{
            std::in_place_type<std::shared_ptr < CompileError>>,
            error};
        return AssetDeref(content, from_content);
    }

    std::optional<std::any>
    AssetDeref::value_or_empty() const {
        const ContentOrEmptyVisitor<std::any> value_or_empty_visitor;
        return std::visit(value_or_empty_visitor, _content);
    }

    std::optional<std::shared_ptr < CompileError >>
    AssetDeref::compile_error_or_empty() const {
        const ContentOrEmptyVisitor<std::shared_ptr < CompileError>> compile_error_or_empty_visitor;
        return std::visit(compile_error_or_empty_visitor, _content);
    }

    std::any
    AssetDeref::value_or_throw() const {
        const ValueOrThrowVisitor value_or_throw_visitor;
        return std::visit(value_or_throw_visitor, _content);
    }

    bool
    AssetDeref::is_empty() const {
        const IsContentVisitor<std::monostate> is_empty_visitor;
        return std::visit(is_empty_visitor, _content);
    }

    bool
    AssetDeref::is_either_value_or_type() const {
        const IsContentVisitor<std::any> is_either_value_or_type_visitor;
        return std::visit(is_either_value_or_type_visitor, _content);
    }

    bool
    AssetDeref::is_compile_error() const {
        const IsContentVisitor<std::shared_ptr < CompileError>> is_compile_error_visitor;
        return std::visit(is_compile_error_visitor, _content);
    }

}