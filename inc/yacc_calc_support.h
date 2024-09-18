#ifndef YACC_CALC_SUPPORT_H
#define YACC_CALC_SUPPORT_H

/**
 * @brief Calc's helper method for the parser.
 *
 * @detail Provides means to get variable's value during
 *         expression evaluation from the inside of yyparse()
 *         (from rules in yacc/yacc.y). Meant to be used by the
 *         parser only and only during parsing process
 *         (in yyparse() called from the main evaluation
 *         method - calc_eval_expr()). Otherwise behaviour
 *         of this function may be invalid.
 *
 *         If variable is undefined, exits with failure.
 *
 * @param[in] var_name Variable's name.
 *
 * @return Variable's value.
 */
float calc_get_var_value(const char* var_name);

#endif /* YACC_CALC_SUPPORT_H */
