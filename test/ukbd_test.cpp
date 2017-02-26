#include <stdio.h>
#include <stdlib.h>

#include <check.h>


START_TEST(tests_the_truth) {
  ck_assert(1);
}
END_TEST

Suite *ukbd_suite(void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("UKBD");
  tc_core = tcase_create("core");

  tcase_add_test(tc_core, tests_the_truth);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int failures_count;
  Suite *s;
  SRunner *sr;

  s = ukbd_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failures_count = srunner_ntests_failed(sr);
  srunner_free(sr);

  if (failures_count == 0) {
    puts("\x1B[1;32mPASS\x1B[0m");
    return EXIT_SUCCESS;
  }
  else {
    puts("\x1B[1;31mFAIL\x1B[0m");
    return EXIT_FAILURE;
  }
}
