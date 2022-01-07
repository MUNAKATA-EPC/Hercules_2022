void Motor_limit() {
  operation_G = operation_A + motor_1;

  if (operation_G < -40) {
    operation_G = -40;
  } else if (operation_G > 40) {
    operation_G = 40;
  }

  operation_H = operation_A + motor_2;

  if (operation_H < -40) {
    operation_H = -40;
  } else if (operation_H > 40) {
    operation_H = 40;
  }

  operation_I = operation_A + motor_3;

  if (operation_I < -40) {
    operation_I = -40;
  } else if (operation_I > 40) {
    operation_I = 40;
  }

  operation_J = operation_A + motor_4;

  if (operation_J < -40) {
    operation_J = -40;
  } else if (operation_J > 40) {
    operation_J = 40;
  }
}

//停止
void Motor_1() {
  motor_1 = 0;  //右前
  motor_2 = 0;  //右後
  motor_3 = 0;  //左前
  motor_4 = 0;  //左後

  Motor_limit();

  dsr1202.move(operation_G, operation_H, operation_I, operation_J);
}

//前
void Motor_2() {
  motor_1 = motor_speed; //右前
  motor_2 = motor_speed; //右後
  motor_3 = -motor_speed;  //左前
  motor_4 = -motor_speed;  //左後

  Motor_limit();

  dsr1202.move(operation_G, operation_H, operation_I, operation_J);
}

//後
void Motor_3() {
  motor_1 = -motor_speed;  //右前
  motor_2 = -motor_speed;  //右後
  motor_3 = motor_speed; //左前
  motor_4 = motor_speed; //左後

  Motor_limit();

  dsr1202.move(operation_G, operation_H, operation_I, operation_J);
}

//左
void Motor_4() {
  motor_1 = motor_speed; //右前
  motor_2 = -motor_speed;  //右後
  motor_3 = motor_speed; //左前
  motor_4 = -motor_speed;  //左後

  Motor_limit();

  dsr1202.move(operation_G, operation_H, operation_I, operation_J);
}

//右
void Motor_5() {
  motor_1 = -motor_speed;  //右前
  motor_2 = motor_speed; //右後
  motor_3 = -motor_speed;  //左前
  motor_4 = motor_speed; //左後

  Motor_limit();

  dsr1202.move(operation_G, operation_H, operation_I, operation_J);
}

//左前
void Motor_6() {
  motor_1 = motor_speed; //右前
  motor_2 = 0;  //右後
  motor_3 = 0;  //左前
  motor_4 = -motor_speed;  //左後

  Motor_limit();

  dsr1202.move(operation_G, operation_H, operation_I, operation_J);
}

//右前
void Motor_7() {
  motor_1 = 0;  //右前
  motor_2 = motor_speed; //右後
  motor_3 = -motor_speed;  //左前
  motor_4 = 0;  //左後

  Motor_limit();

  dsr1202.move(operation_G, operation_H, operation_I, operation_J);
}

//左後
void Motor_8() {
  motor_1 = 0;  //右前
  motor_2 = -motor_speed;  //右後
  motor_3 = motor_speed; //左前
  motor_4 = 0;  //左後

  Motor_limit();

  dsr1202.move(operation_G, operation_H, operation_I, operation_J);
}

//右後
void Motor_9() {
  motor_1 = -motor_speed;  //右前
  motor_2 = 0;  //右後
  motor_3 = 0;  //左前
  motor_4 = motor_speed; //左後

  Motor_limit();

  dsr1202.move(operation_G, operation_H, operation_I, operation_J);
}