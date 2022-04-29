#Single Color RGB565 Blob Tracking Example
#kudoken rcap
# This example shows off single color RGB565 tracking using the OpenMV Cam.

import sensor, image, time, math#ライブラリーの読み込み
from pyb import UART, LED, Pin, Timer, DAC#ライブラリーの読み込み

red_led   = LED(1)
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
thresholds1 = [(42, 74, 54, 75, 49, 76) ]#ball
#thresholds1 = [(0, 100, 53, 63, 31, 39)]
#thresholds1 = [(45, 90, 13, 84, -1, 64)]#検証１
#thresholds1 = [(53, 88, 48, 85, -22, 40)]#検証2
thresholds2 = [(43, 53, -36, -12, -2, 36)]#court
#thresholds3 = [(47, 70, -10, 15, 44, 100)]#ゴール（黄）
thresholds3 = [(10, 43, -3, 20, -58, -39)]#ゴール（青）
#上で色の変更可　ただLAB色空間での探知である
# generic_blue_thresholds
uart = UART(3, 115200, timeout_char=1000)#TX4 RX5

sensor.reset()
sensor.set_pixformat(sensor.RGB565)#カラースケール
sensor.set_framesize(sensor.QVGA)#解像度
sensor.skip_frames(time = 400)#描写速度
sensor.set_contrast(0)#コントラスト
sensor.set_brightness(-3)#明るさ
sensor.set_saturation(1)#彩
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False,(-2.502073, -3.219987, 0.6176831))# must be turned off for color tracking
clock = time.clock()

tim1 = Timer(4, freq=1000)
#tim2 = Timer(8, freq=1000)

dac = DAC(Pin("P6"),bits=12)

# Only blobs that with more pixels than "pixel_threshold" and more area than "area_threshold" are
# returned by "find_blobs" below. Change "pixels_threshold" and "area_threshold" if you change the
# camera resolution. "merge=True" merges all overlapping blobs in the image.

while(True):  #メインループ
 n=0#ボールカラーを取ったブロックの個数（for文の繰り返した回数）
 N=0#ゴールの色を取ったブロックの個数（for文の繰り返した回数）
 m=0
 cut_fro_and_bak=130#画面上での横線の定義
 cut_lef_and_rig=172#画面上での縦線の定義
 #count=0#ブロックの個数
 areapf=0
 ball=0#取得したブロックの密度の最大値を保存
 court=0#取得したブロックの面積の最大値を保存
 goal=0
 areaA=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロックの面積を配列にして1つの関数に保存
 areaB=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロックの面積を配列にして1つの関数に保存
 areaC=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 rectA=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック（ボール）の中心のX座標、Y座標、ブロックの横幅、縦幅の値を配列にして1つの関数に保存
 rectB=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック（ゴール）の中心のX座標、Y座標、ブロックの横幅、縦幅の値を配列にして1つの関数に保存
 rectC=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 cxA=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック（ボール）の中心のX座標のみを配列にして1つの関数に保存
 cxB=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック（ゴール）の中心のX座標のみを配列にして1つの関数に保存
 cxC=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 cyA=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック（ボール）の中心のY座標のみを配列にして1つの関数に保存
 cyB=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック（ゴール）の中心のY座標のみを配列にして1つの関数に保存
 cyC=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 val=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#画面中心のX座標
 vall=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#画面中心のY座標
 r=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#atan2を使って出した角度（単位ラジアン）
 rads1=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#ｒによって出た角度を絶対値に
 rads2=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 rads3=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 riole1=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#ボールの左右有無の判別用
 riole2=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 riole3=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
 distance1=[0,0,0,0,0,0,0,0,0,0,]
 densityA=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#ボールの色の取った面積に対する密度
 densityB=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#コートの色の取った面積に対する密度
 densityC=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#ゴールの色の取った面積に対する密度
 clock.tick()
 img = sensor.snapshot()
 for blob in img.find_blobs([thresholds1[threshold_index]], pixels_threshold=1, area_threshold=1, merge=True,margin=25):
     n+=1
     cxA[n]=blob.cx()
     cyA[n]=blob.cy()
     rectA[n]=blob.rect()
     val[n]=blob.cx()-cut_lef_and_rig#値の調整　画面中央を座標(0,0)に
     vall[n]=blob.cy()-cut_fro_and_bak
     r[n]=int(math.atan2(-vall[n],-val[n])*100*0.31)#範囲の調整片側１８０度
     distance1[n]=int((math.sqrt((math.pow(val[n],2))+(math.pow(vall[n],2)))))
     rads1[n]=abs(r[n])#atan2で出した値を絶対値に修正
     #densityA[n]=blob.density()
     areaA[n]=blob.area()
     #count=blob.count()#使ってない
     if vall[n]>0:
         riole1[n]=100#light or left
     else:
         riole1[n]=0

     for i in range(16):#見えたときの確認用LED
        led_control(2)
 for blob in img.find_blobs([thresholds2[threshold_index]], pixels_threshold=10, area_threshold=10, merge=True,margin=30):
     N+=1
     cxB[N]=blob.cx()
     cyB[N]=blob.cy()
     rectB[N]=blob.rect()
     val[N]=blob.cx()-cut_lef_and_rig
     vall[N]=blob.cy()-cut_fro_and_bak
     r[N]=int(math.atan2(-vall[N],-val[N])*100*0.31)#範囲の調整片側１８０度
     rads2[N]=abs(r[N])
     #densityB[N]=blob.density()
     areaB[N]=blob.area()
     if vall[N]>0:
         riole2[N]=100#light or left
     else:
         riole2[N]=0

     #for i in range(16):#見えたときの確認用LED
     #   led_control(2)
 for blob in img.find_blobs([thresholds3[threshold_index]], pixels_threshold=1, area_threshold=1, merge=True,margin=25):
     m+=1
     cxC[m]=blob.cx()
     cyC[m]=blob.cy()
     rectC[m]=blob.rect()
     val[m]=blob.cx()-cut_lef_and_rig
     vall[m]=blob.cy()-cut_fro_and_bak
     r[m]=int(math.atan2(-vall[m],-val[m])*100*0.31)#範囲の調整片側１８０度
     rads3[m]=abs(r[m])
     #densityC[m]=blob.density()
     areaC[m]=blob.area()
     if vall[m]>0:
         riole3[m]=100#light or left
     else:
         riole3[m]=0

     #for i in range(16):#見えたときの確認用LED
     #   led_control(2)
 for i in range(16):#見えないときはオフ
      led_control(0)
 ball=(max(areaA[:]))
 court=(max(areaB[:]))
 goal=(max(areaC[:]))


 if areaA[1]==ball!=0:#ボールの色を整理　補足したブロックの密度で判別しソート　　　　　　　　　　　　　↓↓↓ボール↓↓↓
     img.draw_rectangle(rectA[1])#長方形の生成
     img.draw_cross(cxA[1], cyA[1]) #中央のバツの生成
     ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads1[1])
     ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole1[1])
     ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=distance1[1])
     #dac.write(distance1[1])
 elif areaA[2]==ball!=0:
     img.draw_rectangle(rectA[2])#長方形の生成
     img.draw_cross(cxA[2], cyA[2]) #中央のバツの生成
     ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads1[2])
     ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole1[2])
     ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=distance1[2])
     #dac.write(distance1[2])
 elif areaA[3]==ball!=0:
     img.draw_rectangle(rectA[3])#長方形の生成
     img.draw_cross(cxA[3], cyA[3]) #中央のバツの生成
     ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads1[3])
     ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole1[3])
     ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=distance1[3])
     #dac.write(distance1[3])
 elif areaA[4]==ball!=0:
     img.draw_rectangle(rectA[4])#長方形の生成
     img.draw_cross(cxA[4], cyA[4]) #中央のバツの生成
     ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads1[4])
     ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole1[4])
     ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=distance1[4])
     #dac.write(distance1[4])
 elif areaA[5]==ball!=0:
     img.draw_rectangle(rectA[5])#長方形の生成
     img.draw_cross(cxA[5], cyA[5]) #中央のバツの生成
     ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads1[5])
     ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole1[5])
     ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=distance1[5])
     #dac.write(distance1[5])
 elif areaA[6]==ball!=0:
     img.draw_rectangle(rectA[6])#長方形の生成
     img.draw_cross(cxA[6], cyA[6]) #中央のバツの生成
     ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads1[6])
     ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole1[6])
     ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=distance1[6])
     #dac.write(distance1[6])
 elif areaA[7]==ball!=0:
     img.draw_rectangle(rectA[7])#長方形の生成
     img.draw_cross(cxA[7], cyA[7]) #中央のバツの生成
     ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads1[7])
     ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole1[7])
     ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=distance1[7])
     #dac.write(distance1[7])
 elif areaA[8]==ball!=0:
     img.draw_rectangle(rectA[8])#長方形の生成
     img.draw_cross(cxA[8], cyA[8]) #中央のバツの生成
     ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads1[8])
     ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole1[8])
     ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=distance1[8])
     #dac.write(distance1[8])
 elif areaA[9]==ball!=0:
     img.draw_rectangle(rectA[9])#長方形の生成
     img.draw_cross(cxA[9], cyA[9]) #中央のバツの生成
     ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads1[9])
     ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole1[9])
     ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=distance1[9])
     #dac.write(distance1[9])
 elif areaA[10]==ball!=0:
     img.draw_rectangle(rectA[10])#長方形の生成
     img.draw_cross(cxA[10], cyA[10]) #中央のバツの生成
     ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads1[10])
     ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole1[10])
     ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=distance1[10])
     #dac.write(distance1[10])
 elif areaA[11]==ball!=0:
     img.draw_rectangle(rectA[11])#長方形の生成
     img.draw_cross(cxA[11], cyA[11]) #中央のバツの生成
     ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads1[11])
     ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole1[11])
     ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=distance1[11])
     #dac.write(distance1[11])
 elif areaA[12]==ball!=0:
     img.draw_rectangle(rectA[12])#長方形の生成
     img.draw_cross(cxA[12], cyA[12]) #中央のバツの生成
     ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads1[12])
     ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole1[12])
     ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=distance1[12])
     #dac.write(distance1[12])
 elif areaA[13]==ball!=0:
     img.draw_rectangle(rectA[13])#長方形の生成
     img.draw_cross(cxA[13], cyA[13]) #中央のバツの生成
     ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads1[13])
     ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole1[13])
     ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=distance1[13])
     #dac.write(distance1[13])
 elif areaA[14]==ball!=0:
     img.draw_rectangle(rectA[14])#長方形の生成
     img.draw_cross(cxA[14], cyA[14]) #中央のバツの生成
     ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads1[14])
     ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole1[14])
     ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=distance1[14])
     #dac.write(distance1[14])
 elif areaA[15]==ball!=0:
     img.draw_rectangle(rectA[15])#長方形の生成
     img.draw_cross(cxA[15], cyA[15]) #中央のバツの生成
     ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads1[15])
     ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole1[15])
     ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=distance1[15])
     #dac.write(distance1[15])
 else:
     ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=100)
     ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=50)
     riole1[1]=50 #つけくわえ

 if areaB[1]==court!=0:#                            　 ↓↓↓コート↓↓↓
    img.draw_rectangle(rectB[1])#長方形の生成
    img.draw_cross(cxB[1], cyB[1]) #中央のバツの生成
 elif areaB[2]==court!=0:
    img.draw_rectangle(rectB[2])#長方形の生成
    img.draw_cross(cxB[2], cyB[2]) #中央のバツの生成
 elif areaB[3]==court!=0:
    img.draw_rectangle(rectB[3])#長方形の生成
    img.draw_cross(cxB[3], cyB[3]) #中央のバツの生成
 elif areaB[4]==court!=0:
    img.draw_rectangle(rectB[4])#長方形の生成
    img.draw_cross(cxB[4], cyB[4]) #中央のバツの生成
 elif areaB[5]==court!=0:
    img.draw_rectangle(rectB[5])#長方形の生成
    img.draw_cross(cxB[5], cyB[5]) #中央のバツの生成
 elif areaB[6]==court!=0:
    img.draw_rectangle(rectB[6])#長方形の生成
    img.draw_cross(cxB[6], cyB[6]) #中央のバツの生成
 elif areaB[7]==court!=0:
    img.draw_rectangle(rectB[7])#長方形の生成
    img.draw_cross(cxB[7], cyB[7]) #中央のバツの生成
 elif areaB[8]==court!=0:
    img.draw_rectangle(rectB[8])#長方形の生成
    img.draw_cross(cxB[8], cyB[8]) #中央のバツの生成
 elif areaB[9]==court!=0:
    img.draw_rectangle(rectB[9])#長方形の生成
    img.draw_cross(cxB[9], cyB[9]) #中央のバツの生成
 elif areaB[10]==court!=0:
    img.draw_rectangle(rectB[10])#長方形の生成
    img.draw_cross(cxB[10], cyB[10]) #中央のバツの生成
 elif areaB[11]==court!=0:
    img.draw_rectangle(rectB[11])#長方形の生成
    img.draw_cross(cxB[11], cyB[11]) #中央のバツの生成
 elif areaB[12]==court!=0:
    img.draw_rectangle(rectB[12])#長方形の生成
    img.draw_cross(cxB[12], cyB[12]) #中央のバツの生成
 elif areaB[13]==court!=0:
    img.draw_rectangle(rectB[13])#長方形の生成
    img.draw_cross(cxB[13], cyB[13]) #中央のバツの生成
 elif areaB[14]==court!=0:
    img.draw_rectangle(rectB[14])#長方形の生成
    img.draw_cross(cxB[14], cyB[14]) #中央のバツの生成
 elif areaB[15]==court!=0:
    img.draw_rectangle(rectB[15])#長方形の生成
    img.draw_cross(cxB[15], cyB[15]) #中央のバツの生成

 if areaC[1]==goal!=0:#                           　　　　　　↓↓↓ゴール↓↓↓
    img.draw_rectangle(rectC[1])#長方形の生成
    img.draw_cross(cxC[1], cyC[1]) #中央のバツの生成
 elif areaC[2]==goal!=0:
    img.draw_rectangle(rectC[2])#長方形の生成
    img.draw_cross(cxC[2], cyC[2]) #中央のバツの生成
 elif areaC[3]==goal!=0:
    img.draw_rectangle(rectC[3])#長方形の生成
    img.draw_cross(cxC[3], cyC[3]) #中央のバツの生成
 elif areaC[4]==goal!=0:
    img.draw_rectangle(rectC[4])#長方形の生成
    img.draw_cross(cxC[4], cyC[4]) #中央のバツの生成
 elif areaC[5]==goal!=0:
    img.draw_rectangle(rectC[5])#長方形の生成
    img.draw_cross(cxC[5], cyC[5]) #中央のバツの生成
 elif areaC[6]==goal!=0:
    img.draw_rectangle(rectC[6])#長方形の生成
    img.draw_cross(cxC[6], cyC[6]) #中央のバツの生成
 elif areaC[7]==goal!=0:
    img.draw_rectangle(rectC[7])#長方形の生成
    img.draw_cross(cxC[7], cyC[7]) #中央のバツの生成
 elif areaC[8]==goal!=0:
    img.draw_rectangle(rectC[8])#長方形の生成
    img.draw_cross(cxC[8], cyC[8]) #中央のバツの生成
 elif areaC[9]==goal!=0:
    img.draw_rectangle(rectC[9])#長方形の生成
    img.draw_cross(cxC[9], cyC[9]) #中央のバツの生成
 elif areaC[10]==goal!=0:
    img.draw_rectangle(rectC[10])#長方形の生成
    img.draw_cross(cxC[10], cyC[10]) #中央のバツの生成
 elif areaC[11]==goal!=0:
    img.draw_rectangle(rectC[11])#長方形の生成
    img.draw_cross(cxC[11], cyC[11]) #中央のバツの生成
 elif areaC[12]==goal!=0:
    img.draw_rectangle(rectC[12])#長方形の生成
    img.draw_cross(cxC[12], cyC[12]) #中央のバツの生成
 elif areaC[13]==goal!=0:
    img.draw_rectangle(rectC[13])#長方形の生成
    img.draw_cross(cxC[13], cyC[13]) #中央のバツの生成
 elif areaC[14]==goal!=0:
    img.draw_rectangle(rectC[14])#長方形の生成
    img.draw_cross(cxC[14], cyC[14]) #中央のバツの生成
 elif areaC[15]==goal!=0:
    img.draw_rectangle(rectC[15])#長方形の生成
    img.draw_cross(cxC[15], cyC[15]) #中央のバツの生成
 else:
    riole3[1]=50

 img.draw_line(0,cut_fro_and_bak,320,cut_fro_and_bak)#横線
 img.draw_line(cut_lef_and_rig,0,cut_lef_and_rig,240)#縦線

 #print(distance1[6])

 uart.write("w")#court
 uart.writechar(rads2[1])
 uart.write("x")#court
 uart.writechar(riole2[1])
 uart.write("y")#goal
 uart.writechar(rads3[1])
 uart.write("z")#goal
 uart.writechar(riole3[1])
