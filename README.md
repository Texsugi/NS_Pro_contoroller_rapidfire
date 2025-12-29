#Rapidfire configuration

■連射設定の流れ
L,R,ZL,ZRボタン長押し
↓
白赤緑青とHOMEボタンのLEDが1回光る
↓
連射設定したいボタンを押す
↓
HOMEボタンのLEDがボタンごとの連射設定状況に応じて光る
↓
ZRボタンでモード選択、Lで連射間隔を長く、Rで連射間隔を短くする。
↓
ZLボタン長押しで設定モードを完了
↓
白赤緑青とHOMEボタンのLEDが2回光る

※連射設定中の設定オプション
上ボタン：虹色点灯オン
下ボタン：虹色点灯オフ

-ボタン：初弾のボタンオン時間を長くする
+ボタン：初弾のボタンオン時間を短くする

SSボタン：2発目以降のボタンオン時間を長くする
HOMEボタン：2発目以降のボタンオン時間を短くする

ボタンオン時間の調整は連射の引っかかりなどがある場合の調整用で、各4段階。

■モード毎の動作

白点灯：連射無し
↓
赤点滅の時：シングルクリック長押し固定で連射、離すと連射オフ。ダブルクリックで連射無し、長押しすると連射無しの固定
↓
緑点滅：シングルクリックは連射無しと同じ。ダブルクリック長押しで連射。
↓
青点滅：クリックする毎に連射ホールド、連射解除。
↓
白点灯に戻る

#GPIO定義

outputs = {
    'A': Pin(36, Pin.OUT), 'B': Pin(34, Pin.OUT), 'X': Pin(32, Pin.OUT), 'Y': Pin(27, Pin.OUT),
    'L': Pin(33, Pin.OUT), 'R': Pin(30, Pin.OUT), 'ZL': Pin(31, Pin.OUT),
    'UP': Pin(16, Pin.OUT), 'DOWN': Pin(18, Pin.OUT), 'LEFT': Pin(19, Pin.OUT), 'RIGHT': Pin(17, Pin.OUT),
    'Home': Pin(11, Pin.OUT), 'SS': Pin(9, Pin.OUT), '+': Pin(13, Pin.OUT), '-': Pin(10, Pin.OUT)
}

switches = {
    'A': Pin(43, Pin.IN, Pin.PULL_UP), 'B': Pin(42, Pin.IN, Pin.PULL_UP),
    'X': Pin(44, Pin.IN, Pin.PULL_UP), 'Y': Pin(41, Pin.IN, Pin.PULL_UP),
    'L': Pin(1, Pin.IN, Pin.PULL_UP), 'R': Pin(2, Pin.IN, Pin.PULL_UP),
    'ZL': Pin(0, Pin.IN, Pin.PULL_UP),
    'UP': Pin(20, Pin.IN, Pin.PULL_UP), 'DOWN': Pin(23, Pin.IN, Pin.PULL_UP),
    'LEFT': Pin(21, Pin.IN, Pin.PULL_UP), 'RIGHT': Pin(22, Pin.IN, Pin.PULL_UP),
    'Home': Pin(4, Pin.IN, Pin.PULL_UP), 'SS': Pin(6, Pin.IN, Pin.PULL_UP),
    '+': Pin(5, Pin.IN, Pin.PULL_UP), '-': Pin(7, Pin.IN, Pin.PULL_UP)
}


#RGBLED(anode common)

RGB_R = Pin(45, Pin.OUT)
RGB_G = Pin(46, Pin.OUT)
RGB_B = Pin(47, Pin.OUT)
