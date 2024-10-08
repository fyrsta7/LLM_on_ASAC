# LLM on ASAC

用于在 ASAC benchmark 上自动测评大模型解决算法竞赛题目的能力。
目前使用 ChatGPT 的 API。

具体流程是将 prompt 和英文题面组合作为大模型的输入，要求大模型输出一个求解该问题的 C++ 程序，然后在本地编译程序，并运行 ASAC benchmark 中包含的所有测试，最后计算大模型生成的程序能通过多少测试点。


## 项目架构

`main.py`: 用于运行的脚本

`main_multi.py`: 用于运行的脚本，区别是同一个 benchmark 可以向 LLM 反复询问并找到最优的结果

`config.py`: 运行相关变量，例如大模型的 API key 等

`util.py`: 测试中用到的函数

`cache.py`: 用于操作缓存的函数

`run_test.py`: 用于运行测试数据

`statistic.py`: 用于统计结果

`delete_mzn_annotation.py`: 用于删除 MiniZinc 文件中的注释

`delete_non_cpp_file.py`: 用于删除文件夹中除了 cpp 以外文件，主要用于删除 result 文件夹中的可执行文件

`print_to_csv.py`: 将 json 格式的测试结果输出为 csv 格式，便于后续统计和分析

`output.csv`: 输出的 csv 格式的测试结果

`ASAC_without_annotation`: 将 ASAC 中 MiniZinc 格式的输入删除了注释之后的结果

`result/`: 测试过程中大模型生成的程序，以及从程序中编译得到的可执行文件

`cache/*.json`: 测试结果的缓存

`result_backup`: 测试结果的备份

`result.md`: 测试结果的汇总


## 使用说明

### 环境配置

需要提前下载 ASAC benchmark: https://github.com/AuQWQuA/ASAC

需要安装 ChatGPT API 的库:
```
$ pip install openai
```

### 需要修改的内容

`result` 文件夹中若包含之前生成的结果，需要提前清空，避免之前测试的结果影响本次测试。

`config.py` 中必须补全的内容：
1. `*_base_url`: 大模型的 base URL
2. `*_api_key`: 大模型的 API key
3. `*_model`: 所选择的 model
4. `root_path`: 本项目所在文件夹的路径

`main.py` 中必须修改的内容：
1. `cache_path`: 存储当前实验结果的文件路径
2. 实验使用的模型对应的变量：例如目前使用 DeepSeek 的 API，在 `main.py` 中就会使用 `deepseek_base_url`, `deepseek_api_key`, `deepseek_model` 这三个变量。如果需要切换到其他大模型的 API，可以在 `main.py` 改为使用其他大模型对应的上述三个变量。

`main.py` 中可以修改的设置：
1. `compile_timeout`: 编译的时长上限，单位为秒
2. `test_timeout`: 运行测试的时长上限，单位为秒
3. `prompt`: 大模型输入中开头的 prompt。大模型输入的具体构成形式: prompt + problem description
4. `benchmark_file_name`: 大模型输入中 problem description 对应的文件名。例如在 ASAC 中可能是 `task_e.md` 或 `task_e.mzn` 等。

### 运行方式

```
$ python3 main.py
```


## 结果说明

`result` 文件夹中存放大模型生成的 C++ 程序，以及编译得到的可执行文件

每道题目测试结束后输出的数据：
1. `test_num`: 该题目包含多少个测试点
2. `correct_num`: 大模型生成的程序通过了多少个测试点

测试全部结束后输出的数据：
1. `test_num_sum`: 用于测试的题目一共包含多少个测试点
2. `correct_num_sum`: 大模型生成的程序一共通过了多少个测试点
3. `pass_all_test_num`: 大模型生成的程序中有多少能通过对应的所有测试点