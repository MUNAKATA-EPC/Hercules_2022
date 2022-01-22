int head_USS; //USSからのヘッダ
int USS; //超音波センサ値(方向指定値)
int USS1 = 0;
int USS2 = 0;
int USS3 = 0;
int USS4 = 0;

int IMU; //IMU値

int val_LCD = 0;  //タクトスイッチの状態
int old_val_LCD = 0;  //val_LCDの直前の値の保存
int state_LCD = 0;  //LCDの表示情報

int val_white = 0;  //白いボタンの状態
int old_val_white = 0;  //val_whiteの直前の値の保存
int state_white = 0;  //プログラムモード