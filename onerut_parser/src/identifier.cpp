#include<onerut_scalar/scalar.hpp>
#include<onerut_parser/identifier.hpp>

namespace onerut_parser {

    ConstDoubleHolder::ConstDoubleHolder(double value) :
    value(value) {
    }

    DereferencedCompileResult ConstDoubleHolder::get_compile_result() const {
        return DereferencedCompileResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::LitDouble>(value));
    }
    //------------------

    CompileResultConstRef::CompileResultConstRef(std::u32string name, DereferencedCompileResult value) :
    name(name),
    value(value) {
    }

    std::u32string CompileResultConstRef::get_name() const {
        return name;
    }

    DereferencedCompileResult CompileResultConstRef::get_compile_result() const {
        return value;
    }
    //------------------------------------

    CompileResultNotConstRef::CompileResultNotConstRef(std::u32string name, DereferencedCompileResult value) :
    name(name),
    value(value) {
    }

    std::u32string CompileResultNotConstRef::get_name() const {
        return name;
    }

    DereferencedCompileResult CompileResultNotConstRef::get_compile_result() const {
        return value;
    }

    void CompileResultNotConstRef::set_compile_result(DereferencedCompileResult new_value) {
        value = new_value;
    }
}
