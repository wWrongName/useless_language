#ifndef __INTERPRETER_HEADERS__
#define __INTERPRETER_HEADERS__
#include <iostream>
#include <cstring>
#include <deque>
#include <map>
#define NERR 2147483647

typedef struct DOUBLE_VAR {
    int l1;
    int l2;
} d_var;

typedef struct LOOP_CONDITION {
    d_var first;
    int symbol;
    d_var second;
} L_C;

typedef struct P_NODE {
    struct P_NODE *right;
    struct P_NODE *left;
    d_var symbol;
} p_node;

enum tables {num, var, math, loop, logg, sys};
enum math_symbols {plus, minus, multiply, divide};
enum log_symbols  {greater, less, equal, n_equal};
enum loop_table {assignment, c_begin, c_end, l_end};
enum sys_table  {s_letter, s_num, m_end};

p_node *insert_lp(p_node*, d_var*, d_var*);
p_node *insert_hp(p_node*, d_var*, d_var*);
p_node *create_node(d_var);
int go_around_loop(std::deque<int>*, L_C*);
int parser(std::deque<int>*, bool);
int lexer(char*, std::deque<int>*);
int operation(int, int, int);
int read_number(char*);
int count_all(p_node*);
int solve_equation();
int getl();
void write_var_in_buf(std::deque<int>*, unsigned int);
void find_loop(std::deque<int>*, int);
char *preproc(FILE*);
char sgetc(char*);
bool get_priority(int);
bool check_cond(L_C*);
unsigned char num_length(unsigned int);
void read_condition(L_C *);

#endif