import subprocess
import time
import numpy as np
import os
import random
from pathlib import Path
mode = 2
l = 4
k = 4
n = 256
gamma1 = pow(2,17)
beta = 78
omega=80
Q = 8380417

# global number_one
#
# number_one =0
def read_data(filename, s1_file, pk_file):
    # 从第二个压缩包读取 s1
    s1 = get_s1(s1_file)

    # 消息仍然从原来的 metadata 文件中读取
    profiling_data = np.load(filename, allow_pickle=True)
    msg = profiling_data["msg"]

    # 公钥从第二个压缩包的 pk_16.txt 中读取
    with open(pk_file, "r", encoding="ascii") as f:
        pk = "".join(f.read().split()).lower()

    if len(pk) != 2624:
        raise ValueError(
            f"公钥长度错误：{len(pk)} 个十六进制字符，应为 2624"
        )

    if any(c not in "0123456789abcdef" for c in pk):
        raise ValueError("pk_16.txt 中包含非法字符")

    return msg, s1, pk

def max_z(z,bound):
    max =-99999999
    for i in range(l):
        for j in range(256):
            #print(z[i][j])
            if abs(z[i][j]) > max:
                max = abs(z[i][j])
                
    if max >=   gamma1-beta:
        #print(max)
        return True
    else:
        return False          

def get_t():
    t_list =[]
    with open('./median_value/t.txt','r',encoding = 'utf-8') as f:
        for line in f:
            temp_list = []
            # print(line.split('\n')[0].split(' '))
            for item in line.split('\n')[0].split(' ')[:-1]:
                temp_list.append(int(item))
            t_list.append(temp_list)
    # print(len(t_list))
    # print(t_list)
    return t_list

def get_z():
    z_list = []
    with open('./median_value/z.txt', 'r', encoding='utf-8') as f:
        for line in f:
            temp_list = []
            # print(line.split('\n')[0].split(' '))
            for item in line.split('\n')[0].split(' ')[:-1]:
                temp_list.append(int(item))
            z_list.append(temp_list)
    # print(len(t_list))
    # print(t_list)
    return z_list
    
def get_s1(filename):
    s1_list = []
    with open(filename, 'r', encoding='utf-8') as f:
        for line in f:
            temp_list = []
            # print(line.split('\n')[0].split(' '))
            range_list = ['-1','-2','-3','-4','0','1','2','3','4']
            if	line.split('\n')[0].split(' ')[-1] in range_list:
                for item in line.split('\n')[0].split(' '):
                    temp_list.append(int(item))
            else:
                for item in line.split('\n')[0].split(' ')[:-1]:
                    temp_list.append(int(item))
            s1_list.append(temp_list)
    # print(len(t_list))
    # print(t_list)
    return s1_list

def get_w1():
    w1_list = []
    with open('./median_value/w1.txt', 'r', encoding='utf-8') as f:
        for line in f:
            temp_list = []
            # print(line.split('\n')[0].split(' '))
            for item in line.split('\n')[0].split(' ')[:-1]:
                temp_list.append(int(item))
            w1_list.append(temp_list)
    return w1_list

    pass

def get_c():
    c_list =[]
    with open('./median_value/c.txt','r',encoding = 'utf-8') as f:
        for line in f:
            for item in line.split('\n')[0].split(' ')[:-1]:
                c_list.append(int(item))
    return c_list

h=[]
for i in range(k):
    temp_list =[]
    for j in range(256):
        temp_list.append(0)
    h.append(temp_list)
    
def forgery_sign(m,s1,pk):

    makefile_path = "./c_file/"
    if os.path.exists(makefile_path+'PQCgenKAT_sign'):
        #print("文件存在")
        pass
    else:
        #print("文件不存在")
        subprocess.run(["make"],cwd=makefile_path)
    #subprocess.run(["make"],cwd=makefile_path)
    with open('./median_value/m.txt','w',encoding='utf-8') as f:
        f.write('m = {}'.format(m))
    with open('./median_value/write_s1.txt','w',encoding='utf-8') as f:
        for i in range(l):
            for j in range(256):
                if mode == 2 or 5:
                    if s1_work[i][j] == -1:
                        s1_work[i][j] = 3
                    if s1_work[i][j] == -2:
                        s1_work[i][j] = 4
                else:
                    if s1_work[i][j] == -1:
                        s1_work[i][j] = 5
                    if s1_work[i][j] == -2:
                        s1_work[i][j] = 6
                    if s1_work[i][j] == -3:
                        s1_work[i][j] = 7
                    if s1_work[i][j] == -4:
                        s1_work[i][j] = 8  				
                if j == 255:
                    f.write(str(s1_work[i][j]))
                else:
                    f.write('{} '.format(s1_work[i][j]))
            f.write('\n')
    with open('./median_value/pk.txt','w',encoding='utf-8') as f:
        f.write('{}'.format(pk))
                
    diedai = 0
    flag = True
    while flag:
        if diedai == 100:
            return ' '
        #print('flag is {}'.format(flag))
        #source_file = './c_file/PQCgenKAT_sign'
        #destination_file = './PQCgenKAT_sign'
        #command = 'mv {} {}'.format(source_file,destination_file)
        #subprocess.run(command,shell=True)
        #time.sleep(0.1)
        execute_command = ["./PQCgenKAT_sign",str(diedai)]
        #subprocess.run(execute_command)
        result = subprocess.run(execute_command, capture_output=True, text=True,cwd='./c_file')
        print(result.stdout, end='')
        print(result.stderr, end='')
        diedai +=1
        print("第{}次迭代".format(diedai))
        number_one = 0
        t = get_t()
        w = get_w1()
        #c = get_c()
        for i in range (k):
            for j in range (n):
                if t[i][j] != w[i][j] :
                    h[i][j] = 1
                else:
                    h[i][j] = 0
                number_one = number_one + h[i][j]
        #print(number_one)
        # z = get_z()
        # if max_z(z,gamma1 - beta) or number_one > omega:
        #     flag = True
        #     #print('dayu!')
        #     continue
        # else:
        #     flag = False
        # if '验证失败' in result.stdout:
        #     flag = True
        #     #print('verify signature failure')
        # else:
        #     flag = False
        #     #print('verify signature success!')

        z = get_z()
        
        # C 程序是否通过 crypto_sign_open() 验证
        verify_ok = (
            result.returncode == 0
            and "验证失败" not in result.stdout
        )

        # 输出 C 程序的验证信息
        print(result.stdout, end="")
        print(result.stderr, end="")

        # rejection 条件
        rejected_by_norm = max_z(z, gamma1 - beta)
        rejected_by_hint = number_one > omega

        if rejected_by_norm or rejected_by_hint or not verify_ok:
            flag = True
            print(
                "当前候选被拒绝："
                f"norm={rejected_by_norm}, "
                f"hint={rejected_by_hint}, "
                f"verify={verify_ok}"
            )
            continue

        # 三个条件都满足
        flag = False
        print("伪造签名成功")
            
        #print("迭代次数是:{}".format(diedai))
    with open('./c_file/PQCsignKAT_2544.rsp','r',encoding = 'utf-8') as f:
        for line in f:
            if 'sm =' in line:
                if flag == False:
                    #print("签名是：")
                    print(line.split('=')[1].split(' ')[1].split('\n')[0])
                    return line.split('=')[1].split(' ')[1].split('\n')[0]

'''
def verify_sign(z,h,c):
    #写入z
    with open('new_z.txt','w',encoding='utf-8') as f:
        for i in range(l):
            for j in range(256):
                if j == 255:
                    f.write(str(z[i][j]))
                else:
                    f.write('{} '.format(z[i][j]))
            f.write('\n')
    
    #写入h
    with open('new_h.txt','w',encoding='utf-8') as f:
        for i in range(k):
            for j in range(256):
                if j == 255:
                    f.write(str(h[i][j]))
                else:
                    f.write('{} '.format(h[i][j]))
            f.write('\n')
    #写入c
    with open('new_c.txt','w',encoding='utf-8') as f:
        for i in range(256):
            if i == 255:
                f.write(str(c[i]))
            else:
                f.write('{} '.format(c[i]))
        f.write('\n')
    execute_command = ["./verify_sign"]
    #subprocess.run(execute_command)
    result = subprocess.run(execute_command, capture_output=True, text=True)
    print(result)
    if '验证失败' in result.stdout:
        return False
    else:
        return True
    pass

'''
alph = ['1','2','3','4','5','6','7','8','9','a','b','c','d','e','f']

def random_get_msg(length):
    str =''
    for i in range(length):
        str += random.choice(alph)
    #print(str)
    return str

if __name__ == '__main__': 	
    #m返回是一个消息列表m，包含700条消息，pk是一个str类型
    #输入文件是包含s1秘钥的文件s1.txt和meta_data_part0.npz
    
    m, s1, pk = read_data(
        './input_s1_pk_m/meta_data_part0.npz',
        './input_s1_pk_m/s1_true.txt',
        './input_s1_pk_m/pk_16.txt'
    )
    #print(pk)
    
    
    
    
    #sm是存放签名的列表
    sm_list =[]
    s1_work = [row[:] for row in s1]
    #meta_data_part0.npz中包含len(m)条消息，对每条消息签名
    for i in range(len(m)):
        sm = forgery_sign(m[i],s1,pk)
        sm_list.append(sm)
        
    #把生成的sm写入文件夹output的new_sm.txt中
    with open('./forgery_signature_output/new_sm.txt','w',encoding='utf-8') as f:
        for sm in sm_list:
            f.write('sm = {}\n'.format(sm))