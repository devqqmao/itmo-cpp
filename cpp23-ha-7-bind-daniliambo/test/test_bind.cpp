#include <catch2/catch_test_macros.hpp>

#include <bind.hpp>

#include <functional>
#include <memory>
#include <string>
#include <type_traits>

//! Tests for fn::bind. Based on tests for boost::bind.
//! http://www.boost.org/doc/libs/1_55_0/libs/function/test/

namespace {

int global_int;
size_t res = 0;
std::string res_str;

void void_f_void() { res = 10; }

int int_f_void() { return 11; }

[[maybe_unused]] int int_f_void2() { return 12; }

std::string string_f_void() { return "string_f_void"; }

int const_int_f_void() { return 31; }

std::string string_const_f_void() { return "string_const_f_void"; }

void *void_ptr_f_void() { return reinterpret_cast<void *>(20); }

int *int_ptr_f_void() { return reinterpret_cast<int *>(21); }

std::string *string_ptr_f_void() { return reinterpret_cast<std::string *>(22); }

std::string const * string_const_ptr_const_f_void() {
  return reinterpret_cast<std::string *>(52);
}

std::string &string_ref_f_void() { return res_str; }

std::string const &string_const_ref_f_void() { return res_str; }

void assign_five(int &v) { v = 5; }

void rvalue_assign_six(int &&v) { v = 6; }

void rvalue_assign_six_and_test(int &&v, std::string &&s) {
  v = 6;
  s = "test";
}

std::string const *rvalue_const(std::string const &&s) { return &s; }

[[maybe_unused]] std::string const *rvalue_const(std::string &&) { return nullptr; }

int const *pass_const_reference(int const &v) { return &v; }

int &&return_rvalue() { return std::move(global_int); }

int const &&return_const_rvalue() { return std::move(global_int); }

int &return_reference() { return global_int; }

int const &return_const_reference() { return global_int; }

[[maybe_unused]] double assign_five_and_eight(int &a, double &b) {
  a = 5;
  b = 8;

  return a + b;
}

[[maybe_unused]] double assign_one_and_two(int &a, double &b) {
  a = 1;
  b = 2;

  return a + b;
}

void assign_five_and_test(int &v, std::string &s) {
  v = 5;
  s = "test";
}

char *void_f_char_array(char s[3]) {
  s[0] = 'a';
  s[1] = 'b';
  s[2] = 0;

  return s;
}

typedef int (*int_f_void_ptr_t)(void);

int_f_void_ptr_t func_ptr(int_f_void_ptr_t f) { return f; }

double double_f_double(double x) { return x; }

long f_0() { return 17041L; }

long f_1(long a) { return a; }

long f_2(long a, long b) { return a + 10 * b; }

long global_result;

void fv_0() { global_result = 17041L; }

void fv_1(long a) { global_result = a; }

void fv_2(long a, long b) { global_result = a + 10 * b; }

template <class R, class Func> R call(Func f) { return f(); }

template <class R, class Func, class Arg> R call1(Func f, Arg a) {
  return f(a);
}

template <class R, class Func, class Arg1, class Arg2>
R call2(Func f, Arg1 a1, Arg2 a2) {
  return f(a1, a2);
}

int type(int &&) { return 0; }
int type(int const &&) { return 1; }
int type(int &) { return 2; }
int type(int const &) { return 3; }

std::string string_copy(std::string const &s) { return s; }

std::unique_ptr<int> move_unique_ptr(std::unique_ptr<int> up) {
  return up;
}

int sum_unique_ptr(std::unique_ptr<int> up1, std::unique_ptr<int> up2) {
  return *up1 + *up2;
}

} // namespace

// #define USE_STD
#if !defined(USE_STD)
namespace n = fn;
using fn::_1;
using fn::_2;
#else
namespace n = std;
using std::placeholders::_1;
using std::placeholders::_2;
#endif

TEST_CASE("return_types", "[bind]") {
  res = 0;
  n::bind(&void_f_void)();
  REQUIRE(res == 10);

  REQUIRE(n::bind(&int_f_void)() == 11);
  REQUIRE(n::bind(&string_f_void)() == "string_f_void");
  REQUIRE(n::bind(&const_int_f_void)() == 31);
  REQUIRE(n::bind(&string_const_f_void)() == "string_const_f_void");
  REQUIRE(n::bind(&void_ptr_f_void)() == reinterpret_cast<void *>(20));
  REQUIRE(n::bind(&int_ptr_f_void)() == reinterpret_cast<int *>(21));
  REQUIRE(n::bind(&string_ptr_f_void)() == reinterpret_cast<std::string *>(22));
  REQUIRE(n::bind(&string_const_ptr_const_f_void)() == reinterpret_cast<std::string *>(52));

  std::string & s1 = n::bind(&string_ref_f_void)();
  REQUIRE(&res_str == &s1);

  // TODO: check that result is const
  auto f2 = n::bind(&string_const_ref_f_void);
  std::string const & s2 = f2();
  REQUIRE(&res_str == &s2);
}

TEST_CASE("placeholders", "[bind]") {
  struct C
  {
  } c;

  //n::bind(&f_2); // shouldn't compile
  //n::bind(&f_2, 1); // shouldn't compile
  REQUIRE(n::bind(&f_2, 1, 2)() == 21);
  REQUIRE(n::bind(&f_2, 1, 2)(c) == 21);
  REQUIRE(n::bind(&f_2, 1, 2)(c, 6.0) == 21);
  //REQUIRE(n::bind(&f_2, 1, _1)() == 21); // shouldn't compile
  REQUIRE(n::bind(&f_2, 1, _1)(2) == 21);
  REQUIRE(n::bind(&f_2, 1, _1)(2, c) == 21);
  REQUIRE(n::bind(&f_2, _1, 1)(2) == 12);
  REQUIRE(n::bind(&f_2, _1, 1)(2, c) == 12);
  REQUIRE(n::bind(&f_2, 2, _2)(2, 1) == 12);
  REQUIRE(n::bind(&f_2, 2, _2)(c, 1) == 12);
  REQUIRE(n::bind(&f_2, _2, 1)(c, 2) == 12);
  REQUIRE(n::bind(&f_2, _2, _2)(c, 2) == 22);
  //n::bind(&f_2, _1, _2)(1); // shouldn't compile
  REQUIRE(n::bind(&f_2, _1, _2)(1, 2) == 21);
  REQUIRE(n::bind(&f_2, _2, _1)(1, 2) == 12);
  //n::bind(&f_2, _1, _1)(); // shouldn't compile
  REQUIRE(n::bind(&f_2, _1, _1)(3) == 33);
  REQUIRE(n::bind(&f_2, _1, _1)(3, c) == 33);
}

TEST_CASE("pass_reference", "[bind]") {
  int x;
  std::string s;

  x = 0;
  n::bind(&assign_five, _1)(x);
  REQUIRE(x == 5);

  x = 0;
  n::bind(&assign_five, std::ref(x))();
  REQUIRE(x == 5);

  x = 0;
  s.clear();
  n::bind(&assign_five_and_test, _1, _2)(x, s);
  REQUIRE((x == 5 && s == "test"));

  x = 0;
  s.clear();
  n::bind(&assign_five_and_test, _2, _1)(s, x);
  REQUIRE((x == 5 && s == "test"));

  x = 0;
  s.clear();
  n::bind(&assign_five_and_test, std::ref(x), _1)(s);
  REQUIRE((x == 5 && s == "test"));

  x = 0;
  s.clear();
  n::bind(&assign_five_and_test, _1, std::ref(s))(x);
  REQUIRE((x == 5 && s == "test"));

  x = 0;
  s.clear();
  n::bind(&assign_five_and_test, std::ref(x), std::ref(s))();
  REQUIRE((x == 5 && s == "test"));
}

TEST_CASE("pass_rvalue_reference", "[bind]") {
  int x;
  std::string s;

  x = 0;
  n::bind(&rvalue_assign_six, _1)(std::move(x));
  REQUIRE(x == 6);

  x = 0;
  s.clear();
  n::bind(&rvalue_assign_six_and_test, _1, _2)(std::move(x), std::move(s));
  REQUIRE((x == 6 && s == "test"));

  x = 0;
  s.clear();
  n::bind(&rvalue_assign_six, _1)(std::move(x), std::move(5));
  REQUIRE(x == 6);

  std::string const s2;
  REQUIRE(n::bind((std::string const * (*)(std::string const &&))&rvalue_const, _1)(std::move(s2)) == &s2);
}

TEST_CASE("return_types_2", "[bind]") {
  REQUIRE(type(n::bind(&return_rvalue)()) == 0);
  REQUIRE(type(n::bind(&return_const_rvalue)()) == 1);
  REQUIRE(type(n::bind(&return_reference)()) == 2);
  REQUIRE(type(n::bind(&return_const_reference)()) == 3);
}

TEST_CASE("pass_object_without_copy_constructor", "[bind]") {
  std::unique_ptr<int> up;

  REQUIRE(n::bind(&int_f_void)(up) == 11);
  REQUIRE(n::bind(&int_f_void)(up, up) == 11);
  REQUIRE(n::bind(&f_1, _1)(1, up) == 1);
  REQUIRE(n::bind(&f_1, _2)(up, 1) == 1);

  up.reset(new int(7));
  REQUIRE(*n::bind(&move_unique_ptr, _1)(std::move(up)) == 7);

  std::unique_ptr<int> up1(new int(2));
  std::unique_ptr<int> up2(new int(3));
  REQUIRE(n::bind(&sum_unique_ptr, _1, _2)(std::move(up1), std::move(up2)) == 5);
}

TEST_CASE("pass_primitive_types", "[bind]") {
  char s[3];

  s[0] = 0;
  REQUIRE(n::bind(&void_f_char_array, _1)(s) == s);
  REQUIRE(std::string(s) == "ab");

  s[0] = 0;
  REQUIRE(n::bind(&void_f_char_array, s)() == s);
  REQUIRE(std::string(s) == "ab");

  REQUIRE(n::bind(&func_ptr, &int_f_void)() == &int_f_void);
  REQUIRE(n::bind(&func_ptr, _1)(&int_f_void) == &int_f_void);

  REQUIRE(n::bind(&double_f_double, 0.25f)() == 0.25);

  int const & x = 5;
  REQUIRE(n::bind(&pass_const_reference, _1)(x) == &x);

  auto f = n::bind(&string_copy, std::string(8000, 'A'));
  std::string tmp(8000, 'B');
  REQUIRE(f() == std::string(8000, 'A'));
}

TEST_CASE("copy_constructor", "[bind]") {
  auto f1 = n::bind(&int_f_void);
  REQUIRE(call<int>(f1) == 11);
  REQUIRE(call<int>(std::move(f1)) == 11);

  auto f2 = n::bind(&f_1, _1);
  REQUIRE(call1<long>(f2, 3) == 3);

  auto f3 = n::bind(&f_2, _1, _2);
  REQUIRE(call2<long>(f3, 3, 4) == 43);
}

TEST_CASE("std_bind_cannot_be_copied", "[bind]") {
#if !defined(USE_STD)
  auto f1 = n::bind(&int_f_void);
  REQUIRE(f1() == 11);

  auto f2 = n::bind(&int_f_void2);
  REQUIRE(f2() == 12);

  f1 = f2;
  REQUIRE(f1() == 12);
  REQUIRE(f2() == 12);

  f1 = f1;
  REQUIRE(f1() == 12);

  int a, c;
  double b, d;

  a = b = 0;
  auto f3 = n::bind(&assign_five_and_eight, std::ref(a), _1);
  REQUIRE((f3(b) == 13 && a == 5 && b == 8));

  c = d = 0;
  auto f4 = n::bind(&assign_one_and_two, std::ref(c), _1);
  REQUIRE((f4(d) == 3 && c == 1 && d == 2));

  auto tmp = f3;
  f3 = f4;
  f4 = tmp;

  a = b = 0;
  c = d = 0;
  REQUIRE((f3(d) == 3 && c == 1 && d == 2));
  REQUIRE((f4(b) == 13 && a == 5 && b == 8));
#else
  REQUIRE(true);
#endif // !defined(USE_STD)
}

TEST_CASE("move", "[bind]") {
  auto f1 = n::bind(&int_f_void);
  REQUIRE(f1() == 11);
  
  auto f2 = std::move(f1);
  REQUIRE(f2() == 11);
}

TEST_CASE("boost_tests", "[bind]") {
  int const i = 1;

  REQUIRE(n::bind(f_0)(i) == 17041L);
  REQUIRE(n::bind(f_1, _1)(i) == 1L);
  REQUIRE(n::bind(f_2, _1, 2)(i) == 21L);

  REQUIRE((n::bind(fv_0)(i), (global_result == 17041L)));
  REQUIRE((n::bind(fv_1, _1)(i), (global_result == 1L)));
  REQUIRE((n::bind(fv_2, _1, 2)(i), (global_result == 21L)));
}
