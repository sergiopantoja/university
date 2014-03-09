#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// we know that the input will never have a line larger than 1024 bytes
#define LINE_BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    char *string_a, *string_b, *infile, *outfile;
    char *input_buffer, *output_buffer, *pin_buffer, *pout_buffer, *pointer;
    FILE *fpin, *fpout;
    size_t len_diff;
    int ch, max_size, total_replacements = 0;

    if (argc != 5) {
        fprintf(stderr, "USAGE: %s <string_a> <string_b> <infile> <outfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    string_a = argv[1];
    string_b = argv[2];
    infile = argv[3];
    outfile = argv[4];

    if (string_a[0] == '\0') {
        fprintf(stderr, "ERROR: <string_a> cannot be empty.\n");
        exit(EXIT_FAILURE);
    }

    if ((fpin = fopen(infile, "r")) == NULL) {
        fprintf(stderr, "ERROR: Can't open  %s\n", infile);
        exit(EXIT_FAILURE);
    }

    if ((fpout = fopen(outfile, "w+")) == NULL) {
        fprintf(stderr, "ERROR: Can't open %s\n", outfile);
        fclose(fpin);
        exit(EXIT_FAILURE);
    }

    if ((input_buffer = (char *) malloc(LINE_BUFFER_SIZE)) == NULL) {
        fprintf(stderr, "ERROR: Can't allocate enough memory.\n");
        fclose(fpin);
        fclose(fpout);
        exit(EXIT_FAILURE);
    }

    // instead of repeatedly allocating memory in the while() loop, we allocate it once with a calcuated
    // maximum size that will work for all replacements (even multiple replacements on the same line)
    max_size = (strlen(string_b) / strlen(string_a)) + 1;

    if ((output_buffer = (char*) malloc(LINE_BUFFER_SIZE * max_size)) == NULL) {
        fprintf(stderr, "ERROR: Can't allocate enough memory.\n");
        free(input_buffer);
        fclose(fpin);
        fclose(fpout);
        exit(EXIT_FAILURE);
    }

    while (fgets(input_buffer, LINE_BUFFER_SIZE, fpin) != NULL)
    {
        // string_a will never be empty because we checked for that earlier
        if ((strstr(input_buffer, string_a)) != NULL)
        {
            // part of the reason why we have to use temp vars is so we can modify them without losing
            // the position of the original pointer when we free() the memory block
            pin_buffer = input_buffer;
            pout_buffer = output_buffer;

            while ((pointer = strstr(pin_buffer, string_a)) != NULL)
            {
                len_diff = (size_t) abs(pointer - pin_buffer);
                
                strncpy(pout_buffer, pin_buffer, len_diff);
                strncpy(pout_buffer + len_diff, string_b, strlen(string_b));
                
                pin_buffer += len_diff + strlen(string_a);
                pout_buffer += len_diff + strlen(string_b);
                total_replacements++;
            }

            // no more replacements, attach the end of the string
            strcpy(pout_buffer, pin_buffer);
        }
        else {
            strcpy(output_buffer, input_buffer);
        }

        if (fputs(output_buffer, fpout) == EOF) {
            fprintf(stderr, "ERROR: Could not write to output stream.");
            fclose(fpin);
            fclose(fpout);
            free(input_buffer);
            free(output_buffer);
            exit(EXIT_FAILURE);
        }
    }

    printf("\n%d\n\n", total_replacements);
    
    // seek to beginning of output file and print the contents
    fseek(fpout, 0, SEEK_SET);
    while ((ch = fgetc(fpout)) != EOF)
        putchar(ch);

    fclose(fpin);
    fclose(fpout);
    free(input_buffer);
    free(output_buffer);
    return 0;
}
