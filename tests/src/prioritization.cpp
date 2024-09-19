#include <gtest/gtest.h>

extern "C"
{
#include "calc.h"
}

static float sEval_res = 0.f;

TEST(PRIORITIZATION_TESTING, PARANTHESES)
{
  calc_eval_expr("{2+2}*2", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 8.f);

  calc_eval_expr("-{1-3}", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 2.f);
}

TEST(PRIORITIZATION_TESTING, EXPR_TERM)
{
  calc_eval_expr("2+2*2", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 6.f);

  calc_eval_expr("2*2-2", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 2.f);

  calc_eval_expr("2+2/2", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 3.f);

  calc_eval_expr("2/2-2", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, -1.f);
}

TEST(PRIORITIZATION_TESTING, TERM_POWER)
{
  calc_eval_expr("2^3*2", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 16.f);

  calc_eval_expr("2^3/2", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 4.f);
}

TEST(PRIORITIZATION_TESTING, EXPR_POWER)
{
  calc_eval_expr("2^3+2", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 10.f);

  calc_eval_expr("2^3-2", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 6.f);
}

TEST(PRIORITIZATION_TESTING, UNARY)
{
  calc_eval_expr("-2+1", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, -1.f);

  calc_eval_expr("-2*3", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, -6.f);

  calc_eval_expr("-2^3", NULL, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, -8.f);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
