int head_CAM, CAM_angle, CAM_distance, CAM_FieldAngle;  //OpenMV 

int head_USS, USS, USS1, USS2, USS3, USS4;  //USS

int IMU; //IMU値

class Status {
public:
  int val, old_val;
  int state;
};

class Timer {
public:
  unsigned long timer, timer_start;
};

Status LCD, white;
Timer LINE, position;

int val_I;
int deviation, old_deviation, val_D;
float operation_A, operation_B, operation_C;

int motor[4];

int MotorPower[4];  //最終操作量