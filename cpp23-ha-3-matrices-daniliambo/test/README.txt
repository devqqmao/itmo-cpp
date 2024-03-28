To run matrices smoke test you need POSIX compatible shell
(bash + awk will be enough).

1. Build your solution. Locate executable file, e.g. ./matrices
2. Run smoke_test with path to your solution executable:

./smoke_test.sh ./matrices

3. Check output for unexpected errors.

If you have valgrind you can enable it by uncommenting line in the
./smoke_test.sh that marked accordingly.
