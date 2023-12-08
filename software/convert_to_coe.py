
# 读取一个二进制文件
# 将其转换为coe文件
# file_name = 'test.bin'
# coe_name = 'test.coe'
def convert_to_coe(file_name, coe_name):
    with open(file_name, 'rb') as f:
        data = f.read()

    with open(coe_name, 'w') as f:
        f.write('memory_initialization_radix=16;\n')
        f.write('memory_initialization_vector=\n')
        for i in range(len(data) // 4):
            dat = 0
            for j in range(4):
                dat = (dat >> 8) + (data[i*4+j] << 24)
            f.write('{:08x}'.format(dat))
            if i == len(data)//4-1:
                f.write(';')
            else:
                f.write(',\n')

def main():
    file_name = './picotest-simple/build/pico-la32r.bin'
    coe_name  = './picotest-simple/build/pico-la32r.coe'
    convert_to_coe(file_name, coe_name)

main()