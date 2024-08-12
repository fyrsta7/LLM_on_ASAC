# LLM on ASAC

用于在 ASAC benchmark 上自动测评大模型解决算法竞赛题目的能力。
目前使用 ChatGPT 的 API。

具体流程是将 prompt 和英文题面组合作为大模型的输入，要求大模型输出一个求解该问题的 C++ 程序，然后在本地编译程序，并运行 ASAC benchmark 中包含的所有测试，最后计算大模型生成的程序能通过多少测试点。

## 使用说明

需要提前下载 ASAC benchmark: https://github.com/AuQWQuA/ASAC

运行前需要在 `config.py` 中补全的内容：
1. *_base_url: LLM 的 base URL
2. *_api key: LLM 的 API key
3. *_model: 所选择的 model
4. asac_path: ASAC benchmark 文件夹的路径

`main.py`可以修改的设置：
1. compile_timeout: 编译的时长上限，单位为秒
2. test_timeout: 运行测试的时长上限，单位为秒
3. prompt: LLM 输入中开头的 prompt。LLM 输入的具体构成形式: prompt + problem description

运行前 `result` 文件夹中若包含之前生成的结果，需要提前清空。

运行方式：`python3 main.py`

## 结果说明

`result` 文件夹中存放 LLM 生成的 C++ 程序，以及编译得到的可执行文件

每道题目测试结束后输出的数据：
1. test_num: 该题目包含多少个测试点
2. correct_num: LLM 生成的程序通过了多少个测试点

测试全部结束后输出的数据：
1. test_num_sum: 用于测试的题目一共包含多少个测试点
2. correct_num_sum: LLM 生成的程序一共通过了多少个测试点
3. pass_all_test_num: LLM 生成的程序中有多少能通过对应的所有测试点