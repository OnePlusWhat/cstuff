#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     IR_Sensor,      sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     motorRight,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Flag,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorLift,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorLeft,     tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    servoBox,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    lift_hook,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    Angular_Lift,         tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

#define MAX(a, b) if((a) > (b)) maxValue = a; else maxValue = b;
float Robo_Breadth = 16.5;
float Wheel_Dia = 2.66;
float Wheel_Circ = 3.14*Wheel_Dia;
int speed = 80;
const int rotCount = 1440;
//bool amIDone = false;
const bool display = false;

void Stop_Motors()
{
	motor[motorRight] = 0;
	motor[motorLeft] = 0;
}

void Reset_Encoders()
{
	nMotorEncoder[motorRight] = 0;
}

void Move(float dist, int speed)
{
	float Num_Rot = dist/Wheel_Circ;
	float count = Num_Rot * rotCount;

	Reset_Encoders();
  while (nMotorEncoder[motorRight] <= count)
  {
   motor[motorRight] = speed;
   motor[motorLeft] = speed;
  }

	Stop_Motors();
	wait10Msec(100);
}

void Move_Back(float dist, int speed)
{
	Move(dist, -speed);
}

void Move_Front(float dist,int speed)
{
	Move(dist, speed);
}

void Turn_Left(int angle)
{
	float numRotCount = (rotCount * angle * Robo_Breadth) / (360.0 * Wheel_Dia);
	int count = numRotCount;

	if(display)
	{
		nxtDisplayCenteredTextLine(1,"Turn Count: %d",count);
		wait1Msec(1000);
	}

	Reset_Encoders();
	while(abs(nMotorEncoder[motorRight]) <= count)
	{
		motor[motorLeft] = -speed;
		motor[motorRight] = speed;

		if(display)
		{
			nxtDisplayCenteredTextLine(1,"Encoder Count: %d",nMotorEncoder[motorRight]);
			wait1Msec(1000);
		}
	}

	Stop_Motors() ;
	wait10Msec(100);
}

void Turn_Right(int angle)
{
	float numRotCount = (rotCount * angle * Robo_Breadth) / (360.0 * Wheel_Dia);
	int count = numRotCount;

	Reset_Encoders();
	while(abs(nMotorEncoder[motorRight]) <= count)
	{
		motor[motorLeft] = speed;
		motor[motorRight] = -speed;
	}

	Stop_Motors();
	wait10Msec(100);
}

void InitializeServos()
{
	servo[Angular_Lift]=0;

	wait10Msec(100);
}

task main()
{
	InitializeServos() ;
	waitForStart();
	wait10Msec(100);

	// Drop block
	Move_Front(21.5,speed);
	servo[Angular_Lift]=255;
	wait10Msec(100);

	// Climb Ramp
	Move_Front(22,speed);
	Turn_Right(90);
	Move_Back(15,speed);
}
