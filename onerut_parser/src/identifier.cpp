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

    ConstCompileResultRef::ConstCompileResultRef(CompileResult value) :
    value(value) {
    }

    CompileResult ConstCompileResultRef::get_compile_result() const {
        return value;
    }
    //------------------------------------

    CompileResultRef::CompileResultRef(CompileResult value) :
    value(value) {
    }

    CompileResult CompileResultRef::get_compile_result() const {
        return value;
    }

    void CompileResultRef::set_compile_result(CompileResult new_value) {
        value = new_value;
    }
}
