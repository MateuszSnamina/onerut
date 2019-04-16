#ifndef ONERUT_PARSER_SHARE_FROM
#define ONERUT_PARSER_SHARE_FROM

#include<memory>

// https://stackoverflow.com/questions/657155/how-to-enable-shared-from-this-of-both-parent-and-derived:

namespace {

    // -------------------------------------------------------------------------
    // ---------- Helper functions:  -------------------------------------------
    // -------------------------------------------------------------------------

    template <typename Base>
    inline std::shared_ptr<Base>
    shared_from_base(std::enable_shared_from_this<Base>* base) {
        return base->shared_from_this();
    }

    template <typename Base>
    inline std::shared_ptr<const Base>
    shared_from_base(std::enable_shared_from_this<Base> const* base) {
        return base->shared_from_this();
    }

    // -------------------------------------------------------------------------
    // ---------  Public api:  -------------------------------------------------
    // -------------------------------------------------------------------------

    // Use the below function in derived classes 
    // instead of direct using inherited shared_from_this() member function.
    // i.e use: shared_from(this) instead of: shared_from_this().

    template <typename That>
    inline std::shared_ptr<That>
    shared_from(That* that) {
        return std::static_pointer_cast<That>(shared_from_base(that));
    }

}

#endif
