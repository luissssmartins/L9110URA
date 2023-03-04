from motor.DCMotor import DCMotor

import time

class L9110URA(DCMotor):

    def __init__(self, pinLeft1, pinLeft2, pinRight1, pinRight2):
        self.name = 'L9110URA'
        self.parameter1 = 0
        self.parameter2 = 0
        self.speedBaseRight = 1000
        self.speedBaseLeft = 1000
        self.maximumAllowedCmdTime = 5000

        self.leftMotor = DCMotor(pinLeft1, pinLeft2)
        self.rightMotor = DCMotor(pinRight1, pinRight2)
    
    def setSpeed(self, _sl, _sr):
        self.speedBaseLeft = _sl
        self.speedBaseRight = _sr
    
    def configuration(self, leftWay, leftPower, rightWay, rightPower):
        self.leftMotor.way(leftWay)
        self.leftMotor.power(leftPower)

        self.rightMotor.way(rightWay)
        self.rightMotor.power(rightPower)

    
    def motors(self, speedLeft, speedRight):
        directionRight = 1
        directionLeft = 1

        customLeftSpeed = self.speedBaseLeft - speedLeft
        customRightSpeed = self.speedBaseRight - speedRight

        if speedLeft <= 0:
            directionRight = 0
            customLeftSpeed = -speedLeft
        elif speedRight <= 0:
            directionLeft = 0
            customRightSpeed = -speedRight
        
        self.configuration(directionRight, customLeftSpeed, directionLeft, customRightSpeed)
    
    def front(self, vel = 1000):

        if (vel > 1000):
            vel = 1000
        
        self.configuration(1, 1000 - vel, 1000 - vel)
    
    def reverse(self, vel = 1000):
        self.configuration(0, vel, 0, vel)
    
    def left(self):
        self.configuration(0, self.speedBaseLeft, 1, 0)
    
    def right(self):
        self.configuration(1, 0, 0, self.speedBaseRight)
    
    def stop(self):
        self.configuration(0, 0, 0, 0)
    
    def timer(self, _t):

        if (_t > self.maximumAllowedCmdTime):
            time.sleep_ms(self.maximumAllowedCmdTime)
        else:
            time.sleep_ms(_t)
        
        self.configuration(0, 0, 0, 0)
    
    def moveFront(self, time = 300):
        self.configuration(1, 0, 1, 0)
        self.timer(time)
    
    def moveReverse(self, time = 300):
        self.configuration(0, self.speedBaseLeft, 0, self.speedBaseRight)
        self.timer(time)
    
    def moveLeft(self, time = 150):
        self.configuration(0, self.speedBaseLeft, 1, 0)
        self.timer(time)
    
    def moveRight(self, time = 150):
        self.configuration(1, 0, 0, self.speedBaseRight)
        self.timer(time)
    

    

    
