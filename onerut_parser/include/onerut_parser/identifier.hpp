#ifndef ONERUT_PARSER_IDENTIFIER
#define ONERUT_PARSER_IDENTIFIER

#include<onerut_parser/builder.hpp>

namespace onerut_parser {

    class ConstDoubleIdentifier : public Builder {
    public:
        ConstDoubleIdentifier(double value);
        CompileResult build() const;
        CompileResult build_dry_run() const;
        const double value;
    };

    // ConstDoubleRefIdentifier TODO
    // RefDoubleIdentifier TODO

}

#endif
