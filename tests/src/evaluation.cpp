#include <gtest/gtest.h>

extern "C"
{
#include "calc.h"
}

static float sEval_res = 0.f;

TEST(EVALUATION_TESTING, ADD)
{
  calc_eval_expr("1+2", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 3.f);

  calc_eval_expr("0+1", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 1.f);

  calc_eval_expr("1+0", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 1.f);

  calc_eval_expr("0+0", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 0.f);
}

TEST(EVALUATION_TESTING, SUB)
{
  calc_eval_expr("2-1", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 1.f);

  calc_eval_expr("1-2", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, -1.f);

  calc_eval_expr("1-0", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 1.f);

  calc_eval_expr("0-1", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, -1.f);
}

TEST(EVALUATION_TESTING, MUL)
{
  calc_eval_expr("2*2", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 4.f);

  calc_eval_expr("1*0", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 0.f);

  calc_eval_expr("0*1", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 0.f);

  calc_eval_expr("2*0.5", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 1.f);
}

TEST(EVALUATION_TESTING, DIV)
{
  calc_eval_expr("2/2", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 1.f);

  calc_eval_expr("1/2", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 0.5f);

  calc_eval_expr("1/0.5", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 2.f);

  calc_eval_expr("0/10", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 0.f);
}

TEST(EVALUATION_TESTING, POW)
{
  calc_eval_expr("2^2", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 4.f);

  calc_eval_expr("2^1", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 2.f);

  calc_eval_expr("2^0", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 1.f);

  calc_eval_expr("2^-1", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 0.5f);
}

TEST(EVALUATION_TESTING, UNARY_PLUS)
{
  calc_eval_expr("+2", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 2.f);

  calc_eval_expr("+0", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 0.f);
}

TEST(EVALUATION_TESTING, UNARY_MINUS)
{
  calc_eval_expr("-2", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, -2.f);

  calc_eval_expr("-0", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 0.f);
}

TEST(EVALUATION_TESTING, UNARY_NOT)
{
  calc_eval_expr("~0", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 1.f);

  calc_eval_expr("~1", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 0.f);

  calc_eval_expr("~10", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 0.f);
}

TEST(EVALUATION_TESTING, STD_CONST)
{
  calc_eval_expr("PI", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 3.141593f);

  calc_eval_expr("EXP", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 2.718282f);
}

TEST(EVALUATION_TESTING, SIN)
{
  calc_eval_expr("sin(0)", NULL, &sEval_res);
  EXPECT_NEAR(sEval_res, 0.f, 1e-6);

  calc_eval_expr("sin(PI)", NULL, &sEval_res);
  EXPECT_NEAR(sEval_res, 0.f, 1e-6);

  calc_eval_expr("sin(PI/2)", NULL, &sEval_res);
  EXPECT_NEAR(sEval_res, 1.f, 1e-6);
}

TEST(EVALUATION_TESTING, COS)
{
  calc_eval_expr("cos(0)", NULL, &sEval_res);
  EXPECT_NEAR(sEval_res, 1.f, 1e-6);

  calc_eval_expr("cos(PI)", NULL, &sEval_res);
  EXPECT_NEAR(sEval_res, -1.f, 1e-6);

  calc_eval_expr("cos(PI/2)", NULL, &sEval_res);
  EXPECT_NEAR(sEval_res, 0.f, 1e-6);
}

TEST(EVALUATION_TESTING, TG)
{
  calc_eval_expr("tg(0)", NULL, &sEval_res);
  EXPECT_NEAR(sEval_res, 0.f, 1e-6);
}

TEST(EVALUATION_TESTING, CTG)
{
  calc_eval_expr("ctg(PI/2)", NULL, &sEval_res);
  EXPECT_NEAR(sEval_res, 0.f, 1e-6);
}

TEST(EVALUATION_TESTING, SQRT)
{
  calc_eval_expr("sqrt(0)", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 0.f);

  calc_eval_expr("sqrt(1)", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 1.f);

  calc_eval_expr("sqrt(4)", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 2.f);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
