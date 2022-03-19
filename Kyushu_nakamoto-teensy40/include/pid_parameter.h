const int IMU_center =  90; //ジャイロ中心値
#define gain_P 0.5  //比例ゲイン
#define gain_I 0.04  //積分ゲイン
#define gain_D 1.02  //微分ゲイン
const int operation_PID = 1; //操作分母量

const int set_limit_operation = 30;  //操作量限界値
const int motor_speed = 25;  //モーター速度
const int motor_limit = 40;  //モーター速度限界値