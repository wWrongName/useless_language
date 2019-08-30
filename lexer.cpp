#include "headers.hpp"
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <cmath>

unsigned int s_ctr = 0;
std::map<char, unsigned int> math_table = {{')', plus},
                                           {'(', minus},
                                           {'D', multiply},
                                           {'x', divide}};
std::map<char, unsigned int> log_table = {{'b', greater},
                                          {'p', less},
                                          {'e', equal},
                                          {'!', n_equal}};
std::map<unsigned int, int> var_table;

int lexer(char *l_input, std::deque<int> *l_output) {
    int number;
    char l_char;
    char l_string [2];
    bool already_read = false;
    l_string[0] = sgetc(l_input);
    l_string[1] = sgetc(l_input);
    if (!strcmp(l_string, "->")) {
        while (true) {
            if (!already_read)
                l_char = sgetc(l_input);
            else
                already_read = false;         
            if (l_char == '{') {
                number = read_number(l_input);
                if (number == NERR)
                    return NERR;
                write_var_in_buf(l_output, (unsigned int)number);
            }
            else if (l_char == '<'){
                l_char = sgetc(l_input);
                if (l_char == '-'){
                    l_output->push_back(sys);
                    l_output->push_back(m_end);
                }
                else {
                    already_read = true;
                    l_output->push_back(loop);
                    l_output->push_back(assignment);
                }
            }
            else if (isdigit(l_char) || (l_char == '-')) {
                if (l_char == '-') {
                    number = read_number(l_input);
                    if (number == NERR)
                        return NERR;
                    number *= -1;
                }
                else {
                    s_ctr--;
                    number = read_number(l_input);
                    if (number == NERR)
                        return NERR;
                }
                l_output->push_back(num);
                l_output->push_back(number);
            }
            else if (l_char == '@') {
                l_char = sgetc(l_input);
                if (l_char == '>'){
                    l_output->push_back(loop);
                    l_output->push_back(l_end);
                }
                else {
                    int tmp_number;
                    if (!isdigit(l_char))
                        return NERR;
                    number = l_char - '0';
                    tmp_number = read_number(l_input);
                    if (tmp_number != NERR) {
                        unsigned char tmp_ctr = num_length(tmp_number);
                        number = number * (int)pow(10.0, (int)tmp_ctr) + tmp_number;
                    }
                    l_output->push_back(loop);
                    l_output->push_back(c_begin);
                    l_output->push_back(num);
                    l_output->push_back(number);
                }
            }
            else if (l_char == '>') {
                l_output->push_back(loop);
                l_output->push_back(c_end);
            }
            else if (l_char == ':') {
                l_char = sgetc(l_input);
                if (math_table.find(l_char) != math_table.end()) {
                    l_output->push_back(math);
                    l_output->push_back(math_table[l_char]);
                }
                else if (log_table.find(l_char) != log_table.end()) {
                    l_output->push_back(logg);
                    l_output->push_back(log_table[l_char]);
                }
                else if ((l_char == 'w') || (l_char == 'l')) {
                    l_char = sgetc(l_input);
                    if (l_char == 'o'){
                        l_char = sgetc(l_input);
                        if (l_char == 'w') {
                            l_output->push_back(sys);
                            l_output->push_back(s_letter);
                        }
                        else if (l_char == 'l') {
                            l_output->push_back(sys);
                            l_output->push_back(s_num);
                        }
                        else 
                            return NERR;
                    }
                    else 
                        return NERR;
                }
                else
                    return NERR;
            }
            else if (l_char == '\n')
                break;
            else 
                return NERR;
        }
    }
    else
        return NERR;
    return 0;
}

int read_number(char *r_input){
    char r_char = sgetc(r_input); 
    int outnum = 0;
    if (r_char == '}')
        return NERR;
    while (r_char != '}'){
        if (!isdigit(r_char))
            return NERR;
        outnum = outnum * 10 + (r_char - '0');
        r_char = sgetc(r_input);
    }
    return outnum;
}

void write_var_in_buf(std::deque<int> *w_buf, unsigned int w_num){
    if (var_table.find(w_num) == var_table.end())
        var_table.insert(std::pair<unsigned int, int>(w_num, 0));
    w_buf->push_back(var);
    w_buf->push_back(w_num);
}

unsigned char num_length(unsigned int number){
    if (!number)
        return 1;
    unsigned char counter = 0;
    while (number) {
        number /= 10;
        counter++;
    }
    return counter;
}

char sgetc(char* str) {
    return str[s_ctr++];
}