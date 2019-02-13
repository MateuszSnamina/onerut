#ifndef ONERUT_SCALAR_UTILITY_CALLABLE_ON_TUPLE
#define ONERUT_SCALAR_UTILITY_CALLABLE_ON_TUPLE

// This header allows you to apply callable on elements collected in a tuple.
//
// In other words: it provides api to call a callable
// in which the arguments of the callable are passed altogether in a single tuple instance.
//
//
// More details and used names:
//
// For:
// - given callable f of type F, and
// - given tuple t = (t1, t2, ... , tN) of type T, 
//   where T = std::tuple<T1, T2, ..., TN>, and
// - given overload/templates functions set 
//   extract(T1 x), extract(T2 x), ..., extract(TN x)
// expression:
//   callable_on_tuple(f, t)
// is equivalent to:
//   callable(extract(t1), extract(t2), ..., , extract(tN))
//
// Note1: t1, t2, ..., tN may be of different types,
//        but for the each type function extract(Tn) must be defined.
//
// Note2: the function callable_on_tuple(Callable, T)
//        constitutes the whole public api defined in this header.
//
// Reference:
//   https://github.com/iwongu/sqlite3pp/wiki/Using-variadic-templates-with-function-calls-using-tuple

namespace onerut_scalar::utility {

    // -------------------------------------------------------------------------    
    // -----    CallableOnTuple -- helper infrastructure       -----------------
    // -------------------------------------------------------------------------    

    template<size_t N>
    struct CallableOnTupleInpl {
        template<typename F, typename T, typename... A>
        static inline auto apply(F&& f, T&& t, A&&... a)
        -> decltype(CallableOnTupleInpl<N - 1 > ::apply(
                std::forward<F>(f),
                std::forward<T>(t),
                std::get<N - 1 > (std::forward<T>(t)),
                std::forward<A>(a)...)) {
            return CallableOnTupleInpl < N - 1 > ::apply(
                    std::forward<F>(f),
                    std::forward<T>(t),
                    std::get < N - 1 > (std::forward<T>(t)),
                    std::forward<A>(a)...);
        }
    };

    template<>
    struct CallableOnTupleInpl<0> {
        template<typename F, typename T, typename... A>
        static inline auto apply(F&& f, T&&, A&&... a)
        -> decltype(std::forward<F>(f) (extract(std::forward<A>(a))...)) {
            return std::forward<F>(f) (extract(std::forward<A>(a))...);
        }
    };

    // -------------------------------------------------------------------------    
    // -----    CallableOnTuple -- public API                 -----------------
    // -------------------------------------------------------------------------        

    template<typename F, typename T>
    inline
    auto callable_on_tuple(F&& f, T&& t)
    -> decltype(CallableOnTupleInpl<std::tuple_size<typename std::decay<T>::type>::value>::apply(std::forward<F>(f), std::forward<T>(t))) {
        return CallableOnTupleInpl < std::tuple_size<typename std::decay<T>::type>::value>::apply(
                std::forward<F>(f), std::forward<T>(t));
    }

}

#endif