

#include <MPU6050_6Axis_MotionApps20.h>

#define UART_BAUD 250000
#define INT_PIN   1
#define SW_PIN    0
#define LED 13
/*
 UART_BAUD はシリアルモニタのボーレートと一致させます
 INT_PIN はArduinoボードのデジタルピン番号を指定します(InterruptPin番号ではないので注意)
 SW_PIN は正面設定用タクトスイッチのデジタルピン番号を指定します
 */

/*
 シリアルプリントによるデモを有効にします
 コメントアウトで無効化します
 */

MPU6050 imu(MPU6050_ADDRESS_AD0_LOW);
/*
 MPU6050のAD0ピンをVccに接続するかGNDに接続するかでアドレスが変わります
 GY-521ボードはデフォルトでAD0がGNDに接続されていますのでAD0_LOWを指定します
 */

uint16_t 	packetSize;
uint16_t 	fifoCount;
uint8_t  	fifoBuffer[1024];
uint8_t 	mpuIntStatus;
float    	raw_ypr[3], ofset_ypr[3], ypr[3];
volatile bool   mpuInterrupt = false;

void setup()
{
  pinMode(SW_PIN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  /*
	 ピンがGNDにスイッチされた時にアクティブになります(Active Low)
	 入力モードは回路により最適なものを設定してください
   */
  
  Wire.begin();
  Wire.setClock(400000);

 \
  Serial1.begin(250000);

  while (!Serial1)
  {
    ;
  }
    //Serial.begin(115200);

  imu_init();
  imu_attachSensorOfset(93, -26, 13, 1565);
  // Your offsets:	-2841	313	1565	93	-26	13
  /*
	 Calibrationプログラムによって得られたオフセットを適用します
	 コメントアウトされた"Your offsets"の後の並びとimu_attachSensorOfset()の引数を参照して
	 それぞれのセンサーのオフセットを適用してください
   */

  delay(2500);
  /*
	 センサーが安定動作するまでの2.5[秒]待機します
   */

  upload();
  attachOfset();
  /*
   初回読み込みと初回オフセット設定
   ロボットに搭載した際に 電源投入後と大きく外れた値が出るのを防ぎます
   */
}

void loop()
{
  upload();	// ypr[]の内部情報が最新のデータに更新されます
  if(digitalRead(SW_PIN) == LOW){
  	attachOfset();
  }

  
    Serial1.write((AD_TO_DEG * ypr[0] )/2);
    delay(10);
    
  

  //Serial.write(RAD_TO_DEG * ypr[0]);

  //Serial.write((uint8_t)(ypr[0] / PI * 128.0));
}

void imu_init()
{
  imu.initialize();
  imu.dmpInitialize();
  imu.setDMPEnabled(true);

  attachInterrupt(digitalPinToInterrupt(INT_PIN), dmpDataReady, RISING);
  mpuIntStatus = imu.getIntStatus();
  packetSize = imu.dmpGetFIFOPacketSize();
}

void imu_attachSensorOfset(int16_t XG, int16_t YG, int16_t ZG, int16_t ZA)
{
  imu.setXGyroOffset(XG);
  imu.setYGyroOffset(YG);
  imu.setZGyroOffset(ZG);
  imu.setZAccelOffset(ZA);
}

void dmpDataReady()
{
  mpuInterrupt = true;
}

void attachOfset()
{
  for (int i = 0; i < 3; ++i) {
    ofset_ypr[i] = raw_ypr[i];
  }
}

void upload()
{
	// digitalWrite(LED, LOW);

  while (mpuInterrupt == false && fifoCount < packetSize);
  mpuInterrupt = false;

  mpuIntStatus = imu.getIntStatus();
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    imu.resetFIFO();
    digitalWrite(LED, HIGH);
    delay(10);
    digitalWrite(LED, LOW);
  }

  while (fifoCount < packetSize) fifoCount = imu.getFIFOCount();

  fifoBuffer[64];
  imu.getFIFOBytes(fifoBuffer, packetSize);
  fifoCount -= packetSize;

  Quaternion _quaternion;
  VectorFloat _gravity;
  imu.dmpGetQuaternion(&_quaternion, fifoBuffer);
  imu.dmpGetGravity(&_gravity, &_quaternion);
  imu.dmpGetYawPitchRoll(raw_ypr, &_quaternion, &_gravity);

  for (int i = 0; i < 3; ++i) {
    ypr[i] = raw_ypr[i] - ofset_ypr[i];
    if(ypr[i] >  PI) ypr[i] -= 2 * PI;
    if(ypr[i] < -PI) ypr[i] += 2 * PI;
  }
}