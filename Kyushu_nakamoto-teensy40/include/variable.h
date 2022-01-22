int head_CAM;
int CAM_angle = 0;
int CAM_distance = 0;
int CAM_area;

int head_USS; //USSからのヘッダ
int USS; //超音波センサ値(方向指定値)
int USS1 = 0;
int USS2 = 0;
int USS3 = 0;
int USS4 = 0;

int IMU; //IMU値

class Class1 {
private:
  /* private何もわからん */
public:
  int val = 0;
  int old_val = 0;
  int state = 0;
};

Class1 LCD, white;

unsigned long timer;
unsigned long timer_start = 0;

unsigned long position_timer = 0;
unsigned long old_position_timer = 0;

double val_I, old_val_I = 0;
double deviation, val_D = 0;
double operation_A, operation_B, operation_C = 0;

int motor_1;
int motor_2;
int motor_3;
int motor_4;

int operation_G, operation_H, operation_I, operation_J; //最終操作量

int direction; //方向判定用