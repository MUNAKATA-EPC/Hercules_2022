int head_CAM, CAM_angle, CAM_distance; 

int head_USS, USS, USS1, USS2, USS3, USS4;

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

int motor[] = {0, 0, 0, 0};

int operation_G, operation_H, operation_I, operation_J = 0; //最終操作量