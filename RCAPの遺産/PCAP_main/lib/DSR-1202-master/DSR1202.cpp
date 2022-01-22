/*
  DSR1202.cpp

  created by anbara
*/

#include "Arduino.h"
#include "DSR1202.h"
#include "math.h"

//PID制御基盤

double Y = 0; //ジャイロ中心値

double K = 10;	//比例ゲイン
double L = 0.8; //積分ゲイン
double M = 19;	//微分ゲイン

int O = 30; //操作分母量

double W, V = 0;
double X, Z = 0;
double A, B, C = 0;

int direction = 0;

DSR1202::DSR1202(int pin)
{
	PinNo = pin;
}

void DSR1202::Init()
{
	//Serial.begin(250000);
	//Serial4.bigin(115200);

	if (PinNo == 2)
	{
		Serial2.begin(115200);
	}
	else if (PinNo == 3)
	{
		Serial3.begin(115200);
	}
	else
	{
		Serial1.begin(115200);
	}
}
void DSR1202::move(int direction, int angle, int speed, int kakudo)
{ //ジャーロセンサーの値からPID制御と三角関数を使って方角、角度、スピードから出力を決定する関数

	int M1 = sin((direction + 45)  / 180 * PI) * speed;
	int M2 = sin((direction + 135) / 180 * PI) * speed;
	int M3 = sin((direction + 225) / 180 * PI) * speed;
	int M4 = sin((direction + 315) / 180 * PI) * speed;

	int M1a = abs(M1);
	int M2a = abs(M2);
	int M3a = abs(M3);
	int M4a = abs(M4);

	int speed_max = max(max(max(M1a, M2a), M3a), M4a);


	

	M1 = M1 * speed / speed_max;
	M2 = M2 * speed / speed_max;
	M3 = M3 * speed / speed_max;
	M4 = M4 * speed / speed_max; //ここまで角度
/*
	Y = angle;

	int IMU = kakudo;
	X = IMU - Y; //偏差:現在角度と目標角度のズレ(0は実際にはMPU6050からの値)
	W = W + X;		//偏差の積分値
	Z = X - V;		//偏差の微分値
	V = X;			//微分用前回偏差値の保存

	A = K * X; //比例ゲイン*偏差
	B = L * W; //積分ゲイン*偏差の積分値
	C = M * Z; //微分ゲイン*偏差の微分値

	A = A + B + C; //最終的な操作量
	A = A / O;	   //ゲインを1未満で設定できるように、共通分母で割る(通常ゲインは1以上で設定できない)

	if (A < -30)
	{
		A = -30; //下限値
	}
	else if (A > 30)
	{
		A = 30; //上限値
	}

	A = -A; //操作量の反転(最終的な操作量)

	M1 = M1 + A;
	M2 = M2 + A;
	M3 = M3 + A;
	M4 = M4 + A;
	
	*/

	int val = 0;
	int input[4] = {M1, M2, M4, M3};
	int output[4] = {0, 0, 0, 0};
	String StringA = "0";
	String StringB = "0";
	String StringC = "0";
	String StringD = "0";
	String StringX = "0";
	String StringY = "0";
	String StringZ = "0";
	String String0 = "0";

	StringX = String(1);
	val = input[0];
	if (val < 0 && val >= -100)
	{
		StringY = String('R');
		val = abs(val);
		StringZ = String(val);
	}
	else if (val >= 0 && val <= 100)
	{
		StringY = String('F');
		StringZ = String(val);
	}
	else
	{
		StringY = String('F');
		StringZ = String(0);
	}
	if (val < 10)
	{
		String0 = String("00");
		StringZ = String0 + StringZ;
	}
	else if (val < 100)
	{
		String0 = String('0');
		StringZ = String0 + StringZ;
	}
	else
	{
		String0 = String("");
	}
	StringA = StringX + StringY + StringZ;

	StringX = String(2);
	val = input[1];
	if (val < 0 && val >= -100)
	{
		StringY = String('R');
		val = abs(val);
		StringZ = String(val);
	}
	else if (val >= 0 && val <= 100)
	{
		StringY = String('F');
		StringZ = String(val);
	}
	else
	{
		StringY = String('F');
		StringZ = String(0);
	}
	if (val < 10)
	{
		String0 = String("00");
		StringZ = String0 + StringZ;
	}
	else if (val < 100)
	{
		String0 = String('0');
		StringZ = String0 + StringZ;
	}
	else
	{
	}
	StringB = StringX + StringY + StringZ;

	StringX = String(3);
	val = input[2];
	if (val < 0 && val >= -100)
	{
		StringY = String('R');
		val = abs(val);
		StringZ = String(val);
	}
	else if (val >= 0 && val <= 100)
	{
		StringY = String('F');
		StringZ = String(val);
	}
	else
	{
		StringY = String('F');
		StringZ = String(0);
	}
	if (val < 10)
	{
		String0 = String("00");
		StringZ = String0 + StringZ;
	}
	else if (val < 100)
	{
		String0 = String('0');
		StringZ = String0 + StringZ;
	}
	else
	{
	}
	StringC = StringX + StringY + StringZ;

	StringX = String(4);
	val = input[3];
	if (val < 0 && val >= -100)
	{
		StringY = String('R');
		val = abs(val);
		StringZ = String(val);
	}
	else if (val >= 0 && val <= 100)
	{
		StringY = String('F');
		StringZ = String(val);
	}
	else
	{
		StringY = String('F');
		StringZ = String(0);
	}
	if (val < 10)
	{
		String0 = String("00");
		StringZ = String0 + StringZ;
	}
	else if (val < 100)
	{
		String0 = String('0');
		StringZ = String0 + StringZ;
	}
	else
	{
	}
	StringD = StringX + StringY + StringZ;

	Serial1.println(StringA + StringB + StringC + StringD);

}

void DSR1202::moter(int a, int b, int c, int d)

{
	int val = 0;
	int input[4] = {a, b, c, d};
	int output[4] = {0, 0, 0, 0};
	String StringA = "0";
	String StringB = "0";
	String StringC = "0";
	String StringD = "0";
	String StringX = "0";
	String StringY = "0";
	String StringZ = "0";
	String String0 = "0";

	StringX = String(1);
	val = input[0];
	if (val < 0 && val >= -100)
	{
		StringY = String('R');
		val = abs(val);
		StringZ = String(val);
	}
	else if (val >= 0 && val <= 100)
	{
		StringY = String('F');
		StringZ = String(val);
	}
	else
	{
		StringY = String('F');
		StringZ = String(0);
	}
	if (val < 10)
	{
		String0 = String("00");
		StringZ = String0 + StringZ;
	}
	else if (val < 100)
	{
		String0 = String('0');
		StringZ = String0 + StringZ;
	}
	else
	{
		String0 = String("");
	}
	StringA = StringX + StringY + StringZ;

	StringX = String(2);
	val = input[1];
	if (val < 0 && val >= -100)
	{
		StringY = String('R');
		val = abs(val);
		StringZ = String(val);
	}
	else if (val >= 0 && val <= 100)
	{
		StringY = String('F');
		StringZ = String(val);
	}
	else
	{
		StringY = String('F');
		StringZ = String(0);
	}
	if (val < 10)
	{
		String0 = String("00");
		StringZ = String0 + StringZ;
	}
	else if (val < 100)
	{
		String0 = String('0');
		StringZ = String0 + StringZ;
	}
	else
	{
	}
	StringB = StringX + StringY + StringZ;

	StringX = String(3);
	val = input[2];
	if (val < 0 && val >= -100)
	{
		StringY = String('R');
		val = abs(val);
		StringZ = String(val);
	}
	else if (val >= 0 && val <= 100)
	{
		StringY = String('F');
		StringZ = String(val);
	}
	else
	{
		StringY = String('F');
		StringZ = String(0);
	}
	if (val < 10)
	{
		String0 = String("00");
		StringZ = String0 + StringZ;
	}
	else if (val < 100)
	{
		String0 = String('0');
		StringZ = String0 + StringZ;
	}
	else
	{
	}
	StringC = StringX + StringY + StringZ;

	StringX = String(4);
	val = input[3];
	if (val < 0 && val >= -100)
	{
		StringY = String('R');
		val = abs(val);
		StringZ = String(val);
	}
	else if (val >= 0 && val <= 100)
	{
		StringY = String('F');
		StringZ = String(val);
	}
	else
	{
		StringY = String('F');
		StringZ = String(0);
	}
	if (val < 10)
	{
		String0 = String("00");
		StringZ = String0 + StringZ;
	}
	else if (val < 100)
	{
		String0 = String('0');
		StringZ = String0 + StringZ;
	}
	else
	{
	}
	StringD = StringX + StringY + StringZ;



	if (PinNo == 2)
	{
		Serial2.println(StringA + StringB + StringC + StringD);
	}
	else if (PinNo == 3)
	{
		Serial3.println(StringA + StringB + StringC + StringD);
	}
	else
	{
		Serial1.println(StringA + StringB + StringC + StringD);
	}
}
