import os
import subprocess

def create_result_folder(root_path):
    command = 'cd ' + root_path + '; mkdir -p result; rm -r result/*'
    process = subprocess.Popen(
        ['bash', '-c', command],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    _, stderr = process.communicate()
    if stderr:
        print('mkdir Error:', stderr)

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

def compile_program(result_folder_path, problem_name, timeout):
    command = 'cd ' + result_folder_path + '; g++ -std=c++17 ' + problem_name + '.cpp' + ' -o ' + problem_name
    print(command)
    try:
        process = subprocess.Popen(
            ['bash', '-c', command],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        _, stderr = process.communicate(timeout = timeout)
        return stderr
    
    except subprocess.TimeoutExpired as e:
        # Handle the timeout situation
        process.kill()  # Kill the process if it exceeds the timeout
        # stdout, stderr = process.communicate()  # Get the output and error streams
        return "Process timed out"
    
    except Exception as e:
        # Handle any other exceptions
        return str(e)


def count_files_in_directory(directory_path):
    return len([f for f in os.listdir(directory_path) if os.path.isfile(os.path.join(directory_path, f))])


def run_process_with_timeout(program, input_text, timeout):
    try:
        process = subprocess.Popen(
            [program],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        
        # Write input to the process's stdin
        process.stdin.write(input_text + '\n')
        process.stdin.flush()
        
        # Communicate with the process and set the timeout
        stdout, stderr = process.communicate(timeout = timeout)
        
        return stdout, stderr
    
    except subprocess.TimeoutExpired as e:
        # Handle the timeout situation
        process.kill()  # Kill the process if it exceeds the timeout
        # stdout, stderr = process.communicate()  # Get the output and error streams
        return None, "Process timed out"
    
    except Exception as e:
        # Handle any other exceptions
        return None, str(e)