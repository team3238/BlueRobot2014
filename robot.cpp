#include <WPILib.h>
#include "robot.h"
#include "portnums.h"

robot::robot(void){
	joystick = new Joystick(joystickPort);
	theChassis = new chassis(leftFrontTalonPort, leftRearTalonPort, rightFrontTalonPort, rightRearTalonPort);
	theCatapult = new catapult(catapultTalonOnePort, catapultTalonTwoPort, catapultEncoderPortA, catapultEncoderPortB, catapultLimitSwitchPort);
	theCollector = new collector(liftingTalonPort, rollerTalonPort, ballSensorPort, upperLimitSensorPort, lowerLimitSensorPort);
}

void robot::RobotInit() {
	theCatapult->SetMotorPower(-1.0);
	insight_ballDistance.setHeader("Count:");
	insight.registerData(insight_ballDistance, 1);
	insight.startDisplay();
}
	
void robot::DisabledInit() {
	theCollector->ReInit();
	theCatapult->ReInit();
}

void robot::AutonomousInit() {

}

void robot::TeleopInit() {

}
	
void robot::DisabledPeriodic() {
	theCatapult->SetStoppingPoint(0);
	int ballDistance = theCatapult->GetEncoderCount();
	insight_ballDistance.setData(ballDistance);
}

void robot::AutonomousPeriodic() {

}
	
void robot::TeleopPeriodic() {
	float x = joystick->GetRawAxis(1);
	float y = joystick->GetRawAxis(2);
	float twist = joystick->GetRawAxis(3);
	theChassis->SetJoystickData(x, y, -twist);
	if(joystick->GetRawButton(1)){
		theCatapult->SetStoppingPoint(185);
		theCatapult->Fire();
	}
	if(joystick->GetRawButton(2)){
		theCollector->Run();
	}
	if(joystick->GetRawButton(3)){
		theCollector->Disable();
	}
	if(joystick->GetRawButton(4)){
		theCollector->ReInit();
	}
	theCatapult->Idle();
	theCollector->Idle();
	theChassis->Idle();
}


START_ROBOT_CLASS(robot);
