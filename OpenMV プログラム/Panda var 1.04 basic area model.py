# Single Color RGB565 Blob Tracking Example
#　１０月１４日　訂正完了
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
thresholds1 = [(0, 100, 57, 91, 33, 61)]#メイン
thresholds2 = [(5, 16, 14, 38, -46, -33)]#ゴール（青色)
thresholds3 = [(0, 100, -11, 20, 44, 66)]#ゴール（貴色）
thresholds4 = [(35, 64, -14, 1, -11, 4)]#コート（緑色）
#thresholds1 = [(53, 88, 48, 85, -22, 40)]#検証2
#thresholds2 = [(0, 100, 11, 31, -67, -45)]#ゴール（青色）
#上で色の変更可　ただLAB色空間での探知である
# generic_blue_thresholds
uart = UART(3, 115200)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)#カラースケール
sensor.set_framesize(sensor.QVGA)#解像度
sensor.skip_frames(time = 350)#描写速度
sensor.set_contrast(1)#コントラスト
sensor.set_brightness(-3)#明るさ
sensor.set_saturation(2)#彩
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking,(-5.874588, -6.02073, -1.887871)
clock = time.clock()

tim1 = Timer(4, freq=1000)


dac = DAC(Pin("P6"),bits=12)

# Only blobs that with more pixels than "pixel_threshold" and more area than "area_threshold" are
# returned by "find_blobs" below. Change "pixels_threshold" and "area_threshold" if you change the
# camera resolution. "merge=True" merges all overlapping blobs in the image.

while(True):  #メインループ
    n = 0#ボールカラーを取ったブロックの個数（for文の繰り返した回数）
    N = 0#ゴールの色を取ったブロックの個数（for文の繰り返した回数）
    m = 0
    M = 0
    blue_namber = 0
    yellow_namber = 0
    green_namber = 0
    ball_namber = 0
    a = 0
    b = 0
    d = 0
    #___________________________________________________________________________________________________________________________
    yoko_line = 100
    tate_line = 194
    tatetate_line = 170
    #___________________________________________________________________________________________________________________________気にしないで
    count = 0#ブロックの個数（今話使っていない
    areapf = 0
    iwashi = 0#取得したブロックの密度の最大値を保存
    haraga = 0#取得したブロックの面積の最大値を保存
    shinya = 0
    akiya  = 0
    #___________________________________________________________________________________________________________________________
    areaA    = [0,0,0,0,0,0,0,0,0,0]#取得したブロックの面積を配列にして1つの関数に保存
    areaB    = [0,0,0,0,0,0,0,0,0,0]
    areaC    = [0,0,0,0,0,0,0,0,0,0]
    areaD    = [0,0,0,0,0,0,0,0,0,0]
    #___________________________________________________________________________________________________________________________
    rectA    = [0,0,0,0,0,0,0,0,0,0]#取得したブロック（ボール）の中心のX座標、Y座標、ブロックの横幅、縦幅の値を配列にして1つの関数に保存
    rectB    = [0,0,0,0,0,0,0,0,0,0]
    rectC    = [0,0,0,0,0,0,0,0,0,0]
    rectD    = [0,0,0,0,0,0,0,0,0,0]
    #___________________________________________________________________________________________________________________________
    cxA      = [0,0,0,0,0,0,0,0,0,0]#取得したブロック（ボール）の中心のX座標のみを配列にして1つの関数に保存
    cxB      = [0,0,0,0,0,0,0,0,0,0]
    cxC      = [0,0,0,0,0,0,0,0,0,0]
    cxD      = [0,0,0,0,0,0,0,0,0,0]
    #___________________________________________________________________________________________________________________________
    cyA      = [0,0,0,0,0,0,0,0,0,0]#取得したブロック（ボール）の中心のY座標のみを配列にして1つの関数に保存
    cyB      = [0,0,0,0,0,0,0,0,0,0]
    cyC      = [0,0,0,0,0,0,0,0,0,0]
    cyD      = [0,0,0,0,0,0,0,0,0,0]
    #___________________________________________________________________________________________________________________________
    val_A_F    = [0,0,0,0,0,0,0,0,0,0]#画面中心のX座標
    val_A_S    = [0,0,0,0,0,0,0,0,0,0]#画面中心のX座標
    vall_A   = [0,0,0,0,0,0,0,0,0,0]#画面中心のY座標
    val_B    = [0,0,0,0,0,0,0,0,0,0]#画面中心のX座標
    vall_B   = [0,0,0,0,0,0,0,0,0,0]#画面中心のY座標
    val_C    = [0,0,0,0,0,0,0,0,0,0]#画面中心のX座標
    vall_C   = [0,0,0,0,0,0,0,0,0,0]#画面中心のY座標
    val_D    = [0,0,0,0,0,0,0,0,0,0]#画面中心のX座標
    vall_D   = [0,0,0,0,0,0,0,0,0,0]#画面中心のY座標
    #___________________________________________________________________________________________________________________________
    rA_F       = [0,0,0,0,0,0,0,0,0,0]#atan2を使って出した角度（単位ラジアン）
    rA_S       = [0,0,0,0,0,0,0,0,0,0]#atan2を使って出した角度（単位ラジアン）
    rB_P     = [0,0,0,0,0,0,0,0,0,0]#atan2を使って出した角度（単位ラジアン）
    rB_S     = [0,0,0,0,0,0,0,0,0,0]#atan2を使って出した角度（単位ラジアン）
    rC_P     = [0,0,0,0,0,0,0,0,0,0]#atan2を使って出した角度（単位ラジアン）
    rC_S     = [0,0,0,0,0,0,0,0,0,0]#atan2を使って出した角度（単位ラジアン）
    rD       = [0,0,0,0,0,0,0,0,0,0]#atan2を使って出した角度（単位ラジアン）
    #___________________________________________________________________________________________________________________________
    radsA_F    = [0,0,0,0,0,0,0,0,0,0]#ｒによって出た角度を絶対値に
    radsA_S    = [0,0,0,0,0,0,0,0,0,0]#ｒによって出た角度を絶対値に
    radsB_P  = [0,0,0,0,0,0,0,0,0,0]#ｒによって出た角度を絶対値に
    radsB_S  = [0,0,0,0,0,0,0,0,0,0]#ｒによって出た角度を絶対値に
    radsC_P  = [0,0,0,0,0,0,0,0,0,0]#ｒによって出た角度を絶対値に
    radsC_S  = [0,0,0,0,0,0,0,0,0,0]#ｒによって出た角度を絶対値に
    radsD    = [0,0,0,0,0,0,0,0,0,0]#ｒによって出た角度を絶対値に
    #___________________________________________________________________________________________________________________________
    rioleA   = [0,0,0,0,0,0,0,0,0,0]#ボールの左右有無の判別用
    rioleB   = [0,0,0,0,0,0,0,0,0,0]#ボールの左右有無の判別用
    rioleC   = [0,0,0,0,0,0,0,0,0,0]#ボールの左右有無の判別用
    rioleD   = [0,0,0,0,0,0,0,0,0,0]#ボールの左右有無の判別用
    #___________________________________________________________________________________________________________________________
    distanceA= [0,0,0,0,0,0,0,0,0,0]
    distanceB= [0,0,0,0,0,0,0,0,0,0]
    distanceC= [0,0,0,0,0,0,0,0,0,0]
    distanceD= [0,0,0,0,0,0,0,0,0,0]
    #___________________________________________________________________________________________________________________________
    densityA = [0,0,0,0,0,0,0,0,0,0]#ボールの色の取った面積に対する密度
    densityB = [0,0,0,0,0,0,0,0,0,0]#ゴールの色の取った面積に対する密度

    clock.tick()
    img = sensor.snapshot()

###########################################################################################################################################################################

    for blob in img.find_blobs([thresholds1[threshold_index]], pixels_threshold=1, area_threshold=1, merge=True,margin=25):#下９０行目までカラーボールトラッキング
        if n > 9:
            break
        else:
            n += 1
        cxA[n]       = blob.cx()
        cyA[n]       = blob.cy()
        rectA[n]     = blob.rect()
        val_A_F[n]     = blob.cx()-tate_line#値の調整　画面中央を座標(0,0)に（口にあるやつ）
        val_A_S[n]     = blob.cx()-tatetate_line#値の調整　画面中央を座標(0,0)に
        vall_A[n]    = blob.cy()-yoko_line
        rA_F[n]        = int(math.atan2(-vall_A[n],-val_A_F[n])*100*0.31)#範囲の調整片側１８０度
        rA_S[n]        = int(math.atan2(-vall_A[n],-val_A_S[n])*100*0.31)#範囲の調整片側１８０度
        distanceA[n] = int((math.sqrt((math.pow(val_A_F[n],2))+(math.pow(vall_A[n],2))))*29.16666666666667)#２点間の距離の公式
        radsA_F[n]     = 100 - abs(rA_F[n])#atan2で出した値を絶対値に修正
        radsA_S[n]     = 100 - abs(rA_S[n])#atan2で出した値を絶対値に修正
        if radsA_F[n] > 38 :
            radsA[n] = radsA_F[n]
        else:
            radsA[n] = radsA_S[n]
        densityA[n]  = blob.density()
        areaA[n]     = blob.area()
        count        = blob.count()#使ってない
        if vall_A[n] > 0:
            rioleA[n] = 100#light or left
        else:
            rioleA[n] = 0

        #area.append(blob.area())
        for i in range(16):#見えたときの確認用LED
            led_control(2)
    for blob in img.find_blobs([thresholds2[threshold_index]], pixels_threshold=10, area_threshold=10, merge=True,margin=30):#青コート認識用カラートラッキング
        if m > 9:
            break
        else:
            m += 1
        cxB[m]       = blob.cx()
        cyB[m]       = blob.cy()
        rectB[m]     = blob.rect()
        val_B[m]     = blob.cx()-tate_line#値の調整　画面中央を座標(0,0)に
        vall_B[m]    = blob.cy()-yoko_line
        rB_P[m]      = int(math.atan2(-vall_B[m],val_B[m])*100*0.31)#範囲の調整片側１８０度
        rB_S[m]      = int(math.atan2(-vall_B[m],-val_B[m])*100*0.31)#範囲の調整片側１８０度
        distanceB[m] = int((math.sqrt((math.pow(val_B[m],2))+(math.pow(vall_B[m],2))))*29.16666666666667)#２点間の距離の公式
        radsB_P[m]     = int(abs((rB_P[m]+100)/2))#atan2で出した値を絶対値に修正
        radsB_S[m]     = int(abs((rB_S[m]+100)/2))#atan2で出した値を絶対値に修正
        densityB[m]  = blob.density()
        areaB[m]     = blob.area()
    for blob in img.find_blobs([thresholds3[threshold_index]], pixels_threshold=10, area_threshold=10, merge=True,margin=30):#黄コート認識用カラートラッキング
        if M > 9:
            break
        else:
            M += 1
        cxC[M]       = blob.cx()
        cyC[M]       = blob.cy()
        rectC[M]     = blob.rect()
        val_C[M]     = blob.cx()-tate_line#値の調整　画面中央を座標(0,0)に
        vall_C[M]    = blob.cy()-yoko_line
        rC_P[M]      = int(math.atan2(-vall_C[M],-val_C[M])*100*0.31)#範囲の調整片側１８０度
        rC_S[M]      = int(math.atan2(-vall_C[M],val_C[M])*100*0.31)#範囲の調整片側１８０度
        distanceC[M] = int((math.sqrt((math.pow(val_C[M],2))+(math.pow(vall_C[M],2))))*29.16666666666667)#２点間の距離の公式
        radsC_P[M]     = int((abs(rC_P[M]+100))/2)#atan2で出した値を絶対値に修正
        radsC_S[M]     = int((abs(rC_S[M]+100))/2)#atan2で出した値を絶対値に修正
        #densityC[M]  = blob.density()
        areaC[M]     = blob.area()
    for blob in img.find_blobs([thresholds4[threshold_index]], pixels_threshold=10, area_threshold=10, merge=True,margin=30):#コート認識用カラートラッキング
        if N > 9:
            break
        else:
            N += 1
        cxD[N]       = blob.cx()
        cyD[N]       = blob.cy()
        #valD[n]=blob.cx()-165#値の調整　画面中央を座標(0,0)に
        val_D[N]     = blob.cx()-tate_line
        #vallD[n]=blob.cy()-105
        vall_D[N]    = blob.cy()-yoko_line
        #rD[n]=int(math.atan2(-vall_D[n],-val_D[n])*100*0.31)#範囲の調整片側１８０度
        rD[N]        = int(((math.atan2(-vall_D[N],-val_D[N])*100*0.31)+100)/2)#範囲の調整片側１８０度
        #radsD[n]=int((rD[n]+100)%2)#atan2で出した値を絶対値に修正
        #radsD[n]=abs(rD[n])
        radsD[N]     = rD[N]
        rectD[N]     = blob.rect()
        areaD[N]     = blob.area()
        '''if vall_D[N]>0:
            radsD[N]
        else:
            radsD[N] = -radsD[N]+100'''
    for i in range(16):#見えないときはオフ
         led_control(0)
    iwashi = (max(areaA[:]))
    shinya = (max(areaB[:]))
    akiya  = (max(areaC[:]))
    haraga = (max(areaD[:]))

############################################################################################################################################################################

    if areaA[1] == iwashi != 0:#ボールの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectA[1],thickness=2)#長方形の生成
        img.draw_cross(cxA[1], cyA[1]) #中央のバツの生成
        ch1 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=radsA[1])
        ch2 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rioleA[1])
        dac.write(distanceA[1])
        ball_namber = 1
    elif areaA[2] == iwashi != 0:
        img.draw_rectangle(rectA[2],thickness=2)#長方形の生成
        img.draw_cross(cxA[2], cyA[2]) #中央のバツの生成
        ch1 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=radsA[2])
        ch2 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rioleA[2])
        dac.write(distanceA[2])
        ball_namber = 2
    elif areaA[3] == iwashi != 0:
        img.draw_rectangle(rectA[3],thickness=2)#長方形の生成
        img.draw_cross(cxA[3], cyA[3]) #中央のバツの生成
        ch1 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=radsA[3])
        ch2 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rioleA[3])
        dac.write(distanceA[3])
        ball_namber = 3
    elif areaA[4] == iwashi != 0:
        img.draw_rectangle(rectA[4],thickness=2)#長方形の生成
        img.draw_cross(cxA[4], cyA[4]) #中央のバツの生成
        ch1 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=radsA[4])
        ch2 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rioleA[4])
        dac.write(distanceA[4])
        ball_namber = 4
    elif areaA[5] == iwashi != 0:
        img.draw_rectangle(rectA[5],thickness=2)#長方形の生成
        img.draw_cross(cxA[5], cyA[5]) #中央のバツの生成
        ch1 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=radsA[5])
        ch2 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=rioleA[5])
        dac.write(distanceA[5])
        ball_namber = 5
    else:
        ch1 = tim1.channel(2, Timer.PWM, pin=Pin("P8"), pulse_width_percent=100)
        ch2 = tim1.channel(1, Timer.PWM, pin=Pin("P7"), pulse_width_percent=50)
        ball_namber = 0


    if areaB[1] == shinya != 0:#ボールの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectB[1],[29,137,235],thickness=1)#長方形の生成
        img.draw_cross(cxB[1], cyB[1],[29,137,235]) #中央のバツの生成
        blue_namber = 1
    elif areaB[2] == shinya != 0:
        img.draw_rectangle(rectB[2],[29,137,235],thickness=1)#長方形の生成
        img.draw_cross(cxB[2], cyB[2],[29,137,235]) #中央のバツの生成
        blue_namber = 2
    elif areaB[3] == shinya != 0:
        img.draw_rectangle(rectB[3],[29,137,235],thickness=1)#長方形の生成
        img.draw_cross(cxB[3], cyB[3],[29,137,235]) #中央のバツの生成
        blue_namber = 3
    elif areaB[4] == shinya != 0:
        img.draw_rectangle(rectB[4],[29,137,235],thickness=1)#長方形の生成
        img.draw_cross(cxB[4], cyB[4],[29,137,235]) #中央のバツの生成
        blue_namber = 4
    elif areaB[5] == shinya != 0:
        img.draw_rectangle(rectB[5],[29,137,235],thickness=1)#長方形の生成
        img.draw_cross(cxB[5], cyB[5],[29,137,235]) #中央のバツの生成
        blue_namber = 5
    else:
        blue_namber = 0

    if areaC[1] == akiya != 0:#ボールの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectC[1],[231,247,17],thickness=1)#長方形の生成
        img.draw_cross(cxC[1], cyC[1],[231,247,17]) #中央のバツの生成
        yellow_namber = 1
    elif areaC[2] == akiya != 0:
        img.draw_rectangle(rectC[2],[231,247,17],thickness=1)#長方形の生成
        img.draw_cross(cxC[2], cyC[2],[231,247,17]) #中央のバツの生成
        yellow_namber = 2
    elif areaC[3] == akiya != 0:
        img.draw_rectangle(rectC[3],[231,247,17],thickness=1)#長方形の生成
        img.draw_cross(cxC[3], cyC[3],[231,247,17]) #中央のバツの生成
        yellow_namber = 3
    elif areaC[4] == akiya != 0:
        img.draw_rectangle(rectC[4],[231,247,17],thickness=1)#長方形の生成
        img.draw_cross(cxC[4], cyC[4],[231,247,17]) #中央のバツの生成
        yellow_namber = 4
    elif areaC[5] == akiya != 0:
        img.draw_rectangle(rectC[5],[231,247,17],thickness=1)#長方形の生成
        img.draw_cross(cxC[5], cyC[5],[231,247,17]) #中央のバツの生成
        yellow_namber = 5
    else:
        yellow_namber = 0

    if areaD[1] == haraga != 0:#コートの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectD[1])#長方形の生成
        img.draw_cross(cxD[1], cyD[1]) #中央のバツの生成
        ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=radsD[1])
        green_namber = 1
    elif areaD[2] == haraga != 0:#コートの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectD[2])#長方形の生成
        img.draw_cross(cxD[2], cyD[2]) #中央のバツの生成
        ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=radsD[2])
        green_namber = 2
    elif areaD[3] == haraga != 0:#コートの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectD[3])#長方形の生成
        img.draw_cross(cxD[3], cyD[3]) #中央のバツの生成
        ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=radsD[3])
        green_namber = 3
    elif areaD[4] == haraga != 0:#コートの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectD[4])#長方形の生成
        img.draw_cross(cxD[4], cyD[4]) #中央のバツの生成
        ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=radsD[4])
        green_namber = 4
    elif areaD[5] == haraga != 0:#コートの色を整理　補足したブロックの密度で判別しソート
        img.draw_rectangle(rectD[5])#長方形の生成
        img.draw_cross(cxD[5], cyD[5]) #中央のバツの生成
        ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"), pulse_width_percent=radsD[5])
        green_namber = 5
    else:
        green_namber = 0


    if cxB[blue_namber] < cxC[yellow_namber]:
        attacking_goal_distance = distanceC[yellow_namber]
        attacking_goal_rads = radsC_S[yellow_namber]
        defensing_goal_rads = radsB_S[blue_namber]
        r_valx = 1
        r_valy = 1
    elif cxB[blue_namber] > cxC[yellow_namber]:
        attacking_goal_distance = distanceB[blue_namber]
        attacking_goal_rads = radsB_P[blue_namber]
        defensing_goal_rads = radsC_P[yellow_namber]
        r_valx = -1
        r_valy = -1
    else:
        attacking_goal_distance = distanceC[yellow_namber]
        attacking_goal_rads = radsC_P[yellow_namber]
        defensing_goal_rads = radsB_P[blue_namber]


    #a = (cyC[yellow_namber] - cyB[blue_namber])/(cxC[yellow_namber] - cxB[blue_namber])#ゴール間の直線の2次関数を取得
    #b = cyB[blue_namber] - (((cyC[yellow_namber] - cyB[blue_namber])*cxB[blue_namber])/(cxC[yellow_namber] - cxB[blue_namber]))

    #d = (abs((-a)*0 + 0 + (-b)))/(math.sqrt(math.pow(a,2)+math.pow(1,2)))

    img.draw_line(cxB[blue_namber], cyB[blue_namber],cxC[yellow_namber], cyC[yellow_namber],thickness=2)

    uart.write(str(abs(cxA[ball_namber]-320)))
    uart.write("a")
    uart.write(str(abs(cyA[ball_namber])))
    uart.write("b")
    uart.write(str(radsD[green_namber]))
    uart.write("c")
    uart.write(str(abs(yoko_line-240)))
    uart.write("d")
    uart.write(str(abs(tate_line-320)))
    uart.write("e")
    uart.write(str(abs(tatetate_line-320)))
    uart.write("f")
    uart.write(str(defensing_goal_rads))
    uart.write("g")
    uart.write(str(attacking_goal_rads))
    uart.write("h")
    uart.write(str(attacking_goal_distance))#max5500
    uart.write("i")
    uart.write(str(0))#max5500
    uart.write("j")
    uart.write(str(radsA[ball_namber]))
    uart.write("k")
    uart.write(str(0))
    uart.write("\n")


##############################################################################################################################################################################

    img.draw_line(0,yoko_line,320,yoko_line)#横線
    img.draw_line(tate_line,0,tate_line,240)#縦線
    img.draw_line(tatetate_line,0,tatetate_line,240)#縦線


    #dac.write(128)
    #print(iwashi,count,density[:])123 345
    #print(radsB[blue_namber],radsC[yellow_namber])
    print(radsA[ball_namber])
    #print(sensor.get_rgb_gain_db())

