void Motor_limit() {
  G = A + motor_1;

  if (G < -30) {
    G = -30;
  } else if (G > 30) {
    G = 30;
  }

  H = A + motor_2;

  if (H < -30) {
    H = -30;
  } else if (H > 30) {
    H = 30;
  }

  I = A + motor_3;

  if (I < -30) {
    I = -30;
  } else if (I > 30) {
    I = 30;
  }

  J = A + motor_4;

  if (J < -30) {
    J = -30;
  } else if (J > 30) {
    J = 30;
  }
}

void Motor_1() {  //停止
  motor_1 = 0;  //右前
  motor_2 = 0;  //右後
  motor_3 = 0;  //左前
  motor_4 = 0;  //左後

  Motor_limit();

  dsr1202.move(G, H, I, J);
}

void Motor_2() {  //前
  motor_1 = 20; //右前
  motor_2 = 20; //右後
  motor_3 = -20;  //左前
  motor_4 = -20;  //左後

  Motor_limit();

  dsr1202.move(G, H, I, J);
}

void Motor_3() {  //後
  motor_1 = -20;  //右前
  motor_2 = -20;  //右後
  motor_3 = 20; //左前
  motor_4 = 20; //左後

  Motor_limit();

  dsr1202.move(G, H, I, J);
}

void Motor_4() {  //左
  motor_1 = 20; //右前
  motor_2 = -20;  //右後
  motor_3 = 20; //左前
  motor_4 = -20;  //左後

  Motor_limit();

  dsr1202.move(G, H, I, J);
}

void Motor_5() {  //右
  motor_1 = -20;  //右前
  motor_2 = 20; //右後
  motor_3 = -20;  //左前
  motor_4 = 20; //左後

  Motor_limit();

  dsr1202.move(G, H, I, J);
}

void Motor_6() {  //左前
  motor_1 = 20; //右前
  motor_2 = 0;  //右後
  motor_3 = 0;  //左前
  motor_4 = -20;  //左後

  Motor_limit();

  dsr1202.move(G, H, I, J);
}

void Motor_7() {  //右前
  motor_1 = 0;  //右前
  motor_2 = 20; //右後
  motor_3 = -20;  //左前
  motor_4 = 0;  //左後

  Motor_limit();

  dsr1202.move(G, H, I, J);
}

void Motor_8() {  //左後
  motor_1 = 0;  //右前
  motor_2 = -20;  //右後
  motor_3 = 20; //左前
  motor_4 = 0;  //左後

  Motor_limit();

  dsr1202.move(G, H, I, J);
}

void Motor_9() {  //右後
  motor_1 = -20;  //右前
  motor_2 = 0;  //右後
  motor_3 = 0;  //左前
  motor_4 = 20; //左後

  Motor_limit();

  dsr1202.move(G, H, I, J);
}