# LLM on ASAC

用于在 ASAC benchmark 上自动测评大模型解决算法竞赛题目的能力。
目前使用 ChatGPT 的 API。

## 使用说明

需要提前下载 ASAC benchmark: https://github.com/AuQWQuA/ASAC

运行前需要在 `config.py` 中补全的内容：
1. chatgpt_base_url: ChatGPT 的 base URL
2. chatgpt_api key: ChatGPT 的 API key
3. chatgpt_model: 所选择的 model
4. asac_path: ASAC benchmark 文件夹的路径

`main.py`可以修改的设置：
1. compile_timeout: 编译的时长上限，单位为秒
2. test_timeout: 运行测试的时长上限，单位为秒
3. prompt: LLM 输入中开头的 prompt。LLM 输入的具体构成形式: prompt + problem description

目前统计的数据：
1. test_num_sum: 用于测试的题目一共包含多少个测试点
2. correct_num_sum: LLM 生成的程序一共通过了多少个测试点
3. pass_all_test_num: LLM 生成的程序中有多少能通过对应的所有测试点