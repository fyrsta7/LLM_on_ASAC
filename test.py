import sys

# 打开文件用于写入
with open('output.txt', 'w') as file:
    # 保存原始 stdout
    original_stdout = sys.stdout
    # 重定向 stdout 到文件
    sys.stdout = file
    
    try:
        print("这行会被写入到文件中")
    finally:
        # 恢复原始 stdout
        sys.stdout = original_stdout

print("这行会在控制台中显示")
