#ifndef MOTIONMODEL_H_
#define MOTIONMODEL_H_

#include <Eigen3/Eigen/Core>
#include <boost/random.hpp>
#include <math.h>

using namespace Eigen;

class MotionModel {
public:
  MotionModel() {
    a.push_back(0.005);
    a.push_back(5 * (M_PI / 180));
    a.push_back(0.02);
    a.push_back(0.01);
  }

  // typedef Transform< double, 2, Affine > 	Affine2d
  /*Transformation is an affine transformation stored as a (Dim+1)^2 matrix
   * whose last row is assumed to be [0 ... 0 1].*/
  // typedef Rotation2D< double > 	Rotation2Dd
  /*
  template<typename Scalar>
  class Eigen::Rotation2D< Scalar >
  Represents a rotation/orientation in a 2 dimensional space.*/
}

#endif /* MOTIONMODEL_H_ */
