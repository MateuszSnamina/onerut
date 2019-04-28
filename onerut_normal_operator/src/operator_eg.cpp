#include<cassert>

#include<onerut_normal_operator/operator_eg.hpp>

const arma::mat matrix_sigma_x = {
    {+0, +1},
    {+1, +0}
};

const arma::mat matrix_sigma_z = {
    {+1, +0},
    {+0, -1}
};

namespace onerut_normal_operator {

    SigmaXOperator::SigmaXOperator(std::shared_ptr<const EgDomain> domain) :
    DenseOperator(domain, matrix_sigma_x) {
        assert(domain);
    }

    SigmaZOperator::SigmaZOperator(std::shared_ptr<const EgDomain> domain) :
    DenseOperator(domain, matrix_sigma_z) {
        assert(domain);
    }

}