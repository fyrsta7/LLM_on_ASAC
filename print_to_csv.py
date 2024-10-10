import json
import csv
from config import *
from cache import *

def json_to_csv(json_filename, csv_filename):
    """
    将特定格式的JSON文件转换为CSV文件

    :param json_filename: 输入的JSON文件名
    :param csv_filename: 输出的CSV文件名
    """
    cache = load_cache(json_filename)

    # 准备CSV文件的写入
    with open(csv_filename, 'w', newline='', encoding='utf-8') as csv_file:
        writer = csv.writer(csv_file)
        
        # 写入标题行
        writer.writerow(['Problem', 'Test Number', 'Correct Number'])
        
        # 遍历JSON数据并写入CSV
        # for game, values in data.items():
        #     writer.writerow([game, values['test_num'], values['correct_num']])

        for d in sorted(os.listdir(asac_path)):
            # get problem
            original_name = d
            problem_name = d.replace(" ", "_")
            problem_name = problem_name.replace("’", "")
            problem_name = problem_name.replace("'", "")

            if problem_name == ".DS_Store" or problem_name == ".gitignore" or problem_name == ".git" or problem_name == "asacdata.pkl" or problem_name == "evaluate.py" or problem_name == "README.md":
                continue

            print("problem_name:", problem_name, flush=True)

            if problem_name in cache:
                test_num = cache[problem_name]["test_num"]
                correct_num = cache[problem_name]["correct_num"]
                writer.writerow([original_name, test_num, correct_num])


input_file = root_path + "/result_backup/en_md/o1-mini.json"
output_file = root_path + "/output.csv"
json_to_csv(input_file, output_file)
