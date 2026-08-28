一、实验环境说明：
Python 3.8.0
Linux Ubuntu 20.04.6
OpenSSL 1.1.1f

二所需安装库函数以及版本信息
numpy-------------1.24.4

三、用法:
1、文件夹input_s1_pk_m存放输入文件，文件夹中包含meta_data_part{序号}.npz、s1_true.txt和pk_16.txt 三个文件作为输入文件，从中去拿msg,pk和s1.
   可以通过修改forgery_signature.py文件中的main函数的read_data()函数的参数来修改输入的msg，pk，s1
   读取函数read_data()，返回一个msg列表，pk是字符串，s1是二维列表
   forgery_sign()函数中需要传入一个字符串形式的消息、二维列表形式的s1、字符串形式的pk,输出结果是一个字符串形式的伪造签名。
   输出结果存放在forgery_signature_output文件夹下，该文件夹下的new_sm.txt包含了对多条消息执行签名后的伪造签名
2、运行方法：
   修改正确forgery_signature.py文件中的main函数的文件路径后
   在安装完依赖的模块后，在命令行运行python3  forgery_signature.py即可在forgery_signature_output文件夹下得到输出结果