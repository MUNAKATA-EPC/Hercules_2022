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

  MotorPower[0] = motor[0] + operation_A;
  if (MotorPower[0] < -motor_limit) {
    MotorPower[0] = -motor_limit;
  } else if (MotorPower[0] > motor_limit) {
    MotorPower[0] = motor_limit;
  }

  MotorPower[1] = motor[1] + operation_A;
  if (MotorPower[1] < -motor_limit) {
    MotorPower[1] = -motor_limit;
  } else if (MotorPower[1] > motor_limit) {
    MotorPower[1] = motor_limit;
  }

  MotorPower[2] = motor[2] + operation_A;
  if (MotorPower[2] < -motor_limit) {
    MotorPower[2] = -motor_limit;
  } else if (MotorPower[2] > motor_limit) {
    MotorPower[2] = motor_limit;
  }

  MotorPower[3] = motor[3] + operation_A;
  if (MotorPower[3] < -motor_limit) {
    MotorPower[3] = -motor_limit;
  } else if (MotorPower[3] > motor_limit) {
    MotorPower[3] = motor_limit;
  }

  Motor0 = MotorPower[0];
  Motor1 = MotorPower[1];
  Motor2 = MotorPower[2];
  Motor3 = MotorPower[3];

  dsr1202.move(Motor0, Motor1, Motor2, Motor3);
}