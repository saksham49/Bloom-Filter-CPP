# To run string test cases
run_string_1: ./tests/test_string_1.cpp bloom_filter.hpp
	@g++ ./tests/test_string_1.cpp bloom_filter.hpp
	@./a.out $(TEST_FILE) $(FPR) $(EXPECTED_INSERT)

run_string_2: ./tests/test_string_2.cpp bloom_filter.hpp
	@g++ ./tests/test_string_2.cpp bloom_filter.hpp
	@./a.out $(TEST_FILE) $(HASH_COUNT) $(BIT_COUNT) $(EXPECTED_INSERT)


# To run int test cases
run_int_1: ./tests/test_int_1.cpp bloom_filter.hpp
	@g++ ./tests/test_int_1.cpp bloom_filter.hpp
	@./a.out $(TEST_FILE) $(FPR) $(EXPECTED_INSERT)

run_int_2: ./tests/test_int_2.cpp bloom_filter.hpp
	@g++ ./tests/test_int_2.cpp bloom_filter.hpp
	@./a.out $(TEST_FILE) $(HASH_COUNT) $(BIT_COUNT) $(EXPECTED_INSERT)


# To run double test cases
run_double_1: ./tests/test_double_1.cpp bloom_filter.hpp
	@g++ ./tests/test_double_1.cpp bloom_filter.hpp
	@./a.out $(TEST_FILE) $(FPR) $(EXPECTED_INSERT)

run_double_2: ./tests/test_double_2.cpp bloom_filter.hpp
	@g++ ./tests/test_double_2.cpp bloom_filter.hpp
	@./a.out $(TEST_FILE) $(HASH_COUNT) $(BIT_COUNT) $(EXPECTED_INSERT)
