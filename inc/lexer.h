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
 * @brief Base token struct. 
 */
typedef struct
{
  token_class_t class;
} token_t;

//---------------------------------------------

/**
 * @brief Subtype of the operator tokens.
 */
typedef enum
{
  BINARY, /* Binary operator ('+', '*' etc.) */
  UNARY, /* Unary operator ('~' etc.) */
} oper_subclass_t;

/**
 * @brief Enumerated type, describing possible binary and unary operators.
 */
typedef enum
{
  /* Binary operators. */
  ADD, /* '+' */
  SUB, /* '-' */
  MUL, /* '*' */
  DIV, /* '/' */
  AND, /* '&' */
  OR, /* '|' */
  XOR, /* '^' */

  /* Unary operators. */
  NEG, /* '~' */
} oper_val_t;

/**
 * @brief Operator token struct.
 */
typedef struct
{
  token_t base;
  oper_subclass_t subclass;
  oper_val_t val;
} oper_token_t;

//---------------------------------------------

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

/**
 * @brief Standard function token struct.
 */
typedef struct
{
  token_t base;
  std_func_t val;
} std_func_token_t;

//---------------------------------------------

/**
 * @brief Enumerated type, describing supported standard constants.
 */
typedef enum
{
  PI, /* Pi. */
  EXP, /* Euler's number. */
} std_const_t;

/**
 * @brief Standard constant token struct.
 */
typedef struct
{
  token_t base;
  std_const_t val;
} std_const_token_t;

//---------------------------------------------

/**
 * @brief Enumerated type, describing punctuation symbols.
 */
typedef enum
{
  OP_BR, /* Opening bracket. */
  CL_BR, /* Closing bracket. */
} punct_symb_t;

/**
 * @brief Punctuation symbol token struct.
 */
typedef struct
{
  token_t base;
  punct_symb_t val;
} punct_symb_token_t;

#endif /* LEXER_H */
