#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;
// extern pros::adi::DigitalOut middle;

inline pros::MotorGroup intake({-15, 20});

inline pros::Motor intake1(20);  //bottom
inline pros::Motor intake2(-15);  //top

// inline pros::MotorGroup intake ({17, 10});

// inline pros::Motor intakeTop(10);
// inline pros::Motor intakeBottom(17);

// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');