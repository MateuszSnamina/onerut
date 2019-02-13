#ifndef ONERUT_SCALAR_UTILITY_STATIC_ALL_OF
#define ONERUT_SCALAR_UTILITY_STATIC_ALL_OF

// The header defines static_all_of<TrueOrFalseTypes> template.
//
// For a set of TrueOrFalseTypes being std::true_type or std::false_type 
// static_all_of<TrueOrFalseTypes> inherits from std::true_type or std::false_type.
//
// static_all_of<TrueOrFalseTypes> inherits form std::true_type
// when all of TrueOrFalseTypes are std::true_type (or TrueOrFalseTypes pack is empty)
// static_all_of<TrueOrFalseTypes> inherits form std::false_type
// in other cases.
//
//  Reference:
//    https://codereview.stackexchange.com/questions/9736/variadic-function-with-restricted-types

namespace onerut_scalar::utility {

    template <typename ... TrueOrFalseTypes>
    struct static_all_of;

    template <>
    struct static_all_of<>
    : std::true_type {
    };

    template <typename ... TrueOrFalseTypes>
    struct static_all_of<std::false_type, TrueOrFalseTypes...>
    : std::false_type {
    };

    template <typename ... TrueOrFalseTypes>
    struct static_all_of<std::true_type, TrueOrFalseTypes...>
    : static_all_of<TrueOrFalseTypes...>::type {
    };

}

#endif
