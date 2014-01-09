#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,     none,     none,  none)
#pragma config(Motor,  mtr_S1_C1_1,           empty,tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,                  robotLifter,                   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     flagSpinner,          tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     driveLeft,   tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     driveRight,   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     primaryCubeIntake,  tmotorNormal, openLoop, reversed)
#pragma config(Servo,  srvo_S2_C1_1,    cubeDropper,  tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    cubeLifter,   tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    flagExtender,   tServoStandard)
#pragma config(Sensor, S3,     HTCOMPASS,           sensorI2CCustom)//
#pragma config(Sensor, S4,     HTIRS,           sensorI2CCustom)

//TODO: Change end of crate check
//			Calibrate compass sensor

#include "/hitechnic-irseeker-v2.h"
#include "/hitechnic-compass.h"
#include "JoystickDriver.c"

#define fullHeight 4.5
#define cubeDropperUp 0
#define cubeDropperDown 135
#define cubeLifterStop 128
#define cubeLifterUp 255
#define cubeLifterDown 0
int dcS1,dcS2,dcS3,dcS4,dcS5,compassHeading;
float time,time2,wait=0.0; //Seconds
bool irFound,cubeRaised;

void init(){
 				HTMCsetTarget(HTCOMPASS);
        bFloatDuringInactiveMotorPWM = false;
        irFound=cubeRaised=false;
        servo[cubeDropper] = cubeDropperUp;
        servo[cubeLifter] = cubeLifterStop;
}

//Movement Functions
void forward(int powerLevel,float seconds){
        motor[driveLeft] = powerLevel;
        motor[driveRight] = powerLevel;
        wait1Msec(seconds*1000);
        motor[driveLeft] = 0;
        motor[driveRight] = 0;
}
void forward(int powerLevel){
        motor[driveLeft] = powerLevel;
        motor[driveRight] = powerLevel;
}

void reverse(int powerLevel,float seconds){
        motor[driveLeft] = -powerLevel;
        motor[driveRight] = -powerLevel;
        wait1Msec(seconds*1000);
        motor[driveLeft] = 0;
        motor[driveRight] = 0;
}
void reverse(int powerLevel){
        motor[driveLeft] = -powerLevel;
        motor[driveRight] = -powerLevel;
}

void left(int powerLevel,float seconds){
        motor[driveLeft] = -powerLevel;
        motor[driveRight] = powerLevel;
        wait1Msec(seconds*1000);
        motor[driveLeft] = 0;
        motor[driveRight] = 0;
}
void left(int powerLevel){
        motor[driveLeft] = -powerLevel;
        motor[driveRight] = powerLevel;
}

void compassLeft(int powerLevel, int targetCompassHeading){
	while(abs(compassHeading-targetCompassHeading)>2){
		left(powerLevel);
	}
  motor[driveLeft] = 0;
  motor[driveRight] = 0;
}

void right(int powerLevel,float seconds){
        motor[driveLeft] = powerLevel;
        motor[driveRight] = -powerLevel;
        wait1Msec(seconds*1000);
        motor[driveLeft] = 0;
        motor[driveRight] = 0;
}
void right(int powerLevel){
        motor[driveLeft] = powerLevel;
        motor[driveRight] = -powerLevel;
}

void driveStop(){
        motor[driveLeft] = 0;
        motor[driveRight] = 0;
}
void allStop(){
        motor[primaryCubeIntake]=0;
        motor[robotLifter]=0;
        motor[driveLeft]=0;
        motor[driveRight]=0;
        motor[flagSpinner]=0;
        motor[motorA]=0;
        motor[motorB]=0;
        servo[cubeLifter]=128;
        servo[cubeDropper]=ServoValue[cubeDropper];
}

//Secondary Actions
void dropCube(){
        servo[cubeDropper] = cubeDropperDown;
}

void cubeUp(){
        servo[cubeDropper] = cubeDropperUp;
}

void raiseCube(float seconds){
        servo[cubeLifter]=255;
        wait1Msec(seconds*1000);
        servo[cubeLifter]=128;
}

void lowerCube(float seconds){
        servo[cubeLifter]=0;
        wait1Msec(seconds*1000);
        servo[cubeLifter]=128;
}

void intakeOn(float seconds){
        motor[primaryCubeIntake] = 100;
        wait1Msec(seconds*1000);
        motor[primaryCubeIntake] = 0;
}

void raiseArms(float seconds){
        motor[robotLifter] = 100;
        wait1Msec(seconds*1000);
        motor[robotLifter] = 0;
}

void lowerArms(float seconds){
        motor[robotLifter] = -100;
        wait1Msec(seconds*1000);
        motor[robotLifter] = 0;
}

void DEBUG(){
        nxtDisplayCenteredTextLine(1,"IRSENSOR");
        nxtDisplayCenteredTextLine(2,"%i",dcS1);
        nxtDisplayCenteredTextLine(3,"%i",dcS2);
        nxtDisplayCenteredTextLine(4,"%i",dcS3);
        nxtDisplayCenteredTextLine(5,"%i",dcS4);
        nxtDisplayCenteredTextLine(6,"%i",dcS5);
}

task raiseCubeLifter(){
	raiseCube(fullHeight);
	cubeRaised=true;
  StopTask(raiseCubeLifter);
}

task raiseArmsTask(){
        raiseArms(2);
        StopTask(raiseArmsTask);
}

task initiateCubePosition(){
        intakeOn(2);
        StartTask(raiseCubeLifter);
        StopTask(initiateCubePosition);
}


task main()
{

        while(nNxtButtonPressed!=3){ //Choose wait time
                nxtDisplayCenteredBigTextLine(1,"%f",wait);
                if(nNxtButtonPressed==2)
                {while(nNxtButtonPressed!=-1){}
                        wait-=.1;
                      }
                else if(nNxtButtonPressed==1)
                {while(nNxtButtonPressed!=-1){}
                        wait+=.1;
                      }
                if(wait<0.0){

                        wait=0;
                      }
        }

        //waitForStart();

        init();

        StartTask(initiateCubePosition);

        wait1Msec(wait*1000);

        HTIRS2readAllDCStrength(HTIRS, dcS1, dcS2, dcS3, dcS4, dcS5); //Take IR reading
        ClearTimer(T1);
        while(!irFound){
                reverse(30);
                HTIRS2readAllDCStrength(HTIRS, dcS1, dcS2, dcS3, dcS4, dcS5); //Take IR reading
                DEBUG();
                if(dcS3>50){
                        driveStop();
                        time=time1[T1];
                        irFound=true;
                        break;
                }
                if(time1[T1]/1000>=5){ //End of crates(use ultrasonic or something) RECHECK For IR
                        time=time1[T1];
                        ClearTimer(T1);
                        while(!irFound){
                                forward(30);
                                HTIRS2readAllDCStrength(HTIRS, dcS1, dcS2, dcS3, dcS4, dcS5); //Take IR reading
                                DEBUG();
                                if(dcS3>50){
                                        driveStop();
                                        time2=time1[T1];
                                        irFound=true;
                                        break;
                                }
                                if(time1[T1]>=time){ //Still no ir found, goto ramp
                                        goto ramp;
                                }
                        }
                }
        }
        left(100,1.65);
        while(!cubeRaised){}
        reverse(30,.7);
        dropCube();
        wait1Msec(1000); //Let cube fall
        cubeUp();
        forward(30,.65);
        right(100,1.75);
        forward(30,abs((time/1000)-(time2/1000)));

        ramp:;
        //Ramp
        StartTask(raiseArmsTask);
        right(100,1);
        forward(100,1);
        right(100,1.2);
        forward(100,1.2);
        right(100,1.4);
        forward(100,2);
        lowerCube(fullHeight);

        end:; //Failed IR
        allStop();
}
