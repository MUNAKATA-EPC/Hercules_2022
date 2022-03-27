const int IMU_center =  90; //ジャイロ中心値
#define gain_P 10  //比例ゲイン
#define gain_I 0.8  //積分ゲイン
#define gain_D 17  //微分ゲイン
const int operation_PID = 30; //操作分母量

const int set_limit_operation = 20;  //操作量限界値(絶対値)
const int motor_speed = 22;  //モーター速度(絶対値)
const int motor_limit = 40;  //モーター速度限界値(絶対値)