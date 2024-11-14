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
    FILE *f1, *f2, *f3, *f4;
    char label[100], opcode[100], operand[100], *e, opc[5], opr[5];
    long int SA, locctr;
    int opcode_found;

    f1 = fopen("input.txt", "r");
    f2 = fopen("optab.txt", "r");
    f3 = fopen("symtab.txt", "w");
    f4 = fopen("inter.txt", "w");

    if (!f1 || !f2 || !f3 || !f4) {
        printf("Error opening files.\n");
        return 1;
    }

    // Read the first line to initialize START address
    fscanf(f1, "%s %s %s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        SA = strtol(operand, &e, 16);
        locctr = SA;
        fprintf(f4, "%lx\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        
        // Write the START label (e.g., COPY) to symtab.txt with its address
        if (strcmp(label, "-") != 0 && strlen(label) > 0) {
            fprintf(f3, "%s\t%lx\n", label, locctr);
        }
    } else {
        locctr = 0;
    }

    // Process each line in the input file
    while (fscanf(f1, "%s %s %s", label, opcode, operand) != EOF) {
        opcode_found = 0;

        // Search for the opcode in optab.txt
        rewind(f2);  // Reset the optab file pointer for each line in input.txt
        while (fscanf(f2, "%s %s", opc, opr) != EOF) {
            if (strcmp(opcode, opc) == 0) {
                fprintf(f4, "%lx\t%s\t%s\t%s\n", locctr, label, opcode, operand);
                locctr += 3;
                opcode_found = 1;
                break;
            }
        }

        // Handle directives and symbols if opcode not found in optab
        if (!opcode_found) {
            if (strcmp(opcode, "WORD") == 0) {
                fprintf(f4, "%lx\t%s\t%s\t%s\n", locctr, label, opcode, operand);
                // Record label to symtab before incrementing locctr
                if (strcmp(label, "-") != 0 && strlen(label) > 0) {
                    fprintf(f3, "%s\t%lx\n", label, locctr); // Correct locctr for WORD
                }
                locctr += 3;  // Increment locctr by 3 for WORD
            } else if (strcmp(opcode, "BYTE") == 0) {
                fprintf(f4, "%lx\t%s\t%s\t%s\n", locctr, label, opcode, operand);
                // Record label to symtab before incrementing locctr
                if (strcmp(label, "-") != 0 && strlen(label) > 0) {
                    fprintf(f3, "%s\t%lx\n", label, locctr); // Correct locctr for BYTE
                }
                locctr += (strlen(operand) - 3);  // Adjust for BYTE size
            } else if (strcmp(opcode, "RESW") == 0) {
                fprintf(f4, "%lx\t%s\t%s\t%s\n", locctr, label, opcode, operand);
                // Record label to symtab before incrementing locctr
                if (strcmp(label, "-") != 0 && strlen(label) > 0) {
                    fprintf(f3, "%s\t%lx\n", label, locctr); // Correct locctr for RESW
                }
                locctr += (3 * strtol(operand, &e, 10)); // Increment locctr for RESW
            } else if (strcmp(opcode, "RESB") == 0) {
                fprintf(f4, "%lx\t%s\t%s\t%s\n", locctr, label, opcode, operand);
                // Record label to symtab before incrementing locctr
                if (strcmp(label, "-") != 0 && strlen(label) > 0) {
                    fprintf(f3, "%s\t%lx\n", label, locctr); // Correct locctr for RESB
                }
                locctr += strtol(operand, &e, 10); // Increment locctr for RESB
            } else if (strcmp(opcode, "END") == 0) {
                fprintf(f4, "%lx\t%s\t%s\t%s\n", locctr, label, opcode, operand);
                break;
            }
        }

        // If there's a label, write it to symtab with the current locctr
        if (strcmp(label, "-") != 0 && strlen(label) > 0 && opcode_found) {
            fprintf(f3, "%s\t%lx\n", label, locctr); // Correctly update symtab entry
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);

    return 0;
}
