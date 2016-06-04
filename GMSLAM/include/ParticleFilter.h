#include <boost/foreach.hpp>
#include <boost/function.hpp>
#include <boost/random.hpp>
#include <boost/range/combine.hpp>
#include <boost/tuple/tuple.hpp>

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
