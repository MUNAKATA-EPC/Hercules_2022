int head_CAM, CAM_angle, CAM_distance;  //OpenMV 

int head_USS, USS, USS1, USS2, USS3, USS4;  //USS

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

int val_I = 0;
int deviation, old_deviation, val_D = 0;
float operation_A, operation_B, operation_C = 0;

int motor[] = {0, 0, 0, 0};

int MotorPower[] = {0, 0, 0, 0};  //最終操作量