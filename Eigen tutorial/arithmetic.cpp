#include <Eigen3/Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;
int main(int argc, char const *argv[]) {
  MatrixXcf a = MatrixXcf::Random(2, 2);
  cout << "Here is the matrix a\n" << a << endl;
  cout << "Here is the matrox a^T \n"
       << a.transpose() << "\nHere is matrix a \n"
       << a << endl;
  cout << "Here is the conjugate of a \n"
       << a.conjugate() << "\nHere is matrix a \n"
       << a << endl;
  cout << "Here is the matrix a^* \n"
       << a.adjoint() << "\nHere is matrix a \n"
       << a << endl;
  return 0;
}
