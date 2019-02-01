#ifndef ONERUT_PARSER_BUILDER
#define ONERUT_PARSER_BUILDER

#include<onerut_parser/compile_result.hpp>

// *****************************************************************************
// ********************** BUILDERS        **************************************
// *****************************************************************************

namespace onerut_parser {

    class Builder {
    public:
        virtual CompileResult build() const = 0;
        virtual CompileResult build_dry_run() const = 0;
    };

    //class CachedBuilder : public Builder {};

}

#endif
