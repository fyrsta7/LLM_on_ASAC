from openai import OpenAI
from tqdm import tqdm
import subprocess
import os
import sys
from config import *
from util import *
from cache import *



def run_deepseek():
    compile_timeout = 5
    test_timeout = 2

    # create result folder, used to store .cpp and executable file
    file_path = os.path.abspath(__file__)
    root_path = os.path.dirname(file_path)
    result_folder_path = root_path + "/result_backup/en_md/deepseek-coder/"
    cache_path = root_path + "/cache/deepseek-coder.json"

    test_num_sum = 0
    correct_num_sum = 0
    pass_all_test_num = 0
    cache = load_cache(cache_path)
    is_cover = False
    # for d in os.listdir(asac_path):
    for d in tqdm(os.listdir(asac_path)):
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

        problem_folder_path = asac_path + "/" + original_name
        problem_path = problem_folder_path + "/task_e.md"
        with open(problem_path, 'r', encoding='utf-8') as file:
            content = file.read()

        # get program from LLM
        cpp_program_path = result_folder_path + problem_name + ".cpp"
        if not os.path.isfile(cpp_program_path):
            print("no program!", cpp_program_path)
            continue
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
        test_folder_path = problem_folder_path + "/tests/"
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




def run_4o():
    compile_timeout = 5
    test_timeout = 2

    # create result folder, used to store .cpp and executable file
    file_path = os.path.abspath(__file__)
    root_path = os.path.dirname(file_path)
    result_folder_path = root_path + "/result_backup/gpt-4o/"
    cache_path = root_path + "/cache/gpt-4o.json"

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

        problem_folder_path = asac_path + "/" + original_name
        problem_path = problem_folder_path + "/task_e.md"
        with open(problem_path, 'r', encoding='utf-8') as file:
            content = file.read()

        # get program from LLM
        cpp_program_path = result_folder_path + problem_name + ".cpp"
        if not os.path.isfile(cpp_program_path):
            print("no program!")
            continue
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
        test_folder_path = problem_folder_path + "/tests/"
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





def run_4o_mini():
    compile_timeout = 5
    test_timeout = 2

    # create result folder, used to store .cpp and executable file
    file_path = os.path.abspath(__file__)
    root_path = os.path.dirname(file_path)
    result_folder_path = root_path + "/result_backup/gpt-4o-mini/"
    cache_path = root_path + "/cache/gpt-4o-mini.json"

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

        problem_folder_path = asac_path + "/" + original_name
        problem_path = problem_folder_path + "/task_e.md"
        with open(problem_path, 'r', encoding='utf-8') as file:
            content = file.read()

        # get program from LLM
        cpp_program_path = result_folder_path + problem_name + ".cpp"
        if not os.path.isfile(cpp_program_path):
            print("no program!")
            continue
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
        test_folder_path = problem_folder_path + "/tests/"
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




def run_o1_mini():
    compile_timeout = 5
    test_timeout = 2

    # create result folder, used to store .cpp and executable file
    file_path = os.path.abspath(__file__)
    root_path = os.path.dirname(file_path)
    result_folder_path = root_path + "/result/"
    cache_path = root_path + "/cache/o1-mini.json"

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

        problem_folder_path = asac_path + "/" + original_name
        problem_path = problem_folder_path + "/task_e.md"
        with open(problem_path, 'r', encoding='utf-8') as file:
            content = file.read()

        # get program from LLM
        cpp_program_path = result_folder_path + problem_name + ".cpp"
        if not os.path.isfile(cpp_program_path):
            print("no program!")
            continue
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
        test_folder_path = problem_folder_path + "/tests/"
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




# run_deepseek()
# run_4o()
# run_4o_mini()
run_o1_mini()