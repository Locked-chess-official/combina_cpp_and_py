def combina_cpp_and_py(cpp_code: str, py_code: str):
    return f"""
#if false
r'''
#endif
{cpp_code}
#if false
'''
{py_code}
#endif"""

def select_file(title):
    import tkinter as tk
    from tkinter import filedialog
    root = tk.Tk()
    root.withdraw()  # 隐藏主窗口
    file_path = filedialog.askopenfilename(title=title)
    return file_path

def read_file(file_path):
    if not file_path:  # 用户取消选择
        return None
    with open(file_path, 'r', encoding='utf-8') as f:
        return f.read()

def save_file(content):
    import tkinter as tk
    from tkinter import filedialog
    root = tk.Tk()
    root.withdraw()
    file_path = filedialog.asksaveasfilename(
        title="保存合并后的文件",
        defaultextension=".py",
        filetypes=[("Python files", "*.py"), ("All files", "*.*")]
    )
    if file_path:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(content)
        if file_path[-3:] == '.py':
            with open(file_path[:-3] + '.cpp', 'w', encoding='utf-8') as f:
                f.write(content)
            return True
    return False

def main():
    import tkinter as tk
    from tkinter import messagebox
    
    # 选择C++文件
    cpp_path = select_file("选择C++文件")
    if not cpp_path:
        return
    
    # 选择Python文件
    py_path = select_file("选择Python文件")
    if not py_path:
        return
    
    # 读取文件内容
    cpp_code = read_file(cpp_path)
    py_code = read_file(py_path)
    
    if cpp_code is None or py_code is None:
        messagebox.showerror("错误", "读取文件失败")
        return
    
    # 合并代码
    combined_code = combina_cpp_and_py(cpp_code, py_code)
    
    # 保存结果
    if save_file(combined_code):
        messagebox.showinfo("成功", "文件合并并保存成功！")
    else:
        messagebox.showwarning("取消", "保存操作已取消")

if __name__ == '__main__':
    main()
