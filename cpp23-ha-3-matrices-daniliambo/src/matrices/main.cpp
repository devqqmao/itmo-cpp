#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::string;
using std::vector;

struct Holder {
  Holder(const vector<double> &mat, int n1, int m1)
      : mat(mat), n1(n1), m1(m1) {}
  vector<double> mat;
  int n1, m1;
};

std::queue<std::string> process_parameters(int argc, char **argv) {
  if ((argc == 1) || (argc > 2 && argc % 2 == 1)) {
    throw std::invalid_argument("invalid amount of arguments");
  };

  std::queue<std::string> q;
  for (int i = 1; i < argc; ++i) {
    q.push(argv[i]);
  }
  return q;
}
//
auto read_matrix(const string &path) {

  if (!(std::filesystem::exists(path))) {
    throw std::invalid_argument("invalid path");
  };

  int m, n;
  std::ifstream f(path);
  f >> n >> m;
  vector<double> mat;
  mat.reserve(n * m);

  for (int i = 0; i < n * m; i++) {
    double el;
    f >> el;
    mat.push_back(el);
  }

  Holder holder(mat, n, m);
  return holder;
}

void print_out(const vector<double> &mat, int n, int m) {

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << mat[m * i + j] << ' ';
    }
    cout << '\n';
  }
}

vector<double> sum_matrix(const vector<double> &mat1,
                          const vector<double> &mat2, int n1, int m1, int n2,
                          int m2) {
  vector<double> mat;
  mat.reserve(n1 * m1);

  if (n1 != n2 || m1 != m2) {
    throw std::invalid_argument("n1 != n2 || m1 != m2");
  }

  for (int i = 0; i < n1; i++) {
    for (int j = 0; j < m1; j++) {
      double el;
      el = mat1[m1 * i + j] + mat2[m2 * i + j];
      mat.push_back(el);
    }
  }
  return mat;
}
vector<double> mul_matrix(const vector<double> &mat1,
                          const vector<double> &mat2, int n1, int m1, int n2,
                          int m2) {
  if (n2 != m1) {
    throw std::invalid_argument("n2 != m1");
  }

  // n2 == m1

  vector<double> mat;
  mat.reserve(n1 * m1);

  for (int i = 0; i < n1; ++i) {
    for (int j = 0; j < m2; ++j) {
      double sum = 0;
      for (int k = 0; k < n2; ++k) {
        double el;
        el = mat1[m1 * i + k] * mat2[m2 * k + j];
        sum += el;
      }
      mat.push_back(sum);
    }
  }
  return mat;
}

auto solve(std::queue<std::string> &q) {

  vector<double> mat1;
  vector<double> mat2;

  string op;
  int n1, m1, n2, m2;

  try {
    auto res = read_matrix(q.front());
    mat1 = std::move(res.mat);
    n1 = res.n1;
    m1 = res.m1;
    q.pop();
  } catch (const std::invalid_argument &e) {
    throw std::invalid_argument("argc == 1");
  };

  while (q.size() > 1) {

    op = q.front();
    q.pop();

    auto res = read_matrix(q.front());
    mat2 = std::move(res.mat);
    n2 = res.n1;
    m2 = res.m1;

    q.pop();

    if (op == "--add") {
      mat1 = sum_matrix(mat1, mat2, n1, m1, n2, m2);
    } else if (op == "--mult") {
      mat1 = mul_matrix(mat1, mat2, n1, m1, n2, m2);
      m1 = m2;
    } else {
      throw std::invalid_argument("not --add or --mult");
    }
  }
  Holder holder(mat1, n1, m1);
  return holder;
}

// convert matrix to str
int print_matrix(const vector<double> &mat, int n, int m) {
  cout << n << " " << m << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << mat[m * i + j] << ' ';
    }
    cout << '\n';
  }
  return 0;
}

int main(int argc, char **argv) {
  vector<double> mat1;
  int n1, m1;
  std::queue<string> q;

  try {
    q = process_parameters(argc, argv);
  } catch (const std::invalid_argument &e) {
    std::cerr << e.what() << endl;
    return 1;
  };

  try {
    auto res = solve(q);
    mat1 = std::move(res.mat);
    n1 = res.n1;
    m1 = res.m1;
  } catch (const std::invalid_argument &e) {
    std::cerr << e.what() << endl;
    return 1;
  };
  print_matrix(mat1, n1, m1);
  return 0;
}
