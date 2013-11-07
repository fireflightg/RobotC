#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Motor,  mtr_S1_C1_1,   	leftMotor,tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,  		rightMotor,   		tmotorNormal, openLoop, reversed)

task main()
{
	while(nNxtButtonPressed==-1){}
	motor[rightMotor]=100;
	motor[leftMotor]=100;
	wait1Msec(1000);


}
