#ifndef ONERUT_SCALAR_UTILITY_FOR_EACH_ON_TUPLE
#define ONERUT_SCALAR_UTILITY_FOR_EACH_ON_TUPLE

namespace onerut_scalar::utility {

    // -------------------------------------------------------------------------    
    // -----    ForEachOnTuple -- helper infrastructure        -----------------
    // -------------------------------------------------------------------------    

    template<size_t N>
    struct ForEachOnTupleImpl {

        template<typename F, typename T>
        static inline void apply(F&& f, T&& t) {
            std::forward<F>(f) (std::get < N - 1 > (std::forward<T>(t)));
            ForEachOnTupleImpl < N - 1 > ::apply(
                    std::forward<F>(f),
                    std::forward<T>(t));
        }
    };

    template<>
    struct ForEachOnTupleImpl<0> {

        template<typename F, typename T>
        static inline void apply(F&& f, T&&) {
        }
    };

    // -------------------------------------------------------------------------    
    // -----    ForEachOnTuple  -- public API                  -----------------
    // -------------------------------------------------------------------------        

    template<typename F, typename T>
    inline
    void for_each_on_tuple(F&& f, T&& t) {
        ForEachOnTupleImpl < std::tuple_size<typename std::decay<T>::type>::value>::apply(
                std::forward<F>(f), std::forward<T>(t));
    }

}

#endif