#include "ti_msp_dl_config.h"
#include "Servo.h"
 
 
 

void Servo_SetAngle_0(float Angle)
{
	float b=0;
  b=2000-(Angle / 180 * 200 + 50);
	DL_TimerG_setCaptureCompareValue(TIMA0, b, DL_TIMER_CC_1_INDEX);
}

void Servo_SetAngle_1(float Angle_1)
{
	float c=0;
  c=2000-(Angle_1 / 180 * 200 + 50);
	DL_TimerG_setCaptureCompareValue(TIMA0, c, DL_TIMER_CC_2_INDEX);
}

void Servo_SetAngle_2(float Angle_2)
{
	float d=0;
  d=2000-(Angle_2 / 180 * 200 + 50);
	DL_TimerG_setCaptureCompareValue(TIMA0, d, DL_TIMER_CC_3_INDEX);
}


