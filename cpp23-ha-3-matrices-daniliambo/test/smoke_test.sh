#!/bin/sh -eu

if [ "$#" -lt 1 ]; then
    echo "Usage:"
    echo "    $0 path_to_matrices"
    exit -1
fi

EXECUTABLE="$1"
REAL_EXEC="$EXECUTABLE"
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

VALGRIND_OPTS="--leak-check=yes -q --leak-resolution=high --main-stacksize=64000000"
# To use Valgrind uncomment next line:
#REAL_EXEC="valgrind $VALGRIND_OPTS $EXECUTABLE"

run()
{
    echo "***** Running: $EXECUTABLE $@"
    $REAL_EXEC "$@" 1>out.txt 2>err.txt
    CODE=$?
    cat out.txt
    cat err.txt
    return $CODE
}

compare()
{
    $SCRIPT_DIR/compare_matrices.awk $SCRIPT_DIR/$1 $2
}

check_empty_err()
{
    test ! -s err.txt || (echo "Error: expected empty stderr, got:"; cat err.txt; exit 1)
}

check_empty_out()
{
    test ! -s out.txt || (echo "Error: expected empty stdout, got:"; cat out.txt; exit 1)
}

check_non_empty_err()
{
    test -s err.txt || (echo "Error: expected non-empty stderr"; exit 1)
}

expected_error()
{
    echo "Error: expected non-zero exit code"
    exit 1
}

expected_ok()
{
    echo "Error: expected zero exit code"
    echo "stdout:"
    cat out.txt
    echo "stderr:"
    cat err.txt
    exit 1
}

h()
{
    echo $@
}

# "run" wraps run of actual matrices executable
run 5.txt || expected_ok
compare 5.txt out.txt
check_empty_err

run 5.txt --add 2.txt || expected_ok
compare 7.txt out.txt
check_empty_err

run 5.txt --mult 2.txt || expected_ok
compare 10.txt out.txt
check_empty_err

run q_7x7.txt --mult r_7x16.txt || expected_ok
compare 7x16_0-111.txt out.txt
check_empty_err

run rr_16x7.txt --mult qq_7x7.txt || expected_ok
compare 16x7_0-111.txt out.txt
check_empty_err

run 0-167_8x21.txt --add 0-334_8x21.txt || expected_ok
compare 8x21_-167-0.txt out.txt
check_empty_err

run 0-167_21x8.txt --add 0-334_21x8.txt || expected_ok
compare 21x8_-167-0.txt out.txt
check_empty_err

run 5.txt --mult 2.txt --add 4.txt || expected_ok
compare 14.txt out.txt
check_empty_err

run 1.txt --mult 2.txt --add 0.txt --mult 3.txt || expected_ok
compare 6.txt out.txt
check_empty_err

run A_3x7.txt --mult B_7x13.txt --add minus_A_mult_B.txt || expected_ok
compare 3x13_0.txt out.txt
check_empty_err

# filename without txt extension: "5"
run 5 || expected_ok
compare 5.txt out.txt
check_empty_err

# No arguments - should be an error
run && expected_error
check_empty_out
check_non_empty_err

# Wrong operation name - should be an error
run 5.txt --a 2.txt && expected_error
check_empty_out
check_non_empty_err

# Wrong operation name - should be an error
run 5.txt --xxx 2.txt && expected_error
check_empty_out
check_non_empty_err

# Wrong operation name - should be an error
run 5.txt --add 1.txt --a 2.txt && expected_error
check_empty_out
check_non_empty_err

# Wrong operation name - should be an error
run 5.txt --aaa 2.txt && expected_error
check_empty_out
check_non_empty_err

# Wrong operation name - should be an error
run 5.txt --mmmm 2.txt && expected_error
check_empty_out
check_non_empty_err

# Missing matrix operand - should be an error
run 0.txt --add && expected_error
check_empty_out
check_non_empty_err

run 0.txt 1.txt --add && expected_error
check_empty_out
check_non_empty_err

# Wrong operation name and missing matrix operand - should be an error
run 0.txt --xxx && expected_error
check_empty_out
check_non_empty_err

# Incorrect matrices dimensions for adding - should be an error
run A_3x7.txt --add B_7x13.txt && expected_error
check_empty_out
check_non_empty_err

# Incorrect matrices dimensions for adding - should be an error
run A_3x7.txt --mult B_7x13.txt --add B_7x13.txt && expected_error
check_empty_out
check_non_empty_err

# Incorrect matrices dimensions for multiplication - should be an error
run B_7x13.txt --mult A_3x7.txt && expected_error
check_empty_out
check_non_empty_err

# Incorrect matrices dimensions for multiplication - should be an error
run A_3x7.txt --mult B_7x13.txt --mult A_3x7.txt && expected_error
check_empty_out
check_non_empty_err

# Incorrect matrices dimensions for multiplication - should be an error
run B_7x13.txt --mult 7.txt && expected_error
check_empty_out
check_non_empty_err

# Missing matrix file - should be an error
run 2.txt --add xxx.txt && expected_error
check_empty_out
check_non_empty_err

echo "Smoke test passed!"
