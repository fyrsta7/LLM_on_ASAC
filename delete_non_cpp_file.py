import os
from tqdm import tqdm

def delete_non_cpp_files(directory):
    for filename in tqdm(os.listdir(directory)):
        file_path = os.path.join(directory, filename)
        
        if os.path.isfile(file_path) and not filename.endswith('.cpp'):
            try:
                os.remove(file_path)
                print(f'Deleted: {file_path}')
            except Exception as e:
                print(f'Error deleting {file_path}: {e}')

directory_path = "/Users/zhaoyuwei/Desktop/ky/LLM_on_OI/LLM_on_ASAC/result_backup/en_without_annotation_mzn/deepseek-coder_loop10"
delete_non_cpp_files(directory_path)
