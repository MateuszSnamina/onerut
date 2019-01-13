#include<armadillo>

int main() {
  arma::mat X = {{0,1},{1,0}};
  X = X * X;
  arma::mat beta;
  arma::vec epsilon;
  arma::eig_sym(epsilon, beta , X);
  arma::sp_mat Y(5000, 5000);
  Y(0,0) = -5;
  Y(1,1) = -8;
  Y(20,20) = -54;
  Y(3,3) = -2;
  Y(4,4) = -3;
  //arma::eigs_sym(epsilon, beta , Y, 7, "sa");
  //std::cout << epsilon << std::endl;
  //std::cout << beta << std::endl;
}
