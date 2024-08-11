import os

def check_first_line(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        first_line = file.readline().strip()
        return first_line == "```cpp"

def remove_first_line(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        lines = file.readlines()
    with open(file_path, 'w', encoding='utf-8') as file:
        file.writelines(lines[1:])

def check_last_line(file_path):
    with open(file_path, 'rb') as file:  # 以二进制模式打开，以处理可能的文件编码问题
        file.seek(-1, 2)  # 移动到文件末尾的倒数第一个字节
        while file.tell() > 0:  # 确保文件不是空的
            byte = file.read(1)
            if byte == b'\n':  # 找到最后一行的开始
                break
            file.seek(-2, 1)  # 移动到倒数第二个字节
        last_line = file.readline().decode('utf-8').strip()  # 读取最后一行并解码
        return last_line == "```"

def remove_last_line(file_path):
    with open(file_path, 'rb+') as file:  # 以二进制读写模式打开
        file.seek(-1, 2)  # 移动到文件末尾的最后一个字节
        while file.tell() > 0:  # 确保文件不是空的
            byte = file.read(1)
            if byte == b'\n':  # 找到最后一行的开始
                break
            file.seek(-2, 1)  # 移动到倒数第二个字节
        file.truncate()  # 删除最后一行
        # 注意：truncate() 将文件截断到当前位置，即文件指针的位置

def count_files_in_directory(directory_path):
    return len([f for f in os.listdir(directory_path) if os.path.isfile(os.path.join(directory_path, f))])