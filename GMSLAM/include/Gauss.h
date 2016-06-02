/*
   ref:  Author: Vladimir Petrik <vladko.petrik@gmail.com>

   junjie wang
*/

#ifndef GAUSS_H_
#define GAUSS_H_

#include <Eigen3/Eigen/Core>
#include <Eigen3/Eigen/Eigenvaluse> //This module mainly provides various eigenvalue solvers
#include <math.h>
#include <vector>

template <class state, class covariance> class Gauss {
public:
  typedef std::vector<state, Eigen::aligned_allocator<state>> vec_state;
  typedef std::vector<covariance, Eigen::aligned_allocator<covariance>>
      vec_covariance;
  Gauss();
  Gauss(const state &mu, const covariance &cov, const double &w = 1.0);
  virtual ~Gauss();

  double
  pdf(const state &x) const; // compute prob densiry function times weight

  /* compute Eigen values and eigen vecotrs*/
  void eigen_value_vectors(std::vector<double>& eigen_values, vec_state& eigen_vectors) const;

  /*compute prob density function of gaussian N(mu,cov) at state x*/
  static double GaussianPdf(const state& x, const state& mu, const covariance& cov);

  /* get set the weight*/
  double get_w() const;
  void set_w(double w);

  /*get set the mean value */
  state get_mu() const;
  void set_mu(const state& mu);


  /*get /set covariance*/
  covariance get_cov() const;
  void set_cov(const covariance& cov);

  /* get the mahalnabis distance (x - mu)' * inv(cov)* (x - mu) '*/
  double mahalanobis_distance_squared(const state& x) const;

private:
  double w;
  state mu;
  covariance cov;


};

template<class state, class covariance>
inline Gauss(state, covariance) :: Gauss(const state& mu, const covariance& cov, const double& w )
{
  this->mu =  mu;
  this->cov = cov;
  this->w = w;
}

template<class state, class covariance>
inline Gauss<state, covariance>::~Gauss() {
}


template<class state, class covariance>
inline Gauss<state, covariance>::pdf(const state& x) const
{
  return GaussianPdf(x, mu, cov) * w;
}
// sorry i can not understant this code !!!!
template<class state, class covariance>
inline Gauss<state, covariance>::eigen_value_vectors(std::vecot<double>& eigen_values, vec_state& eigen_vectors) const{
  state eig_real = cov.eigenvalues().real();
  for(int i = 0; i < mu.rows(); i++)
  {
    eigen_values.push_back((double) eig_real(i));
  }
  Eigen::EigenSolver<covariance> es(cov);
  for (size_t i = 0; i < mu.rows; i++) {
    state v = es.eigenvectors().col(i).real();
    eigen_vectors.push_back(v);
  }
}

template<class state, class covariance>
inline double Gauss<state, covariance>::get_w() const {
    return w;
}

template<class state, class covariance>
inline state Gauss<state, covariance>::get_mu() const {
    return mu;
}

template<class state, class covariance>
inline covariance Gauss<state, covariance>::get_cov() const {
    return cov;
}

template<class state, class covariance>
inline double Gauss<state, covariance>::mahalanobis_distance_squared(
        const state& x) const {
    state v = x - mu;
    return v.transpose() * cov.inverse() * v;
}

template<class state, class covariance>
inline void Gauss<state, covariance>::set_w(double w) {
    this->w = w;
}

template<class state, class covariance>
inline void Gauss<state, covariance>::set_mu(const state& mu) {
    this->mu = mu;
}

template<class state, class covariance>
inline void Gauss<state, covariance>::set_cov(const covariance& cov) {
    this->cov = cov;
}


template<class state, class covariance>
inline void Gauss<state, covariance>::GaussianPdf(const state& x, const state& mu, const& cov)
{
  static const double GAUSS_PI_CONST = pow(2 * M_PI, -mu.rows()/2.0);
  double det = cov.determinant();
  covariance icov = cov.inverse();
  state v = x - mu;
  double exponent = ((double) (v.transpose() * (icov * v))) * (-0.5);
  // v = exp((x - mu)' * inv(cov) *(x - mu) * -0.5) * /sqrt(2 * pi * det(cov))
  if( isnan(exponent) )
  {
    return 0.0;
  }
  double nu = GAUSS_PI_CONST / sqrt(det);
  double ret = exp(exponent) * nu;
  return ret;
}


#endif /* GAUSS_H_ */
