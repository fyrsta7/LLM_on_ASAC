from openai import OpenAI
import subprocess
import os
import sys
from config import *
from util import *
from cache import *

client = OpenAI(
    base_url = deepseek_base_url,
    api_key = deepseek_api_key,
)
compile_timeout = 5
test_timeout = 2
# prompt = "Here is an algorithm competition problem. Please provide a correct C++ program for this problem and ensure that the program's complexity is as low as possible. Don't use the bits/stdc++.h library. The answer should include only the C++ program. Don't add explanation outside the program. Don't use markdown format."
prompt = "Here is an algorithm competition problem described in MiniZinc. Please provide a correct C++ program for this problem and ensure that the program's complexity is as low as possible. The answer should include only the C++ program. Don't add explanation outside the program. Don't use markdown format. \n\n"
benchmark_file_name = "task_e_without_annotation.mzn"

# path of problem folder, the path of problem description would be <problem_root_path/problem_name/benchmark_file_name>
problem_root_path = asac_without_annotation_path
# path of test folder, the path of test file would be <test_root_path/problem_name/tests>
test_root_path = asac_path
# path of result folder, used to store .cpp and executable file
result_folder_path = root_path + "/result/"
# create result folder 
create_result_folder(root_path)
# path of cache, used to store test result
cache_path = root_path + "/cache/deepseek-coder.json"

test_num_sum = 0
correct_num_sum = 0
pass_all_test_num = 0
cache = load_cache(cache_path)
is_cover = False
for d in os.listdir(asac_path):
    # get problem
    original_name = d
    problem_name = d.replace(" ", "_")
    problem_name = problem_name.replace("’", "")
    problem_name = problem_name.replace("'", "")

    if problem_name == ".DS_Store" or problem_name == ".gitignore" or problem_name == ".git" or problem_name == "asacdata.pkl" or problem_name == "evaluate.py" or problem_name == "README.md":
        continue

    print("problem_name:", problem_name, flush=True)

    if problem_name in cache:
        print("already have result in cache, continue\n")
        test_num = cache[problem_name]["test_num"]
        correct_num = cache[problem_name]["correct_num"]
        test_num_sum += test_num
        correct_num_sum += correct_num
        if test_num == correct_num:
            pass_all_test_num += 1
        continue

    problem_folder_path = problem_root_path + "/" + original_name
    problem_path = problem_folder_path + "/" + benchmark_file_name
    with open(problem_path, 'r', encoding='utf-8') as file:
        content = file.read()

    # get program from LLM
    cpp_program_path = result_folder_path + problem_name + ".cpp"
    if not os.path.isfile(cpp_program_path):
        # print("the content is: ", prompt + content)
        response = client.chat.completions.create(
            model = deepseek_model,
            messages = [
                {
                    "role": "user",
                    "content": prompt + content,
                }
            ],
        )
        program = response.choices[0].message.content
        with open(cpp_program_path, 'w', encoding='utf-8') as file:
            file.write(program)
    print("get program done", flush=True)

    # remove markdown format
    if check_first_line(cpp_program_path):
        remove_first_line(cpp_program_path)
    if check_last_line(cpp_program_path):
        remove_last_line(cpp_program_path)

    # compile program
    exe_program_path = result_folder_path + problem_name
    if not os.path.isfile(exe_program_path):
        stderr = compile_program(result_folder_path, problem_name, compile_timeout)
        if stderr:
            print('Compile Error:', stderr)
    print("compile done", flush=True)
    
    # run test
    test_folder_path = test_root_path + "/" + original_name + "/tests/"
    input_folder_path = test_folder_path + "origin_form/"
    answer_folder_path = test_folder_path + "ans/"
    test_num = count_files_in_directory(input_folder_path)
    correct_num = 0

    # if there is no executable file, continue
    if not os.path.isfile(exe_program_path):
        test_num_sum += test_num
        correct_num_sum += correct_num
        if test_num == correct_num:
            pass_all_test_num += 1
        cache[problem_name] = {"test_num": test_num, "correct_num": correct_num, "error": "no exe"}
        save_cache(cache_path, cache, is_cover)
        is_cover = True
        print("\n", flush=True)
        continue

    for i in range(1, test_num + 1):
        print("\ntest", i, flush=True)
        test_index = i

        # get input
        input_path = input_folder_path + str(test_index) + ".in"
        with open(input_path, 'r', encoding='utf-8') as file:
            input = file.read()

        # run program and get output
        result = ""
        try:
            result = run_with_timeout(run_test, args=(exe_program_path, input,), timeout=5)
            # print("Function result:", result)
        except TimeoutError as e:
            print("Run Error: timed out")
            print("false")
            continue
        except Exception as e:
            print("Run Error:", str(e))
            print("false")
            continue

        # get correct answer
        answer_path = answer_folder_path + str(test_index) + ".out"
        with open(answer_path, 'r', encoding='utf-8') as file:
            answer = file.read()
        
        # compare output with the correct answer
        output = result[0].rstrip('\n')
        answer = answer.rstrip('\n')
        # print("output:", output)
        # print("answer:", answer)
        if output == answer:
            print("true")
            correct_num += 1
        else:
            print("false")

    test_num_sum += test_num
    correct_num_sum += correct_num
    if test_num == correct_num:
        pass_all_test_num += 1

    print("\n")
    print("There are", test_num, "tests.")
    print("It passed", correct_num, "tests.")
    print("\n", flush=True)

    cache[problem_name] = {"test_num": test_num, "correct_num": correct_num}
    save_cache(cache_path, cache, is_cover)
    if not is_cover:
        is_cover = True

print("In all problems, there are", test_num_sum, "tests.")
print("It passed", correct_num_sum, "tests.")
print("It passed all tests in", pass_all_test_num, "problems.", flush=True)

cache["test_num_sum"] = test_num_sum
cache["correct_num_sum"] = correct_num_sum
cache["pass_all_test_num"] = pass_all_test_num
save_cache(cache_path, cache, is_cover)

