#pragma once

#define RUN_TEST(test) Setup(); test(); Cleanup();
#define RUN_BATCH(batch) printf("\n  --- "#batch" ---\n"); batch.RunAll();

#define SUCCESS(test) printf("SUCCESS --- "#test"\n");
#define FAIL(test) printf("FAIL ------ "#test"\n");

#define ASSERT_SUCCESS(test) SUCCESS(test) return;
#define ASSERT_FAIL(test) FAIL(test) return;

#define ASSERT_EQUAL(expected, actual, test) \
	if (expected == actual) {SUCCESS(test)} \
	else {FAIL(test)}

#define ADD_ASSERT_EQUAL(expected, actual) expected == actual &&

#define BEGIN_ASSERT if (

#define END_ASSERT(test) true) {SUCCESS(test)} else {FAIL(test)}