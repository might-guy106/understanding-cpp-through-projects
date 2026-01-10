// main.cpp
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <string_view>

std::vector<std::string_view> tokenize(std::string_view sv){
    std::vector<std::string_view> tokens;
    std::size_t start = 0, len = 0;
    for(std::size_t i = 0; i < sv.size(); i++){
        if(sv[i] == ' '){
            if(len != 0){
                tokens.push_back(sv.substr(start, len));
                len = 0;
            }
            start = i + 1;
        } else {
            len++;
        }
    }
    if(len != 0){
        tokens.push_back(sv.substr(start, len));
    }

    return tokens;
}


std::optional<std::pair<int,int>> parse_two_ints(const std::vector<std::string_view>& tokens) {
    if (tokens.size() != 3) {
        std::cout << "Usage: " << tokens[0] << " <int> <int>\n";
        return std::nullopt;
    }
    try {
        std::string str1{tokens[1]};
        int a = std::stoi(str1);
        std::string str2{tokens[2]};
        int b = std::stoi(str2);
        return std::make_pair(a, b);
    } catch (const std::exception&) {
        std::cout << "Invalid input: expected integers\n";
        return std::nullopt;
    }
}

int main() {
  while (true) {
    std::cout << "> ";
    std::string s = "";
    if (!std::getline(std::cin, s)) break;
    if (s == "exit" || s == "quit") {
      break;
    }
    if(s.empty()) continue;

    std::string_view sv{s};
    std::vector<std::string_view> tokens = tokenize(sv);
    if (tokens.empty()) continue;
    std::string_view cmd = tokens[0];
    if (cmd == "echo") {
        for (size_t i = 1; i < tokens.size(); ++i) {
            std::cout << tokens[i] << ' ';
        }
        std::cout << std::endl;
    }
    else if (cmd == "add") {
        if (auto args = parse_two_ints(tokens)) {
            std::cout << args->first + args->second << '\n';
        }
    }
    else if (cmd == "sub") {
        if (auto args = parse_two_ints(tokens)) {
            std::cout << args->first - args->second << '\n';
        }
    }
    else if (cmd == "mul") {
        if (auto args = parse_two_ints(tokens)) {
            std::cout << args->first * args->second << '\n';
        }
    }
    else if (cmd == "div") {
        if (auto args = parse_two_ints(tokens)) {
            if (args->second == 0) {
                std::cout << "Error: division by zero\n";
            } else {
                std::cout << args->first / args->second << '\n';
            }
        }
    }
    else if (cmd == "help") {
        std::cout << "Available commands:\n";
        std::cout << "  echo <text...>\n";
        std::cout << "  add <int> <int>\n";
        std::cout << "  sub <int> <int>\n";
        std::cout << "  mul <int> <int>\n";
        std::cout << "  div <int> <int>\n";
        std::cout << "  help\n";
        std::cout << "  exit | quit\n";
    }
    else{
        std::cout << "Unknown command: " << cmd << "\n";
    }
  }
}
