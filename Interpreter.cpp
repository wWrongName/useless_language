#include "headers.hpp"

#define ARGC_ERROR std::cout << "error -> invalid input, you need two arguments\n";\
                   return 1;
#define LEX_ERROR  std::cout << "lex_error, please check your code!\n";\
                   return 1;
#define PARS_ERROR std::cout << "pars_error, please check your code!\n";\
                   return 1;
#define FILE_ERROR std::cout << "error -> file was not opened, please check a filepath!\n";\
                   return 1;

int main(int argc, char **argv){
    std::cout << ">> useless_lang interpreter 1.02\n";
    if (argc != 2) {
        ARGC_ERROR
    }
    char *text_data;
    FILE *file;
    std::deque<int> lexemes;
    int rv;
    /* write in string without ' ' and '\n' */
    file = fopen(argv[1], "r");
    if (file == NULL) {
        FILE_ERROR
    }
    text_data = preproc(file);
    fclose(file);
    /* separate whole text into lexemes */
    rv = lexer(text_data, &lexemes);
    free(text_data);
    if (rv != 0) {
        fclose(file);
        LEX_ERROR
    }
    /* interpret lexemes */
    rv = parser(&lexemes, true); //true -> outside call
    if (rv != 0) {
        fclose(file);
        PARS_ERROR
    }
    fclose(file);
    std::cout << '\n';
    return 0;
}