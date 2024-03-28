#include <catch2/catch_test_macros.hpp>

#include <lazy_string.hpp>

using namespace std_utils;

TEST_CASE("template_arguments_compiles", "[lazy_str]") {
  [[maybe_unused]] lazy_basic_string<char, std::char_traits<char>> ss1;
  [[maybe_unused]] lazy_basic_string<char> ss2;
  [[maybe_unused]] lazy_basic_string<wchar_t> ss3;

  REQUIRE(true);
}

TEST_CASE("constructors_compiles", "[lazy_str]") {
  [[maybe_unused]] lazy_string s1;
  [[maybe_unused]] lazy_string s2("Test");
  [[maybe_unused]] lazy_string s3 = "Test";
  [[maybe_unused]] lazy_string s4(s3);
  [[maybe_unused]] lazy_string s5(3, 'X');
  [[maybe_unused]] lazy_string const s6(0, 'A');
  [[maybe_unused]] lazy_string const s7;
  [[maybe_unused]] lazy_string s8(s7);

  REQUIRE(true);
}

TEST_CASE("read_only_operations", "[lazy_str]") {
  [[maybe_unused]] lazy_string s1;
  [[maybe_unused]] lazy_string s2("Test");
  [[maybe_unused]] lazy_string s3 = "Test";
  [[maybe_unused]] lazy_string s4(s3);
  [[maybe_unused]] lazy_string s5(3, 'X');
  [[maybe_unused]] lazy_string const s6(0, 'A');

  REQUIRE("Test" == s2);
  REQUIRE(s3 == "Test");
  REQUIRE("Test" == s4);
  REQUIRE(s4.c_str() == s3.c_str());
  REQUIRE(std::string(s4.c_str()) == "Test");
  REQUIRE(s4.size() == 4);
  REQUIRE(s5 == "XXX");
  REQUIRE(s5 != "XXY");
  REQUIRE("XXY" != s5);
  REQUIRE(s5 < "XXx");
  REQUIRE("XX" < s5);
  REQUIRE(s6.empty());
  REQUIRE(s6 == "");
  REQUIRE(s6 == s1);
  REQUIRE(s6.size() == 0);
}

TEST_CASE("modification_operations", "[lazy_str]") {
  [[maybe_unused]] lazy_string s1;
  [[maybe_unused]] lazy_string s2("Test");
  [[maybe_unused]] lazy_string s3 = "Test";
  [[maybe_unused]] lazy_string s4(s3);
  [[maybe_unused]] lazy_string s5(3, 'X');
  [[maybe_unused]] lazy_string const s6(0, 'A');

  s4.swap(s1);
  REQUIRE(s4 == "");
  REQUIRE(s1.c_str() == s3.c_str());
  s4 = "abc";
  s1 = s4;
  REQUIRE(s1.c_str() == s4.c_str());
  REQUIRE(s3 == "Test");
  REQUIRE(s1 == "abc");
  swap(s3, s1);
  swap(s3, s1);
  REQUIRE(s1.c_str() == s4.c_str());

  REQUIRE((s1[0] == 'a'));
  REQUIRE((s1[1] == 'b'));
  REQUIRE((s1[2] == 'c'));
  REQUIRE((s1[3] == 0));
  REQUIRE(s1.c_str() == s4.c_str());

  s1[1] = 'X';
  REQUIRE(s1 == "aXc");
  REQUIRE(s4 == "abc");
  (s1[2] = 'Y') = 'Z';
  REQUIRE(s1 == "aXZ");

  s5 = s4;
  s5 += 'a';
  REQUIRE(s4 == "abc");
  REQUIRE(s5 == "abca");

  s5 += "ABC";
  REQUIRE(s5 == "abcaABC");
  REQUIRE(("[" + s4) + ']' == ('[' + s4) + "]");
  REQUIRE(s4 + s5 == "abcabcaABC");
  REQUIRE(s4 + s5 == s4 + s5);
  REQUIRE(s4 + s5 != s5 + s4);
  REQUIRE(!(s4 < s4));

  s1 = s5;
  s4 = std::move(s5);
  REQUIRE(s4 == "abcaABC");
  REQUIRE(s1.c_str() == s4.c_str());
  s5.size();
  s5.empty();
  std::string(s5.c_str());
}

TEST_CASE("wide_constructors_compiles", "[lazy_str]") {
  [[maybe_unused]] lazy_wstring const ws1;
  [[maybe_unused]] lazy_wstring ws2(L"Тест");
  [[maybe_unused]] lazy_wstring ws3 = L"Тест";
  [[maybe_unused]] lazy_wstring ws4(ws1);
  [[maybe_unused]] lazy_wstring ws5(3, L'Я');

  REQUIRE(true);
}

TEST_CASE("wide_read_only_operations", "[lazy_str]") {
  [[maybe_unused]] lazy_wstring s1;
  [[maybe_unused]] lazy_wstring s2(L"Test");
  [[maybe_unused]] lazy_wstring s3 = L"Test";
  [[maybe_unused]] lazy_wstring s4(s3);
  [[maybe_unused]] lazy_wstring s5(3, L'X');
  [[maybe_unused]] lazy_wstring const s6(0, L'A');

  REQUIRE(L"Test" == s2);
  REQUIRE(s3 == L"Test");
  REQUIRE(L"Test" == s4);
  REQUIRE(s4.c_str() == s3.c_str());
  REQUIRE(std::wstring(s4.c_str()) == L"Test");
  REQUIRE(s4.size() == 4);
  REQUIRE(s5 == L"XXX");
  REQUIRE(s5 != L"XXY");
  REQUIRE(L"XXY" != s5);
  REQUIRE(s5 < L"XXx");
  REQUIRE(L"XX" < s5);
  REQUIRE(s6.empty());
  REQUIRE(s6 == L"");
  REQUIRE(s6 == s1);
  REQUIRE(s6.size() == 0);
}

TEST_CASE("wide_modification_operations", "[lazy_str]") {
  [[maybe_unused]] lazy_wstring s1;
  [[maybe_unused]] lazy_wstring s2(L"Test");
  [[maybe_unused]] lazy_wstring s3 = L"Test";
  [[maybe_unused]] lazy_wstring s4(s3);
  [[maybe_unused]] lazy_wstring s5(3, L'X');
  [[maybe_unused]] lazy_wstring const s6(0, L'A');

  s4.swap(s1);
  REQUIRE(s4 == L"");
  REQUIRE(s1.c_str() == s3.c_str());
  s4 = L"abc";
  s1 = s4;
  REQUIRE(s1.c_str() == s4.c_str());
  REQUIRE(s3 == L"Test");
  REQUIRE(s1 == L"abc");
  swap(s3, s1);
  swap(s3, s1);
  REQUIRE(s1.c_str() == s4.c_str());

  REQUIRE((s1[0] == L'a'));
  REQUIRE((s1[1] == L'b'));
  REQUIRE((s1[2] == L'c'));
  REQUIRE((s1[3] == 0));
  REQUIRE(s1.c_str() == s4.c_str());

  s1[1] = L'X';
  REQUIRE(s1 == L"aXc");
  REQUIRE(s4 == L"abc");
  (s1[2] = L'Y') = L'Z';
  REQUIRE(s1 == L"aXZ");

  s5 = s4;
  s5 += L'a';
  REQUIRE(s4 == L"abc");
  REQUIRE(s5 == L"abca");

  s5 += L"ABC";
  REQUIRE(s5 == L"abcaABC");
  REQUIRE((L"[" + s4) + L']' == (L'[' + s4) + L"]");
  REQUIRE(s4 + s5 == L"abcabcaABC");
  REQUIRE(s4 + s5 == s4 + s5);
  REQUIRE(s4 + s5 != s5 + s4);
  REQUIRE(!(s4 < s4));

  s1 = s5;
  s4 = std::move(s5);
  REQUIRE(s4 == L"abcaABC");
  REQUIRE(s1.c_str() == s4.c_str());
  s5.size();
  s5.empty();
  std::wstring(s5.c_str());
}

TEST_CASE("istring_tests", "[lazy_str]") {
  [[maybe_unused]] lazy_istring const is1;
  [[maybe_unused]] lazy_istring is2("Test");
  [[maybe_unused]] lazy_istring is3 = "Test";
  [[maybe_unused]] lazy_istring is4(is1);
  [[maybe_unused]] lazy_istring is5(3, 'X');

  REQUIRE(is5 == "xxx");
  REQUIRE(!(is5 < "xxx"));
}
