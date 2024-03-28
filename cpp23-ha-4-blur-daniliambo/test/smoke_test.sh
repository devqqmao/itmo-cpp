#!/bin/sh -eu

if [ "$#" -lt 1 ]; then
    echo "Usage:"
    echo "    $0 params"
    exit -1
fi

EXECUTABLE="$1"
REAL_EXEC="$EXECUTABLE"
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
FUZZ_FACTOR="$2"

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

compare_result()
{
    IMG_BASELINE="$SCRIPT_DIR/$2"
    IMG="$1"
    echo "***** Comparing: compare -fuzz "$FUZZ_FACTOR" -metric AE "$IMG_BASELINE" "$IMG" "$IMG.diff.png""
    compare -fuzz "$FUZZ_FACTOR" -metric AE "$IMG_BASELINE" "$IMG" "$IMG.diff.png"
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

# square img radius 1
run -i helena_500x500.bmp -o helena_500x500_out.bmp -r 1 || expected_ok
compare_result helena_500x500_out.bmp helena_500x500_filtered_1.bmp || expected_ok
check_empty_out
check_empty_err

# square img radius 5
run -i helena_500x500.bmp -o helena_500x500_out.bmp -r 5 || expected_ok
compare_result helena_500x500_out.bmp helena_500x500_filtered_5.bmp || expected_ok
check_empty_out
check_empty_err

# square img radius 15
run -i helena_500x500.bmp -o helena_500x500_out.bmp -r 15 || expected_ok
compare_result helena_500x500_out.bmp helena_500x500_filtered_15.bmp || expected_ok
check_empty_out
check_empty_err

# square img radius 45
run -i helena_500x500.bmp -o helena_500x500_out.bmp -r 45 || expected_ok
compare_result helena_500x500_out.bmp helena_500x500_filtered_45.bmp || expected_ok
check_empty_out
check_empty_err

# square img radius 151
run -i helena_500x500.bmp -o helena_500x500_out.bmp -r 151 || expected_ok
compare_result helena_500x500_out.bmp helena_500x500_filtered_151.bmp || expected_ok
check_empty_out
check_empty_err

# args order independence
run -o helena_500x500_out.bmp -r 5 -i helena_500x500.bmp || expected_ok
compare_result helena_500x500_out.bmp helena_500x500_filtered_5.bmp || expected_ok
check_empty_out
check_empty_err

# args order independence
run -r 5 -o helena_500x500_out.bmp -i helena_500x500.bmp || expected_ok
compare_result helena_500x500_out.bmp helena_500x500_filtered_5.bmp || expected_ok
check_empty_out
check_empty_err

# args order independence
run -r 5 -i helena_500x500.bmp -o helena_500x500_out.bmp  || expected_ok
compare_result helena_500x500_out.bmp helena_500x500_filtered_5.bmp || expected_ok
check_empty_out
check_empty_err

# no args - should be an error
run && expected_error
check_empty_out
check_non_empty_err

# wrong radius - should be an error
run -a helena_500x500.bmp -o helena_500x500_out.bmp -r 4 && expected_error
check_empty_out
check_non_empty_err

# wrong radius - should be an error
run -a helena_500x500.bmp -o helena_500x500_out.bmp -r -1 && expected_error
check_empty_out
check_non_empty_err

# wrong radius - should be an error
run -a helena_500x500.bmp -o helena_500x500_out.bmp -r 0 && expected_error
check_empty_out
check_non_empty_err

# wrong operation name - should be an error
run -a helena_500x500.bmp -o helena_500x500_out.bmp -r 5 && expected_error
check_empty_out
check_non_empty_err

# wrong operation name - should be an error
run -i helena_500x500.bmp -a helena_500x500_out.bmp -r 5 && expected_error
check_empty_out
check_non_empty_err

# wrong operation name - should be an error
run -i helena_500x500.bmp -o helena_500x500_out.bmp -a 5 && expected_error
check_empty_out
check_non_empty_err

# not enough args - should be an error
run -i helena_500x500.bmp -o helena_500x500_out.bmp && expected_error
check_empty_out
check_non_empty_err

# not enough args - should be an error
run -i helena_500x500.bmp -o helena_500x500_out.bmp -r && expected_error
check_empty_out
check_non_empty_err

# not enough args - should be an error
run -i helena_500x500.bmp -r 5 && expected_error
check_empty_out
check_non_empty_err

# not enough args - should be an error
run -i helena_500x500.bmp -o -r 5 && expected_error
check_empty_out
check_non_empty_err

# not enough args - should be an error
run -o helena_500x500_out.bmp -r 5 && expected_error
check_empty_out
check_non_empty_err

# not enough args - should be an error
run -i -o helena_500x500_out.bmp -r 5 && expected_error
check_empty_out
check_non_empty_err

echo "Smoke test passed!"
