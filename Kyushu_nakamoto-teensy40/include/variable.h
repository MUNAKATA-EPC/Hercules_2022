int head_CAM = 0;
int CAM_angle = 0;
int CAM_distance = 0;
int CAM_area = 0;

int head_USS = 0; //USSからのヘッダ
int USS = 1;
int USS1, USS2, USS3, USS4 = 0;

int IMU = 90; //IMU値

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
  unsigned long timer = 0;
  unsigned long timer_start = 0;
};

Status LCD, white;
Timer LINE, position;

double val_I, old_val_I = 0;
double deviation, val_D = 0;
double operation_A, operation_B, operation_C = 0;

int motor_1, motor_2, motor_3, motor_4 = 0;

int operation_G, operation_H, operation_I, operation_J = 0; //最終操作量