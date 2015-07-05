/**
-----------------------------------------------------------------------------
@file    wheel_soil.hpp
----------------------------------------------------------------------------
         @@
       @@@@@@
      @```@@@@
     @`  `@@@@@@
   @@`   `@@@@@@@@
  @@`    `@@@@@@@@@           Tohoku University
  @` `   `@@@@@@@@@       SPACE ROBOTICS LABORATORY
  @`` ## `@@@@@@@@@    http://www.astro.mech.tohoku.ac.jp/
  @` #..#`@@@@@@@@@        Planetary Robotics Group
  @` #..#`@@@@@@@@@
  @` ### `@@@@@@@@@          Professor Kazuya Yoshida
  @` ###``@@@@@@@@@      Associate Professor Keiji Nagatani
   @### ``@@@@@@@@
   ###  ` @@@@@@@
  ###  @  @@@@@                 Creation Date:
 ###    @@@@@               @date Dec. 16. 2014
 /-\     @@
|   |      %%                      Authors:
 \-/##    %%%%%             @author Kei Nakata
   #### %%%                  menschenjager.mark.neun@gmail.com
     ###%%       *
      ##%%     *****
       #%%      ***
        %%     *   *
         %%
          %%%%%
           %%%
-----------------------------------------------------------------------------
@brief Encapsulates Bekker-Wong Theory for Vehicle-Wheel Interactionshear
-----------------------------------------------------------------------------
*/
#pragma once
#include<cmath>
#include <functional>
#include <eigen3/Eigen/Core>

#include "angle.hpp"

using std::function;

/*
*    @struct Soil
*    @brief parameters for Soil
*/
struct Soil {
    double phi {0.0}; //! angle of internal shearing resistance
    double c {298.123};               //! cohesion[Pa]
    double K {0.00068509};            //! shear deformation modulus[m]
    double k1 {0.141e6};             //! pressure sinkage modulus 1
    double k2 {0.0};                   //! pressure sinkage modulus 2
    double n {0.89};                  //! exponent of sinkage to width ratio
    double gamma {0.0575};            //! density[N/m^3]
    double d{1.0}; // sink constant[m/]
    double a0{0.4}; // max sigma angle constant1
    double a1{0.15}; //max sigma angle constant2
};

/*
*    @struct Wheel
*    @brief parameters for wheel
*/
struct Wheel {
    /* Wheel properties */
    double r {0.13};                   //! radius[m]
    double b {0.16};                   //! width[m]
    double w {135};                   //! vertical axle load[N]
    Eigen::Vector3d velocity;
};

/*
*    @class WheelSoil
*    @brief Encapsulates Bekker-Wong Theory for Vehicle-Wheel Interaction
*/
class WheelSoil
{
private:
    Soil soil_;
    Wheel wheel_;
    double getSigma1_(const double& theta, const double& theta1) const;
    double getSigma2_(const double& theta, const double& theta1, const double& theta2,
                      const double& theta_m) const;
public:
    WheelSoil(const Soil& soil, const Wheel& wheel);
    double getSigma(const double& theta, const double& theta1, const double& theta2,
                    const double& theta_m) const;
    double getTau_x(const double& theta, const double& theta1, const double& theta2,
                  const double& theta_m, const double& slip) const;
    double getTorque(const double& theta1, const double& theta2, const double& theta_m, const double& slip) const;
    double getDrawbar(const double& theta1, const double& theta2, const double& theta_m, const double& slip) const;
    double getTau_y(const double& theta, const double& theta1, const double& theta2, const double& theta_m, const double& slip, const double& beta) const;
    Eigen::Vector3d getForce(double slip, double theta1, double theta2) const;
};

