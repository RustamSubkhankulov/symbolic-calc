#ifndef LEXER_H
#define LEXER_H

/**
 * @brief Enumerated type for the token class. Divides all
 *        tokens into the large groups. Sum of the token classes
 *        can possibly have subtype.
 */
typedef enum
{
  OPER, /* Operator. */
  VAR_ID, /* Variable indentificator. */
  STD_FUNC, /* Predefined standard fucntion name. */
  STD_CONST, /* Predefined standard constant name. */
  NUMINT, /* Integer number. */
  NUMFLT, /* Floating-point number. */
  PUNCT_SYMB, /* Punctuation symbol (e.g. brackets) */
} token_class_t;

/**
 * @brief Subtype of the operator tokens.
 */
typedef enum
{
  BINARY, /* Binary operator ('+', '*' etc.) */
  UNARY, /* Unary operator ('~' etc.) */
} oper_subclass_t;

/**
 * @brief Enumerated type, describing possible binary operations.
 */
typedef enum
{
  ADD, /* '+' */
  SUB, /* '-' */
  MUL, /* '*' */
  DIV, /* '/' */
  AND, /* '&' */
  OR, /* '|' */
  XOR, /* '^' */
} binary_oper_t;

/**
 * @brief Enumerated type, describing possible unary operations.
 */
typedef enum
{
  NEG, /* '~' */
} unary_oper_t;

/**
 * @brief Enumerated type, describing supported standard functions.
 */

typedef enum
{
  SIN, /* Sine. */
  COS, /* Cosine. */
  TG, /* Cotangent. */
  CTG, /* Tangent. */
  SQRT, /* Square root. */
} std_func_t;

typedef enum
{
  PI, /* Pi. */
  EXP, /* Euler's number. */
} std_const_t;

typedef enum
{
  OP_BR, /* Opening bracket. */
  CL_BR, /* Closing bracket. */
} punct_symb_t;

#endif /* LEXER_H */
