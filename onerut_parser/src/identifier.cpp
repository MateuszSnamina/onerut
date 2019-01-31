#include<onerut_scalar/scalar.hpp>
#include<onerut_parser/identifier.hpp>

namespace onerut_parser {

    ConstDoubleIdentifier::ConstDoubleIdentifier(double value) :
    value(value) {
    }

    BuildResult ConstDoubleIdentifier::build() const {
        return BuildResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::LitDouble>(value));
    }

    BuildResult ConstDoubleIdentifier::build_dry_run() const {
        return BuildResult::from_type<onerut_scalar::Double>();
    }


}
