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
    # Read s1 from the second data package.
    s1 = get_s1(s1_file)

    # Read the messages from the original metadata file.
    profiling_data = np.load(filename, allow_pickle=True)
    msg = profiling_data["msg"]

    # Read the public key from pk_16.txt in the second data package.
    with open(pk_file, "r", encoding="ascii") as f:
        pk = "".join(f.read().split()).lower()

    if len(pk) != 2624:
        raise ValueError(
            f"Invalid public-key length: got {len(pk)} hexadecimal characters; expected 2624"
        )

    if any(c not in "0123456789abcdef" for c in pk):
        raise ValueError("pk_16.txt contains non-hexadecimal characters")

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
        #print("File exists")
        pass
    else:
        #print("File does not exist")
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
        print("Iteration {}".format(diedai))
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
        # if 'Verification failed' in result.stdout:
        #     flag = True
        #     #print('verify signature failure')
        # else:
        #     flag = False
        #     #print('verify signature success!')

        z = get_z()
        
        # Check whether the C program passes crypto_sign_open() verification.
        verify_ok = (
            result.returncode == 0
            and "Verification failed" not in result.stdout
        )

        # Print the verification output from the C program.
        print(result.stdout, end="")
        print(result.stderr, end="")

        # Rejection conditions.
        rejected_by_norm = max_z(z, gamma1 - beta)
        rejected_by_hint = number_one > omega

        if rejected_by_norm or rejected_by_hint or not verify_ok:
            flag = True
            print(
                "Current candidate rejected: "
                f"norm={rejected_by_norm}, "
                f"hint={rejected_by_hint}, "
                f"verify={verify_ok}"
            )
            continue

        # All three conditions are satisfied.
        flag = False
        print("Signature forgery succeeded")
            
        #print("Number of iterations: {}".format(diedai))
    with open('./c_file/PQCsignKAT_2544.rsp','r',encoding = 'utf-8') as f:
        for line in f:
            if 'sm =' in line:
                if flag == False:
                    #print("Signature:")
                    print(line.split('=')[1].split(' ')[1].split('\n')[0])
                    return line.split('=')[1].split(' ')[1].split('\n')[0]

'''
def verify_sign(z,h,c):
    # Write z.
    with open('new_z.txt','w',encoding='utf-8') as f:
        for i in range(l):
            for j in range(256):
                if j == 255:
                    f.write(str(z[i][j]))
                else:
                    f.write('{} '.format(z[i][j]))
            f.write('\n')
    
    # Write h.
    with open('new_h.txt','w',encoding='utf-8') as f:
        for i in range(k):
            for j in range(256):
                if j == 255:
                    f.write(str(h[i][j]))
                else:
                    f.write('{} '.format(h[i][j]))
            f.write('\n')
    # Write c.
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
    if 'Verification failed' in result.stdout:
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
    # m is a list of 700 messages, and pk is a string.
    # The input files are s1.txt, which contains s1, and meta_data_part0.npz.
    
    m, s1, pk = read_data(
        './input_s1_pk_m/meta_data_part0.npz',
        './input_s1_pk_m/s1_true.txt',
        './input_s1_pk_m/pk_16.txt'
    )
    #print(pk)
    
    
    
    
    # Store the signatures in sm_list.
    sm_list =[]
    s1_work = [row[:] for row in s1]
    # Sign each of the len(m) messages in meta_data_part0.npz.
    for i in range(len(m)):
        sm = forgery_sign(m[i],s1,pk)
        sm_list.append(sm)
        
    # Write the generated signed messages to forgery_signature_output/new_sm.txt.
    with open('./forgery_signature_output/new_sm.txt','w',encoding='utf-8') as f:
        for sm in sm_list:
            f.write('sm = {}\n'.format(sm))
