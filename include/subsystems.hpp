#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

inline pros::MotorGroup intake({-11, 20});

inline pros::Motor intake1(20);  //bottom
inline pros::Motor intake2(-11);  //top

// inline pros::MotorGroup intake ({17, 10});

// inline pros::Motor intakeTop(10);
// inline pros::Motor intakeBottom(17);

// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');