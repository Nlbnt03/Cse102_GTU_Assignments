#include <stdio.h>
#include <string.h>

const char *opcodes[29] = {"ADD","ADDI","ADDM","AND","ANDI","ANDM","OR","ORI","ORM","SUB","SUBI",
"SUBM","INC","DEC","SHL","SHR","BRE","BRN","J","NOR","LDA","STR","SWP","LESS","GRT",
"PRI","PRII","PRIM","EXIT"};

const char *opcode_binaries[29] = {"00000001","00000010","00000011","00000100","00000101","00000110","00000111",
"00001000","00001001","00001010","00001011","00001100","00001101","00001110","00001111","00010000","00010001","00010010",
"00010011","00010100","00010101","00010110","00010111","00011000","00011001","00011010","00011011","00011100","00011101"};

typedef struct {
    char memoryCell[100][8];
} Memory;

typedef struct {
    char arr[8];
} Register;

typedef struct {
    char instruction[24];
} InstructionRegister;

int ft_recursive_power(int nb, int power) {
    if (power == 0)
        return 1;
    if (nb == 0 || power < 0)
        return 0;
    return nb * ft_recursive_power(nb, power - 1);
}

void decimalToBinary8(int decimal, char binary[]) {
    int i;
    for (i = 7; i >= 0; i--) {
        binary[i] = (decimal % 2) + '0';
        decimal /= 2;
    }
}

int binaryToDecimal8(char binary[]) {
    int decimal = 0;
    int i;
    for (i = 7; i >= 0; i--) {
        decimal += (binary[i] - '0') * ft_recursive_power(2, 7 - i);
    }
    return decimal;
}

char *getOpcodeBinary(char *opcode) {
    int i;
    for (i = 0; i < 29; i++) {
        if (strcmp(opcodes[i], opcode) == 0) {
            return (char *)opcode_binaries[i]; 
        }
    }
    return "Opcode not found";
}

void ADD(Register *a, Register *b) {
    int ar = binaryToDecimal8(a->arr);
    int br = binaryToDecimal8(b->arr);
    int result = ar + br;
    decimalToBinary8(result, a->arr);
}

void ADDI(Register *a, int i) {
    int ar = binaryToDecimal8(a->arr);
    int result = ar + i;
    decimalToBinary8(result, a->arr);
}

void ADDM(Register *a, int memoryAddress, Memory *memory) {
    int memoryValue = binaryToDecimal8(memory->memoryCell[memoryAddress]);
    int registerValue = binaryToDecimal8(a->arr);
    int result = memoryValue + registerValue;
    decimalToBinary8(result, a->arr);
    decimalToBinary8(result, memory->memoryCell[memoryAddress]);
}

void AND(Register *a, Register *b) {
    int result = binaryToDecimal8(a->arr) & binaryToDecimal8(b->arr);
    decimalToBinary8(result, a->arr);
}

void ANDI(Register *a, int number) {
    int ar = binaryToDecimal8(a->arr);
    int result = ar & number;
    decimalToBinary8(result, a->arr);
}

void ANDM(Register *a, int memoryAddress, Memory *memory) {
    int registerValue = binaryToDecimal8(a->arr);
    int memoryValue = binaryToDecimal8(memory->memoryCell[memoryAddress]);
    int result = registerValue & memoryValue;
    decimalToBinary8(result, a->arr);
    decimalToBinary8(result, memory->memoryCell[memoryAddress]);
}

void OR(Register *a, Register *b) {
    int aValue = binaryToDecimal8(a->arr);
    int bValue = binaryToDecimal8(b->arr);
    int result = aValue | bValue;
    decimalToBinary8(result, a->arr);
}

void ORI(Register *a, int num) {
    int aValue = binaryToDecimal8(a->arr);
    int result = aValue | num;
    decimalToBinary8(result, a->arr);
}

void ORM(Register *a, int memoryAddress, Memory *memory) {
    int aValue = binaryToDecimal8(a->arr);
    int memoryValue = binaryToDecimal8(memory->memoryCell[memoryAddress]);
    int result = aValue | memoryValue;
    decimalToBinary8(result, a->arr);
    decimalToBinary8(result, memory->memoryCell[memoryAddress]);
}

void SUB(Register *a, Register *b) {
    int aValue = binaryToDecimal8(a->arr);
    int bValue = binaryToDecimal8(b->arr);
    int result = aValue - bValue;
    decimalToBinary8(result, a->arr);
}

void SUBI(Register *a, int num) {
    int aValue = binaryToDecimal8(a->arr);
    int result = aValue - num;
    decimalToBinary8(result, a->arr);
}

void SUBM(Register *a, int memoryAddress, Memory *memory) {
    int aValue = binaryToDecimal8(a->arr);
    int memValue = binaryToDecimal8(memory->memoryCell[memoryAddress]);
    int result = aValue - memValue;
    decimalToBinary8(result, a->arr);
    decimalToBinary8(result, memory->memoryCell[memoryAddress]);
}

void INC(Register *a) {
    int value = binaryToDecimal8(a->arr);
    value++;
    decimalToBinary8(value, a->arr);
}

void DEC(Register *b) {
    int value = binaryToDecimal8(b->arr);
    value--;
    decimalToBinary8(value, b->arr);
}

void SHR(Register *a, int value) {
    int i, j;
    for (i = 0; i < value; i++) {
        for (j = 0; j < 7; j++) {
            a->arr[j] = a->arr[j + 1];
        }
        a->arr[7] = '0';
    }
}

void SHL(Register *a, int value) {
    int i, j;
    for (i = 0; i < value; i++) {
        for (j = 7; j > 0; j--) {
            a->arr[j] = a->arr[j - 1];
        }
        a->arr[0] = '0';
    }
}

void BRE(Register *a, Register *b, int *pc, int line) {
    if (binaryToDecimal8(a->arr) == binaryToDecimal8(b->arr)) {
        *pc = line - 1;
    }
}

void BRN(Register *a, Register *b, int *pc, int line) {
    if (binaryToDecimal8(a->arr) != binaryToDecimal8(b->arr)) {
        *pc = line - 1;
    }
}

void J(int *pc, int line) {
    *pc = line - 1;
}

void NOR(Register *a, Register *b) {
    int i;
    for (i = 0; i < 8; i++) {
        if (a->arr[i] == '0' && b->arr[i] == '0') {
            a->arr[i] = '1';
        } else {
            a->arr[i] = '0';
        }
    }
}

void LDA(Register *a, int i, Memory *memory) {
    if (i >= 0 && i < 100) {
        strcpy(a->arr, memory->memoryCell[i]);
    } else {
        printf("Invalid memory address: %d\n", i);
    }
}

void STR(Register *a, int memoryAddress, Memory *memory) {
    if (memoryAddress >= 0 && memoryAddress < 100) {
        strcpy(memory->memoryCell[memoryAddress], a->arr);
    } else {
        printf("Invalid memory address: %d\n", memoryAddress);
    }
}

void SWP(Register *a, Register *b) {
    char temp[8];
    strcpy(temp, a->arr);
    strcpy(a->arr, b->arr);
    strcpy(b->arr, temp);
}

void LESS(Register *a, Register *b) {
    int aValue = binaryToDecimal8(a->arr);
    int bValue = binaryToDecimal8(b->arr);
    if (aValue < bValue) {
        decimalToBinary8(1, a->arr);
    } else {
        decimalToBinary8(0, a->arr);
    }
}

void GRT(Register *a, Register *b) {
    int aValue = binaryToDecimal8(a->arr);
    int bValue = binaryToDecimal8(b->arr);
    if (aValue > bValue) {
        decimalToBinary8(1, a->arr);
    } else {
        decimalToBinary8(0, a->arr);
    }
}

void PRI(Register *a) {
    int result = binaryToDecimal8(a->arr);
    printf("%d\n", result);
}

void PRII(int value) {
    printf("%d\n", value);
}

void PRIM(int memoryAddress, Memory *memory) {
    if (memoryAddress >= 0 && memoryAddress < 100) {
        int result = binaryToDecimal8(memory->memoryCell[memoryAddress]);
        printf("%d\n", result);
    } else {
        printf("Invalid memory address: %d\n", memoryAddress);
    }
}

void fetchInstruction(char *line, InstructionRegister *ir) {
    strcpy(ir->instruction, line);
}

void decodeInstruction(InstructionRegister *ir, char *command, char *operand, int *value) {
    char dummy[10]; 
    sscanf(ir->instruction, "%s %s %d", command, operand, value);
    if (sscanf(ir->instruction, "%s %s %d", command, dummy, value) == 2) {
        *value = -1; 
    }
}

int executeInstruction(char *command, char *operand, int value, Register *a, Register *b, Memory *memory, int *pc) {
    if (strcmp(command, "ADD") == 0) {
        ADD(a, b);
    } else if (strcmp(command, "ADDI") == 0) {
        ADDI(a, value);
    } else if (strcmp(command, "ADDM") == 0) {
        ADDM(a, value, memory);
    } else if (strcmp(command, "AND") == 0) {
        AND(a, b);
    } else if (strcmp(command, "ANDI") == 0) {
        ANDI(a, value);
    } else if (strcmp(command, "ANDM") == 0) {
        ANDM(a, value, memory);
    } else if (strcmp(command, "OR") == 0) {
        OR(a, b);
    } else if (strcmp(command, "ORI") == 0) {
        ORI(a, value);
    } else if (strcmp(command, "ORM") == 0) {
        ORM(a, value, memory);
    } else if (strcmp(command, "SUB") == 0) {
        SUB(a, b);
    } else if (strcmp(command, "SUBI") == 0) {
        SUBI(a, value);
    } else if (strcmp(command, "SUBM") == 0) {
        SUBM(a, value, memory);
    } else if (strcmp(command, "INC") == 0) {
        INC(a);
    } else if (strcmp(command, "DEC") == 0) {
        DEC(b);
    } else if (strcmp(command, "SHL") == 0) {
        SHL(a, value);
    } else if (strcmp(command, "SHR") == 0) {
        SHR(a, value);
    } else if (strcmp(command, "BRE") == 0) {
        BRE(a, b, pc, value);
    } else if (strcmp(command, "BRN") == 0) {
        BRN(a, b, pc, value);
    } else if (strcmp(command, "J") == 0) {
        J(pc, value);
    } else if (strcmp(command, "NOR") == 0) {
        NOR(a, b);
    } else if (strcmp(command, "LDA") == 0) {
        LDA(a, value, memory);
    } else if (strcmp(command, "STR") == 0) {
        STR(a, value, memory);
    } else if (strcmp(command, "SWP") == 0) {
        SWP(a, b);
    } else if (strcmp(command, "LESS") == 0) {
        LESS(a, b);
    } else if (strcmp(command, "GRT") == 0) {
        GRT(a, b);
    } else if (strcmp(command, "PRI") == 0) {
        PRI(a);
    } else if (strcmp(command, "PRII") == 0) {
        PRII(value);
    } else if (strcmp(command, "PRIM") == 0) {
        PRIM(value, memory);
    } else if (strcmp(command, "EXIT") == 0) {
        printf("Program terminated.\n");
        return 1; 
    }
    return 0;
}

void createMemory(Memory *memory) {
    int i, j;
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 8; j++) {
            memory->memoryCell[i][j] = '0';
        }
    }
}

void initializeRegisters(Register *a, Register *b) {
    int i;
    for (i = 0; i < 8; i++) {
        a->arr[i] = '0';
        b->arr[i] = '0';
    }
}

int main() {
    Memory memory;
    createMemory(&memory);

    Register a, b;
    initializeRegisters(&a, &b);

    InstructionRegister ir;
    int pc = 0;
    char command[10], operand[10];
    int value;

    char filename[100];
    printf("Enter the assembly code file name (with .asm extension): ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File could not be opened.\n");
        return 1;
    }

    char line[100];
    int terminate = 0;
    while (fgets(line, sizeof(line), file) && !terminate) {
        pc++;
        fetchInstruction(line, &ir);
        decodeInstruction(&ir, command, operand, &value);
        terminate = executeInstruction(command, operand, value, &a, &b, &memory, &pc);
    }

    fclose(file);

    return 0;
}