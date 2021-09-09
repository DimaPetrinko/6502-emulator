#pragma once

#define SET_COLOR_AND_TYPE(type, color) "\033["#type";"#color
#define SET_COLOR(color) "\033["#color

#define RUN_TEST(test) Setup(); test(); Cleanup();
#define RUN_BATCH(batch) printf("\n  --- "#batch" ---\n"); batch.RunAll();

#define SUCCESS(test) printf(SET_COLOR_AND_TYPE(1, 32m) "SUCCESS" SET_COLOR(0m) " --- " #test "\n");
#define FAIL(test) printf(SET_COLOR_AND_TYPE(1, 31m) "FAIL" SET_COLOR(0m) " ------ " #test "\n");

#define ASSERT_SUCCESS(test) SUCCESS(test) return;
#define ASSERT_FAIL(test) FAIL(test) return;

#define ASSERT_EQUAL(expected, actual, test) \
	if (expected == actual) {SUCCESS(test)} \
	else {FAIL(test)}

#define ADD_ASSERT_EQUAL(expected, actual) expected == actual &&

#define BEGIN_ASSERT if (

#define END_ASSERT(test) true) {SUCCESS(test)} else {FAIL(test)}