#include<onerut_scalar/scalar.hpp>
#include<onerut_parser/identifier.hpp>

namespace onerut_parser {

    ConstDoubleIdentifier::ConstDoubleIdentifier(double value) :
    value(value) {
    }

    CompileResult ConstDoubleIdentifier::build() const {
        return CompileResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::LitDouble>(value));
    }

    CompileResult ConstDoubleIdentifier::build_dry_run() const {
        return CompileResult::from_type<onerut_scalar::Double>();
    }


}
