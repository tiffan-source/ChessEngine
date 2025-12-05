

#include "unity.h"

#include "config.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_config_should_be_init_whith_depth(void)
{
    int test_depth = 5;
    init_config(test_depth);
    TEST_ASSERT_NOT_NULL(get_config());
    TEST_ASSERT_EQUAL_INT(test_depth, GET_DEPTH_FROM_CONFIG(get_config()));
    free_config();
}

