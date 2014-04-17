#pragma config(Sensor, S2,     colorSensor,    sensorCOLORFULL)
#pragma config(Sensor, S3,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S4,     touchSensor,    sensorTouch)
#pragma config(Motor,  motorB,           top,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           base,             tmotorNXT, PIDControl)

#define A 100000000000
#define B 10000000

int joyValToInt(int joyVal){ //All going in one int, need to signify negative values without being negative
	return joyVal<0?2000+abs(joyVal):1000+joyVal;
}

task main()
{
	bFloatDuringInactiveMotorPWM = true;
	//Store centered position
	int baseStartingPos = nMotorEncoder[base];
	int topStartingPos = nMotorEncoder[top];
	//Communication Protocal
	int my_message = 000000000000; //JvalJvalSonB

	while(true){
		my_message = joyValToInt(motor[top])*A+joyValToInt(motor[base])*B+SensorValue[sonarSensor]*1000+SensorValue[touchSensor];

		//Return Joystick to initial position
		if(motor[base] != baseStartingPos)
			motor[base] = baseStartingPos-motor[base];
		else
			motor[base] = 0;
		if(motor[top]!=topStartingPos)
			motor[top] = topStartingPos-motor[top];
		else
			motor[top] = 0;

		sendMessage(my_message);
	}
}
