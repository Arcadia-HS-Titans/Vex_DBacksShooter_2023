#include "vex.h"
#include "Timer.h"
#include <thread>

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
motor leftDrive = motor(PORT7, ratio18_1, false);
motor rightDrive = motor(PORT8, ratio18_1, true);
gyro TurnGyroSmart = gyro(Brain.ThreeWirePort.D);
smartdrive Drivetrain = smartdrive(leftDrive, rightDrive,
                                   TurnGyroSmart, 319.19, 320, 130, mm, 1);

// VEXcode generated functions

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */


static bool stopVexProgram = false;
long long currentTime = 0;
Timer checkErrors{"AAA"};

void startSecondThread() {
  while(!stopVexProgram) {
    long long time = checkErrors.getTime() - currentTime;
    if(time >= 1000) {
      Brain.Screen.printAt(10, 20, "Main thread is stalling!");
    } else {
      Brain.Screen.printAt(10, 20, "Main thread is working! ");
    }
    this_thread::sleep_for(20);
  }
}

void vexcodeInit(void) {
  checkErrors.start();
  thread errorChecker{startSecondThread};
  while(!stopVexProgram) {
    // Loop inside here
    leftDrive.spinFor(90, degrees);
    currentTime = checkErrors.getTime();
  }
}