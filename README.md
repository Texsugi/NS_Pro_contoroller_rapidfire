#GPIO

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


# RGB LED (anode common)
RGB_R = Pin(45, Pin.OUT)
RGB_G = Pin(46, Pin.OUT)
RGB_B = Pin(47, Pin.OUT)
