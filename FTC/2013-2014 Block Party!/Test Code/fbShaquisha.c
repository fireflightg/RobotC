#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Motor,  mtr_S1_C1_1,   	rightMotor,tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,  		leftMotor,   		tmotorNormal, openLoop, reversed)
#pragma config(Sensor, S2,     S2,          sensorSONAR)
#pragma config(Sensor, S3,     S3,          sensorSONAR)
#pragma config(Sensor, S4,     S4,          sensorLightActive)

task main()
{bFloatDuringInactiveMotorPWM=true;

	//while(nNxtButtonPressed==-1){}
while(true){
	while(SensorValue[S2]>30){
		if(SensorValue[S4]>38){
			motor[rightMotor]=100;
			motor[leftMotor]=100;
		}else
		{
			motor[rightMotor]=100;
			motor[leftMotor]=-100;
		}
	}
	while(SensorValue[S3]>30 ){

		if(SensorValue[S4]>38){
		motor[rightMotor]=-100;
		motor[leftMotor]=-100;
	}
	else{
		motor[rightMotor]=-100;
		motor[leftMotor]=100;
	}
	}
}
}
