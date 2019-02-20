#include<onerut_scalar/scalar.hpp>
#include<onerut_parser/identifier.hpp>

namespace onerut_parser {

    //------------------

    CompileResultConstRef::CompileResultConstRef(std::string name, CompileResultDeref value) :
    name(name),
    value(value) {
    }

    std::string CompileResultConstRef::get_name() const {
        return name;
    }

    CompileResultDeref CompileResultConstRef::get_compile_result_deref() const {
        return value;
    }

    //------------------------------------

    CompileResultNotConstRef::CompileResultNotConstRef(std::string name, CompileResultDeref value) :
    name(name),
    value(value) {
    }

    std::string CompileResultNotConstRef::get_name() const {
        return name;
    }

    CompileResultDeref CompileResultNotConstRef::get_compile_result_deref() const {
        return value;
    }

    void CompileResultNotConstRef::set_compile_result(CompileResultDeref new_value) {
        value = new_value;
    }

    //------------------

    CompileResultUnsetRef::CompileResultUnsetRef(std::string name) :
    name(name) {
    }

    std::string CompileResultUnsetRef::get_name() const {
        return name;
    }

    CompileResultDeref CompileResultUnsetRef::get_compile_result_deref() const {
        return CompileResultDeref();
    }

}
