/*
 * このプログラムはESP32ライブラリがV1.0.4の場合のみ正常に動作します
 * とくに拘りがなければ大人しくV1.0.4を入れてください
 */

#include <Ps3Controller.h>

#define LED 32

int rads, send_data, send_power, IMUrads, send_IMUThr, judge, direction_, Front, Back, Left, Right;

void  setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  Ps3.begin("4C:75:25:C5:BD:B4"); //PicoのMACアドレス
}

void  loop() {
  if (Ps3.isConnected()) {
    digitalWrite(LED, HIGH);
/*
    if (Ps3.data.button.select){
      Serial.println("select ボタン圧下");
    }
    if (Ps3.data.button.l3 ){
      Serial.println("l3 ボタン圧下");
    }
    if (Ps3.data.button.r3){
      Serial.println("r3 ボタン圧下");
    }
    if (Ps3.data.button.start){
      Serial.println("start ボタン圧下");
    }

    if (Ps3.data.button.up ){
      Serial.println("up ボタン圧下");
    }
    if (Ps3.data.button.right){
      Serial.println("right ボタン圧下");
    }
    if (Ps3.data.button.down ){
      Serial.println("down ボタン圧下");
    }
    if (Ps3.data.button.left){
      Serial.println("left ボタン圧下");
    }

    if (Ps3.data.button.l2 ){
      Serial.println("l2 ボタン圧下");
    }
    if (Ps3.data.button.r2){
      Serial.println("r2 ボタン圧下");
    }
    if (Ps3.data.button.l1 ){
      Serial.println("l1 ボタン圧下");
    }
    if (Ps3.data.button.r1){
      Serial.println("r1 ボタン圧下");
    }

    if (Ps3.data.button.cross){
      Serial.println("cross ボタン圧下");
    }
    if (Ps3.data.button.square){
      Serial.println("square ボタン圧下");
    }
    if (Ps3.data.button.triangle){
      Serial.println("triangle ボタン圧下");
    }
    if (Ps3.data.button.circle){
      Serial.println("circle ボタン圧下");
    }

    if (Ps3.data.button.ps){
      Serial.println("ps ボタン圧下");
    }
*/

    if (Ps3.data.button.up) {
      Front = 1;
    } else {
      Front = 0;
    }
    if (Ps3.data.button.right) {
      Right = 8;
    } else {
      Right = 0;
    }
    if (Ps3.data.button.down) {
      Back = 4;
    } else {
      Back = 0;
    }
    if (Ps3.data.button.left) {
      Left = 2;
    } else {
      Left = 0;
    }

    direction_ = Front + Left + Back + Right;

    rads = atan2((-Ps3.data.analog.stick.lx), (-Ps3.data.analog.stick.ly)) * 180 / PI;  //X,Y座標から逆正接関数を用いて角度を求める

    if (rads < 0) {
      rads += 360;
    }
    /*
      ロボット側関数の都合
    */

    send_data = abs(rads);
    send_data /= 2;

    send_power = sqrt(pow((Ps3.data.analog.stick.lx), 2) + pow((Ps3.data.analog.stick.ly), 2)), 2;
    send_power /= 5;
    
    if (send_power > 25) {
      send_power = 25;
    }

    if (direction_ == 1) {  //前
      send_data = 0;
      send_power = 25;
    } else if (direction_ == 2) { //左
      send_data = 90 / 2;
      send_power = 25;
    } else if (direction_ == 3) { //左前
      send_data = 45 / 2;
      send_power = 25;
    } else if (direction_ == 4) { //後
      send_data = 180 / 2;
      send_power = 25;
    } else if (direction_ == 6) { //左後
      send_data = 135 / 2;
      send_power = 25;
    } else if (direction_ == 8) { //右
      send_data = 270 / 2;
      send_power = 25;
    } else if (direction_ == 9) { //右前
      send_data = 315 / 2;
      send_power = 25;
    } else if (direction_ == 12) {  //右後
      send_data = 225 / 2;
      send_power = 25;
    }

    if (Ps3.data.button.l2 && !Ps3.data.button.r2) {
      send_power /= 1.5;
    } else if (!Ps3.data.button.l2 && Ps3.data.button.r2) {
      send_power = 0;
    } else if (Ps3.data.button.l2 && Ps3.data.button.r2) {
      send_power = 0;
    }

    
    //Serial.print("128,-128,LX=,"); //プロッタ用基準線
    //Serial.print("LX=");
    //Serial.print(Ps3.data.analog.stick.lx);
    //Serial.print("LY=");
    //Serial.print(Ps3.data.analog.stick.ly);
    //Serial.print("RX=");
    //Serial.print(Ps3.data.analog.stick.rx);
    //Serial.print("RY=");
    //Serial.print(Ps3.data.analog.stick.ry);
    //Serial.print(",SX=,");
    //Serial.print(Ps3.data.sensor.accelerometer.x);
    //Serial.print(",SY=,");
    //Serial.print(Ps3.data.sensor.accelerometer.y);
    //Serial.print(",SZ=,");
    //Serial.print(Ps3.data.sensor.accelerometer.z); 
    //Serial.print("R=");
    //Serial.print(send_data);
    //Serial.print("P=");
    //Serial.print(send_power);
    //Serial.println();

    Serial.write(255);
    Serial.write(send_data);
    Serial.write(send_power);
  }
}
