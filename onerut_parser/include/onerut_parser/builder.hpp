#ifndef ONERUT_PARSER_BUILDER
#define ONERUT_PARSER_BUILDER

#include<onerut_parser/build_result.hpp>

// *****************************************************************************
// ********************** BUILDERS        **************************************
// *****************************************************************************

namespace onerut_parser {

    class Builder {
    public:
        virtual BuildResult run() const = 0;
        virtual BuildResult dry_run() const = 0;
    };

    //class CachedBuilder : public Builder {};

}

#endif
