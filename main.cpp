/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\amadden                                          */
/*    Created:      Tue Nov 08 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// left_front           motor         2               
// right_front          motor         3               
// left_back            motor         4               
// right_back           motor         5               
// Roller               motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

const int SCALE = 120;
void set_tank(int left, int right) {
  left_front.spin(fwd, left*SCALE, voltageUnits::mV);
  left_back.spin(fwd, left*SCALE, voltageUnits::mV);
  right_front.spin(fwd, right*SCALE, voltageUnits::mV);
  right_back.spin(fwd, right*SCALE, voltageUnits::mV);
}
//This sets the tank to a spin determined by the amount the 
//joystick is moved multipled by a predetermined scalar, the SCALE

void set_roller(int input) {
  Roller.spin(forward, input*SCALE, voltageUnits::mV);
}
//This sets the Rollar to spin the amount of an input

void pre_auton(void) {
  vexcodeInit();
}
//Auton code
void autonomous(void) {

}

void usercontrol(void) {
  while(true) {
    int left_joy = Controller1.Axis3.position();
    int right_joy = Controller1.Axis2.position();
    //sets variables left_joy and right_joy to joystick position
    if (abs(left_joy) < 5) {
      left_joy = 0;
    }
    //top and bottom both allow the joysticks to return to 0 quicker
    if (abs(right_joy) < 5) {
      right_joy=0;
    }

    set_tank(left_joy,right_joy);
    //sets the robot spin to the joystick values
    

    if(Controller1.ButtonL2.pressing()) {
      set_roller(100);
    }
    else {
      set_roller(0);
    }
    //if button is pressed rollars moves forward, else its off
    wait(20,msec);
    //sleeps Zzzzzzz.... good night robot!
}

int main() {
  
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  
  pre_auton();

 
  while (true) {
    wait(100, msec);
  }
}
