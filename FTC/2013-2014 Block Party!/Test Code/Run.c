#pragma config(Hubs,  S1, HTMotor,  none,  none,  none)
#pragma config(Motor, mtr_S1_C1_1, rightMotor, motorNormal)
#pragma config(Motor, mtr_S1_C1_2, leftMotor, motorNormal, reversed)
#pragma config(Sensor, S2,     S2,               sensorLightActive)
#pragma config(Sensor, S3,     S3,               sensorSONAR)
#pragma config(Sensor, S4,     S4,               sensorSONAR)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define distance 30
#define threshold 40 //Line value

task main()
{
	bFloatDuringInactiveMotorPWM=true;
	while(true){
		while(SensorValue[S4]>distance){
			nxtDisplayCenteredBigTextLine(1,"Forward");
			nxtDisplayCenteredBigTextLine(5,"%icm",SensorValue[S4]);
				motor[rightMotor]=100;
				motor[leftMotor]=100;

		}
		while(SensorValue[S3]>distance){
			nxtDisplayCenteredBigTextLine(1,"Reverse");
			nxtDisplayCenteredBigTextLine(5,"%icm",SensorValue[S3]);
				motor[rightMotor]=-100;
				motor[leftMotor]=-100;
		}
	}
}
