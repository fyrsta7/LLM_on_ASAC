import os
import subprocess
import time
import threading

def create_result_folder(root_path):
    command = 'cd ' + root_path + '; mkdir -p result'
    # print(command, flush=True)
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

def create_prompt_folder(root_path):
    command = 'cd ' + root_path + '; mkdir -p prompt'
    # print(command, flush=True)
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
    with open(file_path, 'rb') as file:
        file.seek(-1, 2)
        while file.tell() > 0:
            byte = file.read(1)
            if byte == b'\n':
                break
            file.seek(-2, 1)
        last_line = file.readline().decode('utf-8').strip()
        return last_line == "```"

def remove_last_line(file_path):
    with open(file_path, 'rb+') as file:
        file.seek(-1, 2)
        while file.tell() > 0:
            byte = file.read(1)
            if byte == b'\n':
                break
            file.seek(-2, 1)
        file.truncate()


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
        process.kill()
        return "Process timed out"
    except Exception as e:
        return str(e)


def count_files_in_directory(directory_path):
    return len([f for f in os.listdir(directory_path) if os.path.isfile(os.path.join(directory_path, f))])


class TimeoutError(Exception):
    pass

def run_with_timeout(func, args=(), kwargs={}, timeout=5):
    result = [None]
    exception = [None]
    def target():
        try:
            result[0] = func(*args, **kwargs)
        except Exception as e:
            exception[0] = e
    thread = threading.Thread(target=target)
    thread.start()
    thread.join(timeout)
    if thread.is_alive():
        thread.join(0)
        raise TimeoutError("Function call timed out.")
    if exception[0] is not None:
        raise exception[0]
    return result[0]


def run_test(program, input_text):
    start_time = time.time()
    process = subprocess.Popen(
        [program],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    process.stdin.write(input_text + '\n')
    process.stdin.flush()
    stdout, stderr = process.communicate()
    return stdout, stderr