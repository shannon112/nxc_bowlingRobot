#define LIGHTSENSOR IN_2
#define UltrasonicSENSOR IN_1
#define rightWheel OUT_A
#define leftWheel OUT_B
#define twoWheel OUT_AB
#define arm OUT_C
int RLwidth=2000;//avoid box width
int nearBox=10;//cm
int detectBoxError=5;//how many count
int openArmDegree=90;//dergree of open servo arm to make ball out
bool missionSuc=false;

inline void initailSetup(){
  TextOut(1,LCD_LINE7,"NTUME ROBOTIC");
  TextOut(1,LCD_LINE8,"GIVE ME A+ !!");
  SetSensorLowspeed(UltrasonicSENSOR);
  OnFwdReg(arm,0,OUT_REGMODE_SPEED);
}

inline void turnRight90(){
	//trun right
	OnFwd(rightWheel, 75);
	OnRev(leftWheel, 75);
 	Wait(360);
	Off(twoWheel);
 	//go throught width
	OnFwdReg(twoWheel,50,OUT_REGMODE_SYNC);
	wait(RLwidth);
	Off(twoWheel);
	//trun left
	OnFwd(leftWheel, 75);
	OnRev(rightWheel, 75);
 	Wait(360);
	Off(twoWheel);
}

inline void goSkipBox(){
	int nearCounter=0;
	int getoutCounter=0;
	OnFwdReg(twoWheel,50,OUT_REGMODE_SYNC);
	while(true){
		if (SensorUS(UltrasonicSENSOR)<nearBox) nearCounter++;
		else nearCounter=0;
		if(counter>detectBoxError) break;
	}
	while(true){
		if (SensorUS(UltrasonicSENSOR)>nearBox) getoutCounter++;
		else getoutCounter=0;
		if(counter>detectBoxError) break;
	}
	Off(twoWheel);
}

inline void turnLeft90(){
	//trun left
	OnFwd(leftWheel, 75);
	OnRev(rightWheel, 75);
 	Wait(360);
	Off(twoWheel);
 	//go throught width
	OnFwdReg(twoWheel,50,OUT_REGMODE_SYNC);
	wait(RLwidth);
	Off(twoWheel);
	//trun right
	OnFwd(rightWheel, 75);
	OnRev(leftWheel, 75);
 	Wait(360);
	Off(twoWheel);
}

inline void throwBall(){
	RotateMotor(arm,80,openArmDegree);
    OnFwdReg(arm,0,OUT_REGMODE_SPEED);
    missionSuc=true;
}

task main(){
  initailSetup();
  while(missionSuc==false)
  {
    turnRight90();
    goSkipBox();
    turnLeft90();
    throwBall();
  }
  TextOut(1,LCD_LINE7,"NTUME ROBOTIC");
  TextOut(1,LCD_LINE8,"MISSION OK!");
}