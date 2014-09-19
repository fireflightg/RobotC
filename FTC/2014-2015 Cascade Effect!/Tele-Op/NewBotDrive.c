#pragma config(Hubs,   S1, HTMotor, HTServo, HTMotor, none)
#pragma config(Motor,  mtr_S1_C1_1,     driveRight,   tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     lift,  tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     driveLeft,  tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     intake, tmotorNormal, openLoop)

#include "JoystickDriver.c"

#define open 180
#define grab 100
#define closed 0
#define _threshold 20

bool grabberOpen = true;
bool lastGrabState = true;

void init(){

}

void allStop(){
	motor[driveLeft] = 0;
}

float exponentialJoystick(int joyVal){
	return (float)pow((joyVal/12),2);
}

void joyStickOne(){

	if(abs(joystick.joy1_y2)>_threshold){
		motor[driveRight] = -joystick.joy1_y2/abs(joystick.joy1_y2)*exponentialJoystick(joystick.joy1_y2);
	}
	else{
		motor[driveRight] = 0;
	}
	if(abs(joystick.joy1_y1)>_threshold){
		motor[driveLeft] = joystick.joy1_y1/abs(joystick.joy1_y1)*exponentialJoystick(joystick.joy1_y1);
	}
	else{
		motor[driveLeft] = 0;
	}

	if(joy1Btn(6))
		motor[lift] = 50;
	else if(joy1Btn(5))
		motor[lift] = -20;
	else
		motor[lift] = 0;
}

void joyStickTwo(){

}

task main()
{
	init();

	waitForStart();

	while(true){
		joystickOne();
	}
}
