#include <boost/foreach.hpp>
#include <boost/function.hpp>
#include <boost/random.hpp>
#include <boost/range/combine.hpp>
#include <boost/tuple/tuple.hpp>
using namesapce std;
using namespace boost;

template <class particle> class ParticleFilter {

public:
  typedef boost::function<double(particle &)>
      weight_function_ptr; // point to weight function

private:
  typedef boost::tuple<double &, particle &> pw_tuple;

public:
  ParticleFilter(unsigned int num_of_particles, const particle &initial_state);
  virtual ~ParticleFilter();

  void set_weigt_function(weight_function_ptr f);

  void update_and_resample(bool inverse_weight = false);

  void update_weights();

  void resample();

  void normalize_weights(bool inverse_weight = false);

  particle get_maximum_weight_particle();

public:
  std::vector<particle> particles;
  std::vector<double> weights;

private:
  weight_function_ptr fnct_w;
};

template <class particle>
inline ParticleFilter<particle>::ParticleFilter(
    unsigned int number_of_particles, const particle &initial_state) {
  double w = 1.0 / number_of_particles;
  weights.resize(number_of_particles, w);
  particles.resize(number_of_particles, initial_state);
}

template <class particle> inline ParticleFilter<particle>::~ParticleFilter() {}

template <class particle>
inline void ParticleFilter<particle>::update_weights() {

  if (!fnct_w) {
    std::cout << "weights function is not set -- can not update weights "
              << std::endl;
    return;
  }
  // FIXED: I do not understand
  BOOST_FOREACH (pw_tuple p, combine(weights, particles)) {
    get<0>(p) = fnct_w(get(1)(p));
  }
}

template <class particle>
inline void
ParticleFilter<particle>::set_weight_function(weight_function_ptr f) {
  fnct_w = f;
}
// FIXED: this should add systemic resample and multiple resample and so on
template <class particle> inline void ParticleFilter<particle>::resample() {
  static boost::mt19937 gen(time(NULL));
  boost::random::discrete_distribution<> dist(weights.begin(), weights.end());
  std::vecor<particle> new_ps;
  new_ps.reserve(particles.size());
  for (size_t i = 0; i < particles.size(); i++) {
    new_ps.push_back(particles[dist(gen)]);
  }
  particles = new_ps();
}

template <class particle>
inline void ParticleFilter<particle>::update_and_resample(bool inverse_weight) {
  update_weights();
  normalize_weights(inverse_weight);
  resample();
}
template <class particle>
inline void ParticleFilter<particle>::normalize_weights(bool inverse_weight) {
  if (inverse_weight) {
    double maximum = *std::max_element(weights.begin(), weights.end());
    BOOST_FOREACH (double &w, weights) { w = maximum - w; }

    double sum = 0.0;
    BOOST_FOREACH (const double &w, weights) { sum += w; }
    if (std::numeric_limits<double>::epsilon() > sum) {
      sum = weights.size();
      BOOST_FOREACH (double &w, weights) { w /= sum; }
    }
  }
}

template <class particle>
inline void ParticleFilter<particle>::get_maximum_weight_particle() {
  unsigned int ind = std::distance(
      weights.begin(), std::max_element(weights.begin(), weights.end()));
  return particles[ind];
}
