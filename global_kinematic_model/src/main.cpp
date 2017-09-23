// In this quiz you'll implement the global kinematic model.
#include <math.h>
#include <iostream>
#include "Eigen-3.3/Eigen/Core"

//
// Helper functions
//
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

const double Lf = 2;

// TODO: Implement the global kinematic model.
// Return the next state.
//
// NOTE: state is [x, y, psi, v]
// NOTE: actuators is [delta, a]
Eigen::VectorXd globalKinematic(Eigen::VectorXd state,
                                Eigen::VectorXd actuators, double dt) {
  
  Eigen::VectorXd next_state(state.size());
  
  auto xt = state(0);
  auto yt = state(1);
  auto vt = state(2);
  auto psit = state(3);
  
  auto at = actuators(0);
  auto deltat = actuators(1);

  auto xt1 = xt + ( vt * cos(psit) * dt);
  auto yt1 = yt + ( vt * sin(psit) * dt);
  auto vt1 = vt + ( at * dt );
  auto psit1 = psit + ( ( vt / Lf ) * deltat * dt);
  
  next_state(0) = xt1;
  next_state(1) = yt1;
  next_state(2) = vt1;
  next_state(3) = psit1;
  
  return next_state;
}

int main() {
  // [x, y, psi, v]
  Eigen::VectorXd state(4);
  // [delta, v]
  Eigen::VectorXd actuators(2);

  state << 0, 0, deg2rad(45), 1;
  actuators << deg2rad(5), 1;

  // should be [0.212132, 0.212132, 0.798488, 1.3]
  auto next_state = globalKinematic(state, actuators, 0.3);

  std::cout << next_state << std::endl;
}