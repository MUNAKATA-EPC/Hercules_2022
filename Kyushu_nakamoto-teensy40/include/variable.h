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

class Status {
private:
  /* private何もわからん */
public:
  int val = 0;
  int old_val = 0;
  int state = 0;
};

class Timer {
private:
  /* マジでprivate何もわからん */
public:
  unsigned long timer;
  unsigned long timer_start = 0;
};

Status LCD, white;
Timer LINE, position;

double val_I, old_val_I = 0;
double deviation, val_D = 0;
double operation_A, operation_B, operation_C = 0;

int motor_1, motor_2, motor_3, motor_4;

int operation_G, operation_H, operation_I, operation_J; //最終操作量