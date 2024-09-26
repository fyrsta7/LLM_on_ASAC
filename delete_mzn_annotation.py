import os
from config import *

def remove_comments(input_file, output_file):
    with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
        for line in infile:
            comment_index = line.find('%')
            if comment_index != -1:
                line = line[:comment_index]
            line = line.rstrip()
            if line:
                outfile.write(line + '\n')

for problem_name in os.listdir(asac_path):
    if problem_name == ".DS_Store" or problem_name == ".gitignore" or problem_name == ".git" or problem_name == "asacdata.pkl" or problem_name == "evaluate.py" or problem_name == "README.md":
        continue

    input_file_path = asac_path + "/" + problem_name + "/" + "task_e.mzn"
    output_file_path = asac_path + "/" + problem_name + "/" + "task_e_without_annotation.mzn"
    remove_comments(input_file_path, output_file_path)

