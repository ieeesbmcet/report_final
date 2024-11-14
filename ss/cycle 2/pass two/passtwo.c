/*Here’s an even shorter algorithm for your pass-two assembler program:

### Short Algorithm for Pass-Two Assembler
1. **Open Files**: Open `optab.txt`, `symtab.txt`, `inter.txt`, and `objpgm.txt`.
2. **Process Lines in `inter.txt`**:
   - If `START`, write header record.
   - For other opcodes, fetch opcode and symbol addresses to form object code.
   - If `WORD`, add operand directly to object code.
3. **Write Text Record**: Print and write text record header with object codes.
4. **Output Object Codes**: Print and write object codes to `objpgm.txt`.
5. **Write End Record**: Print and write end record with starting address.
6. **Close Files**.*/

#include <stdio.h>
#include <stdlib.h> // For system() function
#include <string.h>

void main() {
    FILE *fpobj, *fpop, *fpsym, *fpinter;
    int i = 0, j = 0, n, flag, k;
    long sa, loc;
    char l[5], opc[5], opr[10], *e, address[6], startingadd[6];
    char opname[5], opv[5], length[7] = "00101D", objcode[20][10], symbol[6], stadd[5];

    system("clear"); // Clear console for Linux

    fpop = fopen("optab.txt", "r");
    fpsym = fopen("symtab.txt", "r");
    fpinter = fopen("inter.txt", "r");
    fpobj = fopen("objpgm.txt", "w"); // Open the output file

    // Reading intermediate file
    while (!feof(fpinter)) {
        fscanf(fpinter, "%s%s%s%s", address, l, opc, opr);

        // Writing header record
        if (strcmp(opc, "START") == 0) {
            printf("H^%s  ^00%s^%s\n", l, address, length);
            fprintf(fpobj, "H^%s  ^00%s^%s\n", l, address, length); // Write to file
            strcpy(startingadd, address);
        } else {
            // Taking opcode value from optab.txt to assemble object code
            while (!feof(fpop)) {
                fscanf(fpop, "%s%s", opname, opv);
                if (strcmp(opname, opc) == 0) {
                    strcpy(objcode[i], opv); // adding opcode value to object code
                    fseek(fpop, 0, SEEK_SET); // reset file pointer to start
                    break;
                }
            }

            // Taking address of symbols from symtab.txt to assemble object code
            while (!feof(fpsym)) {
                fscanf(fpsym, "%s%s", symbol, stadd);
                if (strcmp(symbol, opr) == 0) {
                    for (j = 2, k = 0; j <= 5; j++, k++)
                        objcode[i][j] = stadd[k]; // appending address of symbol
                    objcode[i][j] = '\0';
                    fseek(fpsym, 0, SEEK_SET);
                    i++;
                    break;
                }
            }
        }

        // Adding data constants if any to object code
        if (strcmp(opc, "WORD") == 0) {
            strcpy(objcode[i], opr);
            i++;
        }
    }
    n = i;
    i = 0;

    // Writing text record header
    printf("\nT^00%s^00000%d^", startingadd, n);
    fprintf(fpobj, "\nT^00%s^00000%d^", startingadd, n);

    // Printing object codes of all instructions in objcode array
    while (i < n) {
        if (strlen(objcode[i]) == 1) {
            printf("00000^%s\n", objcode[i]);
            fprintf(fpobj, "00000^%s\n", objcode[i]);
        } else {
            printf("^%s", objcode[i]);
            fprintf(fpobj, "^%s", objcode[i]);
        }
        i++;
    }

    // Writing end record
    printf("\nE^00%s", startingadd);
    fprintf(fpobj, "\nE^00%s", startingadd);

    // Close all files
    fclose(fpop);
    fclose(fpsym);
    fclose(fpinter);
    fclose(fpobj);

    getchar(); // Linux-compatible pause
}
