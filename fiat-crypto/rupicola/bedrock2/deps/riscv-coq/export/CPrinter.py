from LanguagePrinter import LanguagePrinter


type_mappings = {
    'BinNums.Z': 'int',
    'Datatypes.bool': 'bool'
}


def convert_type(t):
    global type_mappings
    res = type_mappings.get(t)
    if res:
        return res
    else:
        return t


InstructionListCode = '''
typedef struct {
    Instruction inst;
    int size;
} InstructionList;

InstructionList empty_instruction_list() {
    InstructionList res = { InvalidInstruction(0), 0 };
    return res;
}

InstructionList singleton_instruction_list(Instruction i) {
    InstructionList res = { i, 1 };
    return res;
}

InstructionList concat_instruction_list(InstructionList l1, InstructionList l2) {
    if (l1.size == 0) {
        return l2;
    }
    if (l2.size == 0) {
        return l1;
    }
    InstructionList res = { InvalidInstruction(0), 2 }; // 2 means "more than 1"
    return res;
}

Instruction instruction_list_head_default(InstructionList l, Instruction deflt) {
    if (l.size == 1) {
        return l.inst;
    } else {
        return deflt;
    }
}
'''

class CPrinter(LanguagePrinter):

    def begin_extension(self, extensionName):
        self.branches = {} # constructorName -> (argNames, body string thunk)
        self.extensionName = extensionName

    def execute_case(self, casename, argnames, casebody):
        self.branches[casename] = (argnames, casebody)

    def end_extension(self):
        self.writeln('void execute{}(RiscvState s, Instruction{} inst) {{'
                   .format(self.extensionName, self.extensionName))
        self.increaseIndent()
        self.startln()
        self.write(self.stmt.match('inst', self.branches, default_branch=None, returnsVoid=True))
        self.decreaseIndent()
        self.write('\n}')
        self.end_decl()

    def __init__(self, outfile):
        super(CPrinter, self).__init__(outfile)
        self.expr = CExpressionPrinter(self)
        self.stmt = CStatementPrinter(self)
        self.comment('This C file was autogenerated from Coq')
        self.writeln('#include <stdbool.h>')
        self.writeln('#include <stdint.h>')
        self.end_decl()

    def end_decl(self):
        self.writeln('')

    def comment(self, s):
        self.writeln('// ' + s)

    def type_alias(self, name, rhsName):
        self.writeln('#define {} {}'.format(name, convert_type(rhsName)))
        self.end_decl()

    def enum(self, name, valueNames):
        self.writeln('typedef enum {' + ', '.join(valueNames) + '} ' + name + ';')
        self.end_decl()

    def __variant_struct(self, name, branches):
        '''
        name: str
        branches: list of (branchName, typesList) tuples
        '''
        self.writeln('typedef struct {')
        self.increaseIndent()
        self.writeln('{}_kind kind;'.format(name))
        # note: anonymous unions require "-std=c11"
        self.writeln('union {')
        self.increaseIndent()
        for branchName, argTypes in branches:
            self.writeln('struct {')
            self.increaseIndent()
            for i, t in enumerate(argTypes):
                self.writeln('{} f{};'.format(convert_type(t), i))
            self.decreaseIndent()
            self.writeln('} as_' + branchName + ';')
        self.decreaseIndent()
        self.writeln('};')
        self.decreaseIndent()
        self.writeln('} ' + name + ';')
        self.end_decl()

    def __variant_constructors(self, name, branches):
        '''
        Prints something like

        InstructionCSR Sfence_vma(Register f_0, Register f_1) {
            InstructionCSR res = { K_Sfence_vma, { .as_Sfence_vma = {f_0, f_1} } };
            return res;
        }

        for each constructor
        '''
        for branchName, argTypes in branches:
            params = ', '.join(['{} f_{}'.format(convert_type(t), i)
                                for i, t in enumerate(argTypes)])
            self.writeln('{} {}({}) {{'.format(name, branchName, params))
            self.increaseIndent()
            self.startln()
            self.write(name)
            self.write(' res = {K_')
            self.write(branchName)
            self.write(', { .as_')
            self.write(branchName)
            self.write(' = {')
            self.write(', '.join(['f_{}'.format(i) for i in range(len(argTypes))]))
            self.write('} } };\n')
            self.writeln('return res;')
            self.decreaseIndent()
            self.writeln('}')
            self.end_decl()

    def variant(self, name, branches):
        '''
        name: str
        branches: list of (branchName, typesList) tuples
        '''
        self.enum(name + '_kind', ['K_' + b[0] for b in branches])
        self.__variant_struct(name, branches)
        self.__variant_constructors(name, branches)
        if name == 'Instruction':
            self.writeln(InstructionListCode)

    def constant_decl(self, name, typ, rhs):
        self.writeln('#define ' + name + ' ' + rhs() + '\n')

    def fun_decl(self, name, argnamesWithTypes, returnType, body):
        self.writeln('{} {}({}) {{'.format(convert_type(returnType), name,
            ', '.join([convert_type(tp) + ' ' + argname for argname, tp in argnamesWithTypes])))
        self.increaseIndent()
        self.startln()
        self.write(body())
        self.write('\n')
        self.decreaseIndent()
        self.writeln('}')
        self.end_decl()



class CExpressionPrinter:

    def __init__(self, context):
        self.context = context

    # private helper functions:

    def __binop(self, arg1, op, arg2):
        return "{} {} {}".format(arg1(), op, arg2())

    def __raw_function_call(self, func, args):
        return '{}({})'.format(func, ', '.join(args))


    # public functions:

    def alu_op_name(self, name):
        return 'alu_' + name

    def function_call(self, func, args):
        return self.__raw_function_call(func(), [arg() for arg in args])

    def bit_literal(self, s):
        return '0b' + s # gcc extension

    def true_literal(self):
        return 'true'

    def false_literal(self):
        return 'false'

    def negate_bool(self, e):
        return '! ' + e()

    def access_type_load(self):
        return 'AccessTypeLoad'

    def access_type_store(self):
        return 'AccessTypeStore'

    def var(self, varName):
        return varName.split('.')[-1]

    def if_expr(self, cond, ifyes, ifno):
        res = '((' + cond() + ")\n"
        self.context.increaseIndent()
        res += self.context.indent + "? " + ifyes() + "\n"
        res += self.context.indent + ": " + ifno() + ')'
        self.context.decreaseIndent()
        return res

    def list(self, elems):
        if len(elems) == 0:
            return 'empty_instruction_list()';
        elif len(elems) == 1:
            return 'singleton_instruction_list(' + elems[0]() + ')';
        else:
            raise ValueError('instruction lists of size other than 0 and 1 are not supported')

    def list_length(self, arg):
        return arg() + '.size'

    def list_nth_default(self, index, l, default):
        assert(index() == '0b0')
        return self.__raw_function_call("instruction_list_head_default", [l(), default()])

    def concat(self, first_arg, second_arg):
        return self.__raw_function_call("concat_instruction_list", [first_arg(), second_arg()])

    def equality(self, first_arg, second_arg):
        return self.__binop(first_arg, '==', second_arg)

    def gt(self, first_arg, second_arg):
        return self.__binop(first_arg, '>', second_arg)

    def bigint_mul(self, first_arg, second_arg):
        return self.__binop(first_arg, '*', second_arg); # TODO

    def logical_or(self, first_arg, second_arg):
        return self.__binop(first_arg, '|', second_arg)

    def shift_left(self, first_arg, second_arg):
        return self.__binop(first_arg, '<<', second_arg)

    def boolean_and(self, first_arg, second_arg):
        return self.__binop(first_arg, '&&', second_arg)

    def boolean_or(self, first_arg, second_arg):
        return self.__binop(first_arg, '||', second_arg)

    def silent_id(self, arg):
        return arg()


class CStatementPrinter:

    def __init__(self, context):
        self.context = context

    def if_stmt(self, cond, ifyes, ifno):
        res = 'if ('
        res += cond()
        res += ') {\n'
        self.context.increaseIndent()
        res += self.context.indent
        res += ifyes()
        res += '\n'
        self.context.decreaseIndent()
        self.context.increaseIndent()
        ifno = ifno()
        self.context.decreaseIndent()
        if ifno:
            res += self.context.indent
            res += "} else {\n"
            self.context.increaseIndent()
            res += self.context.indent
            self.context.decreaseIndent()
            res += ifno
            res += '\n'
        res += self.context.indent
        res += "}"
        return res

    def let_in(self, name, typ, rhs, body):
        if name == '_':
            res = ""
        else:
            res = convert_type(typ) + ' ' + name + ' = '
        res += rhs()
        res += ';\n' + self.context.indent
        res += body()
        return res

    def nop(self):
        return 'pass'

    # match over Inductive (where constructors can take args)
    def match(self, discriminee, branches, default_branch, returnsVoid=False):
        res = 'switch ({}.kind) {{\n'.format(discriminee)
        self.context.increaseIndent()
        for constructorName, (argNames, branchBody) in branches.items():
            res += self.context.indent
            res += 'case K_{}: '.format(constructorName)
            res += '{\n'
            self.context.increaseIndent()
            for i, name in enumerate(argNames):
                res += self.context.indent
                # TODO get correct type
                res += ('int {} = {}.as_{}.f{};\n'.format(name, discriminee, constructorName, i))
            res += self.context.indent
            res += branchBody()
            res += '\n'
            if returnsVoid:
                res += self.context.indent
                res += 'break;\n'
            self.context.decreaseIndent()
            res += self.context.indent
            res += '}\n'
        if default_branch:
            res += self.context.indent
            res += 'default: {\n'
            self.context.increaseIndent()
            res += self.context.indent
            res += default_branch()
            self.context.decreaseIndent()
            res += '\n'
            res += self.context.indent
            res += '}\n'
        self.context.decreaseIndent()
        res += self.context.indent + '}'
        return res

    # match over an enum (where constructors cannot take args)
    def switch(self, discriminee, enumName, branches, default_branch):
        res = 'switch ({}) {{\n'.format(discriminee)
        self.context.increaseIndent()
        for constructorName, branchBody in branches.items():
            res += self.context.indent
            res += 'case {}:\n'.format(constructorName)
            self.context.increaseIndent()
            res += self.context.indent
            res += branchBody()
            self.context.decreaseIndent()
            res += '\n'
        if default_branch:
            res += self.context.indent
            res += 'default:\n'.format(constructorName)
            self.context.increaseIndent()
            res += self.context.indent
            res += default_branch()
            self.context.decreaseIndent()
            res += '\n'
        self.context.decreaseIndent()
        res += self.context.indent + '}'
        return res

    def return_value(self, e):
        return "return " + e + ";"