/* Here's a shorter algorithm for your object file reader program:

### Short Algorithm for Reading Object Files
1. **Open File**: Attempt to open `objpgm.txt`.
2. **Check for Header Record**:
   - Read the first line; if it starts with 'H', extract the program name, starting address, and length.
3. **Process Text Records**:
   - For each subsequent line starting with 'T':
     - Extract text address and length.
     - Parse hexadecimal data, converting and printing the byte value at the current address.
4. **Process End Record**:
   - If the line starts with 'E', extract and print the end address, then terminate reading.
5. **Close File**: Ensure the file is closed before exiting.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 256

void read_obj_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        return;
    }

    char line[MAXLEN];
    char program_name[MAXLEN];
    int start_address = 0;
    int length = 0;

    // Process the header record
    fgets(line, sizeof(line), file);
    if (line[0] == 'H') {
        sscanf(line, "H^%[^'^']^%X^%X", program_name, &start_address, &length);
        printf("Program Name: %s\n", program_name);
        printf("Starting Address: %06X\n", start_address);
        printf("Length of Program: %06X\n", length);
    }

    // Process text records
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'T') {
            int text_address = 0;
            int text_length = 0;

            // Extract text address and length
            sscanf(line, "T^%X^%X", &text_address, &text_length);
            printf("Text Address: %06X\n", text_address);
            printf("Text Length: %06X\n", text_length);

            char *data_start = strchr(line, '^') + 1;
            data_start = strchr(data_start, '^') + 1;
            data_start = strchr(data_start, '^') + 1;

            int current_address = text_address;
            while (*data_start != '\0' && *data_start != '\n') {
                char byte_str[3] = {data_start[0], data_start[1], '\0'};
                unsigned int byte = (unsigned int)strtol(byte_str, NULL, 16);
                printf("%04X\t%02X\n", current_address, byte);
                current_address++;
                data_start += 2;
                
                if (*data_start == '^') {
                    data_start++; // Skip the '^' separator
                }
            }
        } else if (line[0] == 'E') {
            char end_address[MAXLEN];
            sscanf(line, "E^%s", end_address);
            printf("End Address : %s\n", end_address);
            break; // End record; stop processing further
        }
    }

    fclose(file);
}

int main() {
    read_obj_file("objpgm.txt");
    return 0;
}
