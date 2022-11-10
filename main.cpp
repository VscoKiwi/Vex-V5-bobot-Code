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
// left_front           motor         11              
// right_front          motor         2               
// left_back            motor         18              
// right_back           motor         20              
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

int AutonNumber = 1;
void pre_auton(void) {
  vexcodeInit();

  Brain.Screen.setPenColor(blue);
 for (int i = 0; i < 8; i++) {
    Brain.Screen.setPenColor(blue);
    Brain.Screen.drawRectangle(5+(60*i), 50, 50, 175, blue);
  }
  while(true) {
    int x = Brain.Screen.xPosition();
    int y = Brain.Screen.yPosition();
    Brain.Screen.setFont(monoM);
    if(50 < y && y < 50+175) {
      for (int i = 0; i < 8;i++) {
        if (5+(60*i) < x && x < (60*(i+1))-5) {
          AutonNumber = i+1;
        }
      }
    }
    Brain.Screen.printAt(5, 30, "Current Auto: %d", AutonNumber); // %d is a formatting character that gets replaced with AutonNumber
    wait(20, msec);
    Brain.Screen.clearLine(1);
  }
}
//Auton code
void autonomous(void) {

  if (AutonNumber == 1) {
    set_tank(20,30);
    wait(500, msec);
    set_tank(0,0);
    set_roller(125);
    wait(75,msec);
    set_roller(0);
  }
  else if (AutonNumber == 2) {
    set_tank(100,100);
    wait(250,msec);
    set_tank(0,100);
    wait(400,msec);
    set_tank(20,20);
    wait(75,msec);
    set_tank(0,0);
    set_roller(125);
    wait(75,msec);
    set_roller(0);
  }
  else if (AutonNumber == 3) {
    // Call Auton 
  }
  else if (AutonNumber == 4) {
    // Call Auton 
  }
  else if (AutonNumber == 5) {
    // Call Auton 
  }
  else if (AutonNumber == 6) {
    // Call Auton 
  }
  else if (AutonNumber == 7) {
    // Call Auton 
  }
  else if (AutonNumber == 8) {
    // Call Auton 
  }
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
}
int main() {
  
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  
  pre_auton();

 
  while (true) {
    wait(100, msec);
  }
}
