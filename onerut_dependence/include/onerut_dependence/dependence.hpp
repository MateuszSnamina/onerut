#ifndef ONERUT_DEPENDENCE_DEPENDENCE
#define ONERUT_DEPENDENCE_DEPENDENCE

#include<vector>
#include<memory>

namespace onerut_dependence {

    class Dependable {
    public:
        virtual std::vector<std::weak_ptr<const Dependable>> dependence() const = 0;
    };

}

#endif
