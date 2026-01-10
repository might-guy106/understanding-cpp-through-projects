// main.cpp
#include <iostream>
#include <string>
#include <vector>
#include <optional>

std::vector<std::string> tokenize(const std::string& s){
    std::vector<std::string> tokens;
    std::string token;
    for (char c : s) {
        if (c == ' ') {
            if (token.size() != 0) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += c;
        }
    }
    if (token.size() != 0) {
        tokens.push_back(token);
    }
    return tokens;
}


std::optional<std::pair<int,int>> parse_two_ints(const std::vector<std::string>& tokens) {
    if (tokens.size() != 3) {
        std::cout << "Usage: " << tokens[0] << " <int> <int>\n";
        return std::nullopt;
    }
    try {
        int a = std::stoi(tokens[1]);
        int b = std::stoi(tokens[2]);
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

    std::vector<std::string> tokens = tokenize(s);
    if (tokens.empty()) continue;
    std::string cmd = tokens[0];
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
