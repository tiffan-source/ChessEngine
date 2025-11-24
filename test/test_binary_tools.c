
#ifdef TEST

#include "unity.h"

#include "binary_tools.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_binary_tools_should_return_0_string_representation_of_U64(void)
{
    const char* expect = "0 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 0\n";

    char* string_0_bit = string_representation_of_U64(0ULL);
    TEST_ASSERT_EQUAL_STRING(expect, string_0_bit);
    free(string_0_bit);
}

void test_binary_tools_should_return_1_string_representation_of_U64(void)
{
    const char* expect = "1 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 0\n";

    char* string_1_bit = string_representation_of_U64(1ULL);
    TEST_ASSERT_EQUAL_STRING(expect, string_1_bit);
    free(string_1_bit);
}

void test_binary_tools_should_return_9598516481584849844_string_representation_of_U64(void)
{
    const char* expect = "0 0 1 0 1 1 0 1\n"
                        "1 1 0 0 0 1 1 1\n"
                        "0 0 0 1 1 0 0 1\n"
                        "1 1 1 0 0 0 0 1\n"
                        "0 1 0 0 0 1 1 1\n"
                        "1 1 1 0 0 0 1 1\n"
                        "0 0 1 0 1 1 0 0\n"
                        "1 0 1 0 0 0 0 1\n";

    char* string_9598516481584849844_bit = string_representation_of_U64(9598516481584849844ULL);
    TEST_ASSERT_EQUAL_STRING(expect, string_9598516481584849844_bit);
    free(string_9598516481584849844_bit);
}

void test_binary_tools_should_return_0_get_lsb_index_of_0(void)
{
    int index = get_lsb_index(0ULL);
    TEST_ASSERT_EQUAL_INT(-1, index);
}

void test_binary_tools_should_return_0_get_lsb_index_of_1(void)
{
    int index = get_lsb_index(1ULL);
    TEST_ASSERT_EQUAL_INT(0, index);
}

void test_binary_tools_should_return_4_get_lsb_index_of_16(void)
{
    int index = get_lsb_index(16ULL);
    TEST_ASSERT_EQUAL_INT(4, index);
}

void test_binary_tools_should_return_2_get_lsb_index_of_4851489844(void)
{
    int index = get_lsb_index(4851489844ULL);
    TEST_ASSERT_EQUAL_INT(2, index);
}

void test_binary_tools_should_return_0_when_counting_bits_set_of_0(void)
{
    int count = count_bits_set(0ULL);
    TEST_ASSERT_EQUAL_INT(0, count);
}

void test_binary_tools_should_return_1_when_counting_bits_set_of_1(void)
{
    int count = count_bits_set(1ULL);
    TEST_ASSERT_EQUAL_INT(1, count);
}

void test_binary_tools_should_return_4_when_counting_bits_set_of_15(void)
{
    int count = count_bits_set(15ULL);
    TEST_ASSERT_EQUAL_INT(4, count);
}

void test_binary_tools_should_return_32_when_counting_bits_set_of_4294967295(void)
{
    int count = count_bits_set(4294967295ULL);
    TEST_ASSERT_EQUAL_INT(32, count);
}

#endif // TEST
