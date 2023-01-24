import sys
from sys import argv
#list_sp_data = [[[1971,11],92.78,3.08], [[1971,12],99.17,3.07], [[1972,1],103.30,3.07],[[1972,2],105.20,3.07],[[1972,3],107.70,3.07],[[1972,4],108.80,3.07],[[1972,5],107.70,3.07]]
def parse_sp_data(filename_sp): # missing test of legal numeric data
    list_sp_data = []
    with open(filename_sp, "r") as f:
        lines = f.readlines()
        judge = "."
        for line in lines:
            sp = line.strip("\n").split(",")
            if len(sp) != 3:
                raise ValueError("number of fields presented not correct")
                sys.exit(2) # not specified in file previously
            if judge in sp[0]:
               time = sp[0].split(".")
               year = int(time[0])
               month = int(time[1])
               if month > 12 or month < 0:
                   raise ValueError("date is not legal")
                   sys.exit(2) # not specified in file previously
               index = float(sp[1])
               if index < 0:
                   raise ValueError("index is negative")
                   sys.exit(2)
               dividend = float(sp[2])
               if dividend < 0:
                   raise ValueError("dividend is negative")
                   sys.exit(2)
               sp_data = [[year, month], index, dividend]
               list_sp_data.append(sp_data)

    if list_sp_data == []:
        raise ValueError("sp_data.csv is empty")#检测文档是否为空
        sys.exit(2)
   
    for i in range(len(list_sp_data) - 1):
        year_i = list_sp_data[i][0][0]
        year_n = list_sp_data[i+1][0][0]
        month_i = list_sp_data[i][0][1]
        month_n = list_sp_data[i+1][0][1]
        if (year_i == year_n and month_i == month_n - 1) or (year_i == year_n -1 and month_i == 12 and month_n == 1):#有问题
            continue
        else:
            print("sp_data is not arranged in proper time sequence")#检测数据是否严格按照时间排序
            sys.exit(2)
     
    return list_sp_data   
    
#list_bond_data=[[[1971,12],5.93],[[1972,1],5.95],[[1972,2],6.08],[[1972,3],6.07],[[1972,4],6.19],[[1972,5],6.13]]    
def parse_bond_data(filename_bond):
    list_bond_data = []
    with open(filename_bond, "r") as f:
        lines = f.readlines()
        judge = "."
        for line in lines:
            bond = line.strip("\n").split(",")
            if len(bond) != 2:
                raise ValueError("number of fields presented not correct")
                sys.exit(3) # not tested previously
            if judge in bond[0]:
                time = bond[0].split(".")
                year = int(time[0])
                month = int(time[1])
                if month > 12 or month < 0:
                    raise ValueError("date is not legal")
                    sys.exit(3) # not tested previously
                percentage = float(bond[1])
                if percentage < 0:
                    raise ValueError("percentage is negative")
                    sys.exit(3)
                bond_data = [[year, month], percentage]
                list_bond_data.append(bond_data)

    if list_bond_data == []: # lines 是空就已经可以检测空文档了，不用到现在测试
        raise ValueError("bond_data.csv is empty")
        sys.exit(3)
        
    for i in range(len(list_bond_data) - 1): 
        year_i = list_bond_data[i][0][0]
        year_n = list_bond_data[i+1][0][0]
        month_i = list_bond_data[i][0][1]
        month_n = list_bond_data[i+1][0][1]
        if (year_i == year_n and month_i == month_n - 1) or (year_i == year_n -1 and month_i == 12 and month_n == 1):#有问题 good test case, comprehensive
            continue
        else:
            print("bond_data is not arranged in proper time sequence")
            sys.exit(3)
        
    return list_bond_data
#list_sp_data = [[[1971,11],92.78,3.08], [[1971,12],99.17,3.07], [[1972,1],103.30,3.07],[[1972,2],105.20,3.07],[[1972,3],107.70,3.07],[[1972,4],108.80,3.07],[[1972,5],107.70,3.07]]
def get_rq_sp(list_sp_data, st_date, ed_date):    
    #判断起止日期是否合法    
    list_rq_sp = []
    
    l_st_date = st_date.split(".")
    st_year = int(l_st_date[0])
    st_month = int(l_st_date[1])
    l_ed_date = ed_date.split(".")
    ed_year = int(l_ed_date[0])
    ed_month = int(l_ed_date[1])
    
    if not ((list_sp_data[0][0][0] + list_sp_data[0][0][1] / 100) <= (st_year + st_month / 100)) and ((ed_year + ed_month / 100) <= (list_sp_data[-1][0][0] + list_sp_data[-1][0][1] / 100)):
        raise RuntimeError("the intended time span go beyond the sp_database")
        sys.exit(1)
    #判断起止日期是否合法, 其实也可以全部变成int形式，用年比较年，月比较月
    for i in range(len(list_sp_data)):
        if list_sp_data[i][0][0] == st_year and list_sp_data[i][0][1] == st_month:
            start = i
        elif list_sp_data[i][0][0] == ed_year and list_sp_data[i][0][1] == ed_month:
            end = i # no need "elif", "if" is enough
    if start == 0:
        raise ValueError("start == 0, not enough data to calculate sp_ror")
    else:
        for n in range(start-1, end+1):
            list_rq_sp.append(list_sp_data[n])
    return list_rq_sp
#print(get_rq_sp(list_sp_data, "1971.12", "1972.05"))


#list_bond_data=[[[1971,12],5.93],[[1972,1],5.95],[[1972,2],6.08],[[1972,3],6.07],[[1972,4],6.19],[[1972,5],6.13]]
def get_rq_bond(list_bond_data, st_date, ed_date):    
       
    list_rq_bond = []
    
    l_st_date = st_date.split(".")
    st_year = int(l_st_date[0])
    st_month = int(l_st_date[1])
    l_ed_date = ed_date.split(".")
    ed_year = int(l_ed_date[0])
    ed_month = int(l_ed_date[1])
    
    if not ((list_bond_data[0][0][0] + list_bond_data[0][0][1] / 100) <= (st_year + st_month / 100)) and ((ed_year + ed_month / 100) <= (list_bond_data[-1][0][0] + list_bond_data[-1][0][1] / 100)):
        raise RuntimeError("the intended time span go beyond the bond_database")
        sys.exit(1)
    #判断起止日期是否合法
    for i in range(len(list_bond_data)):
        if list_bond_data[i][0][0] == st_year and list_bond_data[i][0][1] == st_month:
            start = i
        if list_bond_data[i][0][0] == ed_year and list_bond_data[i][0][1] == ed_month:
            end = i
            
    for n in range(start, end+1):
        list_rq_bond.append(list_bond_data[n])
    return list_rq_bond

#print(get_rq_bond(list_bond_data, "1971.12", "1972.05"))
#list_rq_bond = [[[1971, 12], 5.93], [[1972, 1], 5.95], [[1972, 2], 6.08], [[1972, 3], 6.07], [[1972, 4], 6.19], [[1972, 5], 6.13]]
 
#list_rq=[[[1971, 11], 92.78, 3.08], [[1971, 12], 99.17, 3.07], [[1972, 1], 103.3, 3.07], [[1972, 2], 105.2, 3.07], [[1972, 3], 107.7, 3.07], [[1972, 4], 108.8, 3.07], [[1972, 5], 107.7, 3.07]]

def print_date(list_rq_bond):
    l_date = []
    for m in range(len(list_rq_bond)):
        year = list_rq_bond[m][0][0]
        month = list_rq_bond[m][0][1] / 100
        date = year + month
        l_date.append("%.2f" % date)
    return l_date

def cal_port1(list_rq_sp):    
     bala_t = 0
     l_bala_port1 = []
     contri = 100
     for m in range(len(list_rq_sp) - 1):
         t = m + 1
         
         if list_rq_sp[t][0][1] == 1:
             contri = contri * 1.025 # 每年年初比去年多投进去100刀
                 
         sp_t = list_rq_sp[t][1]
         sp_t_1 = list_rq_sp[t-1][1]
         div_t = list_rq_sp[t][2]
         
         sp_ror_t = sp_t / sp_t_1 - 1
         div_ror_t = (div_t / 12) / sp_t
         port_ror_t = sp_ror_t + div_ror_t
         
         bala_t = bala_t * (1 + port_ror_t) + contri
         l_bala_port1.append("%.2f" % bala_t)
     return l_bala_port1  
 
def cal_port2(list_rq_bond):
    bala_t = 0
    l_bala_port2 = []
    contri = 100
    for m in range(len(list_rq_bond)):
        if list_rq_bond[m][0][1] == 1:
            contri = contri * 1.025 # 每年年初比去年多投进去100刀
        
        bond_t = list_rq_bond[m][1]
        bond_ror_t = bond_t / 12 / 100
        
        bala_t = bala_t * (1 + bond_ror_t) + contri
        l_bala_port2.append("%.2f" % bala_t)
    return l_bala_port2

#print(cal_port2(list_bond_data))

def cal_port3(list_rq_sp, list_rq_bond):
    bala_t = 0
    l_bala_port3 = []
    contri = 100
    life_al_sp = 1
    for i in range(len(list_rq_bond)):
        t = i + 1
        if list_rq_bond[i][0][1] == 1: # 每年年初多投入100刀，并将投资在股票上的比重下调2%
            contri = contri * 1.025
            life_al_sp -= 0.02
        sp_t = list_rq_sp[t][1]
        sp_t_1 = list_rq_sp[t-1][1]
        div_t = list_rq_sp[t][2]        
        sp_ror_t = sp_t / sp_t_1 - 1
        div_ror_t = (div_t / 12) / sp_t
        total_ror_t = sp_ror_t + div_ror_t # 建议改为stock_ror_t以避免all带来的混淆

        bond_t = list_rq_bond[i][1]
        bond_ror_t = bond_t / 12 / 100
        
        bala_t = bala_t * (1 + total_ror_t) * life_al_sp + bala_t * (1 + bond_ror_t) * (1 - life_al_sp) + contri
        l_bala_port3.append("%.2f" % bala_t)
    return l_bala_port3


def make_csv(filename_sp, filename_bond, st_date, ed_date): 
    list_sp_data = parse_sp_data(filename_sp)
    list_bond_data = parse_bond_data(filename_bond)
    
    list_rq_sp = get_rq_sp(list_sp_data, st_date, ed_date)
    list_rq_bond = get_rq_bond(list_bond_data, st_date, ed_date)
    
    l_date = print_date(list_rq_bond)
    l_bala_port1 = cal_port1(list_rq_sp)
    l_bala_port2 = cal_port2(list_rq_bond)
    l_bala_port3 = cal_port3(list_rq_sp, list_rq_bond)
    
    f = open("portfolio.csv", "wt")
    f.write("Date,StrategyOne,StrategyTwo,StrategyThree\n")
    for i in range(len(l_date)):
        f.write("{},{},{},{}\n".format(l_date[i], l_bala_port1[i], l_bala_port2[i], l_bala_port3[i]))
    f.close()
    
if __name__ == "__main__":
    if len(argv) != 5:
        print("Error: Incorrect number of command-line")#判断csv结尾和文件对不对
        sys.exit(1)
        
    start_date = float(argv[3])
    end_date = float(argv[4])
    if start_date >= end_date:
        print("Error: start date greater than or equal to end date")
        sys.exit(1)
        
    legal_sp_filename = argv[1].split(".")
    if len(legal_sp_filename) != 2:
        print("Error: not a legal sp data file")
        sys.exit(2)
    if legal_sp_filename[1] != "csv":
        print("Error: sp data file not stored properly")
        sys.exit(2)
        
    legal_bond_filename = argv[2].split(".")
    if len(legal_bond_filename) != 2:
        print("Error: not a legal bond data file")
        sys.exit(3)
    if legal_bond_filename[1] != "csv":
        print("Error: bond data file not stored properly")              
        sys.exit(3)
        
    try:
        f_sp = open(argv[1])
    except FileNotFoundError:
        print("Error: unable to find bond file")
        sys.exit(2)

    try:
        f_bond = open(argv[2])
    except FileNotFoundError:
        print("Error: unable to find sp file")
        sys.exit(3)        
    
        
    make_csv(argv[1], argv[2], argv[3], argv[4])
    
