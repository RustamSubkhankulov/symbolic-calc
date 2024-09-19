#include <gtest/gtest.h>

extern "C"
{
#include "calc.h"
}

static float sEval_res = 0.f;

TEST(VARIABLES_TESTING, VAR_VALUE)
{
  var_descr_t var_x = { .name  = "x",
                        .value = var_value_t{ .is_named_constant = false, .float_value = -0.5f } };

  calc_opts_t calc_opts = { .vars_num = 1U, .vars = &var_x };

  calc_eval_expr("1+x", &calc_opts, &sEval_res);
  EXPECT_FLOAT_EQ(sEval_res, 0.5f);
}

TEST(VARIABLES_TESTING, VAR_CONST)
{
  var_descr_t var_x = { .name  = "x",
                        .value = var_value_t{ .is_named_constant = true, .constant_name = "PI" } };

  calc_opts_t calc_opts = { .vars_num = 1U, .vars = &var_x };

  calc_eval_expr("sin(x)", &calc_opts, &sEval_res);
  EXPECT_NEAR(sEval_res, 0.f, 1e-6);
}

TEST(VARIABLES_TESTING, VAR_PLURAL)
{
  var_descr_t vars[] = {
    { .name = "x", .value = var_value_t{ .is_named_constant = false, .float_value = 2.f } },
    { .name = "y", .value = var_value_t{ .is_named_constant = true, .constant_name = "PI" } }
  };

  calc_opts_t calc_opts = { .vars_num = 2U, .vars = vars };

  calc_eval_expr("x+sin(y)", &calc_opts, &sEval_res);
  EXPECT_NEAR(sEval_res, 2.f, 1e-6);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
