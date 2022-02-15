void Motor(int direction) {
  if (direction == 1) {
    motor[0] = 0;  //右前
    motor[1] = 0;  //右後
    motor[2] = 0;  //左前
    motor[3] = 0;  //左後
  } else if (direction == 2) {
    motor[0] = motor_speed;  //右前
    motor[1] = motor_speed;  //右後
    motor[2] = -motor_speed; //左前
    motor[3] = -motor_speed; //左後
  } else if (direction == 3) {
    motor[0] = -motor_speed; //右前
    motor[1] = -motor_speed; //右後
    motor[2] = motor_speed;  //左前
    motor[3] = motor_speed;  //左後
  } else if (direction == 4) {
    motor[0] = motor_speed;  //右前
    motor[1] = -motor_speed; //右後
    motor[2] = motor_speed;  //左前
    motor[3] = -motor_speed; //左後
  } else if (direction == 5) {
    motor[0] = -motor_speed; //右前
    motor[1] = motor_speed;  //右後
    motor[2] = -motor_speed; //左前
    motor[3] = motor_speed;  //左後
  } else if (direction == 6) {
    motor[0] = motor_speed;  //右前
    motor[1] = 0;  //右後
    motor[2] = 0;  //左前
    motor[3] = -motor_speed; //左後
  } else if (direction == 7) {
    motor[0] = 0;  //右前
    motor[1] = motor_speed;  //右後
    motor[2] = -motor_speed; //左前
    motor[3] = 0;  //左後
  } else if (direction == 8) {
    motor[0] = 0;  //右前
    motor[1] = -motor_speed; //右後
    motor[2] = motor_speed;  //左前
    motor[3] = 0;  //左後
  } else if (direction == 9) {
    motor[0] = -motor_speed; //右前
    motor[1] = 0;  //右後
    motor[2] = 0;  //左前
    motor[3] = motor_speed;  //左後
  }

  operation_G = operation_A + motor[0];
  if (operation_G < -motor_limit) {
    operation_G = -motor_limit;
  } else if (operation_G > motor_limit) {
    operation_G = motor_limit;
  }

  operation_H = operation_A + motor[1];
  if (operation_H < -motor_limit) {
    operation_H = -motor_limit;
  } else if (operation_H > motor_limit) {
    operation_H = motor_limit;
  }

  operation_I = operation_A + motor[2];
  if (operation_I < -motor_limit) {
    operation_I = -motor_limit;
  } else if (operation_I > motor_limit) {
    operation_I = motor_limit;
  }

  operation_J = operation_A + motor[3];
  if (operation_J < -motor_limit) {
    operation_J = -motor_limit;
  } else if (operation_J > motor_limit) {
    operation_J = motor_limit;
  }

  dsr1202.move(operation_G, operation_H, operation_I, operation_J);
}

void Move(int motor_rads, int motor_power) {
  motor[0] = motor_power * cos((motor_rads + 45) * PI / 180);
  motor[1] = motor_power * sin((motor_rads + 45) * PI / 180);
  motor[2] = -(motor_power * sin((motor_rads + 45) * PI / 180));
  motor[3] = -(motor_power * cos((motor_rads + 45) * PI / 180));

  operation_G = operation_A + motor[0];
  if (operation_G < -motor_limit) {
    operation_G = -motor_limit;
  } else if (operation_G > motor_limit) {
    operation_G = motor_limit;
  }

  operation_H = operation_A + motor[1];
  if (operation_H < -motor_limit) {
    operation_H = -motor_limit;
  } else if (operation_H > motor_limit) {
    operation_H = motor_limit;
  }

  operation_I = operation_A + motor[2];
  if (operation_I < -motor_limit) {
    operation_I = -motor_limit;
  } else if (operation_I > motor_limit) {
    operation_I = motor_limit;
  }

  operation_J = operation_A + motor[3];
  if (operation_J < -motor_limit) {
    operation_J = -motor_limit;
  } else if (operation_J > motor_limit) {
    operation_J = motor_limit;
  }

  dsr1202.move(operation_G, operation_H, operation_I, operation_J);
}