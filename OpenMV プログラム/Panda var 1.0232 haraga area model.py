   # Single Color RGB565 Blob Tracking Example
#　3月2日　ジャパンオープン用
#
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
thresholds1 = [(0, 100, 48, 79, 36, 72)]#メイン
#thresholds2 = [(0, 0, -12, 17, 45, 72)]#ゴール（黄色)
#thresholds3 = [(0, 0, -20, 4, 2, 20)]#ゴール（青色）
thresholds4 = [(54, 67, -20, 4, 2, 20)]#コート（緑色）
#thresholds1 = [(53, 88, 48, 85, -22, 40)]#検証2
#thresholds2 = [(0, 100, 11, 31, -67, -45)]#ゴール（青色）
#上で色の変更可　ただLAB色空間での探知である
# generic_blue_thresholds
uart = UART(3, 115200, timeout_char=1000)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)#カラースケール
sensor.set_framesize(sensor.QVGA)#解像度
sensor.skip_frames(time = 400)#描写速度
sensor.set_contrast(1)#コントラスト
sensor.set_brightness(-2)#明るさ
sensor.set_saturation(2)#彩
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False,(-6.02073, -6.02073, -3.658832)) # must be turned off for color tracking
clock = time.clock()

tim1 = Timer(4, freq=1000)


dac = DAC(Pin("P6"),bits=12)

# Only blobs that with more pixels than "pixel_threshold" and more area than "area_threshold" are
# returned by "find_blobs" below. Change "pixels_threshold" and "area_threshold" if you change the
# camera resolution. "merge=True" merges all overlapping blobs in the image.

while(True):  #メインループ
    n=0#ボールカラーを取ったブロックの個数（for文の繰り返した回数）
    N=0#ゴールの色を取ったブロックの個数（for文の繰り返した回数）
    m=0
    M=0
    count=0#ブロックの個数（今話使っていない
    areapf=0
    iwashi=0#取得したブロックの密度の最大値を保存
    haraga=0#取得したブロックの面積の最大値を保存
    shinya=0
    #akiya=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    areaA=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロックの面積を配列にして1つの関数に保存
    areaD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    rectA=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック（ボール）の中心のX座標、Y座標、ブロックの横幅、縦幅の値を配列にして1つの関数に保存
    rectD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    cxA=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック（ボール）の中心のX座標のみを配列にして1つの関数に保存
    cxD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    cyA=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#取得したブロック（ボール）の中心のY座標のみを配列にして1つの関数に保存
    cyD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    val=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#画面中心のX座標
    vall=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#画面中心のY座標
    valD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#画面中心のX座標
    vallD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#画面中心のY座標
    rA=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#atan2を使って出した角度（単位ラジアン）
    rD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#atan2を使って出した角度（単位ラジアン）
    rads=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#ｒによって出た角度を絶対値に
    radsD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#ｒによって出た角度を絶対値に
    riole=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#ボールの左右有無の判別用
    rioleD=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#ボールの左右有無の判別用
    distanceA=[0,0,0,0,0,0,0,0,0,0,]
    densityA=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#ボールの色の取った面積に対する密度
    densityB=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]#ゴールの色の取った面積に対する密度
    clock.tick()
    img = sensor.snapshot()
    for blob in img.find_blobs([thresholds1[threshold_index]], pixels_threshold=1, area_threshold=1, merge=True,margin=25):#下９０行目までカラーボールトラッキング
        n+=1
        cxA[n]=blob.cx()
        cyA[n]=blob.cy()
        rectA[n]=blob.rect()
        val[n]=blob.cx()-165#値の調整　画面中央を座標(0,0)に
        vall[n]=blob.cy()-105
        rA[n]=int(math.atan2(-vall[n],-val[n])*100*0.31)#範囲の調整片側１８０度
        distanceA[n]=int((math.sqrt((math.pow(val[n],2))+(math.pow(vall[n],2))))*29.16666666666667)#２点間の距離の公式
        rads[n]=abs(rA[n])#atan2で出した値を絶対値に修正
        densityA[n]=blob.density()
        areaA[n]=blob.area()
        count=blob.count()#使ってない
        if vall[n]>0:
            riole[n]=100#light or left
        else:
            riole[n]=0

        #area.append(blob.area())
        for i in range(16):#見えたときの確認用LED
           led_control(2)
    for blob in img.find_blobs([thresholds4[threshold_index]], pixels_threshold=10, area_threshold=10, merge=True,margin=30):#コート認識用カラートラッキング
        M+=1
        cxD[M]=blob.cx()
        cyD[M]=blob.cy()
        #valD[n]=blob.cx()-165#値の調整　画面中央を座標(0,0)に
        valD[M]=blob.cx()-165
        #vallD[n]=blob.cy()-105
        vallD[M]=blob.cy()-105
        #rD[n]=int(math.atan2(-vallD[n],-valD[n])*100*0.31)#範囲の調整片側１８０度
        rD[M]=int(math.atan2(-vallD[M],-valD[M])*100*0.31)#範囲の調整片側１８０度
        #radsD[n]=int((rD[n]+100)%2)#atan2で出した値を絶対値に修正
        #radsD[n]=abs(rD[n])
        radsD[M]=int(abs(rD[M]/2))
        rectD[M]=blob.rect()
        areaD[M]=blob.area()
        if vallD[M]>0:
            radsD[M]
        else:
            radsD[M]=-radsD[M]+100
    for i in range(16):#見えないときはオフ
         led_control(0)
    iwashi=(max(areaA[:]))
    haraga=(max(areaD[:]))
    #shinya=(max(areaC[:]))


    if areaA[1]==iwashi!=0:#ボールの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectA[1])#長方形の生成
        img.draw_cross(cxA[1], cyA[1]) #中央のバツの生成
        ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads[1])
        ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole[1])
        dac.write(distanceA[1])
    elif areaA[2]==iwashi!=0:
        img.draw_rectangle(rectA[2])#長方形の生成
        img.draw_cross(cxA[2], cyA[2]) #中央のバツの生成
        ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads[2])
        ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole[2])
        dac.write(distanceA[2])
    elif areaA[3]==iwashi!=0:
        img.draw_rectangle(rectA[3])#長方形の生成
        img.draw_cross(cxA[3], cyA[3]) #中央のバツの生成
        ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads[3])
        ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole[3])
        dac.write(distanceA[3])
    elif areaA[4]==iwashi!=0:
        img.draw_rectangle(rectA[4])#長方形の生成
        img.draw_cross(cxA[4], cyA[4]) #中央のバツの生成
        ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads[4])
        ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole[4])
        dac.write(distanceA[4])
    elif areaA[5]==iwashi!=0:
        img.draw_rectangle(rectA[5])#長方形の生成
        img.draw_cross(cxA[5], cyA[5]) #中央のバツの生成
        ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads[5])
        ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole[5])
        dac.write(distanceA[5])
    elif areaA[6]==iwashi!=0:
        img.draw_rectangle(rectA[6])#長方形の生成
        img.draw_cross(cxA[6], cyA[6]) #中央のバツの生成
        ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads[6])
        ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole[6])
        dac.write(distanceA[6])
    elif areaA[7]==iwashi!=0:
        img.draw_rectangle(rectA[7])#長方形の生成
        img.draw_cross(cxA[7], cyA[7]) #中央のバツの生成
        ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads[7])
        ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole[7])
    elif areaA[8]==iwashi!=0:
        img.draw_rectangle(rectA[8])#長方形の生成
        img.draw_cross(cxA[8], cyA[8]) #中央のバツの生成
        ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads[8])
        ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole[8])
    elif areaA[9]==iwashi!=0:
        img.draw_rectangle(rectA[9])#長方形の生成
        img.draw_cross(cxA[9], cyA[9]) #中央のバツの生成
        ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads[9])
        ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole[9])
    elif areaA[10]==iwashi!=0:
        img.draw_rectangle(rectA[10])#長方形の生成
        img.draw_cross(cxA[10], cyA[10]) #中央のバツの生成
        ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads[10])
        ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole[10])
    elif areaA[11]==iwashi!=0:
        img.draw_rectangle(rectA[11])#長方形の生成
        img.draw_cross(cxA[11], cyA[11]) #中央のバツの生成
        ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads[11])
        ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole[11])
    elif areaA[12]==iwashi!=0:
        img.draw_rectangle(rectA[12])#長方形の生成
        img.draw_cross(cxA[12], cyA[12]) #中央のバツの生成
        ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads[12])
        ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole[12])
    elif areaA[13]==iwashi!=0:
        img.draw_rectangle(rectA[13])#長方形の生成
        img.draw_cross(cxA[13], cyA[13]) #中央のバツの生成
        ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads[13])
        ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole[13])
    elif areaA[14]==iwashi!=0:
        img.draw_rectangle(rectA[14])#長方形の生成
        img.draw_cross(cxA[14], cyA[14]) #中央のバツの生成
        ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads[14])
        ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole[14])
    elif areaA[15]==iwashi!=0:
        img.draw_rectangle(rectA[15])#長方形の生成
        img.draw_cross(cxA[15], cyA[15]) #中央のバツの生成
        ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rads[15])
        ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=riole[15])
    else:
        ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=100)
        ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=50)

    if areaD[1]==haraga!=0:#コートの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectD[1])#長方形の生成
        img.draw_cross(cxD[1], cyD[1]) #中央のバツの生成
        ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=radsD[1])
    if areaD[2]==haraga!=0:#コートの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectD[2])#長方形の生成
        img.draw_cross(cxD[2], cyD[2]) #中央のバツの生成
        ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=radsD[2])
    if areaD[3]==haraga!=0:#コートの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectD[3])#長方形の生成
        img.draw_cross(cxD[3], cyD[3]) #中央のバツの生成
        ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=radsD[3])
    if areaD[4]==haraga!=0:#コートの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectD[4])#長方形の生成
        img.draw_cross(cxD[4], cyD[4]) #中央のバツの生成
        ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=radsD[4])
    if areaD[5]==haraga!=0:#コートの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectD[5])#長方形の生成
        img.draw_cross(cxD[5], cyD[5]) #中央のバツの生成
        ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=radsD[5])
    if areaD[6]==haraga!=0:#コートの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectD[6])#長方形の生成
        img.draw_cross(cxD[6], cyD[6]) #中央のバツの生成
        ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=radsD[6])
    if areaD[7]==haraga!=0:#コートの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectD[7])#長方形の生成
        img.draw_cross(cxD[7], cyD[7]) #中央のバツの生成
        ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=radsD[7])
    if areaD[8]==haraga!=0:#コートの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectD[8])#長方形の生成
        img.draw_cross(cxD[8], cyD[8]) #中央のバツの生成
        ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=radsD[8])
    if areaD[9]==haraga!=0:#コートの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectD[9])#長方形の生成
        img.draw_cross(cxD[9], cyD[9]) #中央のバツの生成
        ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=radsD[9])
    if areaD[10]==haraga!=0:#コートの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectD[10])#長方形の生成
        img.draw_cross(cxD[10], cyD[10]) #中央のバツの生成
        ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=radsD[10])

    img.draw_line(0,105,320,105)#横線
    img.draw_line(165,0,165,240)#縦線
    #dac.write(128)
    #print(iwashi,count,density[:])123 345
    #print(sensor.get_rgb_gain_db(),iwashi,areaA[:])
    print(radsD[1])

