#Single Color RGB565 Blob Tracking Example
#RCAP
# This example shows off single color RGB565 tracking using the OpenMV Cam.

import sensor, image, time, math#ライブラリーの読み込み
from pyb import UART, LED, Pin, Timer, DAC#ライブラリーの読み込み

red_led   = LED(1)                  #下２１行目までLEDのセットアップ
green_led = LED(2)
blue_led  = LED(3)
ir_led    = LED(4)

def led_control(x):
 if   (x&1)==0: red_led.off()
 elif (x&1)==1: red_led.on()
 if   (x&2)==0: green_led.off()
 elif (x&2)==2: green_led.on()
 if   (x&4)==0: blue_led.off()
 elif (x&4)==4: blue_led.on()
 if   (x&8)==0: ir_led.off()
 elif (x&8)==8: ir_led.on()

threshold_index = 0 # 0 for red, 1 for green, 2 for blue

# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B Min, B Max)
# The below thresholds track in general red/green/blue things. You may wish to tune them...
thresholds1 = [(8, 100, 39, 82, -26, 71)]#メイン
thresholds2 = [(0, 100, -12, 17, 45, 72)]#ゴール（黄色）
thresholds3 = [(0, 0, 42, 73, 26, 57)]#ゴール（青色）
thresholds4 = [(30, 100, -64, -8, -32, 32)]#フィールド(緑色)

#上で色の変更可　ただLAB色空間での探知である
# generic_blue_thresholds
uart = UART(3, 115200, timeout_char = 100)
uart.init(115200, bits=8, parity=None, stop=1, timeout_char=1000)
#uart1 = UART(1, 115200, timeout_char=1000)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)#カラースケール
sensor.set_framesize(sensor.QVGA)#解像度
sensor.skip_frames(time = 400)#描写速度
sensor.set_contrast(1)#コントラスト
sensor.set_brightness(-3)#明るさ
sensor.set_saturation(0)#彩
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False,(-5.02073, -5.019987, 0.6176831))# must be turned off for color tracking
clock = time.clock()

tim1 = Timer(4, freq=1000)
#tim2 = Timer(8, freq=1000)

#dac = DAC(Pin("P6"),bits=12)

# Only blobs that with more pixels than "pixel_threshold" and more area than "area_threshold" are
# returned by "find_blobs" below. Change "pixels_threshold" and "area_threshold" if you change the
# camera resolution. "merge=True" merges all overlapping blobs in the image.

while(True):  #メインループ
 n=0#ボールカラーを取ったブロックの個数（for文の繰り返した回数）
 N=0#ゴール(黄色)の色を取ったブロックの個数（for文の繰り返した回数）
 m=0#ゴール(青色)の色を取ったブロックの個数(for文の繰り返した回数)
 M=0#フィールドの色を取ったブロックの個数(for文の繰り返した回数)
 cut_fro_and_bak=110#画面上での横線の定義
 cut_lef_and_rig=165#画面上での縦線の定義
 count=0#ブロックの個数（今は使っていない)
 areapf=0
 iwashi=0#取得したブロックの密度の最大値を保存
 haraga=0#取得したブロックの面積の最大値を保存
 shinya=0
 hogehoge=0#取得したブロック(フィールド)の密度の最大値を保存
 ball_namber=0
 field_number=0
 #akiya=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 areaA=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロックの面積を配列にして1つの関数に保存
 areaB=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロックの面積を配列にして1つの関数に保存
 areaC=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 areaD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロックの面積を配列にして1つの関数に保存
 rectA=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック（ボール）の中心のX座標、Y座標、ブロックの横幅、縦幅の値を配列にして1つの関数に保存
 rectB=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック（ゴール）の中心のX座標、Y座標、ブロックの横幅、縦幅の値を配列にして1つの関数に保存
 rectC=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 rectD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック(フィールド)の中心のX座標、Y座標、ブロックの横幅、縦幅の値を配列にして保存
 cxA=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック（ボール）の中心のX座標のみを配列にして1つの関数に保存
 cxB=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック（ゴール）の中心のX座標のみを配列にして1つの関数に保存
 cxC=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 cxD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック(フィールド)の中心のX座標のみを配列にして保存
 cyA=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック（ボール）の中心のY座標のみを配列にして1つの関数に保存
 cyB=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック（ゴール）の中心のY座標のみを配列にして1つの関数に保存
 cyC=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 cyD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック(フィールド)の中心のY座標のみを配列にして保存
 val=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#画面中心のX座標
 valD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 vall=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#画面中心のY座標
 vallD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 r=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#atan2を使って出した角度（単位ラジアン）
 rD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 rads=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#ｒによって出た角度を絶対値に
 radsD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 riole=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#ボールの左右有無の判別用
 distanceA=[0,0,0,0,0,0,0,0,0,0,]
 distanceB=[0,0,0,0,0,0,0,0,0,0,]#付け加え三平方
 densityA=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#ボールの色の取った面積に対する密度
 densityB=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#ゴールの色の取った面積に対する密度
 densityD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#フィールドの色の取った面積に対する密度
 clock.tick()
 img = sensor.snapshot()
 for blob in img.find_blobs([thresholds1[threshold_index]], pixels_threshold=1, area_threshold=1, merge=True,margin=25):#下９０行目までカラーボールトラッキング
     n+=1
     cxA[n]=blob.cx()
     cyA[n]=blob.cy()
     rectA[n]=blob.rect()
     val[n]=blob.cx()-cut_lef_and_rig#値の調整　画面中央を座標(0,0)に
     vall[n]=blob.cy()-cut_fro_and_bak
     rads[n]=int(((math.atan2(vall[n],val[n])*-57.32)+180)/2)#範囲の調整片側１８０度
     #distanceA[n]=int((math.sqrt((math.pow(val[n],2))+(math.pow(vall[n],2))))*29.16666666666667)#２点間の距離の公式
     distanceA[n]=int((math.sqrt((math.pow(val[n],2))+(math.pow(vall[n],2)))))
     #rads[n]=abs(r[n])#atan2で出した値を絶対値に修正
     densityA[n]=blob.density()
     areaA[n]=blob.area()
     count=blob.count()#使ってない
     #distanceB[n]=int(math.sqrt(vall[n]^2+val[n]^2))#付け加え三平方
     if vall[n]>0:
         riole[n]=100#light or left
     else:
         riole[n]=0

     #area.append(blob.area())
     #for i in range(1):#見えたときの確認用LED
        #led_control(2)

 for blob in img.find_blobs([thresholds4[threshold_index]], pixels_threshold=1, area_threshold=1, merge=True,margin=25):
     M+=1
     cxD[M]=blob.cx()
     cyD[M]=blob.cy()
     rectD[M]=blob.rect()
     valD[M]=blob.cx()-cut_lef_and_rig#値の調整　画面中央を座標(0,0)に
     vallD[M]=blob.cy()-cut_fro_and_bak
     radsD[M]=int(((math.atan2(vallD[M],val[M])*-57.32)+180)/2)#範囲の調整片側１８０度
     #radsD[M]=abs(rD[M])#atan2で出した値を絶対値に修正
     densityD[M]=blob.density()
     areaD[M]=blob.area()

 iwashi=(max(areaA[:]))
 haraga=(max(areaB[:]))
 shinya=(max(areaC[:]))
 hogehoge=(max(areaD[:]))


 if areaA[1]==iwashi!=0:#ボールの色を整理　補足したブロックの密度で判別しソート
     img.draw_rectangle(rectA[1])#長方形の生成
     img.draw_cross(cxA[1], cyA[1]) #中央のバツの生成
     #ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads[1])
     #ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole[1])
     #ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=distanceA[1])
     #dac.write(distanceA[1])
     ball_namber=1
 elif areaA[2]==iwashi!=0:
     img.draw_rectangle(rectA[2])#長方形の生成
     img.draw_cross(cxA[2], cyA[2]) #中央のバツの生成
     ball_namber=2
 elif areaA[3]==iwashi!=0:
     img.draw_rectangle(rectA[3])#長方形の生成
     img.draw_cross(cxA[3], cyA[3]) #中央のバツの生成
     ball_namber=3
 elif areaA[4]==iwashi!=0:
     img.draw_rectangle(rectA[4])#長方形の生成
     img.draw_cross(cxA[4], cyA[4]) #中央のバツの生成
     ball_namber=4
 elif areaA[5]==iwashi!=0:
     img.draw_rectangle(rectA[5])#長方形の生成
     img.draw_cross(cxA[5], cyA[5]) #中央のバツの生成
     ball_namber=5
 elif areaA[6]==iwashi!=0:
     img.draw_rectangle(rectA[6])#長方形の生成
     img.draw_cross(cxA[6], cyA[6]) #中央のバツの生成
     ball_namber=6
 elif areaA[7]==iwashi!=0:
     img.draw_rectangle(rectA[7])#長方形の生成
     img.draw_cross(cxA[7], cyA[7]) #中央のバツの生成
     ball_namber=7
 elif areaA[8]==iwashi!=0:
     img.draw_rectangle(rectA[8])#長方形の生成
     img.draw_cross(cxA[8], cyA[8]) #中央のバツの生成
     ball_namber=8
 elif areaA[9]==iwashi!=0:
     img.draw_rectangle(rectA[9])#長方形の生成
     img.draw_cross(cxA[9], cyA[9]) #中央のバツの生成
     ball_namber=9
 elif areaA[10]==iwashi!=0:
     img.draw_rectangle(rectA[10])#長方形の生成
     img.draw_cross(cxA[10], cyA[10]) #中央のバツの生成
     ball_namber=10
 elif areaA[11]==iwashi!=0:
     img.draw_rectangle(rectA[11])#長方形の生成
     img.draw_cross(cxA[11], cyA[11]) #中央のバツの生成
     ball_namber=11
 elif areaA[12]==iwashi!=0:
     img.draw_rectangle(rectA[12])#長方形の生成
     img.draw_cross(cxA[12], cyA[12]) #中央のバツの生成
     ball_namber=12
 elif areaA[13]==iwashi!=0:
     img.draw_rectangle(rectA[13])#長方形の生成
     img.draw_cross(cxA[13], cyA[13]) #中央のバツの生成
     ball_namber=13
 elif areaA[14]==iwashi!=0:
     img.draw_rectangle(rectA[14])#長方形の生成
     img.draw_cross(cxA[14], cyA[14]) #中央のバツの生成
     ball_namber=14
 elif areaA[15]==iwashi!=0:
     img.draw_rectangle(rectA[15])#長方形の生成
     img.draw_cross(cxA[15], cyA[15]) #中央のバツの生成
     ball_namber=15
 else:
     riole[1]=50 #つけくわえ
     ball_namber=0


 if areaD[1]==hogehoge!=0:#フィールドの色を整理　補足したブロックの密度で判別しソート
     img.draw_rectangle(rectD[1])#長方形の生成
     img.draw_cross(cxD[1], cyD[1]) #中央のバツの生成
     field_number=1
 elif areaD[2]==hogehoge!=0:
     img.draw_rectangle(rectD[2])#長方形の生成
     img.draw_cross(cxD[2], cyD[2]) #中央のバツの生成
     field_number=2
 elif areaD[3]==hogehoge!=0:
     img.draw_rectangle(rectD[3])#長方形の生成
     img.draw_cross(cxD[3], cyD[3]) #中央のバツの生成
     field_number=3
 elif areaD[4]==hogehoge!=0:
     img.draw_rectangle(rectD[4])#長方形の生成
     img.draw_cross(cxD[4], cyD[4]) #中央のバツの生成
     field_number=4
 elif areaD[5]==hogehoge!=0:
     img.draw_rectangle(rectD[5])#長方形の生成
     img.draw_cross(cxD[5], cyD[5]) #中央のバツの生成
     field_number=5
 elif areaD[6]==hogehoge!=0:
     img.draw_rectangle(rectD[6])#長方形の生成
     img.draw_cross(cxD[6], cyD[6]) #中央のバツの生成
     field_number=6
 elif areaD[7]==hogehoge!=0:
     img.draw_rectangle(rectD[7])#長方形の生成
     img.draw_cross(cxD[7], cyD[7]) #中央のバツの生成
     field_number=7
 elif areaD[8]==hogehoge!=0:
     img.draw_rectangle(rectD[8])#長方形の生成
     img.draw_cross(cxD[8], cyD[8]) #中央のバツの生成
     field_number=8
 elif areaD[9]==hogehoge!=0:
     img.draw_rectangle(rectD[9])#長方形の生成
     img.draw_cross(cxD[9], cyD[9]) #中央のバツの生成
     field_number=9
 elif areaD[10]==hogehoge!=0:
     img.draw_rectangle(rectD[10])#長方形の生成
     img.draw_cross(cxD[10], cyD[10]) #中央のバツの生成
     field_number=10
 elif areaD[11]==hogehoge!=0:
     img.draw_rectangle(rectD[11])#長方形の生成
     img.draw_cross(cxD[11], cyD[11]) #中央のバツの生成
     field_number=11
 elif areaD[12]==hogehoge!=0:
     img.draw_rectangle(rectD[12])#長方形の生成
     img.draw_cross(cxD[12], cyD[12]) #中央のバツの生成
     field_number=12
 elif areaD[13]==hogehoge!=0:
     img.draw_rectangle(rectD[13])#長方形の生成
     img.draw_cross(cxD[13], cyD[13]) #中央のバツの生成
     field_number=13
 elif areaD[14]==hogehoge!=0:
     img.draw_rectangle(rectD[14])#長方形の生成
     img.draw_cross(cxD[14], cyD[14]) #中央のバツの生成
     field_number=14
 elif areaD[15]==hogehoge!=0:
     img.draw_rectangle(rectD[15])#長方形の生成
     img.draw_cross(cxD[15], cyD[15]) #中央のバツの生成
     field_number=15
 else:
     field_number=0

 img.draw_line(0,cut_fro_and_bak,320,cut_fro_and_bak)#横線
 img.draw_line(cut_lef_and_rig,0,cut_lef_and_rig,240)#縦線


 #write_deta = abs(rads[ball_namber])
 uart.writechar(255)
 uart.writechar(rads[ball_namber])
 uart.writechar(distanceA[ball_namber])
 uart.writechar(Rads[field_number])

 #uart.write(str(abs(cxA[ball_namber]-320)))

 #uart.write(str(abs(distanceA[ball_namber])))

 #print(distanceA[ball_namber])
 #dac.write(128)
 #print(iwashi,count,density[:])123 345
 #print(rads[1])
 #print(distanceA[1])
 #print("   ")
 #print(distanceB[1])
 #print(riole[1])
 #print(sensor.get_rgb_gain_db())

