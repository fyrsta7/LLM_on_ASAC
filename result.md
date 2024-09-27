benchmark number: 136

test result description:
1. test_num_sum: test number of all problems
2. correct_num_sum: correct test number of all problems
3. pass_all_test_numpass_all_test_num: problem number in which LLM passes all tests

# 1 new ASAC

## 1.1 MiniZinc without annotation

### 1.1.1 o1-mini
loop_num = 1
"test_num_sum": 1772
"correct_num_sum": 567
"pass_all_test_num": 34

### 1.1.2 deepseek-coder
loop_num = 10
"test_num_sum": 1772
"correct_num_sum": 414
"pass_all_test_num": 24

loop_num = 1
"test_num_sum": 1772
"correct_num_sum": 342
"pass_all_test_num": 22

### 1.1.3 gpt-4o
loop_num = 1
"test_num_sum": 1772
"correct_num_sum": 268
"pass_all_test_num": 17

## 1.2 English natural language, loop_num = 1

### 1.2.1 o1-mini
"test_num_sum": 1772
"correct_num_sum": 1110
"pass_all_test_num": 76

### 1.2.2 deepseek-coder
"test_num_sum": 1772
"correct_num_sum": 755
"pass_all_test_num": 52

### 1.2.3 gpt-4o
"test_num_sum": 1772
"correct_num_sum": 677
"pass_all_test_num": 48

### 1.2.4 gpt-4o-mini
"test_num_sum": 1772
"correct_num_sum": 527
"pass_all_test_num": 33



# 2 old ASAC

## 2.1 English natural language, loop_num = 1

### 2.1.1 deepseek-coder
"test_num_sum": 1560
"correct_num_sum": 712
"pass_all_test_num": 56

### 2.1.2 gpt-4o
"test_num_sum": 1560
"correct_num_sum": 648
"pass_all_test_num": 50

### 2.1.3 gpt-4o-mini
"test_num_sum": 1560
"correct_num_sum": 488
"pass_all_test_num": 34
