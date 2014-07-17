#pragma config(Sensor, S4,     sonarSensor,         sensorSONAR)


float smooth(float data,float filterVal,float smoothedVal){
	if (filterVal > 1){      // check to make sure param's are within range
    filterVal = .99;
  }
  else if (filterVal <= 0){
    filterVal = 0;
  }

  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);
  return smoothedVal;
}

float avgSonarValue(){
  int r = 0;
  float[10] tmpArray = new float[10];
  for(int i=0;i<10;i++){
  	tmpArray[i] = SensorValue[sonarSensor];
	}
	int max=0;
	int min=255;

  for (int i = 0 ; i < 10; i++){
    r += tmpArray[i];
    if(tmpArray[i]>max)
    	max=tmpArray[i];
   	if(tmpArray[i]<min)
   		min=tmpArray[i];
  }
  return (r-min-max) / 8;
}

task main()
{
	float sonarValue = 0;
	float smoothedVal;
	float filterVal = .95;
	while(true){
		sonarValue = SensorValue(sonarSensor);
		smoothedVal = smooth(sonarValue,filterVal,smoothedVal);
	}
}
