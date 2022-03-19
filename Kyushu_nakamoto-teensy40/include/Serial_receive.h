void Serial_receive() {
  if (Serial2.available() > 0) {
    head_CAM = Serial2.read();
    if (head_CAM == 255) {
      CAM_angle = Serial2.read();
      CAM_distance = Serial2.read();
    }
  }

  if (Serial3.available() > 0) {
    head_USS = Serial3.read();
    if (head_USS == 255) {
      USS = Serial3.read();
      USS1 = Serial3.read();
      USS2 = Serial3.read();
      USS3 = Serial3.read();
      USS4 = Serial3.read();
    }
  }

  if (Serial4.available() > 0) {
    IMU = Serial4.read();
  }

  if (CAM_angle < 6) {
    CAM_area = 2; //前
  } else if (CAM_angle < 35) {
    CAM_area = 7; //右前
  } else if (CAM_angle < 56) {
    CAM_area = 5; //右
  } else if (CAM_angle < 76) {
    CAM_area = 9; //右後
  } else if (CAM_angle < 96) {
    CAM_area = 3; //後
  } else if (CAM_angle < 116) {
    CAM_area = 8; //左後
  } else if (CAM_angle < 136) {
    CAM_area = 4; //左
  } else if (CAM_angle < 175) {
    CAM_area = 6; //左前
  } else {
    CAM_area = 2; //前
  }
}