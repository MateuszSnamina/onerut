#ifndef ONERUT_PARSER_EXEC_VECTOR_CAT
#define ONERUT_PARSER_EXEC_VECTOR_CAT

#include<vector>

namespace {

    template <typename T>
    std::vector<T> cat(T first, std::vector<T> others) {
        std::vector<T> result;
        result.reserve(others.size());
        result.push_back(first);
        std::copy(cbegin(others), cend(others), back_inserter(result));
        return result;
    }
}

#endif