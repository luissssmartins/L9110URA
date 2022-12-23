from machine import Pin, PWM

class DCMotor:
    kind = 'DCMotor'

    def __init__(self, pin_esq, pin_dir):
        self.Pwm = PWM(Pin(pin_esq), freq=1000, duty = 0)
        self.Dir = Pin(pin_dir, Pin.OUT)
    
    def power(self, value):
        self.Pwm.duty(value)
    
    def way(self, sen = 0):
        if sen == 0:
            self.Dir.off()
        else:
            self.Dir.on()