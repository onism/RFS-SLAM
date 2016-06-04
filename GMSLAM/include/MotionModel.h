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

  MotionModel(const MotionModel &mm) { this->a = mm.a; }

  ~MotionModel() {}

  // typedef Transform< double, 2, Affine > 	Affine2d
  /*Transformation is an affine transformation stored as a (Dim+1)^2 matrix
   * whose last row is assumed to be [0 ... 0 1].*/
  // typedef Rotation2D< double > 	Rotation2Dd
  /*
  template<typename Scalar>
  class Eigen::Rotation2D< Scalar >
  Represents a rotation/orientation in a 2 dimensional space.*/

  // FIXED:ME should understand this function
  Affine2d motion_model_2d_simple(const Affine2d &rs, const Affine2d &u,
                                  double std_lin, double std_ang) {
    Affine2d uu = Affine2d::Identity();
    uu.translation()[0] = sample(std_lin);
    Rotation2Dd rot(sample(std_ang));
    uu.linear() = rot.toRotationMatrix();
    Affine2d rs_ = rs * u * uu;
    return rs_;
  }

  Affine2d motion_model_2d(const Affine2d &rs, const Affine2d &u) {
    Affine2d rs_ = rs * u;
    Eigen::Rotation2Dd rot(0), rot_(0);
    rot.fromRotationMatrix(rs.rotation());
    rot_.fromRotationMatrix(rs_.rotation());
    double delta_trans = (rs.translation() - rs_.translation()).norm();
    double delta_rot1 = atan2(rs_.translation()(1) - rs.translation()(1),
                              rs_.translation()(0) - rs.translation()(0)) -
                        rot.angle();
    double delta_rot2 = rot_.angle() - rot.angle() - delta_rot1;

    delta_rot1 = norm_angle_diff(delta_rot1);
    delta_rot2 = norm_angle_diff(delta_rot2);

    double n_delta_rot1, n_delta_rot2, n_delta_trans;
    n_delta_rot1 =
        delta_rot1 - sample(a[0] * fabs(norm_angle_PI_2(delta_rot1)) +
                            a[1] * fabs(delta_trans));
    n_delta_trans =
        delta_trans - sample(a[2] * fabs(delta_trans) +
                             a[3] * (fabs(norm_angle_PI_2(delta_rot1)) +
                                     fabs(norm_angle_PI_2(delta_rot2))));
    n_delta_rot2 =
        delta_rot2 - sample(a[0] * fabs(norm_angle_PI_2(delta_rot2)) +
                            a[1] * fabs(delta_trans));
    n_delta_rot1 = norm_angle_diff(n_delta_rot1);
    n_delta_rot2 = norm_angle_diff(n_delta_rot2);

    double x_off = n_delta_trans * cos(rot.angle() + n_delta_rot1);
    double y_off = n_delta_trans * sin(rot.angle() + n_delta_rot1);
    rs_.setIdentity();
    rs_.translation() = rs.translation() + Eigen::Vector2d(x_off, y_off);
    rs_.rotate(Eigen::Rotation2Dd(
        norm_angle_diff(rot.angle() + n_delta_rot1 + n_delta_rot2)));
    return rs_;
  }

  double sample(double std) {
    static boost::mt19937 gen(1);
    boost::normal_distribution<> nd(0, std);
    return nd(gen);
  }
  /* Normalize angle between <-pi pi>*/
  double norm_angle_diff(double angle) const {
    if (angle <= -M_PI)
      angle += 2 * M_PI;
    if (angle > M_PI)
      angle -= 2 * M_PI;
    return angle;
  }

  /* Normalize angle between <-pi/2 pi/2>*/
  double norm_angle_PI_2(double angle) const {

    angle = norm_angle_diff(angle);
    if (angle <= -M_PI_2)
      angle += M_PI;
    if (angle > M_PI_2)
      angle -= M_PI;
    return angle;
  }

public:
  std::vector<double> a;
}

#endif /* MOTIONMODEL_H_ */
