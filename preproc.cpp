#include <iostream>

char *preproc(FILE *p_input) {
    char p_char;
    int counter = 0;
    char *prog_text = (char*)malloc(sizeof(char));
    while ((p_char = fgetc(p_input)) != EOF) {
        if ((p_char - ' ' != 0) && (p_char - '\n' != 0)){
            prog_text = (char*)realloc(prog_text ,sizeof(char) * ++counter);
            prog_text[counter-1] = p_char;
        }
    }
    prog_text[counter] = '\n';
    return prog_text;
}