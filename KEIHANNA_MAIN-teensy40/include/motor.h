void Motor(int direction) {
  switch (direction) {
    case 1:
      motor[0] = 0;  //右前
      motor[1] = 0;  //右後
      motor[2] = 0;  //左前
      motor[3] = 0;  //左後
      break;
    case 2:
      motor[0] = motor_speed;  //右前
      motor[1] = motor_speed;  //右後
      motor[2] = -motor_speed; //左前
      motor[3] = -motor_speed; //左後
      break;
    case 3:
      motor[0] = -motor_speed; //右前
      motor[1] = -motor_speed; //右後
      motor[2] = motor_speed;  //左前
      motor[3] = motor_speed;  //左後
      break;
    case 4:
      motor[0] = motor_speed;  //右前
      motor[1] = -motor_speed; //右後
      motor[2] = motor_speed;  //左前
      motor[3] = -motor_speed; //左後
      break;
    case 5:
      motor[0] = -motor_speed; //右前
      motor[1] = motor_speed;  //右後
      motor[2] = -motor_speed; //左前
      motor[3] = motor_speed;  //左後
      break;
    case 6:
      motor[0] = motor_speed;  //右前
      motor[1] = 0;  //右後
      motor[2] = 0;  //左前
      motor[3] = -motor_speed; //左後
      break;
    case 7:
      motor[0] = 0;  //右前
      motor[1] = motor_speed;  //右後
      motor[2] = -motor_speed; //左前
      motor[3] = 0;  //左後
      break;
    case 8:
      motor[0] = 0;  //右前
      motor[1] = -motor_speed; //右後
      motor[2] = motor_speed;  //左前
      motor[3] = 0;  //左後
      break;
    case 9:
      motor[0] = -motor_speed; //右前
      motor[1] = 0;  //右後
      motor[2] = 0;  //左前
      motor[3] = motor_speed;  //左後
      break;
  }

  MotorPower[0] = operation_A + motor[0];
  if (MotorPower[0] < -motor_limit) {
    MotorPower[0] = -motor_limit;
  } else if (MotorPower[0] > motor_limit) {
    MotorPower[0] = motor_limit;
  }

  MotorPower[1] = operation_A + motor[1];
  if (MotorPower[1] < -motor_limit) {
    MotorPower[1] = -motor_limit;
  } else if (MotorPower[1] > motor_limit) {
    MotorPower[1] = motor_limit;
  }

  MotorPower[2] = operation_A + motor[2];
  if (MotorPower[2] < -motor_limit) {
    MotorPower[2] = -motor_limit;
  } else if (MotorPower[2] > motor_limit) {
    MotorPower[2] = motor_limit;
  }

  MotorPower[3] = operation_A + motor[3];
  if (MotorPower[3] < -motor_limit) {
    MotorPower[3] = -motor_limit;
  } else if (MotorPower[3] > motor_limit) {
    MotorPower[3] = motor_limit;
  }

  dsr1202.move(MotorPower[0], MotorPower[1], MotorPower[2], MotorPower[3]);
}

//0度を真左、90度を直進と想定しています
void Move(int motor_rads, int motor_power) {
  motor[0] = motor_power * sin((motor_rads + 45) * PI / 180); //右前
  motor[1] = -motor_power * cos((motor_rads + 45) * PI / 180);  //右後
  motor[2] = motor_power * cos((motor_rads + 45) * PI / 180); //左前
  motor[3] = -motor_power * sin((motor_rads + 45) * PI / 180);  //左後

  MotorPower[0] = operation_A + motor[0];
  if (MotorPower[0] < -motor_limit) {
    MotorPower[0] = -motor_limit;
  } else if (MotorPower[0] > motor_limit) {
    MotorPower[0] = motor_limit;
  }

  MotorPower[1] = operation_A + motor[1];
  if (MotorPower[1] < -motor_limit) {
    MotorPower[1] = -motor_limit;
  } else if (MotorPower[1] > motor_limit) {
    MotorPower[1] = motor_limit;
  }

  MotorPower[2] = operation_A + motor[2];
  if (MotorPower[2] < -motor_limit) {
    MotorPower[2] = -motor_limit;
  } else if (MotorPower[2] > motor_limit) {
    MotorPower[2] = motor_limit;
  }

  MotorPower[3] = operation_A + motor[3];
  if (MotorPower[3] < -motor_limit) {
    MotorPower[3] = -motor_limit;
  } else if (MotorPower[3] > motor_limit) {
    MotorPower[3] = motor_limit;
  }

  dsr1202.move(MotorPower[0], MotorPower[1], MotorPower[2], MotorPower[3]);
}