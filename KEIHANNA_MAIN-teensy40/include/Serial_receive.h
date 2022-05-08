void Serial_receive() {
  if (Serial2.available() > 0) {
    head_CAM = Serial2.read();
    if (head_CAM == 255) {
      CAM_angle = Serial2.read() * 2;
      CAM_distance = Serial2.read();
      CAM_YellowAngle = Serial2.read() * 2;
      CAM_BlueAngle = Serial2.read() * 2;
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

  if (Serial5.available() > 0) {
    head_BT = Serial5.read();
    if (head_BT == 255) {
      BT_Angle = Serial5.read() * 2;
      BT_Power = Serial5.read();
    }
  }
}