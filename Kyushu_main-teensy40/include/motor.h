//停止
void Motor_1() {
  if (IMU < 23) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (IMU < 45) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (IMU < 68) {
    dsr1202.move(-7, -7, -7, -7); //修正強
  } else if (IMU < 88) {
    dsr1202.move(-7, -7, -7, -7); //修正弱
  } else if (IMU < 92) {
    dsr1202.move(0, 0, 0, 0);
  } else if (IMU < 113) {
    dsr1202.move(7, 7, 7, 7); //修正弱
  } else if (IMU < 135) {
    dsr1202.move(7, 7, 7, 7); //修正強
  } else if (IMU < 158) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  }
}

//前
void Motor_2() {
  if (IMU < 23) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (IMU < 45) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (IMU < 68) {
    dsr1202.move(15, 15, -25, -25); //修正強
  } else if (IMU < 88) {
    dsr1202.move(18, 18, -22, -22); //修正弱
  } else if (IMU < 92) {
    dsr1202.move(20, 20, -20, -20);
  } else if (IMU < 113) {
    dsr1202.move(22, 22, -18, -18); //修正弱
  } else if (IMU < 135) {
    dsr1202.move(25, 25, -15, -15); //修正強
  } else if (IMU < 158) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  }
}

//後
void Motor_3() {
  if (IMU < 23) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (IMU < 45) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (IMU < 68) {
    dsr1202.move(-25, -25, 15, 15); //修正強
  } else if (IMU < 88) {
    dsr1202.move(-22, -22, 18, 18); //修正弱
  } else if (IMU < 92) {
    dsr1202.move(-20, -20, 20, 20);
  } else if (IMU < 113) {
    dsr1202.move(-18, -18, 22, 22); //修正弱
  } else if (IMU < 135) {
    dsr1202.move(-15, -15, 25, 25); //修正強
  } else if (IMU < 158) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  }
}

//左
void Motor_4() {
  if (IMU < 23) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (IMU < 45) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (IMU < 68) {
    dsr1202.move(15, -25, 15, -25); //修正強
  } else if (IMU < 88) {
    dsr1202.move(18, -22, 18, -22); //修正弱
  } else if (IMU < 92) {
    dsr1202.move(20, -20, 20, -20);
  } else if (IMU < 113) {
    dsr1202.move(22, -18, 22, -18); //修正弱
  } else if (IMU < 135) {
    dsr1202.move(25, -15, 25, -15); //修正強
  } else if (IMU < 158) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  }
}

//右
void Motor_5() {
  if (IMU < 23) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (IMU < 45) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (IMU < 68) {
    dsr1202.move(-25, 15, -25, 15); //修正強
  } else if (IMU < 88) {
    dsr1202.move(-22, 18, -22, 18); //修正弱
  } else if (IMU < 92) {
    dsr1202.move(-20, 20, -20, 20);
  } else if (IMU < 113) {
    dsr1202.move(-18, 22, -18, 22); //修正弱
  } else if (IMU < 135) {
    dsr1202.move(-15, 25, -15, 25); //修正強
  } else if (IMU < 158) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  }
}

//左前
void Motor_6() {
  if (IMU < 23) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (IMU < 45) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (IMU < 68) {
    dsr1202.move(15, -7, -7, -25); //修正強
  } else if (IMU < 88) {
    dsr1202.move(18, -7, -7, -22); //修正弱
  } else if (IMU < 92) {
    dsr1202.move(20, 0, 0, -20);
  } else if (IMU < 113) {
    dsr1202.move(22, 7, 7, -18); //修正弱
  } else if (IMU < 135) {
    dsr1202.move(25, 7, 7, -15); //修正強
  } else if (IMU < 158) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  }
}

//右前
void Motor_7() {
  if (IMU < 23) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (IMU < 45) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (IMU < 68) {
    dsr1202.move(-7, 15, -25, -7); //修正強
  } else if (IMU < 88) {
    dsr1202.move(-7, 18, -22, -7); //修正弱
  } else if (IMU < 92) {
    dsr1202.move(0, 20, -20, 0);
  } else if (IMU < 113) {
    dsr1202.move(7, 22, -18, 7); //修正弱
  } else if (IMU < 135) {
    dsr1202.move(7, 25, -15, 7); //修正強
  } else if (IMU < 158) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  }
}

//左後
void Motor_8() {
  if (IMU < 23) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (IMU < 45) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (IMU < 68) {
    dsr1202.move(-7, -25, 15, -7); //修正強
  } else if (IMU < 88) {
    dsr1202.move(-7, -22, 18, -7); //修正弱
  } else if (IMU < 92) {
    dsr1202.move(0, -20, 20, 0);
  } else if (IMU < 113) {
    dsr1202.move(7, -18, 22, 7); //修正弱
  } else if (IMU < 135) {
    dsr1202.move(7, -15, 25, 7); //修正強
  } else if (IMU < 158) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  }
}

//右後
void Motor_9() {
  if (IMU < 23) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (IMU < 45) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (IMU < 68) {
    dsr1202.move(-25, -7, -7, 15); //修正強
  } else if (IMU < 88) {
    dsr1202.move(-22, -7, -7, 18); //修正弱
  } else if (IMU < 92) {
    dsr1202.move(-20, 0, 0, 20);
  } else if (IMU < 113) {
    dsr1202.move(-18, 7, 7, 22); //修正弱
  } else if (IMU < 135) {
    dsr1202.move(-15, 7, 7, 25); //修正強
  } else if (IMU < 158) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  }
}