
/* ### Short Algorithm for Pass-One Assembler
1. **Initialize and Open Files**.
2. **Handle START**:
   - If the first line has `START`, set `locctr` to the starting address; otherwise, set `locctr` to 0.
3. **Process Lines**:
   - Read each line, write it to `inter.txt` with `locctr`.
   - If a label exists, add it to `symtab.txt`.
   - Check `opcode` in `optab`:
     - If found, increment `locctr` by 3.
     - Handle directives: `WORD` (3 bytes), `RESW` (3 × operand), `RESB` (operand bytes), `BYTE` (size based on operand).
4. **Handle END and Close Files**.
5. **Output Completion Message**. */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *input, *optab, *symtab, *inter;
    char label[20], opcode[20], operand[20], opc[20], opr[20];
    long int locctr, startAddress;
    int opcodeFound;
    int endEncountered = 0;

    // Open files
    input = fopen("input.txt", "r");
    optab = fopen("optab.txt", "r");
    symtab = fopen("symtab.txt", "w");
    inter = fopen("inter.txt", "w");

    if (!input || !optab || !symtab || !inter) {
        printf("Error opening files.\n");
        return 1;
    }

    // Read first line to check for START directive
    fscanf(input, "%s %s %s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        startAddress = strtol(operand, NULL, 16);
        locctr = startAddress;
        fprintf(inter, "%04lX\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    } else {
        locctr = 0;
        rewind(input);
    }

    // Process subsequent lines
    while (fscanf(input, "%s %s %s", label, opcode, operand) != EOF) {
        opcodeFound = 0;

        // If END is encountered, write to intermediate and mark flag
        if (strcmp(opcode, "END") == 0) {
            fprintf(inter, "%04lX\t%s\t%s\t%s\n", locctr, label, opcode, operand);
            endEncountered = 1;
            continue;  // Do not break, continue processing data after END
        }

        // Write the current line to the intermediate file
        fprintf(inter, "%04lX\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        // If there is a label, add it to the symbol table
        if (strcmp(label, "-") != 0 && strlen(label) > 0) {
            fprintf(symtab, "%s\t%04lX\n", label, locctr);
        }

        // Check if the opcode is in the operation code table (OPTAB)
        rewind(optab);
        while (fscanf(optab, "%s %s", opc, opr) != EOF) {
            if (strcmp(opcode, opc) == 0) {
                opcodeFound = 1;
                break;
            }
        }

        // Update LOCCTR based on instruction size or directive
        if (opcodeFound) {
            locctr += 3;  // Instruction size for standard instructions
        } else if (strcmp(opcode, "WORD") == 0) {
            locctr += 3;
        } else if (strcmp(opcode, "RESW") == 0) {
            locctr += 3 * strtol(operand, NULL, 10);
        } else if (strcmp(opcode, "RESB") == 0) {
            locctr += strtol(operand, NULL, 10);
        } else if (strcmp(opcode, "BYTE") == 0) {
            if (operand[0] == 'C') {
                locctr += strlen(operand) - 3;  // Length of characters between quotes
            } else if (operand[0] == 'X') {
                locctr += (strlen(operand) - 3) / 2;  // Hex characters
            }
        }
    }

    // Close files
    fclose(input);
    fclose(optab);
    fclose(symtab);
    fclose(inter);

    printf("Pass 1 completed. Intermediate file and symbol table generated.\n");
    return 0;
}
