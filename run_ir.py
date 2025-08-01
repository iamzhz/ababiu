# author of 'run_ir.py': DeepSeek-R1
# ./ababiu_ir test.abb | python run_ir.py

import sys
import re

def get_input():
    with open('/dev/tty', 'r') as tty:
        return tty.readline().strip()
class IRInterpreter:
    def __init__(self):
        self.stack = []          # 用于存储操作数栈
        self.variables = {}       # 存储变量名和值的映射
        self.instructions = {}   # 存储解析后的指令：行号 -> (操作码, 操作数)
        self.next_operand = {}   # 临时存储需要操作数的指令行号

    def parse_immediate(self, operand_str):
        """解析立即数：尝试转换为整数，失败则作为字符串返回"""
        try:
            return int(operand_str)
        except ValueError:
            return operand_str

    def parse_instructions(self, source):
        """解析IR源代码，构建指令字典"""
        lines = source.split('\n')
        pending_operand = None  # 存储当前需要操作数的指令行号
        
        for line in lines:
            # 跳过空行和纯空白行
            if re.match(r'^\s*$', line):
                continue
                
            # 检查是否是指令行（格式为：数字:操作码）
            instruction_match = re.match(r'^\s*(\d+):(\w+)\s*$', line)
            if instruction_match:
                if pending_operand is not None:
                    raise SyntaxError(f"指令 {pending_operand} 缺少操作数")
                
                line_num = int(instruction_match.group(1))
                opcode = instruction_match.group(2)
                
                # 需要操作数的指令列表
                if opcode in ['push_iv', 'push_imm', 'pop_iv', 'pop_imm', 'mov_iv_iv', 
                             'mov_iv_imm', 'call_if', 'jump_imm', 'jumpIfNot_imm', 'jumpIf_imm']:
                    pending_operand = line_num
                    self.next_operand[line_num] = opcode
                else:
                    self.instructions[line_num] = (opcode, None)
            elif pending_operand is not None:
                # 当前行是指令的操作数
                opcode = self.next_operand[pending_operand]
                self.instructions[pending_operand] = (opcode, line.strip())
                pending_operand = None
            else:
                raise SyntaxError(f"无效行: {line}")
                
        if pending_operand is not None:
            raise SyntaxError(f"指令 {pending_operand} 缺少操作数")

    def execute(self):
        """执行解析后的IR指令"""
        if not self.instructions:
            return
            
        # 获取最小和最大行号用于跳转边界检查
        min_line = min(self.instructions.keys())
        max_line = max(self.instructions.keys())
        pc = min_line  # 程序计数器从最小行号开始
        
        while min_line <= pc <= max_line and pc in self.instructions:
            op, arg = self.instructions[pc]
            next_pc = pc + 1  # 默认下一条指令
            
            try:
                # 处理变量压栈
                if op == 'push_iv':
                    var_name = arg
                    self.stack.append(self.variables.get(var_name, 0))
                
                # 处理立即数压栈
                elif op == 'push_imm':
                    imm_val = self.parse_immediate(arg)
                    self.stack.append(imm_val)
                
                # 处理弹出栈顶到变量
                elif op == 'pop_iv':
                    if not self.stack:
                        raise RuntimeError("栈为空")
                    self.variables[arg] = self.stack.pop()
                
                # 处理弹出栈顶（丢弃）
                elif op == 'pop_imm':
                    if self.stack:
                        self.stack.pop()
                
                # 处理二元算术运算
                elif op in ['add', 'sub', 'mul', 'div', 'power']:
                    if len(self.stack) < 2:
                        raise RuntimeError("栈元素不足")
                    b = self.stack.pop()
                    a = self.stack.pop()
                    
                    if op == 'add': result = a + b
                    elif op == 'sub': result = a - b
                    elif op == 'mul': result = a * b
                    elif op == 'div': result = a / b
                    elif op == 'power': result = a ** b
                    
                    self.stack.append(result)
                
                # 处理比较运算
                elif op in ['equal', 'notEqual', 'bigger', 'biggerEqual', 'smaller', 'smallerEqual']:
                    if len(self.stack) < 2:
                        raise RuntimeError("栈元素不足")
                    b = self.stack.pop()
                    a = self.stack.pop()
                    
                    if op == 'equal': result = a == b
                    elif op == 'notEqual': result = a != b
                    elif op == 'bigger': result = a > b
                    elif op == 'biggerEqual': result = a >= b
                    elif op == 'smaller': result = a < b
                    elif op == 'smallerEqual': result = a <= b
                    
                    self.stack.append(result)
                
                # 处理函数调用（目前仅支持print）
                elif op == 'call_if':
                    if arg == 'print' and self.stack:
                        print(self.stack.pop())
                    if arg == 'input':
                        self.stack.append(get_input())
                    if arg == 'inte' and self.stack:
                        self.stack.append(int(self.stack.pop()))
                
                # 处理无条件跳转
                elif op == 'jump_imm':
                    target = int(arg)
                    next_pc = target
                    if not (min_line <= target <= max_line):
                        return  # 跳出循环，程序结束
                
                # 处理条件跳转（栈顶为False时跳转）
                elif op == 'jumpIfNot_imm':
                    if not self.stack or not self.stack.pop():
                        target = int(arg)
                        next_pc = target
                        if not (min_line <= target <= max_line):
                            return
                
                # 处理条件跳转（栈顶为True时跳转）
                elif op == 'jumpIf_imm':
                    if self.stack and self.stack.pop():
                        target = int(arg)
                        next_pc = target
                        if not (min_line <= target <= max_line):
                            return
                elif op == 'callParaBegin':
                    pass
                
                # 未实现的指令
                elif op in ['mov_iv_iv', 'mov_iv_imm']:
                    raise NotImplementedError(f"指令 {op} 尚未实现")
                
                # 未知指令
                else:
                    raise ValueError(f"未知操作码: {op}")
                    
            except Exception as e:
                print(f"执行错误 (行 {pc}): {str(e)}")
                return
                
            pc = next_pc

def main():
    interpreter = IRInterpreter()
    
    try:
        # 从标准输入读取IR代码
        source = sys.stdin.read()
        if not source:
            print("错误：未提供输入代码")
            return
        
        # 解析并执行代码
        interpreter.parse_instructions(source)
        interpreter.execute()
    
    except Exception as e:
        print(f"错误: {str(e)}")

if __name__ == "__main__":
    main()