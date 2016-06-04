#ifndef FILTERBASE_H_
#define FILTERBASE_H_

#include "GMM.h"
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

/*FilterBase is a template library and requires specification of the robot state
 * class, measurement vector class and covariance matrix class. The robot
 * state can be one of the affine transformations types: Affine2d or Affine3d.
 * The only non intuitive restriction for dimen- sion of the state space is that
 * dimension of the robot state has to be smaller or equal to dimension of the
 * measurement vector. Of course covariance matrix has to have dimension
 * comparable to measurement vector so the observation model make sense. */

template <class observation, class covariance, class robot_state>
class FilterBase {
  BOOST_STATIC_ASSERT_MSG(int(observation::RowsAtComplie) >=
                              int(robot_state::RowsAtComplie) - 1,
                          "Robot State Space Dimension must be smaller or "
                          "equal to the Observation State Space Dimension");
  BOOST_STATIC_ASSERT_MSG(
      int(observation::RowsAtComplie) == int(covariance::RowsAtComplie),
      "Covariance and observation dimensions must be equal.");

public:
  FilterBase<observation>
};
#endif FILTERBASE_H_
