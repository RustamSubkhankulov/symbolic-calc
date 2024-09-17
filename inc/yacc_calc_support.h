#ifndef YACC_CALC_SUPPORT_H
#define YACC_CALC_SUPPORT_H

/**
 * @brief Calc's helper method for the parser.
 *
 * @detail Provides means to get variable's value during
 *         expression evaluation. Meant to be used by the
 *         parser only and only during parsing process
 *         (in yyparse() called from the main evaluation
 *         method - calc_eval_expr()).
 *
 * @param[in] var_name Variable's name.
 *
 * @return Variable's value.
 */
float calc_get_var_value(const char* var_name);

#endif /* YACC_CALC_SUPPORT_H */
