#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Motor,  mtr_S1_C1_2,     motorBL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_1,     motorFL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     armR,          tmotorTetrix, openLoop, encoder, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     armL,          tmotorTetrix, openLoop, encoder, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoStandard)
#pragma config(Sensor, S2,     LEGOLS3,            sensorLightActive)
#pragma config(Sensor, S3,     HTIRS2,              sensorI2CCustom)
#pragma config(Sensor, S4,     HTSMUX,              sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "/hitechnic-irseeker-v2.h"
#include "/hitechnic-sensormux.h"
#include "/lego-ultrasound.h"
#include "/lego-light.h"
#include "/hitechnic-force.h"
// The sensor is connected to the first port
// of the SMUX which is connected to the NXT port S1.
// To access that sensor, we must use msensor_S1_1.  If the sensor
// were connected to 3rd port of the SMUX connected to the NXT port S4,
// we would use msensor_S4_3

// Give the sensor a nice easy to use namez
const tMUXSensor HTFS1 = msensor_S4_1;
const tMUXSensor HTFS2 = msensor_S4_2;
const tMUXSensor LEGOLS1 = msensor_S4_3;
const tMUXSensor LEGOLS2 = msensor_S4_4;

int power,fs1,fs2,servoPos,col1,col2,col3,
	dcS1,dcS2,dcS3,dcS4,dcS5,acS1,acS2,acS3,
	acS4,acS5,bottomRow=10,middleRow=1500;

/////////////////////////////////Arm Functions///////////////////////////////////
void raiseArm(int powerLevel){
	motor[armR]=powerLevel;
}

void lowerArm(int powerLevel){
	motor[armR]=-powerLevel;
}
/*
void botRow(){
	while(nMotorEncoder[armL]>
}*/

//////////////////////////////Movement Functions/////////////////////////////////
void forward(int powerLevel){
	motor[motorBL] = powerLevel;
	motor[motorFL] = powerLevel;
	motor[motorBR] = powerLevel;
	motor[motorFR] = powerLevel;
}

void reverse(int powerLevel){
	motor[motorBL] = -powerLevel;
	motor[motorFL] = -powerLevel;
	motor[motorBR] = -powerLevel;
	motor[motorFR] = -powerLevel;
}

void right(int powerLevel){
	motor[motorBL] = -powerLevel;
	motor[motorFL] = powerLevel;
	motor[motorBR] = powerLevel;
	motor[motorFR] = -powerLevel;
}

void left(int powerLevel){
	motor[motorBL] = powerLevel;
	motor[motorFL] = -powerLevel;
	motor[motorBR] = -powerLevel;
	motor[motorFR] = powerLevel;
}

void diagonalFR(int powerLevel){
	motor[motorBL] = 0;
	motor[motorFL] = powerLevel;
	motor[motorBR] = powerLevel;
	motor[motorFR] = 0;
}

void diagonalBL(int powerLevel){
	motor[motorBL] = 0;
	motor[motorFL] = -powerLevel;
	motor[motorBR] = -powerLevel;
	motor[motorFR] = 0;
}

void diagonalFL(int powerLevel){
	motor[motorBL] = powerLevel;
	motor[motorFL] = 0;
	motor[motorBR] = 0;
	motor[motorFR] = powerLevel;
}

void diagonalBR(int powerLevel){
	motor[motorBL] = -powerLevel;
	motor[motorFL] = 0;
	motor[motorBR] = 0;
	motor[motorFR] = -powerLevel;
}

void rotateRight(int powerLevel){
	motor[motorBL] = powerLevel;
	motor[motorFL] = powerLevel;
	motor[motorBR] = -powerLevel;
	motor[motorFR] = -powerLevel;
}

void rotateLeft(int powerLevel){
	motor[motorBL] = -powerLevel;
	motor[motorFL] = -powerLevel;
	motor[motorBR] = powerLevel;
	motor[motorFR] = powerLevel;
}

void stop(){
	motor[motorBL] = 0;
	motor[motorFL] = 0;
	motor[motorBR] = 0;
	motor[motorFR] = 0;
	motor[armR] = 0;
	motor[armL] = 0;
}


////////////////////////////Line Follow Functions///////////////////////////////
void followForward(int powerLevel){
	forward(powerLevel);
	if(SensorValue[LEGOLS1]>50){
		rotateLeft(powerLevel);
	}
	else if(SensorValue[LEGOLS3]>50){
		rotateRight(powerLevel);
	}
	if(SensorValue[LEGOLS1]>50&&SensorValue[LEGOLS3]>50){
		left(powerLevel);
	}
	else if(SensorValue[LEGOLS2]>50){
		right(powerLevel);
	}
}

void followReverse(int powerLevel){
	reverse(powerLevel);
	if(SensorValue[LEGOLS1]>50){
		rotateLeft(powerLevel);
	}
	else if(SensorValue[LEGOLS3]>50){
		rotateRight(powerLevel);
	}
	if(SensorValue[LEGOLS1]>50&&SensorValue[LEGOLS3]>50){
		left(powerLevel);
	}
	else if(SensorValue[LEGOLS2]>50){
		right(powerLevel);
	}
}
//////////////////////////////////////////////////////////////////

void init(){
	fs1 = fs2 = 0; //Force Sensor Values
	servoPos = 0; //Initiate Claw Servo Pos
	servo[servo1] = servoPos; //Set servo to servoPos
	nMotorEncoder[armL] = 0; //Initiate Encoder Pos
	power=50;
	////Column positions left to right////
	col1=col2=col3=0;
}

task main()
{
	forward(50);
	wait1Msec(1000);
	stop();
	wait1Msec(500);
	HTIRS2readAllDCStrength(HTIRS2,dcS1,dcS2,dcS3,dcS4,dcS5);
	HTIRS2readAllACStrength(HTIRS2,acS1,acS2,acS3,acS4,acS5);
	if(acS2<20&&acS4<20&&acS3>20)
		goto column2;
	else if(acS2>acS4)
		goto column1;
	else
		goto column3;

	////////First Column/////////////
	column1:;
	reverse(50);
	wait1Msec(500);
	rotateRight(100);
	wait1Msec(500);
	left(100);
	wait1Msec(1000);
	stop();
	wait1Msec(100);
	while(SensorValue[LEGOLS3]<50){
		forward(100);
	}
	stop();


	while(true){nxtDisplayCenteredTextLine(1,"Column One:");nxtDisplayCenteredTextLine(2,"\n%i\n%i\n%i",acS2,acS3,acS4);}
	////////Second Column/////////////
	column2:;

	stop();


	while(true){nxtDisplayCenteredTextLine(1,"Column Two:");nxtDisplayCenteredTextLine(2,"\n%i\n%i\n%i",acS2,acS3,acS4);}
	////////Third Column//////////////
	column3:;

	stop();


	while(true){nxtDisplayCenteredTextLine(1,"Column Three:");nxtDisplayCenteredTextLine(2,"\n%i\n%i\n%i",acS2,acS3,acS4);}
}
