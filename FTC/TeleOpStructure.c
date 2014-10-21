/*PRAGMA STATEMENTS*/
//HUB
#pragma config(Hubs,  S1, HTMotor,  none,  none,  none)
//Motors
#pragma config(Motor,	mtr_S1_C1_1,	motor111,	tmotorNormal,	openLoop)
//Servos
#pragma config(Servo,  srvo_S2_C1_1,    servo211,  tServoStandard)
//Sensors
#pragma config(Sensor,	S2,	lightSENSOR,	sensorLightInactive)

//Included libraries
#include "JoystickDriver.c"

//Define Constants
#define DEBUGMODE true
#define JOYTHRESHOLD 25

//Define Global Variables

void init(){
	//Initiation Function(initiates robot before waitForStart())
}

void killRobot(){
	//Stop Sending commands/power to all motors and servos
}

void updateSensors(){
	//Do any sensor polling/variable assigning here
}

void DEBUG(){
	//Any debugging info(prints to NXT screen)
	nxtDisplayCenteredTextLine(0,"");
	nxtDisplayCenteredTextLine(1,"");
	nxtDisplayCenteredTextLine(2,"");
	nxtDisplayCenteredTextLine(3,"");
	nxtDisplayCenteredTextLine(4,"");
	nxtDisplayCenteredTextLine(5,"");
	nxtDisplayCenteredTextLine(6,"");
	nxtDisplayCenteredTextLine(7,"");
}

task joystickOne(){
	//Check joystick one input here
	getJoystickSettings(joystick);
	if(abs(joystick.joy1_y1)>JOYTHRESHOLD){
	
	}
	else if(abs(joystick.joy1_y2)>JOYTHRESHOLD){
	
	}
	if(abs(joystick.joy1_x1)>JOYTHRESHOLD){
	
	}
	else if(abs(joystick.joy1_x2)>JOYTHRESHOLD){
	
	}
	if(joy1Btn(0)){
	
	}
	if(joy1Btn(1)){
	
	}
	if(joy1Btn(2)){
	
	}
	if(joy1Btn(3)){
	
	}
	if(joy1Btn(4)){
	
	}
	if(joy1Btn(5)){
	
	}
	if(joy1Btn(6)){
	
	}
	if(joy1Btn(7)){
	
	}
	if(joy1Btn(8)){
	
	}
	if(joy1Btn(9)){
	
	}
	if(joy1Btn(10)){
	
	}
	if(joy1Btn(11)){
	
	}
	if(joy1Btn(12)){
	
	}
}

task joystickTwo(){
	//Check joystick two input here
	getJoystickSettings(joystick);
	if(abs(joystick.joy2_y1)>JOYTHRESHOLD){
	
	}
	else if(abs(joystick.joy2_y2)>JOYTHRESHOLD){
	
	}
	if(abs(joystick.joy2_x1)>JOYTHRESHOLD){
	
	}
	else if(abs(joystick.joy2_x2)>JOYTHRESHOLD){
	
	}
	if(joy2Btn(0)){
	
	}
	if(joy2Btn(1)){
	
	}
	if(joy2Btn(2)){
	
	}
	if(joy2Btn(3)){
	
	}
	if(joy2Btn(4)){
	
	}
	if(joy2Btn(5)){
	
	}
	if(joy2Btn(6)){
	
	}
	if(joy2Btn(7)){
	
	}
	if(joy2Btn(8)){
	
	}
	if(joy2Btn(9)){
	
	}
	if(joy2Btn(10)){
	
	}
	if(joy2Btn(11)){
	
	}
	if(joy2Btn(12)){
	
	}
}

task main(){

	init(); //Initiate pieces
	
	WaitForStart(); //Wait for the FCS to say go
	
	StartTask(joystickOne); //Start joystick polling tasks
	StartTask(joystickTwo);
	
	while(true){ //Main execution loop
		if(DEBUGMODE){DEBUG();}
		
		if(bDisconnected){ //Stop Robot if disconnected
			allStop();
			continue;
        }
		updateSensors();
		//Place any autonomous executions during teleop here
	}
}