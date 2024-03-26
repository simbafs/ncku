#include <fstream>
#include <iostream>
#include <string>

int KMP(std::string str, std::string pat) {
  // std::cout << "str " << str << std::endl;
  // std::cout << "pat " << pat << std::endl;

  int s = str.length();
  int p = pat.length();

  // if str end with non-ascii character, correct the string length
  while (str[s] == '\0' || str[s] == '\n' || str[s] == '\r') {
    s--;
  }
  while (pat[p] == '\0' || pat[p] == '\n' || pat[p] == '\r') {
    p--;
  }

  int failure[p];

  // compute failure function
  failure[0] = -1;
  for (int j = 1; j < p; j++) {
    int i = failure[j - 1];
    while ((pat[j] != pat[i + 1]) && (i >= 0)) {
      i = failure[i];
    }
    if (pat[j] == pat[i + 1]) {
      failure[j] = i + 1;
    } else {
      failure[j] = -1;
    }
  }

  // print failure function
  for (int i = 0; i < p; i++) {
    // std::cout << failure[i] << " " << pat[i] << std::endl;
  }

  // matching
  int i = 0;
  int j = 0;
  while ((i < s) && (j < p)) {
    if (str[i] == pat[j]) {
      // std::cout << "match " << str[i] << " " << pat[j] << std::endl;
      // std::cout << "i " << i << " j " << j << std::endl;
      // std::cout << std::endl;
      i++;
      j++;
    } else if (j == 0) {
      // std::cout << "mismatch 1 " << str[i] << " " << pat[j] << std::endl;
      // std::cout << "i " << i << " j " << j << std::endl;
      // std::cout << std::endl;
      i++;
    } else {
      // std::cout << "mismatch 2 " << str[i] << " " << pat[j] << std::endl;
      // std::cout << "i " << i << " j " << j << std::endl;
      // std::cout << std::endl;
      j = failure[j - 1] + 1;
    }
  }

  // for (int i = 0; i < s ; i++) {
  //   std::cout << str[i];
  // }
  // std::cout << std::endl;
  //
  // for (int j = 0; j < p; j++) {
  //   std::cout << pat[j];
  // }
  // std::cout << std::endl;

  // std::cout << "j " << j << " p " << p << std::endl;

  return (j == p) ? i - p : -1;
}

int main() {
  std::ifstream input("input.txt");
  std::ofstream output("output.txt");

  std::string str, pat;
  std::string line;

  if (input.is_open()) {
    while (getline(input, line)) {
      if (line.length() == 0)
        continue;

      if (line[0] == 'S') { // string
        str = line.substr(2);
      } else if (line[0] == 'P') { // pattern
        pat = line.substr(2);
      }

      if (str.length() > 0 && pat.length() > 0) {
        int r = KMP(str, pat);
        // std::cout << "result " << r << std::endl;
        output << r << std::endl << std::endl;
        str.clear();
        pat.clear();
      }
    }
    input.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }

  return 0;
}
