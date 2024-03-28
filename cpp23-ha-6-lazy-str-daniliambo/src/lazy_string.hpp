#pragma once
#include <memory>

namespace std_utils {
namespace details {

template <typename CharT, typename Traits> struct string_data {
  std::unique_ptr<CharT[]> data;
  size_t data_size;

  string_data(const CharT *c_str) : data(nullptr), data_size(0) {
    auto size = Traits::length(c_str);
    if (size > 0) {
      data = std::make_unique<CharT[]>(size + 1);
      Traits::copy(data.get(), c_str, size);
      data[size] = Traits::to_char_type(0);
      data_size = size;
    }
  }

  string_data() : data(std::make_unique<CharT[]>(1)), data_size(0) {
    CharT *dest = data.get();
    *dest = Traits::to_char_type(0);
  }

  string_data(const size_t size, const CharT character)
      : data(std::make_unique<CharT[]>(size + 1)), data_size(size) {
    CharT *dest = data.get();
    Traits::assign(dest, size, character);
    dest += size;
    *dest = Traits::to_char_type(0);
  }

  string_data(const string_data &str_data)
      : data(std::make_unique<CharT[]>(str_data.data_size + 1)),
        data_size(str_data.data_size) {
    CharT *dest = data.get();
    Traits::copy(dest, str_data.data.get(), str_data.data_size);
    dest += str_data.data_size;
    *dest = Traits::to_char_type(0);
  }

  string_data(const string_data &str_data1, const string_data &str_data2)
      : data(std::make_unique<CharT[]>(str_data1.data_size +
                                       str_data2.data_size + 1)),
        data_size(str_data1.data_size + str_data2.data_size) {
    CharT *dest = data.get();
    Traits::copy(dest, str_data1.data.get(), str_data1.data_size);
    dest += str_data1.data_size;
    Traits::copy(dest, str_data2.data.get(), str_data2.data_size);
    dest += str_data2.data_size;
    *dest = Traits::to_char_type(0);
  }

  string_data &operator=(const string_data &str_data) {
    if (this != &str_data) {
      auto new_data = std::make_unique<CharT[]>(str_data.data_size + 1);
      Traits::copy(new_data.get(), str_data.data.get(), str_data.data_size);
      new_data[str_data.data_size] = Traits::to_char_type(0);
      data = std::move(new_data);
      data_size = str_data.data_size;
    }
    return *this;
  }
  void set_char(size_t i, CharT character) { data[i] = character; }
};



struct ci_char_traits : public std::char_traits<char> {
  static bool lt(char c1, char c2) {
    return std::toupper(c1) < std::toupper(c2);
  }

  static bool eq(char c1, char c2) {
    return std::toupper(c1) == std::toupper(c2);
  }

  static int compare(const char *s1, const char *s2, size_t n) {
    while (n-- != 0) {
      char c1 = std::toupper(*s1++);
      char c2 = std::toupper(*s2++);
      if (c1 != c2) {
        return c1 < c2 ? -1 : 1;
      }
    }
    return 0;
  }
};

}; // namespace details
// to change


template <typename CharT, typename Traits = std::char_traits<CharT>>
class lazy_basic_string {
private:
  struct proxy {
    lazy_basic_string<CharT, Traits> *str;
    size_t pos;

    proxy(lazy_basic_string<CharT, Traits> *str, size_t pos)
        : str(str), pos(pos) {}

    proxy &operator=(const CharT &rhs) {
      str->data_ = std::make_shared<details::string_data<CharT, Traits>>(
          *str->data_.get());
      (*str->data_.get()).set_char(pos, rhs);
      return *this;
    }
    operator const CharT &() const {
      return const_cast<const lazy_basic_string<CharT, Traits> &>(*str)[pos];
    }
  };

public:
  typedef Traits traits_type;
  typedef typename Traits::char_type value_type;

  lazy_basic_string(const lazy_basic_string<CharT, Traits> &str) {
    data_ = str.data_;
  }
  lazy_basic_string(const CharT *c_str) {
    data_ = std::make_shared<details::string_data<CharT, Traits>>(
        details::string_data<CharT, Traits>(c_str));
  }
  lazy_basic_string(const size_t size, const CharT character) {
    data_ =
        std::make_shared<details::string_data<CharT, Traits>>(size, character);
  }

  lazy_basic_string(const details::string_data<CharT, Traits> &data) {
    data_ = std::make_shared<details::string_data<CharT, Traits>>(data);
  }

  lazy_basic_string<CharT, Traits> &operator=(const CharT *c_str) {
    this->data_ = std::make_shared<details::string_data<CharT, Traits>>(c_str);
    return *this;
  }
  lazy_basic_string() {
    data_ = std::make_shared<details::string_data<CharT, Traits>>();
  }

  lazy_basic_string &operator=(const lazy_basic_string<CharT, Traits> &str) {
    this->data_ = str.data_;
    return *this;
  }

  void operator+=(const lazy_basic_string<CharT, Traits> &str) {
    *this = *this + str;
  }
  lazy_basic_string<CharT, Traits>
  operator+(const lazy_basic_string<CharT, Traits> &str) const {
    return lazy_basic_string<CharT, Traits>(details::string_data<CharT, Traits>(
        *this->data_.get(), *str.data_.get()));
  }

  void operator+=(const CharT *c_str) {
    *this = *this + lazy_basic_string<CharT, Traits>(
                        details::string_data<CharT, Traits>(c_str));
  }

  void operator+=(const CharT character) {
    *this = *this + lazy_basic_string<CharT, Traits>(
                        details::string_data<CharT, Traits>(1, character));
  }
  bool operator==(const lazy_basic_string<CharT, Traits> &other) const {
    if (data_ == other.data_) {
      return true;
    }
    if (data_->data_size != other.data_->data_size) {
      return false;
    }
    return traits_type::compare(data_->data.get(), other.data_->data.get(),
                                data_->data_size) == 0;
  }
  bool operator<(const lazy_basic_string<CharT, Traits> &other) const {
    if (data_ == other.data_) {
      return false;
    }

    auto check_result = traits_type::compare(
        data_->data.get(), other.data_->data.get(),
        std::min(data_->data_size, other.data_->data_size));
    if (check_result < 0) {
      return true;
    }
    if (check_result > 0) {
      return false;
    }
    return data_->data_size < other.data_->data_size;
  }

  bool operator==(const CharT *c_str) const {
    if (data_->data_size != traits_type::length(c_str)) {
      return false;
    }
    return traits_type::compare(data_->data.get(), c_str, data_->data_size) ==
           0;
  }
  bool operator!=(const lazy_basic_string<CharT, Traits> &other) const {
    return !(*this == other);
  }
  bool operator!=(const CharT *c_str) const { return !(*this == c_str); }

  bool operator<(const CharT *c_str) const {
    auto compare_result = traits_type::compare(
        data_->data.get(), c_str,
        std::min(data_->data_size, traits_type::length(c_str)));
    if (compare_result < 0) {
      return true;
    }
    if (compare_result > 0) {
      return false;
    }
    return data_->data_size < traits_type::length(c_str);
  }

  const CharT &operator[](const size_t i) const { return data_->data[i]; }

  proxy operator[](const size_t i) { return proxy(this, i); }

  void swap(lazy_basic_string<CharT, Traits> &other) {
    auto tmp = other.data_;
    other.data_ = this->data_;
    this->data_ = tmp;
  };

  CharT *c_str() const { return data_->data.get(); }

  size_t size() const { return this->data_->data_size; }
  bool empty() const { return this->data_->data_size == 0; }

  void clear() {
    data_ = std::make_shared<details::string_data<CharT, Traits>>();
  }

private:
  std::shared_ptr<details::string_data<CharT, Traits>> data_;
};

template <typename CharT, typename Traits>
lazy_basic_string<CharT, Traits>
operator+(const lazy_basic_string<CharT, Traits> &str, const CharT *c_str) {
  return (str + lazy_basic_string<CharT, Traits>(
                    details::string_data<CharT, Traits>(c_str)));
}

template <typename CharT, typename Traits>
lazy_basic_string<CharT, Traits>
operator+(const lazy_basic_string<CharT, Traits> &str, const CharT character) {
  return str + lazy_basic_string<CharT, Traits>(
                   details::string_data<CharT, Traits>(1, character));
}

template <typename CharT, typename Traits>
bool operator!=(const CharT *c_str,
                const lazy_basic_string<CharT, Traits> &str) {
  return str != c_str;
}

template <typename CharT, typename Traits>
lazy_basic_string<CharT, Traits>
operator+(CharT character, const lazy_basic_string<CharT, Traits> &str) {
  return str + character;
}
template <typename CharT, typename Traits>
lazy_basic_string<CharT, Traits>
operator+(const CharT *c_str, lazy_basic_string<CharT, Traits> &str) {
  return str + c_str;
}

template <typename CharT, typename Traits>
bool operator==(const CharT *c_str,
                const lazy_basic_string<CharT, Traits> &str) {
  return str == c_str;
}

template <typename CharT, typename Traits>
void swap(lazy_basic_string<CharT, Traits> &str1,
          lazy_basic_string<CharT, Traits> &str2) {
  str1.swap(str2);
}

template <typename CharT, typename Traits>
bool operator<(const CharT *c_str,
               const lazy_basic_string<CharT, Traits> &str) {
  return !(str < c_str) && str != c_str;
}

typedef lazy_basic_string<wchar_t> lazy_wstring;
typedef lazy_basic_string<char> lazy_string;
typedef lazy_basic_string<char, details::ci_char_traits> lazy_istring;

} // namespace std_utils