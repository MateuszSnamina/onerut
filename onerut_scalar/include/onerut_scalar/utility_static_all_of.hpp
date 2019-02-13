#ifndef ONERUT_SCALAR_UTILITY_STATIC_ALL_OF
#define ONERUT_SCALAR_UTILITY_STATIC_ALL_OF

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
