from openai import OpenAI
import subprocess
import os
import sys
import util

client = OpenAI(
    base_url='https://api.openai-proxy.org/v1',
    api_key='sk-KMdHj9SwoI5LSCpuOfpfMDCAD0E026mGUv6CgGW0l2FH8Qji',
)

asac_path = "/Users/zhaoyuwei/Desktop/LLM_on_ASAC/ASAC/"
program_folder_path = "/Users/zhaoyuwei/Desktop/LLM_on_ASAC/program/"
prompt = "Here is an algorithm competition problem. Please provide a correct C++ program for this problem and ensure that the program's complexity is as low as possible. Don't use the bits/stdc++.h library. The answer should include only the C++ program. Don't add explanation outside the program. Don't use markdown format."

i = 0
for d in os.listdir(asac_path):
    if i > 5:
        break
    i += 1

    original_name = d
    problem_name = d.replace(" ", "_")
    print("problem_name:", problem_name)
    problem_path = asac_path + original_name + "/task_e.md"
    program_path = program_folder_path + problem_name + ".cpp"
    with open(problem_path, 'r', encoding='utf-8') as file:
        content = file.read()
    # print(content)

    response = client.chat.completions.create(
        messages=[
            {
                "role": "user",
                "content": prompt + content,
            }
        ],
        model="gpt-3.5-turbo",
    )

    # get program
    program = response.choices[0].message.content
    # print(program)
    with open(program_path, 'w', encoding='utf-8') as file:
        file.write(program)

    # remove markdown format
    if util.check_first_line(program_path):
        util.remove_first_line(program_path)
    if util.check_last_line(program_path):
        util.remove_last_line(program_path)

    # compile program
    command = 'cd ' + program_folder_path + '; g++ -std=c++17 "' + problem_name + '.cpp"' + ' -o "' + problem_name + '"'
    print(command)
    process = subprocess.Popen(
        ['bash', '-c', command],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    stdout, stderr = process.communicate()
    # print('Output:', stdout)
    if stderr:
        print('Compile Error:', stderr)
        continue

    # run test
    test_path = asac_path + original_name + "/tests/"
    input_folder_path = test_path + "origin_form/"
    answer_folder_path = test_path + "ans/"
    test_num = util.count_files_in_directory(input_folder_path)
    correct_num = 0

    for i in range(1, test_num):
        print("\ntest", i)
        test_index = i

        # get input
        input_path = input_folder_path + str(test_index) + ".in"
        with open(input_path, 'r', encoding='utf-8') as file:
            input = file.read()

        # run program and get output
        program = program_folder_path + problem_name
        process = subprocess.Popen(
            [program],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        process.stdin.write(input + '\n')
        process.stdin.flush()
        stdout, stderr = process.communicate()
        # print('Output:', stdout)
        if stderr:
            print('Run Error:', stderr)
            continue

        # get answer
        answer_path = answer_folder_path + str(test_index) + ".out"
        with open(answer_path, 'r', encoding='utf-8') as file:
            answer = file.read()
        
        # check output
        input = input.rstrip('\n')
        stdout = stdout.rstrip('\n')
        answer = answer.rstrip('\n')
        # print("input:", input)
        print("output:", stdout)
        print("answer:", answer)
        if stdout == answer:
            print("true")
            correct_num += 1
        else:
            print("false")

    print("\n")
    print("test_num:", test_num)
    print("correct_num:", correct_num)
    print("\n")
