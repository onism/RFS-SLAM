#include <iostream>
#include <Eigen3/Eigen/Dense>

using namespace std;
using Eigen::MatrixXd;

int main()
{
  MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = 2;
  cout<<m<<endl;
  return 0;
}
