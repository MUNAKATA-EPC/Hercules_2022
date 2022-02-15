const int IMU_center =  90; //ジャイロ中心値
const double gain_P = 1;  //比例ゲイン
const double gain_I = 0; //積分ゲイン
const double gain_D = 0;  //微分ゲイン
const int operation_PID = 30; //操作分母量

const int set_limit_operation = 30;  //操作量限界値
const int motor_speed = 25;  //モーター速度
const int motor_limit = 40;  //モーター速度限界値