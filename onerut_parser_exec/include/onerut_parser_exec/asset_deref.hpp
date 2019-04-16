#ifndef ONERUT_PARSER_ASSET_DEREF
#define ONERUT_PARSER_ASSET_DEREF

#include<cassert>
#include<memory>
#include<variant>
#include<optional>
#include<any>
#include<stdexcept>

#include<onerut_parser_exec/asset_error.hpp>

namespace onerut_parser {

    // *************************************************************************
    // ********************** DEREFERENCED COMPILE RESULTS *********************
    // *************************************************************************

    class AssetDeref {
    public:
        // Construction:
        AssetDeref() = default;
        AssetDeref(const AssetDeref&) = default;
        AssetDeref(AssetDeref&&) = default;
        AssetDeref & operator=(const AssetDeref&) = default;
        AssetDeref & operator=(AssetDeref&&) = default;
        template<typename T> static AssetDeref from_type();
        template<typename T> static AssetDeref from_value(std::shared_ptr<T> value);
        static AssetDeref from_compile_error(std::shared_ptr<CompileError> error);
        // Accessors and predicates:
        template<typename T> bool is_given_type() const;
        std::optional<std::any> value_or_empty() const;
        std::optional<std::shared_ptr<CompileError>> compile_error_or_empty() const;
        std::any value_or_throw() const;
        template<typename T> std::optional<std::shared_ptr<T>> typed_value_or_empty() const;
        template<typename T> std::shared_ptr<T> typed_value_or_throw() const;
        bool is_empty() const;
        bool is_either_value_or_type() const;
        bool is_compile_error() const;
    private:
        using VariantType = std::variant<
                std::monostate,
                std::shared_ptr<CompileError>,
                std::any>;
        VariantType _content;
        // We use the tag 'from_content' to mope up the overload issues:
        // DereferencedAsset(VariantType) vs DereferencedAsset(DereferencedAsset&)
        struct FromContentT;
        static const FromContentT from_content;
        AssetDeref(const VariantType content, FromContentT);
    };

    struct AssetDeref::FromContentT {
    };

    // *************************************************************************
    // ********   TEMPLATES IMPLEMENTATION -- HELPER FUNCTIONS  ****************
    // *************************************************************************

    namespace {

        template<typename T>
        struct IsGivenTypeVisitor {
            using AnyContentType = std::shared_ptr<T>;
            using ResultType = bool;

            ResultType operator()(const std::any& x) const {
                try {
                    std::any_cast<AnyContentType>(x);
                } catch (std::bad_any_cast &) {
                    return false;
                }
                return true;
            }

            template<typename U>
            ResultType operator()(const U& x) const {
                return false;
            }
        };

        template<typename T>
        struct TypedValueOrThrowVisitor {
            using ResultType = std::shared_ptr<T>;

            ResultType operator()(const std::monostate&) const {
                throw std::runtime_error("BuildResult: Empty result type has no value.");
            }

            ResultType operator()(const std::any& x) const {
                try {
                    return std::any_cast<ResultType>(x);
                } catch (std::bad_any_cast &) {
                    throw std::runtime_error("BuildResult: Result type mismatch.");
                }
            }

            ResultType operator()(std::shared_ptr<CompileError> error) const {
                assert(error);
                throw *error;
            }

        };

        template<typename T>
        struct TypedValueOrEmptyVisitor {
            using AnyContentType = std::shared_ptr<T>;
            using ResultType = std::optional<AnyContentType>;

            ResultType operator()(const std::any& x) const {
                try {
                    return std::any_cast<AnyContentType>(x);
                } catch (std::bad_any_cast &) {
                    return ResultType();
                }
            }

            template<typename U>
            ResultType operator()(const U& x) const {
                return ResultType();
            }

        };

    }

    // *************************************************************************
    // ********   TEMPLATES IMPLEMENTATION   ***********************************
    // *************************************************************************

    template<typename T>
    AssetDeref AssetDeref::from_type() {
        std::shared_ptr<T> value;
        AssetDeref::VariantType content{
            std::in_place_type<std::any>,
            value};
        return AssetDeref(content, from_content);
    }

    template<typename T>
    AssetDeref AssetDeref::from_value(std::shared_ptr<T> value) {
        assert(value);
        AssetDeref::VariantType content{
            std::in_place_type<std::any>,
            value};
        return AssetDeref(content, from_content);
    }

    template<typename T>
    bool AssetDeref::is_given_type() const {
        const IsGivenTypeVisitor<T> is_given_type_visitor;
        return std::visit(is_given_type_visitor, _content);
    }

    template<typename T>
    std::optional<std::shared_ptr<T>> AssetDeref::typed_value_or_empty() const {
        const TypedValueOrEmptyVisitor<T> type_value_or_empty_visitor;
        return std::visit(type_value_or_empty_visitor, _content);
    }

    template<typename T>
    std::shared_ptr<T> AssetDeref::typed_value_or_throw() const {
        const TypedValueOrThrowVisitor<T> type_value_or_throw_visitor;
        return std::visit(type_value_or_throw_visitor, _content);
    }

}
#endif
