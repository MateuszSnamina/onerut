#include<onerut_scalar/scalar.hpp>
#include<onerut_parser/identifier.hpp>

namespace onerut_parser {

    ConstDoubleHolder::ConstDoubleHolder(double value) :
    value(value) {
    }

    CompileResultDeref ConstDoubleHolder::get_compile_result_deref() const {
        return CompileResultDeref::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::LitDouble>(value));
    }
    //------------------

    CompileResultConstRef::CompileResultConstRef(std::u32string name, CompileResultDeref value) :
    name(name),
    value(value) {
    }

    std::u32string CompileResultConstRef::get_name() const {
        return name;
    }

    CompileResultDeref CompileResultConstRef::get_compile_result_deref() const {
        return value;
    }
    //------------------------------------

    CompileResultNotConstRef::CompileResultNotConstRef(std::u32string name, CompileResultDeref value) :
    name(name),
    value(value) {
    }

    std::u32string CompileResultNotConstRef::get_name() const {
        return name;
    }

    CompileResultDeref CompileResultNotConstRef::get_compile_result_deref() const {
        return value;
    }

    void CompileResultNotConstRef::set_compile_result(CompileResultDeref new_value) {
        value = new_value;
    }
}
