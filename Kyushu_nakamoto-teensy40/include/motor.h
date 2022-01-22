//停止
void Motor_1() {
  if (direction == 1) {
    dsr1202.move(-20, -20, -20, -20); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-10, -10, -10, -10); //修正強
  } else if (direction == 4) {
    dsr1202.move(-8, -8, -8, -8); //修正弱
  } else if (direction == 5) {
    Serial1.println("1R0002R0003R0004R000");
  } else if (direction == 6) {
    dsr1202.move(8, 8, 8, 8); //修正弱
  } else if (direction == 7) {
    dsr1202.move(10, 10, 10, 10); //修正強
  } else if (direction == 8) {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(20, 20, 20, 20); //全方向共通値
  }
}

//前
void Motor_2() {
  if (direction == 1) {
    dsr1202.move(-20, -20, -20, -20); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(14, 14, -26, -26); //修正強
  } else if (direction == 4) {
    dsr1202.move(17, 17, -23, -23); //修正弱
  } else if (direction == 5) {
    dsr1202.move(20, 20, -20, -20);
  } else if (direction == 6) {
    dsr1202.move(23, 23, -17, -17); //修正弱
  } else if (direction == 7) {
    dsr1202.move(26, 26, -14, -14); //修正強
  } else if (direction == 8) {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(20, 20, 20, 20); //全方向共通値
  }
}

//後
void Motor_3() {
  if (direction == 1) {
    dsr1202.move(-20, -20, -20, -20); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-26, -26, 14, 14); //修正強
  } else if (direction == 4) {
    dsr1202.move(-23, -23, 17, 17); //修正弱
  } else if (direction == 5) {
    dsr1202.move(-20, -20, 20, 20);
  } else if (direction == 6) {
    dsr1202.move(-17, -17, 23, 23); //修正弱
  } else if (direction == 7) {
    dsr1202.move(-14, -14, 27, 27); //修正強
  } else if (direction == 8) {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(20, 20, 20, 20); //全方向共通値
  }
}

//左
void Motor_4() {
  if (direction == 1) {
    dsr1202.move(-20, -20, -20, -20); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(14, -26, 14, -26); //修正強
  } else if (direction == 4) {
    dsr1202.move(17, -23, 17, -23); //修正弱
  } else if (direction == 5) {
    dsr1202.move(20, -20, 20, -20);
  } else if (direction == 6) {
    dsr1202.move(23, -17, 23, -17); //修正弱
  } else if (direction == 7) {
    dsr1202.move(26, -14, 26, -14); //修正強
  } else if (direction == 8) {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(20, 20, 20, 20); //全方向共通値
  }
}

//右
void Motor_5() {
  if (direction == 1) {
    dsr1202.move(-20, -20, -20, -20); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-26, 14, -26, 14); //修正強
  } else if (direction == 4) {
    dsr1202.move(-23, 17, -23, 17); //修正弱
  } else if (direction == 5) {
    dsr1202.move(-20, 20, -20, 20);
  } else if (direction == 6) {
    dsr1202.move(-17, 23, -17, 23); //修正弱
  } else if (direction == 7) {
    dsr1202.move(-14, 26, -14, 26); //修正強
  } else if (direction == 8) {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(20, 20, 20, 20); //全方向共通値
  }
}

//左前
void Motor_6() {
  if (direction == 1) {
    dsr1202.move(-20, -20, -20, -20); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(14, -10, -10, -26); //修正強
  } else if (direction == 4) {
    dsr1202.move(17, -8, -8, -23); //修正弱
  } else if (direction == 5) {
    dsr1202.move(20, 0, 0, -20);
  } else if (direction == 6) {
    dsr1202.move(23, 8, 8, -17); //修正弱
  } else if (direction == 7) {
    dsr1202.move(26, 10, 10, -14); //修正強
  } else if (direction == 8) {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(20, 20, 20, 20); //全方向共通値
  }
}

//右前
void Motor_7() {
  if (direction == 1) {
    dsr1202.move(-20, -20, -20, -20); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-10, 14, -26, -10); //修正強
  } else if (direction == 4) {
    dsr1202.move(-8, 17, -23, -8); //修正弱
  } else if (direction == 5) {
    dsr1202.move(0, 20, -20, 0);
  } else if (direction == 6) {
    dsr1202.move(8, 23, -17, 8); //修正弱
  } else if (direction == 7) {
    dsr1202.move(10, 26, -14, 10); //修正強
  } else if (direction == 8) {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(20, 20, 20, 20); //全方向共通値
  }
}

//左後
void Motor_8() {
  if (direction == 1) {
    dsr1202.move(-20, -20, -20, -20); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-10, -26, 14, -10); //修正強
  } else if (direction == 4) {
    dsr1202.move(-8, -23, 17, -8); //修正弱
  } else if (direction == 5) {
    dsr1202.move(0, -20, 20, 0);
  } else if (direction == 6) {
    dsr1202.move(8, -17, 23, 8); //修正弱
  } else if (direction == 7) {
    dsr1202.move(10, -14, 26, 10); //修正強
  } else if (direction == 8) {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(20, 20, 20, 20); //全方向共通値
  }
}

//右後
void Motor_9() {
  if (direction == 1) {
    dsr1202.move(-20, -20, -20, -20); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-15, -15, -15, -15); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-26, -10, -10, 14); //修正強
  } else if (direction == 4) {
    dsr1202.move(-23, -8, -8, 17); //修正弱
  } else if (direction == 5) {
    dsr1202.move(-20, 0, 0, 20);
  } else if (direction == 6) {
    dsr1202.move(-17, 8, 8, 23); //修正弱
  } else if (direction == 7) {
    dsr1202.move(-14, 10, 10, 26); //修正強
  } else if (direction == 8) {
    dsr1202.move(15, 15, 15, 15); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(20, 20, 20, 20); //全方向共通値
  }
}