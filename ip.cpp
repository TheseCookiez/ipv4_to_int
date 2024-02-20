#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>

/*
 * Source file name: "ipfile"
 * Result file name: "result"
 *
 * Source file must be formatted as single IPv4 string pr. line
 * Result file will be formatted as single IPv4 unsigned int pr. line
 *
 * if using .csv file, remove header first
 */

// Read ip source file into std::vector
std::vector<std::string> get_file_content() {
  std::fstream ipfile("ipfile");
  std::vector<std::string> ip_vec;
  std::string line;
  if (ipfile.is_open()) {
    while (ipfile.good()) {
      std::getline(ipfile, line);
      ip_vec.push_back(line);
    }
  }
  return ip_vec;
}

// Save std:.vector to result file
void save_file_content(std::vector<unsigned int> ip_int_vec) {
  std::ofstream result("result");
  for (const unsigned int &i : ip_int_vec) {
    result << i << "\n";
  }
}

// Convenience func to print std::vector containing strings
void print_vec(std::vector<std::string> ip_vec) {
  for (const std::string &i : ip_vec) {
    std::cout << i << "\n";
  }
}

// Convenience func to print std::vector containing unsigned int
void print_vec_int(std::vector<unsigned int> ip_vec) {
  for (const unsigned int &i : ip_vec) {
    std::cout << i << "\n";
  }
}

// Bitshift voodoo to convert IPv4 string to unsigned int
unsigned int convertIPv4ToInt(const char *ip) {
  unsigned int a, b, c, d;
  sscanf(ip, "%u.%u.%u.%u", &a, &b, &c, &d);
  return (a << 24) | (b << 16) | (c << 8) | d;
}

// Loop the vector and convert each IPv4 to int repr. and push to new vec<int>
std::vector<unsigned int> convert_to_int(std::vector<std::string> ip_vec) {
  std::vector<unsigned int> ip_int_vec;
  for (const std::string i : ip_vec) {
    unsigned int ip_int = convertIPv4ToInt(i.c_str());
    ip_int_vec.push_back(ip_int);
  }
  return ip_int_vec;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> ip_vec = get_file_content();
  // print_vec(ip_vec);
  std::vector<unsigned int> ip_int_vec = convert_to_int(ip_vec);
  std::sort(ip_int_vec.begin(), ip_int_vec.end(), std::less<unsigned int>());
  // print_vec_int(ip_int_vec);
  save_file_content(ip_int_vec);
  return 0;
}
