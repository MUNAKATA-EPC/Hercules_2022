int head_CAM;
int CAM_angle = 0;
int CAM_distance = 0;

int head_USS; //USSからのヘッダ
int USS; //超音波センサ値(方向指定値)
int USS1 = 0;
int USS2 = 0;
int USS3 = 0;
int USS4 = 0;

int IMU; //IMU値

class Class1 {
private:

public:
  int val = 0;
  int old_val = 0;
  int state = 0;
};

Class1 LCD;
Class1 white;

double timer;
double timer_start = 0.00;

double Y = 90; //ジャイロ中心値
double K = 10;  //比例ゲイン
double L = 0.8; //積分ゲイン
double M = 19;  //微分ゲイン
double O = 30; //操作分母量
double W, V = 0;
double X, Z = 0;
double A, B, C = 0;

int motor_1;
int motor_2;
int motor_3;
int motor_4;

int G, H, I, J; //最終操作量