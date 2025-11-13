#include "EZ-Template/util.hpp"
#include "main.h"
#include "pros/rtos.hpp"
#include "subsystems.hpp"

extern pros::adi::DigitalOut tongue;
extern pros::adi::DigitalOut descore;
extern pros::adi::DigitalOut park;
extern pros::adi::DigitalOut pod;
// extern pros::adi::DigitalOut matchload;
// extern pros::adi::DigitalOut pod;
/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 127;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;
// Was slew the issue??
///
// Constants
///
// 162

void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(12.5, 0.69, 158.0);        // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(15.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(5.7, 0.05, 34, 15.0);       // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 55);      // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 150_ms, 3_in, 350_ms, 350_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.7);

  chassis.odom_look_ahead_set(4_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.4);       // This handles how aggressive the end of boomerang motions are **TRY THIS

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there **EXPERIMENT WITH THIS MAYBE
}

// void descoreUp(){

//   descore.set_value(1);
// }

void rush() {
  default_constants();
  chassis.odom_xyt_set(35_in, -7_in, -90_deg);
  intake.move(127);
  chassis.pid_odom_set({{{-10_in, -48_in, 180_deg}, fwd, 50}}, true);
  chassis.pid_wait_quick_chain();
  tongue.set_value(1);
  chassis.pid_wait_quick_chain();
  pros::delay(100);
  chassis.pid_drive_set(-6, DRIVE_SPEED, true);
}

void SoloSig1() {
  default_constants();
  chassis.odom_xyt_set(-48_in, -15_in, 180_deg);
  intake.move(127);
  tongue.set_value(1);
  chassis.pid_drive_set(30, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(21.5, 100, false);

  chassis.pid_wait_until(10);
  pros::delay(600);
  chassis.pid_targets_reset();

  // chassis.pid_odom_set({{{-60.5_in, -44_in, -91_deg}, fwd, 127}}, true);

  // chassis.pid_wait_quick_chain();
  // pros::delay(180);

  // chassis.pid_drive_set(-10.7, 127, true);

  // chassis.pid_wait_quick_chain();
  // chassis.pid_turn_set(90_deg, TURN_SPEED);
  // chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{-30_in, -42.8_in, -91_deg}, rev, 127}}, false);  // first long goal

  intake2.move(-40);
  intake3.move(-40);
  pros::delay(10);
  chassis.pid_wait_quick_chain();
  descore.set_value(1);
  chassis.pid_drive_set(-4, DRIVE_SPEED, true);
  intake.move(127);
  pros::delay(850);
  chassis.pid_wait_quick_chain();  // finished scoring
  descore.set_value(0);
  chassis.pid_drive_set(17.5, 117, true);
  intake1.move(127);
  intake2.move(0);
  intake3.move(0);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(41_deg, TURN_SPEED);
  tongue.set_value(0);
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{-12_in, -8_in, 45_deg}, fwd, 75}}, true);  // low goal
  chassis.pid_wait_quick_chain();
  intake.move(-110);
  pros::delay(1100);
  chassis.pid_wait_quick_chain();
  intake.move(127);
  chassis.pid_drive_set(-14, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  // descore.set_value(0);

  chassis.pid_odom_set({{{-22.5_in, 29.5_in, 0_deg}, fwd, 110}}, true);  // second blocks
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-16.5, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  intake.move(-127);
  pros::delay(150);
  // chassis.pid_wait_quick_chain();
  intake1.move(127);
  intake2.move(-127);
  intake3.move(127);
  // pros::delay(190);
  // chassis.pid_wait_quick_chain();
  // intake.move(0);

  // chassis.pid_odom_set({{{-48_in, 51_in, -92_deg}, fwd, 60}}, true);
  // tongue.set_value(1);
  // chassis.pid_wait_quick_chain();

  // chassis.pid_drive_set(12.5, DRIVE_SPEED, true);
  // pros::delay(380);
  // chassis.pid_wait_quick_chain();

  // chassis.pid_odom_set({{{-30_in, 52_in, -91_deg}, rev, 90}}, true); //last scoring

  // intake.move(-40);
  // pros::delay(10);
  // chassis.pid_wait_quick_chain();
  // descore.set_value(1);
  // chassis.pid_drive_set(-4, DRIVE_SPEED, true);
  // intake.move(127);

  // pros::delay(1575);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_drive_set(8, 127, true);
  // chassis.pid_wait_quick_chain();

  // chassis.pid_drive_set(-11, DRIVE_SPEED, true);
}

void skills() {
  default_constants();
  chassis.odom_xyt_set(-48_in, -15_in, 180_deg);
  intake.move(127);
  tongue.set_value(1);
  chassis.pid_drive_set(28, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(17.9, 90, true);
  pros::delay(1500);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-10.7, 127, true);

  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{-30_in, -42.7_in, -91_deg}, rev, 127}}, true);  // first long goal

  // pros::delay(10);
  chassis.pid_wait_quick_chain();

  intake.move(-127);
  pros::delay(10);
  descore.set_value(1);
  intake.move(0);
  // chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-3, 80, true);
  pros::delay(160);
  intake.move(127);
  chassis.pid_wait_quick_chain();

  pros::delay(1000);
  chassis.pid_wait_quick_chain();  // finished scoring

  chassis.pid_drive_set(12, 117, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-12, 127, true);
  chassis.pid_wait_quick_chain();
  intake.move(-50);
  chassis.pid_drive_set(22, 117, true);
  descore.set_value(0);
  chassis.pid_wait_quick_chain();
  intake.move(127);
  chassis.pid_odom_set({{{-20_in, -30_in, -91_deg}, rev, 127}}, true);
  chassis.pid_wait();
  tongue.set_value(0);
  chassis.pid_drive_set(-46, 120, true);
  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set({{{48_in, -44_in, -50_deg}, rev, 127}}, true);  // coordinate before second tube
  chassis.pid_wait();

  chassis.pid_turn_set(88_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  tongue.set_value(1);
  intake.move(127);
  chassis.pid_drive_set(13.2, 110, true);
  chassis.pid_wait_quick_chain();
  pros::delay(1000);
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{36_in, -44.7_in, -91_deg}, rev, 90}}, true);  // second scoring of long goal

  chassis.pid_wait_quick_chain();
  intake.move(-127);
  descore.set_value(1);
  pros::delay(10);
  intake.move(0);
  pros::delay(10);
  chassis.pid_wait_quick_chain();
  // intake.move(-127);
  // pros::delay(10);
  // chassis.pid_wait_quick_chain();
  // descore.set_value(1);
  chassis.pid_drive_set(-1.8, 80, true);
  pros::delay(40);
  intake.move(127);
  //
  chassis.pid_wait_quick_chain();
  pros::delay(50);
  // pros::delay(1575);
  chassis.pid_wait_quick_chain();

  // chassis.odom_xyt_set(34.2_in, -44.7_in, -91_deg);


  chassis.pid_drive_set(9, 127, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(2_deg, TURN_SPEED);
  descore.set_value(0);
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{35_in, 51.5_in, 2_deg}, fwd, 127}}, true);  // coordinate before third tube
  chassis.pid_wait();
  chassis.pid_turn_set(88_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  intake.move(127);
  chassis.pid_drive_set(24.3, 110, true);
  chassis.pid_wait_quick_chain();
  pros::delay(1100);
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{27.5_in, 48.5_in, 88_deg}, rev, 80}}, true);  // 3rd scoring
  chassis.pid_wait_quick_chain();

  intake.move(-127);
  pros::delay(10);
  descore.set_value(1);
  intake.move(0);
  pros::delay(10);
  // intake.move(-127);
  // pros::delay(10);
  // chassis.pid_wait_quick_chain();
  // descore.set_value(1);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-1.5, 80, true);
  pros::delay(160);
  intake.move(127);
  chassis.pid_wait_quick_chain();
  pros::delay(1600);
  chassis.pid_wait_quick_chain();

  // chassis.odom_xyt_set(28_in, 48_in, 88_deg);

  chassis.pid_drive_set(13, 117, true);

  // descore.set_value(0);
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{20_in, 36_in, 91_deg}, rev, 127}}, true);
  chassis.pid_wait();
  tongue.set_value(0);
  chassis.pid_drive_set(-46, 120, true);
  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set({{{-48_in, 49_in, 140_deg}, rev, 127}}, true);  // set up in front of 4th tube
  chassis.pid_wait();
  // chassis.pid_drive_set(4, DRIVE_SPEED, true);
  // chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-95_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  descore.set_value(0);
  tongue.set_value(1);
  intake.move(127);
  chassis.pid_drive_set(17, 100, true);
  chassis.pid_wait_quick_chain();
  pros::delay(1100);
  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{-32_in, 50.5_in, -93_deg}, rev, 90}}, true);  // last scoring

  chassis.pid_wait_quick_chain();
  intake.move(-127);
  pros::delay(10);
  descore.set_value(1);
  intake.move(0);
  pros::delay(100);
  chassis.pid_wait_quick_chain();

  // intake.move(-127);
  // pros::delay(10);
  // chassis.pid_wait_quick_chain();
  // descore.set_value(1);
  chassis.pid_drive_set(-3.5, 80, true);
  pros::delay(160);
  intake.move(127);
  chassis.pid_wait_quick_chain();
  pros::delay(1575);
  chassis.pid_wait_quick_chain();

  // chassis.odom_xyt_set(-28.5_in, 51.5_in, -93_deg);
  intake.move(-127);

  chassis.pid_drive_set(8, 127, true);
  chassis.pid_wait_quick_chain();
  tongue.set_value(0);
  chassis.pid_odom_set({{{-63_in, 16.5_in, 179_deg}, fwd, 35}}, true);  // set up in front of park

  // tongue.set_value(1);

  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-18, DRIVE_SPEED, true);
  pod.set_value(1);
  chassis.pid_wait();
  chassis.pid_drive_set(45, 127, true);
  chassis.pid_wait_quick_chain();
  tongue.set_value(0);

  // chassis.pid_odom_set({{{-5_in, -48_in, -90_deg}, fwd, 50}}, true);
  // chassis.pid_wait_quick_chain();
  // pros::delay(400);
  // chassis.pid_drive_set(-6, DRIVE_SPEED, true);
}

void rushRightYay() {
  default_constants();
  chassis.odom_xyt_set(-35_in, -14.37_in, 90_deg);
  intake.move(127);
  chassis.pid_odom_set({{{-16_in, -19_in, 112_deg}, fwd, 127}}, true);

  chassis.pid_wait_quick_chain();
  intake.move(127);

  chassis.pid_odom_set({{{1.4_in, -40_in, 180_deg}, fwd, 127}}, true);
  chassis.pid_wait_quick_chain();
  tongue.set_value(1);
  chassis.pid_wait_quick_chain();
  // pros::delay(100);

  // chassis.pid_drive_set(-6, 127, true);

  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-14, DRIVE_SPEED, true);

  chassis.pid_wait_quick_chain();
  tongue.set_value(0);
  chassis.pid_odom_set({{{-13_in, -27_in, -95_deg}, rev, 127}}, true);

  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(45_deg, TURN_SPEED);

  chassis.pid_wait();
  chassis.pid_drive_set(19, 127, true);
  chassis.pid_wait_quick_chain();

  // chassis.pid_wait_quick_chain();
  // chassis.pid_drive_set(14.5, DRIVE_SPEED, true);
  // chassis.pid_wait_quick_chain();
  intake.move(-127);
  pros::delay(950);

  intake.move(0);
  chassis.pid_drive_set(-48, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  tongue.set_value(1);
  chassis.pid_wait_quick_chain();
  intake.move(127);
  chassis.pid_drive_set(19, 110, true);

  chassis.pid_wait_until(10);
  pros::delay(680);
  chassis.pid_targets_reset();
  // pros::delay(445);
  // chassis.pid_wait_quick_chain();

  // chassis.pid_drive_set(-26, DRIVE_SPEED, true);
  chassis.pid_odom_set({{{-16_in, -49.8_in, -90_deg}, rev, 127}}, true);

  intake.move(-50);
  pros::delay(10);
  intake.move(0);
  
  descore.set_value(1);
  pros::delay(10);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-5, DRIVE_SPEED, true);
  intake.move(127);

  // intake.move(-127);
}

void leftNineBall() {
  default_constants();
  chassis.odom_xyt_set(-35_in, 14.37_in, 90_deg);
  intake.move(127);
  chassis.pid_odom_set({{{-18_in, 19_in, 22_deg}, fwd, 127}}, true);

  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set({{{0.5_in, 45.5_in, -7_deg}, fwd, 127}}, true);
  chassis.pid_wait_quick_chain();
  tongue.set_value(1);

  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-14, 127, true);
  chassis.pid_wait_quick_chain();
  tongue.set_value(0);
  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-12, 127, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  intake.move(0);
  chassis.pid_wait();

  chassis.pid_odom_set({{{-38_in, 52_in, -45_deg}, fwd, 127}}, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-90_deg, TURN_SPEED);

  chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{-20_in, 50.5_in, -92_deg}, rev, 127}}, true);
  descore.set_value(1);
  intake2.move(-120);
  intake3.move(-120);
  pros::delay(30);

  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-6, 127, true);
  intake.move(127);
  pros::delay(700);

  tongue.set_value(1);
  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set({{{-38_in, 51_in, -90_deg}, fwd, 127}}, true);

  chassis.pid_wait_quick_chain();
  intake.move(127);
  descore.set_value(0);
  chassis.pid_drive_set(19, 127, true);

  chassis.pid_wait_until(13);
  pros::delay(625);
  chassis.pid_targets_reset();

  chassis.pid_odom_set({{{-21_in, 51_in, -90_deg}, rev, 70}}, true);

  descore.set_value(1);
  intake1.move(0);
  intake2.move(-120);
  intake3.move(-120);

  pros::delay(30);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-7, 127, true);
  intake.move(127);
}

void rushLeft() {
  default_constants();
  chassis.odom_xyt_set(-35_in, 14.37_in, 90_deg);
  intake.move(127);
  chassis.pid_odom_set({{{-18_in, 19_in, 22_deg}, fwd, 127}}, true);

  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set({{{-0.5_in, 45_in, -8.5_deg}, fwd, 127}}, true);
  chassis.pid_wait_quick_chain();
  tongue.set_value(1);
  chassis.pid_wait_quick_chain();
  // pros::delay(100);

  // chassis.pid_drive_set(-6, 127, true);

  // chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-13, DRIVE_SPEED, true);
  tongue.set_value(0);
  chassis.pid_wait_quick_chain();
  
  intake.move(0);
  chassis.pid_odom_set({{{-13_in, 21.5_in, 40_deg}, rev, 127}}, true);

  // chassis.pid_wait_quick_chain();
  // chassis.pid_odom_set({{{-13_in, -25_in}, rev, 90}}, true);

  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  tongue.set_value(1);

  // tongue.set_value(0);
  chassis.pid_wait();
  chassis.pid_drive_set(-5, 40, true);
  chassis.pid_wait_quick_chain();
  intake.move(-127);
  pros::delay(110);
  intake.move(0);
  chassis.pid_wait_quick_chain();
  intake1.move(90);
  intake2.move(-90);
  intake3.move(90);
  pros::delay(190);
  chassis.pid_wait_quick_chain();
  intake.move(0);

  // intake.move(-127);
  // pros::delay(950);

  // intake.move(0);
  // chassis.pid_drive_set(54, 100, true);

  chassis.pid_odom_set({{{-38_in, 51.5_in, -45_deg}, fwd, 127}}, true);
  tongue.set_value(1);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-90_deg, TURN_SPEED);

  // tongue.set_value(1);
  chassis.pid_wait_quick_chain();
  intake.move(127);
  chassis.pid_drive_set(19, 127, true);

  chassis.pid_wait_until(13);
  pros::delay(550);
  chassis.pid_targets_reset();
  // chassis.pid_wait_quick_chain();
  // pros::delay(400);
  // chassis.pid_wait_quick_chain();
  chassis.pid_odom_set({{{-20_in, 50.7_in, -91_deg}, rev, 70}}, true);

  descore.set_value(1);
  intake2.move(-120);
  intake3.move(-120);
  pros::delay(30);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-6, DRIVE_SPEED, true);
  intake.move(127);
  // tongue.set_value(0);
}

void driving() {
  default_constants();
  chassis.pid_drive_set(48, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(48, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-96, DRIVE_SPEED, true);
  chassis.pid_wait();
}

void firstautoyay() {
  default_constants();
  chassis.odom_xyt_set(-52_in, -13_in, 146_deg);
  intake1.move(127);
  chassis.pid_odom_set({
                           {{-38_in, -28_in, 146_deg}, fwd, 50},          // set up in front of blocks
                           {{-15_in, -14_in, 50_deg}, fwd, DRIVE_SPEED},  // Middle goal
                                                                          // {{6.63_in, 18.42_in, 44.7_deg}, fwd, DRIVE_SPEED},
                                                                          //  {{-12_in, -15_in}, fwd, DRIVE_SPEED}  // THIS IS THE MIDDLE GOAL
                       },
                       true);
  chassis.pid_wait();
  chassis.pid_turn_set(50_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(1, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  pros::delay(600);
  chassis.pid_wait_quick_chain();

  intake.move(-115);
  pros::delay(1200);
  chassis.pid_drive_set(-6, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();
  intake1.move(127);

  chassis.pid_odom_set({{{-12_in, 18_in}, fwd, DRIVE_SPEED}},  // SECOND FUCKING BLOCKS
                       true);

  chassis.pid_wait_quick_chain();
  pros::delay(700);
  chassis.pid_odom_set({{{-3_in, 8_in, 340_deg}, rev, 65}},  // THE TOP MIDDLE GOAL
                       true);

  chassis.pid_wait_quick_chain();
  // middle.set_value(1);
  intake.move(127);
}

// void odom_boomerang_injected_pure_pursuit_example() {
//   chassis.pid_odom_set({{{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
//                         {{12_in, 24_in}, fwd, DRIVE_SPEED},
//                         {{24_in, 24_in}, fwd, DRIVE_SPEED}},
//                        true);
//   chassis.pid_wait();

//   chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
//                        true);
//   chassis.pid_wait();
// }

// void odom_drive_example() {
//   // This works the same as pid_drive_set, but it uses odom instead!
//   // You can replace pid_drive_set with pid_odom_set and your robot will
//   // have better error correction.

//   // default_constants();

//   chassis.odom_xyt_set(0_in, 0_in, 0_deg);

//   chassis.pid_odom_set({{{0_in, 12_in, 0_deg}, fwd, DRIVE_SPEED}}, true);
//   chassis.pid_wait();

//   chassis.pid_odom_set({{{0_in, 6_in, 0_deg}, rev, DRIVE_SPEED}}, true);
//   chassis.pid_wait();

//   chassis.pid_odom_set({{{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED}}, true);
//   chassis.pid_wait();
// }

// //***faulty rotation sensor???
// void odom_boomerang_example() {
//   // Drive forward to (0, 36) forward, end at 45 degrees

//   chassis.pid_odom_set({
//                            {0_in, 30_in},
//                            fwd,
//                            110,
//                        },
//                        true);
//   chassis.pid_wait();
//   chassis.pid_turn_set(135_deg, TURN_SPEED);
//   chassis.pid_wait();
//   chassis.pid_odom_set({{30_in, 0_in}, fwd, 110}, true);
//   chassis.pid_wait();

//   // Drive back to (0, 0) backward, end at 0 degrees
//   // chassis.pid_odom_set({{0, 0, 0}, rev, 110});
//   // chassis.pid_wait();

//   // pros::delay(1000);

//   // chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
//   //                      true);
//   // chassis.pid_wait();
// }

// void testStuff() {
//   chassis.pid_turn_set({10, 26}, fwd, 20);
//   chassis.pid_wait();
//   chassis.pid_odom_set({{10_in, 26_in}, fwd, 20});
//   chassis.pid_wait();
// }

// ///
// // Drive Example
// ///
// void drive_example() {
//   // The first parameter is target inches
//   // The second parameter is max speed the robot will drive at
//   // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
//   // for slew, only enable it when the drive distance is greater than the slew distance + a few inches
//   chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
//   chassis.pid_wait();
//   chassis.pid_turn_set(135_deg, TURN_SPEED);
//   chassis.pid_wait();
//   chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
//   chassis.pid_wait();
// }

// ///
// // Turn Example
// ///

// void angles() {
//   chassis.pid_turn_set(90_deg, TURN_SPEED);
//   chassis.pid_wait_quick_chain();

//   chassis.pid_turn_set(180_deg, TURN_SPEED);
//   chassis.pid_wait_quick_chain();

//   // chassis.pid_turn_set(180_deg, TURN_SPEED);
//   // chassis.pid_wait();
// }

// ///
// // Combining Turn + Drive
// ///
void drive_and_turn() {
  default_constants();
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
}

// ///
// // Wait Until and Changing Max Speed
// ///
// void wait_until_change_speed() {
//   // pid_wait_until will wait until the robot gets to a desired position

//   // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
//   chassis.pid_drive_set(24_in, 30, true);
//   chassis.pid_wait_until(6_in);
//   chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
//   chassis.pid_wait();

//   chassis.pid_turn_set(45_deg, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_turn_set(-45_deg, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_turn_set(0_deg, TURN_SPEED);
//   chassis.pid_wait();

//   // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
//   chassis.pid_drive_set(-24_in, 30, true);
//   chassis.pid_wait_until(-6_in);
//   chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
//   chassis.pid_wait();
// }

// ///
// // Swing Example
// ///
// void swing_example() {
//   // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
//   // The second parameter is the target in degrees
//   // The third parameter is the speed of the moving side of the drive
//   // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

//   chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
//   chassis.pid_wait();

//   chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
//   chassis.pid_wait();

//   chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
//   chassis.pid_wait();

//   chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
//   chassis.pid_wait();
// }

// ///
// // Motion Chaining
// ///
// void motion_chaining() {
//   // Motion chaining is where motions all try to blend together instead of individual movements.
//   // This works by exiting while the robot is still moving a little bit.
//   // To use this, replace pid_wait with pid_wait_quick_chain.
//   chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
//   chassis.pid_wait();

//   chassis.pid_turn_set(45_deg, TURN_SPEED);
//   chassis.pid_wait_quick_chain();

//   chassis.pid_turn_set(-45_deg, TURN_SPEED);
//   chassis.pid_wait_quick_chain();

//   chassis.pid_turn_set(0_deg, TURN_SPEED);
//   chassis.pid_wait();

//   // Your final motion should still be a normal pid_wait
//   chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
//   chassis.pid_wait();
// }

// ///
// // Auto that tests everything
// ///
// void combining_movements() {
//   chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
//   chassis.pid_wait();

//   chassis.pid_turn_set(45_deg, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
//   chassis.pid_wait();

//   chassis.pid_turn_set(0_deg, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_drive_set(-12_in, DRIVE_SPEED, true);
//   chassis.pid_wait();
// }

// ///
// // Interference example
// ///
// void tug(int attempts) {
//   for (int i = 0; i < attempts - 1; i++) {
//     // Attempt to drive backward
//     printf("i - %i", i);
//     chassis.pid_drive_set(-12_in, 127);
//     chassis.pid_wait();

//     // If failsafed...
//     if (chassis.interfered) {
//       chassis.drive_sensor_reset();
//       chassis.pid_drive_set(-2_in, 20);
//       pros::delay(1000);
//     }
//     // If the robot successfully drove back, return
//     else {
//       return;
//     }
//   }
// }

// // If there is no interference, the robot will drive forward and turn 90 degrees.
// // If interfered, the robot will drive forward and then attempt to drive backward.
// void interfered_example() {
//   chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
//   chassis.pid_wait();

//   if (chassis.interfered) {
//     tug(3);
//     return;
//   }

//   chassis.pid_turn_set(90_deg, TURN_SPEED);
//   chassis.pid_wait();
// }

// ///
// // Odom Drive PID
// ///

// ///
// // Odom Pure Pursuit
// ///
// void odom_pure_pursuit_example() {
//   // Drive to 0, 30 and pass through 6, 10 and 0, 20 on the way, with slew
//   chassis.pid_odom_set({{{6_in, 10_in}, fwd, 80},
//                         {{0_in, 40_in}, fwd, 80},
//                         {{0_in, 50_in}, fwd, 80}},
//                        true);
//   chassis.pid_wait();

//   pros::delay(1500);

//   // Drive to 0, 0 backwards
//   chassis.pid_odom_set({{0_in, 0_in}, rev, 80},
//                        true);
//   chassis.pid_wait();
// }

// ///
// // Odom Pure Pursuit Wait Until
// ///
// void odom_pure_pursuit_wait_until_example() {
//   chassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED},
//                         {{12_in, 24_in}, fwd, DRIVE_SPEED},
//                         {{24_in, 24_in}, fwd, DRIVE_SPEED}},
//                        true);
//   chassis.pid_wait_until_index(1);  // Waits until the robot passes 12, 24
//   // Intake.move(127);  // Set your intake to start moving once it passes through the second point in the index
//   chassis.pid_wait();
//   // Intake.move(0);  // Turn the intake off
// }

// ///
// // Odom Boomerang
// ///

// ///
// // Odom Boomerang Injected Pure Pursuit
// ///

// ///
// // Calculate the offsets of your tracking wheels
// ///
void measure_offsets() {
  // Number of times to test
  int iterations = 10;

  // Our final offsets
  double l_offset = 0.0, r_offset = 0.0, b_offset = 0.0, f_offset = 0.0;

  // Reset all trackers if they exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->reset();
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->reset();
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->reset();
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->reset();

  for (int i = 0; i < iterations; i++) {
    // Reset pid targets and get ready for running an auton
    chassis.pid_targets_reset();
    chassis.drive_imu_reset();
    chassis.drive_sensor_reset();
    chassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD);
    chassis.odom_xyt_set(0_in, 0_in, 0_deg);
    double imu_start = chassis.odom_theta_get();
    double target = i % 2 == 0 ? 90 : 270;  // Switch the turn target every run from 270 to 90

    // Turn to target at half power
    chassis.pid_turn_set(target, 63, ez::raw);
    chassis.pid_wait();
    pros::delay(250);

    // Calculate delta in angle
    double t_delta = util::to_rad(fabs(util::wrap_angle(chassis.odom_theta_get() - imu_start)));

    // Calculate delta in sensor values that exist
    double l_delta = chassis.odom_tracker_left != nullptr ? chassis.odom_tracker_left->get() : 0.0;
    double r_delta = chassis.odom_tracker_right != nullptr ? chassis.odom_tracker_right->get() : 0.0;
    double b_delta = chassis.odom_tracker_back != nullptr ? chassis.odom_tracker_back->get() : 0.0;
    double f_delta = chassis.odom_tracker_front != nullptr ? chassis.odom_tracker_front->get() : 0.0;

    // Calculate the radius that the robot traveled
    l_offset += l_delta / t_delta;
    r_offset += r_delta / t_delta;
    b_offset += b_delta / t_delta;
    f_offset += f_delta / t_delta;
  }

  // Average all offsets
  l_offset /= iterations;
  r_offset /= iterations;
  b_offset /= iterations;
  f_offset /= iterations;

  // Set new offsets to trackers that exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->distance_to_center_set(l_offset);
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->distance_to_center_set(r_offset);
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->distance_to_center_set(b_offset);
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->distance_to_center_set(f_offset);
}

// // . . .
// // Make your own autonomous functions here!
// // . . .