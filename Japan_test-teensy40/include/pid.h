void pid() {
  deviation = IMU - IMU_center;  //偏差:現在角度と目標角度のズレ

  if (IMU >= 88 && IMU <= 92) {
    deviation = 0;
  }
  
  val_I += deviation;  //偏差の積分値

  if (val_I < -300) {
    val_I = -300;
  } else if (val_I > 300) {
    val_I = 300;
  }

  if (IMU >= 88 && IMU <= 92) {
    val_I = 0;
  }

  val_D = deviation - old_deviation;  //偏差の微分値
  old_deviation = deviation;  //微分用前回偏差値の保存

  operation_A = gain_P * deviation;  //比例ゲイン*偏差
  operation_B = gain_I * val_I;  //積分ゲイン*偏差の積分値
  operation_C = gain_D * val_D;  //微分ゲイン*偏差の微分値

  operation_A = operation_A + operation_B + operation_C;  //最終的な操作量
  operation_A = operation_A / operation_PID;  //ゲインを1未満で設定できるように、共通分母で割る(通常ゲインは1以上で設定できない)

  if (operation_A < -set_limit_operation) {
    operation_A = -set_limit_operation;  //下限値
  } else if (operation_A > set_limit_operation) {
    operation_A = set_limit_operation; //上限値
  }
}