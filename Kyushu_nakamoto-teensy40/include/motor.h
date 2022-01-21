//停止
void Motor_1() {
  if (direction == 1) {
    dsr1202.move(-11, -11, -11, -11); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-9, -9, -9, -9); //修正強
  } else if (direction == 4) {
    dsr1202.move(-8, -8, -8, -8); //修正弱
  } else if (direction == 5) {
    Serial1.println("1R0002R0003R0004R000");
  } else if (direction == 6) {
    dsr1202.move(8, 8, 8, 8); //修正弱
  } else if (direction == 7) {
    dsr1202.move(9, 9, 9, 9); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(11, 11, 11, 11); //全方向共通値
  }
}

//前
void Motor_2() {
  if (direction == 1) {
    dsr1202.move(-11, -11, -11, -11); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(16, 16, -24, -24); //修正強
  } else if (direction == 4) {
    dsr1202.move(18, 18, -22, -22); //修正弱
  } else if (direction == 5) {
    dsr1202.move(20, 20, -20, -20);
  } else if (direction == 6) {
    dsr1202.move(22, 22, -18, -18); //修正弱
  } else if (direction == 7) {
    dsr1202.move(24, 24, -16, -16); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(11, 11, 11, 11); //全方向共通値
  }
}

//後
void Motor_3() {
  if (direction == 1) {
    dsr1202.move(-11, -11, -11, -11); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-24, -24, 16, 16); //修正強
  } else if (direction == 4) {
    dsr1202.move(-22, -22, 18, 18); //修正弱
  } else if (direction == 5) {
    dsr1202.move(-20, -20, 20, 20);
  } else if (direction == 6) {
    dsr1202.move(-18, -18, 22, 22); //修正弱
  } else if (direction == 7) {
    dsr1202.move(-16, -16, 24, 24); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(11, 11, 11, 11); //全方向共通値
  }
}

//左
void Motor_4() {
  if (direction == 1) {
    dsr1202.move(-11, -11, -11, -11); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(16, -24, 16, -24); //修正強
  } else if (direction == 4) {
    dsr1202.move(18, -22, 18, -22); //修正弱
  } else if (direction == 5) {
    dsr1202.move(20, -20, 20, -20);
  } else if (direction == 6) {
    dsr1202.move(22, -18, 22, -18); //修正弱
  } else if (direction == 7) {
    dsr1202.move(24, -16, 24, -16); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(11, 11, 11, 11); //全方向共通値
  }
}

//右
void Motor_5() {
  if (direction == 1) {
    dsr1202.move(-11, -11, -11, -11); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-24, 16, -24, 16); //修正強
  } else if (direction == 4) {
    dsr1202.move(-22, 18, -22, 18); //修正弱
  } else if (direction == 5) {
    dsr1202.move(-20, 20, -20, 20);
  } else if (direction == 6) {
    dsr1202.move(-18, 22, -18, 22); //修正弱
  } else if (direction == 7) {
    dsr1202.move(-16, 24, -16, 24); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(11, 11, 11, 11); //全方向共通値
  }
}

//左前
void Motor_6() {
  if (direction == 1) {
    dsr1202.move(-11, -11, -11, -11); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(16, -9, -9, -24); //修正強
  } else if (direction == 4) {
    dsr1202.move(18, -8, -8, -22); //修正弱
  } else if (direction == 5) {
    dsr1202.move(20, 0, 0, -20);
  } else if (direction == 6) {
    dsr1202.move(22, 8, 8, -18); //修正弱
  } else if (direction == 7) {
    dsr1202.move(24, 9, 9, -16); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(11, 11, 11, 11); //全方向共通値
  }
}

//右前
void Motor_7() {
  if (direction == 1) {
    dsr1202.move(-11, -11, -11, -11); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-9, 16, -24, -9); //修正強
  } else if (direction == 4) {
    dsr1202.move(-8, 18, -22, -8); //修正弱
  } else if (direction == 5) {
    dsr1202.move(0, 20, -20, 0);
  } else if (direction == 6) {
    dsr1202.move(8, 22, -18, 8); //修正弱
  } else if (direction == 7) {
    dsr1202.move(9, 24, -16, 9); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(11, 11, 11, 11); //全方向共通値
  }
}

//左後
void Motor_8() {
  if (direction == 1) {
    dsr1202.move(-11, -11, -11, -11); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-9, -24, 16, -9); //修正強
  } else if (direction == 4) {
    dsr1202.move(-8, -22, 18, -8); //修正弱
  } else if (direction == 5) {
    dsr1202.move(0, -20, 20, 0);
  } else if (direction == 6) {
    dsr1202.move(8, -18, 22, 8); //修正弱
  } else if (direction == 7) {
    dsr1202.move(9, -16, 24, 9); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(11, 11, 11, 11); //全方向共通値
  }
}

//右後
void Motor_9() {
  if (direction == 1) {
    dsr1202.move(-11, -11, -11, -11); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-24, -9, -9, 16); //修正強
  } else if (direction == 4) {
    dsr1202.move(-22, -8, -8, 18); //修正弱
  } else if (direction == 5) {
    dsr1202.move(-20, 0, 0, 20);
  } else if (direction == 6) {
    dsr1202.move(-18, 8, 8, 22); //修正弱
  } else if (direction == 7) {
    dsr1202.move(-16, 9, 9, 24); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(11, 11, 11, 11); //全方向共通値
  }
}