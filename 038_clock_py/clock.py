class MyClock24:
    '''
    Represents a 24 clock
    '''
    def __init__(self, hour=0, minute=0, second=0):#1. why assign the time to 0 "here", assign it last line(hours=0\nminutes=0) 2. why assign time to 0, shouldn't be what the use waht to input?
        self.hours = hour
        self.minutes = minute
        self.seconds = second
#so self means the three-number-argument inputed by the user?
        
    @property#to what extend can we write in a property-decorated method? or is it just a regular function?
    def hour(self):
        if self.hours > 24:
            self.hours -= 24
            return self.hours #如果输入的小时数大于24，则取余数对应真正的小时数
        else:
            return self.hours
    
    
    @property
    def minute(self):
        return self.minutes #1. why again? self.minutes was initialized in __init__, or self.minutes up there is initialized here? 2.  self.__minutes "__" is used to indicate programmers and users invoking name mangling or internal use, not the computer
    
    
    @property
    def second(self):
        return self.seconds
   
    
    def tick(self):
        self.seconds += 1 #这个方法用于秒针子夜，调用时会反复循环调用所以不用自己循环，之所以后面都可以清零就是因为每次只加一秒，不会出现加一秒使得59分变成2分、3分，只会变成0分，时同理
        if self.seconds == 60:
            self.seconds = 0
            self.minutes += 1#如果这次循环中秒数加的等于60了，向分进一位并清零；当然，不进位就结束这次循环，进入下一次
            if self.minutes == 60:
                self.minutes = 0
                self.hours += 1 #如果这次循环中秒的进位使得分数加的等于60了，向时进一位并清零；当然，不进位就结束这次循环，进入下一次
                if self.hours == 24:
                    self.hours = 0#如果这次循环中分的进位使得时数加的等于24了，直接清零；当然，不进位就结束这次循环，进入下一次
 
    
    def __str__(self):
        return "{:02d}:{:02d}:{:02d}".format(self.hour, self.minute, self.second)#1. what happened if minute or second exceed 60? or just because the test doesn't test it？2. should it be self.hours, self.minutes, self.seconds?


    def __repr__(self):
        return str(self.__dict__)#python内置魔术方法__dict__，把变量名hours, minutes, seconds和对应值转化为字典一一对应，最后变成字符串
    
    
    def __eq__(self, other):#1. other in what form? determined by test? 2. "magic" objects or attributes that live in user-controlled namespaces. E.g. __init__, __import__ or __file__. Never invent such names; only use them as documented. but not built-in like __dict__, I still have to write by myself, then why not __plus__? anyway everything is I wrote
        return (self.hours - other.hours)%24 == 0 and (self.minutes - other.minutes)%60 == 0 and (self.seconds - other.seconds)%60 == 0#全部相等，两个才相等,小时超过24没有意义，于是都变成一天内
#still, what happened when minutes and seconds exceed 60? sure that other inputed won't be "illegal"?    
    
    def __ne__(self, other):
        return not ((self.hours - other.hours)%24 == 0 and (self.minutes - other.minutes)%60 == 0 and (self.seconds - other.seconds)%60 == 0)#一样的，有一个不等那就是不等
    
    
    def __ge__(self, other):#看原有时间是否大于等于新输入的other时间
        if (self.hours - other.hours)%24 > 0:#直接小时数就大了，那铁定大，注意超过24的小时数；谈论等于尚早，往下看
            return True
        elif ((self.hours - other.hours)%24 == 0 and self.minutes - other.minutes>0):#小时数一样（超过24的小时数没有用），分钟数大，也铁定大；谈论等于尚早，往下看
            return True
        elif (((self.hours - other.hours)%24 == 0 and self.minutes - other.minutes==0 and self.seconds - other.seconds>=0)):#小时数一样，分钟数一样（当然不考虑分钟数大于60的情况），秒数大，铁定大；同时秒数相等，也符合大于等于
            return True
        else:
            return False#其他一切情况都小于
        
        
    def __gt__(self, other):
        if (self.hours - other.hours)%24 > 0:
            return True
        elif ((self.hours - other.hours)%24==0 and self.minutes - other.minutes>0):
            return True
        elif (((self.hours - other.hours)%24==0 and self.minutes - other.minutes==0 and self.seconds - other.seconds>0)):#与上面相同，只是不考虑等于的情况
            return True
        else:
            return False
        
        
    def __le__(self, other):
        if (self.hours - other.hours % 24) < 0:#直接小时数小，那铁定小
            return True
        elif ((self.hours - other.hours)%24==0 and self.minutes - other.minutes<0):#小时数一样（超过24不算），分钟数小
            return True
        elif (((self.hours - other.hours)%24==0 and self.minutes - other.minutes==0 and self.seconds - other.seconds<=0)):#小时数一样，分钟数一样，秒数小于等于就可以，当然也不考虑非法分钟数和秒数
            return True
        else:
            return False#其他一切情况都是大于
        
        
    def __lt__(self, other):
        if (self.hours - other.hours) < 0:
            return True
        elif ((self.hours - other.hours) == 0 and self.minutes - other.minutes<0):
            return True
        elif (((self.hours - other.hours) == 0 and self.minutes - other.minutes==0 and self.seconds - other.seconds<0)):#一样的，只是不考虑等于的情况
            return True
        else:
            return False
        
        
    def __add__(self,other):#other can be both a number or a three-number-argument
        if type(other)==int:#如果输入的是一个数字
            for i in range(0,other):#模拟tick（）的一个一个加的模式
                self.seconds += 1
                if self.seconds == 60:
                    self.seconds = 0
                    self.minutes += 1
                    if self.minutes == 60:
                        self.minutes = 0
                        self.hours += 1
                        if self.hours == 24:
                            self.hours -=24
            return self
        else:
            self.seconds += other.seconds #如果输入的是一串三个数字组成的arg，先加秒数
            if self.seconds >= 60:#如果加完了秒数大于60，进位，并清零秒数
                    self.seconds -=60
                    self.minutes += 1
                    if self.minutes >= 60:#如果分数进位后大于60，再进位，并清零分数
                        self.minutes -=60
                        self.hours += 1
                        if self.hours >= 24:#如果时数进位后大于24，直接清零
                            self.hours -=24
            self.minutes +=other.minutes#再加分数，如进位故事
            if self.minutes >= 60:
                self.minutes -=60
                self.hours += 1
                if self.hours >= 24:
                    self.hours = 0
            self.hours+=other.hours#再加时数，不进位，满24直接清零
            if self.hours >= 24:
                    self.hours -=24
            return self
        
        
    def __sub__(self,other):#如加法故事,只不过是向上一位借
        if type(other)==int:
            for i in range(0,other):
                self.seconds -= 1
                if self.seconds < 0:
                    self.seconds += 60
                    self.minutes -= 1
                    if self.minutes < 0:
                        self.minutes += 60
                        self.hours -= 1
                        if self.hours < 0:
                            self.hours +=24
            return self
        else:
            self.seconds -= other.seconds
            if self.seconds < 0:
                self.seconds += 60
                self.minutes -= 1
                if self.minutes < 0:
                    self.minutes += 60
                    self.hours -= 1
                    if self.hours < 0:
                        self.hours +=24
            self.minutes -=other.minutes
            if self.minutes < 0:
                self.minutes += 60
                self.hours -= 1
                if self.hours < 0:
                    self.hours +=24
            self.hours-=other.hours
            if self.hours < 0:
                self.hours +=24
            return self
