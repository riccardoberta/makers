#include "BasicLinearAlgebra.h"

using namespace BLA;

class Kalman {
  
  private:
    // time step
    float dt = 0.01f;                                                                  

    // state
    Matrix<3,1> x = { 0, 
                      0, 
                      0 };

    // error covariance 
    Matrix<3,3> P_matrix = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };                              

    // error covariance 
    Matrix<3,3> A_matrix = { 1, dt, 0, 
                             0,  1, 0, 
                             0,  0, 1 };

    // process noise covariance                          
    Matrix<3,3> Q_matrix = { 0.001,   0,   0, 
                               0, 0.001,   0, 
                               0,   0, 0.001 };   

    // control input
    Matrix<3,1> B_matrix = { 0, 0, 0 };                                                       
    Matrix<1,1> u = { 0 };                                                             

    // Measurement
    Matrix<2,1> z = { 0, 
                      0 };

    // Observation matrix                                                          
    Matrix<2,3> H_matrix = { 1, 0, 0, 
                             0, 1, 1 };

    // Measurement noise covariance
    Matrix<2,2> R_matrix = { 0.1,   0, 
                               0, 0.1 };                                         

  public:
    Kalman2() { };

    float filter(float accelerometer, float giroscope, float dt) {

      z(0,0) = accelerometer;
      z(1,0) = giroscope;
      
      // Project the state ahead
      A_matrix(0,1) = dt;
      x = A_matrix*x + (B_matrix*u);
      
      // Project the error covariance ahead
      P_matrix = A_matrix*P_matrix*~A_matrix + Q_matrix;
      
      // Calculate Kalman gain
      Matrix<3,2> K_matrix = P_matrix*~H_matrix * (H_matrix*P_matrix*~H_matrix + R_matrix).Inverse();

      // Update estimate with measurement
      x = x + K_matrix * (z - H_matrix*x);

      // Update the error covariance
      P_matrix = P_matrix - K_matrix*H_matrix*P_matrix;

      //Serial << "x: " << x << '\n'; 
      
      return x(0,0);
    };
};
