from openai import OpenAI
import subprocess
import os
import sys
from config import *
from util import *

client = OpenAI(
    base_url = deepseek_base_url,
    api_key = deepseek_api_key,
)
compile_timeout = 5
test_timeout = 5
prompt = "Here is an algorithm competition problem. Please provide a correct C++ program for this problem and ensure that the program's complexity is as low as possible. Don't use the bits/stdc++.h library. The answer should include only the C++ program. Don't add explanation outside the program. Don't use markdown format."

# create result folder, used to store .cpp and executable file
file_path = os.path.abspath(__file__)
root_path = os.path.dirname(file_path)
create_result_folder(root_path)
result_folder_path = root_path + "/result/"

test_num_sum = 0
correct_num_sum = 0
pass_all_test_num = 0
for d in os.listdir(asac_path):
    if pass_all_test_num > 3:
        break

    # get problem
    original_name = d
    problem_name = d.replace(" ", "_")
    print("problem_name:", problem_name, flush=True)
    problem_folder_path = asac_path + "/" + original_name
    problem_path = problem_folder_path + "/task_e.md"
    with open(problem_path, 'r', encoding='utf-8') as file:
        content = file.read()

    # set LLM
    response = client.chat.completions.create(
        model = deepseek_model,
        messages = [
            {
                "role": "user",
                "content": prompt + content,
            }
        ],
    )

    # get program from LLM
    program = response.choices[0].message.content
    cpp_program_path = result_folder_path + problem_name + ".cpp"
    with open(cpp_program_path, 'w', encoding='utf-8') as file:
        file.write(program)

    # remove markdown format
    if check_first_line(cpp_program_path):
        remove_first_line(cpp_program_path)
    if check_last_line(cpp_program_path):
        remove_last_line(cpp_program_path)

    # compile program
    stderr = compile_program(result_folder_path, problem_name, compile_timeout)
    if stderr:
        print('Compile Error:', stderr)

    # run test
    exe_program_path = result_folder_path + problem_name
    if not os.path.isfile(exe_program_path):
        continue

    test_folder_path = problem_folder_path + "/tests/"
    input_folder_path = test_folder_path + "origin_form/"
    answer_folder_path = test_folder_path + "ans/"
    test_num = count_files_in_directory(input_folder_path)
    test_num_sum += test_num
    correct_num = 0

    for i in range(1, test_num + 1):
        print("\ntest", i, flush=True)
        test_index = i

        # get input
        input_path = input_folder_path + str(test_index) + ".in"
        with open(input_path, 'r', encoding='utf-8') as file:
            input = file.read()

        # run program and get output
        stdout, stderr = run_process_with_timeout(exe_program_path, input, test_timeout)
        if stderr:
            print('Run Error:', stderr)
            continue

        # get correct answer
        answer_path = answer_folder_path + str(test_index) + ".out"
        with open(answer_path, 'r', encoding='utf-8') as file:
            answer = file.read()
        
        # compare output with the correct answer
        stdout = stdout.rstrip('\n')
        answer = answer.rstrip('\n')
        print("output:", stdout)
        print("answer:", answer)
        if stdout == answer:
            print("true")
            correct_num += 1
        else:
            print("false")

    correct_num_sum += correct_num
    if test_num == correct_num:
        pass_all_test_num += 1
    
    print("\n")
    print("There are", test_num, "tests")
    print("It passes", correct_num, "tests")
    print("\n", flush=True)

print("In all problems, there are", test_num_sum, "tests.")
print("It passes", correct_num_sum, "tests.")
print("It passes all tests in", pass_all_test_num, "problems.", flush=True)