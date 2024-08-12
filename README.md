# LLM on ASAC

用于在 ASAC benchmark 上自动测评大模型解决算法竞赛题目的能力。
目前使用 ChatGPT 的 API。

具体流程是将 prompt 和英文题面组合作为大模型的输入，要求大模型输出一个求解该问题的 C++ 程序，然后在本地编译程序，并运行 ASAC benchmark 中包含的所有测试，最后计算大模型生成的程序能通过多少测试点。


## 项目架构

`main.py`: 用于运行的脚本

`config.py`: 运行相关变量，例如大模型的 API key 等

`util.py`: 用到的一些基本函数

`result/`: 测试过程中大模型生成的程序，以及从程序中编译得到的可执行文件


## 使用说明

需要提前下载 ASAC benchmark: https://github.com/AuQWQuA/ASAC

`result` 文件夹中若包含之前生成的结果，需要提前清空，避免之前测试的结果影响本次测试。

运行前需要在 `config.py` 中补全的内容：
1. `*_base_url`: 大模型的 base URL
2. `*_api_key`: 大模型的 API key
3. `*_model`: 所选择的 model
4. `asac_path`: ASAC benchmark 文件夹的路径

例如目前使用 DeepSeek 的 API，在 `main.py` 中就会使用 `deepseek_base_url`, `deepseek_api_key`, `deepseek_model` 这三个变量。如果需要切换到其他大模型的 API，可以在 `main.py` 改为使用其他大模型对应的上述三个变量。

`main.py` 中可以修改的设置：
1. `compile_timeout`: 编译的时长上限，单位为秒
2. `test_timeout`: 运行测试的时长上限，单位为秒
3. `prompt`: 大模型输入中开头的 prompt。大模型输入的具体构成形式: prompt + problem description

运行方式：
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