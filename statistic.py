import os
from config import *
from util import *
from cache import *

cache_path = "/Users/zhaoyuwei/Desktop/LLM_on_ASAC/cache/deepseek-coder.json"
cache = load_cache(cache_path)
test_num_sum = 0
correct_num_sum = 0
pass_all_test_num = 0

for d in os.listdir(asac_path):
    problem_name = d.replace(" ", "_")
    if problem_name == ".DS_Store" or problem_name == ".gitignore" or problem_name == "asacdata.pkl" or problem_name == "evaluate.py" or problem_name == "README.md":
        continue

    if problem_name in cache:
        test_num = cache[problem_name]["test_num"]
        correct_num = cache[problem_name]["correct_num"]
        test_num_sum += test_num
        correct_num_sum += correct_num
        if test_num == correct_num:
            pass_all_test_num += 1

print(test_num_sum)
print(correct_num_sum)
print(pass_all_test_num)