#include "headers.hpp"
#include <iterator>
#define C_ERR -1
#define LOW 0
#define HIGH 1

extern std::map<unsigned int, int> var_table;
std::deque<int>::iterator it;
d_var glob_lex;

int parser(std::deque<int> *lexemes, bool outside_call) {
    int tmp;
    bool already_read = false;
    if (outside_call)
        it = lexemes->begin();
    int lexeme, lexeme1, rv;
    while (true) {
        if (!already_read) {
            lexeme  = getl();
            lexeme1 = getl();
        }
        else {
            lexeme = glob_lex.l1;
            lexeme1 = glob_lex.l2;
            already_read = false;
        }
        if (lexeme == var) {
            lexeme = getl();
            if ((lexeme == loop) && (assignment == (tmp = getl()))) {
                rv = solve_equation();
                if (rv == NERR)
                    return rv;
                var_table[lexeme1] = rv;
            }
            else 
                return NERR;
            already_read = true;
        }
        else if ((lexeme == loop) && (lexeme1 == c_begin)) {
            L_C cond;
            lexeme = getl();
            if (lexeme != num)
                return NERR;
            lexeme1 = getl();
            read_condition(&cond);
            if (cond.first.l1 == C_ERR)
                return NERR;
            auto tmp_it = it;
            find_loop(lexemes, lexeme1);
            if(lexemes->end() == it)
                return NERR;
            if (NERR == (tmp = go_around_loop(lexemes, &cond)))
                return NERR;
            it = tmp_it;
        }
        else if (lexeme == sys){
            bool char_f = false;
            if (lexeme1 == s_letter)
                char_f = true;
            else if (lexeme1 == m_end)
                return 0;
            lexeme = getl();
            lexeme1 = getl();
            if (char_f) {
                if (lexeme == var)
                    std::cout << (char)var_table[lexeme1];
                else if (lexeme == num)
                    std::cout << (char)lexeme1;
                else 
                    return NERR; 
            }
            else {
                if (lexeme == var)
                    std::cout << var_table[lexeme1];
                else if (lexeme == num)
                    std::cout << lexeme1;
                else 
                    return NERR;
            }
        }
        else if ((lexeme == loop) && (lexeme1 == l_end))
            return 1;
        else 
            return NERR;
    }
}

int getl() {
    return *it++;
}

int solve_equation() {
    bool tmp;
    d_var v_n_lex, math_sym;
    v_n_lex.l1 = getl();
    v_n_lex.l2 = getl();
    if ((v_n_lex.l1 != var) && (v_n_lex.l1 != num))
        return NERR;
    p_node *top = create_node(v_n_lex);
    math_sym.l1 = getl();
    math_sym.l2 = getl();
    glob_lex = math_sym;
    while (math_sym.l1 == math) {
        v_n_lex.l1 = getl();
        v_n_lex.l2 = getl();
        if ((v_n_lex.l1 != var) && (v_n_lex.l1 != num))
            return NERR;
        if (HIGH == (tmp = get_priority(math_sym.l2)))
            top = insert_hp(top, &math_sym, &v_n_lex);
        else 
            top = insert_lp(top , &math_sym, &v_n_lex);
        math_sym.l1 = getl();
        math_sym.l2 = getl();
        glob_lex = math_sym;
    }
    return count_all(top);
}

void read_condition(L_C *cond) {
    int lexeme, lexeme1;
    lexeme = getl();
    if ((lexeme == num) || (lexeme == var)){
        cond->first.l1 = lexeme;
        cond->first.l2 = getl();
        lexeme = getl();
        if (lexeme == logg) {
            cond->symbol = getl();
            lexeme = getl();
            if ((lexeme == num) || (lexeme == var)) {
                cond->second.l1 = lexeme;
                cond->second.l2 = getl();
                goto good_end;
            }
        }
    }
    cond->first.l1 = C_ERR;
    good_end: lexeme = getl();
              lexeme1 = getl();
    if ((lexeme != loop) || (lexeme1 != c_end))
        cond->first.l1 = C_ERR;
}

bool get_priority(int symbol) {
    switch(symbol){
        case plus:     return LOW;
        case minus:    return LOW;
        case multiply: return HIGH;
        case divide:   return HIGH;
    }
}

p_node *insert_hp(p_node *top, d_var *math_s, d_var *var_or_num) {
    if (top->right == NULL) {
        top = insert_lp(top, math_s, var_or_num);
    }
    else {
        p_node *tmp_ptr = top->right;
        top->right = create_node(*math_s);
        top->right->right = create_node(*var_or_num);
        top->right->left = tmp_ptr;
    }
    return top;
}

p_node *insert_lp(p_node *top, d_var *math_s, d_var *var_or_num) {
    p_node *tmp_ptr = top;
    top = create_node(*math_s);
    top->right = create_node(*var_or_num);
    top->left = tmp_ptr;
    return top;
}

int count_all(p_node *top) {
    if (top->symbol.l1 == num){
        return top->symbol.l2;
    }
    if (top->symbol.l1 == var)
        return var_table[top->symbol.l2];
    int c_symbol;
    if (top->symbol.l1 == math)
        c_symbol = top->symbol.l2;
    int num1 = count_all(top->left);
    int num2 = count_all(top->right);
    return operation(num1, num2, c_symbol);
}

int operation(int n1, int n2, int symbol) {
    switch(symbol){
        case plus:     return n1+n2;
        case minus:    return n1-n2;
        case multiply: return n1*n2;
        case divide:   return n1/n2;
    }
}

p_node *create_node(d_var val) {
    p_node *new_node = new p_node;
    new_node->left   = NULL;
    new_node->right  = NULL;
    new_node->symbol = val;
    return new_node;
}

void find_loop(std::deque<int> *lexemes, int num_of_loop) {
    bool end_f = false;
    d_var lexeme;
    while (it != lexemes->end()) {
        lexeme.l1 = getl();
        lexeme.l2 = getl();
        if ((lexeme.l1 == sys) && (lexeme.l2 == m_end))
            end_f = true;
        if (end_f && (lexeme.l1 == loop) && (lexeme.l2 == c_begin)) {
            lexeme.l1 = getl();
            lexeme.l2 = getl();
            if ((lexeme.l1 == num) && (num_of_loop == lexeme.l2))
                break;
        }
    }
}

int go_around_loop(std::deque<int> *lexemes, L_C *cond) {
    d_var lexeme;
    auto tmp_it = it;
    while (check_cond(cond)) {
        int rv = parser(lexemes, false); //false -> inside call
        if (rv != 1)
            return NERR;
        it = tmp_it;
    }
}

bool check_cond(L_C *cond) {
    int num1, num2;
    if (cond->first.l1 == num)
        num1 = cond->first.l2;
    else 
        num1 = var_table[cond->first.l2];
    if (cond->second.l1 == num)
        num2 = cond->second.l2;
    else 
        num2 = var_table[cond->second.l2];
    switch(cond->symbol){
        case greater: {
            if (num1 > num2) return true;
            else return false;
        }
        case less: {
            if (num1 < num2) return true;
            else return false;
        }
        case equal: {
            if (num1 == num2) return true;
            else return false;
        }
        case n_equal: {
            if (num1 != num2) return true;
            else return false;
        }
    }
}