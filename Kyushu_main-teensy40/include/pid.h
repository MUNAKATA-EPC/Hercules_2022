void pid() {

  X = IMU - Y;  //偏差:現在角度と目標角度のズレ
  W = W + X;  //偏差の積分値
  Z = X - V;  //偏差の微分値
  V = X;  //微分用前回偏差値の保存
  A = K * X;  //比例ゲイン*偏差
  B = L * W;  //積分ゲイン*偏差の積分値
  C = M * Z;  //微分ゲイン*偏差の微分値
  A = A + B + C;  //最終的な操作量
  A = A / O;  //ゲインを1未満で設定できるように、共通分母で割る(通常ゲインは1以上で設定できない)

  if (A < -30) {
    A = -30;  //下限値
  } else if (A > 30) {
    A = 30; //上限値
  }
}