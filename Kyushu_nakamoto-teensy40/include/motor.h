//停止
void Motor_1() {
  if (direction == 1) {
    dsr1202.move(-13, -13, -13, -13); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-7, -7, -7, -7); //修正強
  } else if (direction == 4) {
    dsr1202.move(-7, -7, -7, -7); //修正弱
  } else if (direction == 5) {
    dsr1202.move(0, 0, 0, 0);
  } else if (direction == 6) {
    dsr1202.move(7, 7, 7, 7); //修正弱
  } else if (direction == 7) {
    dsr1202.move(7, 7, 7, 7); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(13, 13, 13, 13); //全方向共通値
  }
}

//前
void Motor_2() {
  if (direction == 1) {
    dsr1202.move(-13, -13, -13, -13); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(15, 15, -25, -25); //修正強
  } else if (direction == 4) {
    dsr1202.move(18, 18, -22, -22); //修正弱
  } else if (direction == 5) {
    dsr1202.move(20, 20, -20, -20);
  } else if (direction == 6) {
    dsr1202.move(22, 22, -18, -18); //修正弱
  } else if (direction == 7) {
    dsr1202.move(25, 25, -15, -15); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(13, 13, 13, 13); //全方向共通値
  }
}

//後
void Motor_3() {
  if (direction == 1) {
    dsr1202.move(-13, -13, -13, -13); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-25, -25, 15, 15); //修正強
  } else if (direction == 4) {
    dsr1202.move(-22, -22, 18, 18); //修正弱
  } else if (direction == 5) {
    dsr1202.move(-20, -20, 20, 20);
  } else if (direction == 6) {
    dsr1202.move(-18, -18, 22, 22); //修正弱
  } else if (direction == 7) {
    dsr1202.move(-15, -15, 25, 25); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(13, 13, 13, 13); //全方向共通値
  }
}

//左
void Motor_4() {
  if (direction == 1) {
    dsr1202.move(-13, -13, -13, -13); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(15, -25, 15, -25); //修正強
  } else if (direction == 4) {
    dsr1202.move(18, -22, 18, -22); //修正弱
  } else if (direction == 5) {
    dsr1202.move(20, -20, 20, -20);
  } else if (direction == 6) {
    dsr1202.move(22, -18, 22, -18); //修正弱
  } else if (direction == 7) {
    dsr1202.move(25, -15, 25, -15); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(13, 13, 13, 13); //全方向共通値
  }
}

//右
void Motor_5() {
  if (direction == 1) {
    dsr1202.move(-13, -13, -13, -13); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-25, 15, -25, 15); //修正強
  } else if (direction == 4) {
    dsr1202.move(-22, 18, -22, 18); //修正弱
  } else if (direction == 5) {
    dsr1202.move(-20, 20, -20, 20);
  } else if (direction == 6) {
    dsr1202.move(-18, 22, -18, 22); //修正弱
  } else if (direction == 7) {
    dsr1202.move(-15, 25, -15, 25); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(13, 13, 13, 13); //全方向共通値
  }
}

//左前
void Motor_6() {
  if (direction == 1) {
    dsr1202.move(-13, -13, -13, -13); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(15, -5, -5, -25); //修正強
  } else if (direction == 4) {
    dsr1202.move(18, -2, -2, -22); //修正弱
  } else if (direction == 5) {
    dsr1202.move(20, 0, 0, -20);
  } else if (direction == 6) {
    dsr1202.move(22, 2, 2, -18); //修正弱
  } else if (direction == 7) {
    dsr1202.move(25, 5, 5, -15); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(13, 13, 13, 13); //全方向共通値
  }
}

//右前
void Motor_7() {
  if (direction == 1) {
    dsr1202.move(-13, -13, -13, -13); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-5, 15, -25, -5); //修正強
  } else if (direction == 4) {
    dsr1202.move(-2, 18, -22, -2); //修正弱
  } else if (direction == 5) {
    dsr1202.move(0, 20, -20, 0);
  } else if (direction == 6) {
    dsr1202.move(2, 22, -18, 2); //修正弱
  } else if (direction == 7) {
    dsr1202.move(5, 25, -15, 5); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(13, 13, 13, 13); //全方向共通値
  }
}

//左後
void Motor_8() {
  if (direction == 1) {
    dsr1202.move(-13, -13, -13, -13); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-5, -25, 15, -5); //修正強
  } else if (direction == 4) {
    dsr1202.move(-2, -22, 18, -2); //修正弱
  } else if (direction == 5) {
    dsr1202.move(0, -20, 20, 0);
  } else if (direction == 6) {
    dsr1202.move(2, -18, 22, 2); //修正弱
  } else if (direction == 7) {
    dsr1202.move(5, -15, 25, 5); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(13, 13, 13, 13); //全方向共通値
  }
}

//右後
void Motor_9() {
  if (direction == 1) {
    dsr1202.move(-13, -13, -13, -13); //全方向共通値
  } else if (direction == 2) {
    dsr1202.move(-10, -10, -10, -10); //全方向共通値
  } else if (direction == 3) {
    dsr1202.move(-25, -5, -5, 15); //修正強
  } else if (direction == 4) {
    dsr1202.move(-22, -2, -2, 18); //修正弱
  } else if (direction == 5) {
    dsr1202.move(-20, 0, 0, 20);
  } else if (direction == 6) {
    dsr1202.move(-18, 2, 2, 22); //修正弱
  } else if (direction == 7) {
    dsr1202.move(-15, 5, 5, 25); //修正強
  } else if (direction == 8) {
    dsr1202.move(10, 10, 10, 10); //全方向共通値
  } else if (direction == 9) {
    dsr1202.move(13, 13, 13, 13); //全方向共通値
  }
}