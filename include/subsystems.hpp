#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;
// extern pros::adi::DigitalOut middle;

inline pros::MotorGroup intake({8, -3, -4});

inline pros::Motor intake1(8);  //bottom
inline pros::Motor intake2(-3);  //top
inline pros::Motor intake3(-4);  //yay

// inline pros::MotorGroup intake ({17, 10});

// inline pros::Motor intakeTop(10);
// inline pros::Motor intakeBottom(17);

// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');