#ifndef ONERUT_OP1E
#define ONERUT_OP1E

#include<any>
#include<memory>
#include<vector>

namespace onerut_op1e {

//    class Op1e {
//    public:
//        virtual std::vector<std::pair<double, std::any>> call(const std::any& arg) const = 0;
//        virtual ~Op1e() = default;
//    };
//
//    //    class Simple_Op1e : public Op1e {
//    //    public:
//    //        std::vector<std::pair<double, std::any>> call(const std::any& arg) const final;
//    //        virtual std::pair<double, std::any> call_simple(const std::any& arg) const = 0;
//    //    };
//
//    template<typename T>
//    class TypedOp1e : public Op1e {
//    public:
//        virtual std::vector<std::pair<double, std::any>> call(const std::any& arg) const = 0;
//        std::vector<std::pair<double, T>> typed_call(const T& arg) const final;
//    };
//
//    template<typename T>
//    std::vector<std::pair<double, std::any>> TypedOp1e<T>::call(const std::any& arg) const {
//        const T typed_arg = std::any_cast<T>(arg);
//        const auto typed_results = typed_call(typed_arg);
//        std::vector<std::pair<double, std::any>> results;
//        results.reserve(typed_results.size());
//        for (const auto & typed_result : typed_results) {
//            results.emplace_back(typed_result.first, typed_result.second);
//        }
//        return results;
//    }

}

#endif