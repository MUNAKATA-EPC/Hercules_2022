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

    if (IMU < ThresholdOfIMU[0]) {
      direction = 5;
    } else if (IMU < ThresholdOfIMU[1]) {
      direction = 6;
    } else if (IMU < ThresholdOfIMU[2]) {
      direction = 7;
    } else if (IMU < ThresholdOfIMU[3]) {
      direction = 8;
    } else if (IMU < ThresholdOfIMU[4]) {
      direction = 9;
    } else if (IMU < ThresholdOfIMU[5]) {
      direction = 1;
    } else if (IMU < ThresholdOfIMU[6]) {
      direction = 2;
    } else if (IMU < ThresholdOfIMU[7]) {
      direction = 3;
    } else if (IMU < ThresholdOfIMU[8]) {
      direction = 4;
    } else {
      direction = 5;
    }
  }
}