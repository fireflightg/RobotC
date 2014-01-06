#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,     none,     none,  none)
#pragma config(Motor,  mtr_S1_C1_1,   	empty,tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,  		robotLifter,   		tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     flagSpinner,  	tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     driveLeft,   tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     driveRight,   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     primaryCubeIntake,  tmotorNormal, openLoop, reversed)
#pragma config(Servo,  srvo_S2_C1_1,    cubeDropper,  tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    cubeLifter,   tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    flagExtender,   tServoStandard)
#pragma config(Sensor, S3,     HTCOMPASS,           sensorI2CCustom)//

#include "/hitechnic-compass.h"
#include "JoystickDriver.c"

#define cubeDropperUp 0
#define cubeDropperDown 98
#define CRStop 128
#define CRForward 255
#define CRReverse 0

//Variables
bool intakeOn,joy2Btn_1_Pressed,down;
int cubeLiftCount;

void init(){ //Initiate Robot(servo positions, intake bool)
	bFloatDuringInactiveMotorPWM = false;
	nNoMessageCounterLimit=500;
	cubeLiftCount=0;
	intakeOn = joy2Btn_1_Pressed = down = false;
	servo[cubeDropper] = cubeDropperDown;
	servo[cubeLifter] = CRStop;
	//HTMCstartCal(HTCOMPASS);
}

void allStop(){
	motor[primaryCubeIntake]=0;
	motor[robotLifter]=0;
	motor[driveLeft]=0;
	motor[driveRight]=0;
	motor[flagSpinner]=0;
	motor[motorA]=0;
	motor[motorB]=0;
	servo[cubeLifter]=CRStop;
	servo[cubeDropper]=ServoValue[cubeDropper];
}

float exponentialJoystick(int joyVal){
	return (float)pow((joyVal/12),2);
}

void updateSensors(){
}

void joystickControllerOne() //Driver 1 Controls drive train and hang mechanism

{

	if(joy1Btn(1))
		motor[flagSpinner]=100;
	else if(joy1Btn(3))
		motor[flagSpinner]=-100;
	else
		motor[flagSpinner]=0;

	if(joy1Btn(6)) //Hanging Mecahnism Control
		motor[robotLifter] = 100;
	else if(joy1Btn(5))
		motor[robotLifter] = -100;
	else
		motor[robotLifter] = 0;

	if(joy1Btn(7))
		servo[flagExtender]=CRForward;
	else if(joy1Btn(8))
		servo[flagExtender]=CRReverse;
	else
		servo[flagExtender]=CRStop;

	//Accidental Mode Switch fix
	if(joystick.joy1_TopHat==0){
		motor[driveLeft] = 100;
	}else if(joystick.joy1_TopHat==4){
		motor[driveLeft] = -100;
	}else	if(abs(joystick.joy1_y1)>10){ //Drive train control(tank drive)
		motor[driveLeft] = 100*(abs(joystick.joy1_y1)/joystick.joy1_y1);
		motor[driveRight] = 100*(abs(joystick.joy1_y1)/joystick.joy1_y1);
	}
	else if(abs(joystick.joy1_x1)>10){
		motor[driveLeft] = 100*(abs(joystick.joy1_x1)/joystick.joy1_x1);
		motor[driveRight] = -100*(abs(joystick.joy1_x1)/joystick.joy1_x1);
	}
	else{
		motor[driveLeft] = 0;
		motor[driveRight] = 0;
	}
}

void joystickControllerTwo() //Driver 2 controls cube intake and cube lifter
{
	if(cubeLiftCount<0) //Don't let the count go negative
		cubeLiftCount=0;

	if(joy2Btn(4)){ //Cube dropper Up
		servo[cubeDropper]=cubeDropperUp;
		down=false;
	}
	else if(joy2Btn(3)){ //Cube dropper Down
		servo[cubeDropper]=cubeDropperDown;
		down=true;
		ClearTimer(T2);
	}

	//Continous rotation servo, 0=reverse, 128=stop, 255=forward
	if(joy2Btn(7)){ //Cube lifter Down
		servo[cubeLifter]=CRReverse;
		cubeLiftCount--;
	}
	else if(joy2Btn(8)){ //Cube lifter Up
		servo[cubeLifter]=CRForward;
		cubeLiftCount++;
	}
/*	else if(cubeLiftCount>0&&(down||cubeDropperPos==100)&&time1[T2]>1250){ //Autonomously reset cubeLifter
		if(cubeLiftCount<50) //Reset cubeDropper when at bottom
			cubeDropperPos=0;
		cubeLifterPos=0;
		cubeLiftCount--;
		down=true;
		if(cubeLiftCount<50)
			down=false;
	}*/
	else //Stop
		servo[cubeLifter]=CRStop;

	if(joy2Btn(1)&&!joy2Btn_1_Pressed){ //Intake toggle on if last tick button 1 was Up
		intakeOn=!intakeOn;
		joy2Btn_1_Pressed=true;
	}
	if(!joy2Btn(1))
		joy2Btn_1_Pressed=false;
	if(joystick.joy2_TopHat==4)
		motor[primaryCubeIntake] = 100;
	else if(joy2Btn(2)){ //Reverse intake. Overrides intake forward
		//HTMCstopCal(HTCOMPASS);
		motor[primaryCubeIntake] = -35;
		intakeOn = false;
		motor[motorA] = -100;
		motor[motorB] = -100;
	}
	else if(intakeOn){ //Intake forward if toggle on
		motor[primaryCubeIntake] = 100;
		motor[motorA] = 100;
		motor[motorB] = 100;
	}
	else{ //Stop intake
		motor[primaryCubeIntake] = 0;
		motor[motorA] = 0;
		motor[motorB] = 0;
	}
}

task main(){

	init();

	waitForStart();

	ClearTimer(T1);

	while(true){
		if(bDisconnected){ //Stop Robot if disconnected
			allStop();
		}else{
			joystickControllerOne();
			joystickControllerTwo();
      nxtDisplayCenteredTextLine(2, "%i", HTMCreadHeading(HTCOMPASS));
		}
	}
}
