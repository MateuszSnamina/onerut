#include<onerut_scalar/scalar.hpp>
#include<onerut_parser/identifier.hpp>

namespace onerut_parser {

    ConstDoubleHolder::ConstDoubleHolder(double value) :
    value(value) {
    }

    CompileResult ConstDoubleHolder::get_compile_result() const {
        return CompileResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::LitDouble>(value));
    }
    //------------------

    CompileResultConstRef::CompileResultConstRef(std::u32string name, CompileResult value) :
    name(name),
    value(value) {
    }

    std::u32string CompileResultConstRef::get_name() const {
        return name;
    }

    CompileResult CompileResultConstRef::get_compile_result() const {
        return value;
    }
    //------------------------------------

    CompileResultRef::CompileResultRef(std::u32string name, CompileResult value) :
    name(name),
    value(value) {
    }

    std::u32string CompileResultRef::get_name() const {
        return name;
    }

    CompileResult CompileResultRef::get_compile_result() const {
        return value;
    }

    void CompileResultRef::set_compile_result(CompileResult new_value) {
        value = new_value;
    }
}
