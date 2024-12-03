from openai import OpenAI
import subprocess
import os
import sys
from config import *
from util import *
from cache import *

client = OpenAI(
    base_url = chatgpt_base_url,
    api_key = chatgpt_api_key,
)
compile_timeout = 5
test_timeout = 2
prompt = "Here is an algorithm competition problem. Please provide a correct C++ program for this problem and ensure that the program's complexity is as low as possible. Don't use the bits/stdc++.h library. The answer should include only the C++ program. Don't add explanation outside the program. Don't use markdown format. \n\n"
# prompt = "Here is an algorithm competition problem described in MiniZinc. Please provide a correct C++ program for this problem and ensure that the program's complexity is as low as possible. The answer should include only the C++ program. Don't add explanation outside the program. Don't use markdown format. \n\n"
benchmark_file_name = "task_e.md"

# path of problem folder, the path of problem description would be <problem_root_path/problem_name/benchmark_file_name>
problem_root_path = asac_path
# path of result folder, used to store .cpp and executable file
result_folder_path = root_path + "/result/"
# path of prompt folder, used to store prompt file
prompt_folder_path = root_path + "/prompt/"
# create result folder 
create_prompt_folder(root_path)


for d in os.listdir(asac_path):
    # get problem
    original_name = d
    problem_name = d.replace(" ", "_")
    problem_name = problem_name.replace("’", "")
    problem_name = problem_name.replace("'", "")

    if problem_name == ".DS_Store" or problem_name == ".gitignore" or problem_name == ".git" or problem_name == "asacdata.pkl" or problem_name == "evaluate.py" or problem_name == "README.md":
        continue

    print("problem_name:", problem_name, flush=True)

    problem_folder_path = problem_root_path + "/" + original_name
    problem_path = problem_folder_path + "/" + benchmark_file_name
    with open(problem_path, 'r', encoding='utf-8') as file:
        content = file.read()

    # get program from LLM
    cpp_program_path = result_folder_path + problem_name + ".cpp"

    # print prompt to dile
    if not os.path.isfile(cpp_program_path):
        prompt_file_path = prompt_folder_path + problem_name + ".txt"
        print("the prompt is: \n", prompt + content, flush=True)
        with open(prompt_file_path, "w") as file:
            file.write(prompt + content)
        print(f"The prompt has been written to {prompt_file_path}")
        # break