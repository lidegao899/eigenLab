#include <iostream>
#include <Eigen/Dense>
int main()
{
    // example for array selection
    Eigen::VectorXi v = Eigen::VectorXi::Zero(5);
    v(0) = 1;
    v(1) = 2;
    v(2) = 3;
    v(3) = 4;
    v(4) = 5;
    auto rst = v.array() > 3;
    auto selectTrue = rst.array().select(v, 0);
    auto selectFalse = (!rst).array().select(v, 0);
    std::cout << v << std::endl;
    std::cout << rst << std::endl;
    std::cout << selectTrue << std::endl;
    std::cout << selectFalse << std::endl;
}