#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

class AIDebugger {
public:
    void loadCode(const std::string& filename);
    void analyzeCode();
    void reportIssues();

private:
    std::vector<std::string> codeLines;
    std::vector<std::string> issues;

    void checkSemicolons(int lineNum, const std::string& line);
    void checkBrackets();
};

void AIDebugger::loadCode(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        codeLines.push_back(line);
    }
    file.close();
}

void AIDebugger::analyzeCode() {
    for (size_t i = 0; i < codeLines.size(); ++i) {
        checkSemicolons(i + 1, codeLines[i]);
    }
    checkBrackets();
}

void AIDebugger::checkSemicolons(int lineNum, const std::string& line) {
    std::regex pattern(R"((int|float|double|char|bool|std::string)\s+\w+\s*[^;{]*$)");
    if (std::regex_search(line, pattern) && line.find(";") == std::string::npos) {
        issues.push_back("Line " + std::to_string(lineNum) + ": Possible missing semicolon.");
    }
}

void AIDebugger::checkBrackets() {
    int open = 0, close = 0;
    for (size_t i = 0; i < codeLines.size(); ++i) {
        for (char ch : codeLines[i]) {
            if (ch == '{') open++;
            if (ch == '}') close++;
        }
    }
    if (open != close) {
        issues.push_back("Bracket mismatch: { = " + std::to_string(open) + ", } = " + std::to_string(close));
    }
}

void AIDebugger::reportIssues() {
    if (issues.empty()) {
        std::cout << "✅ No issues found.\n";
    } else {
        std::cout << "⚠️ Issues detected:\n";
        for (const auto& issue : issues) {
            std::cout << " - " << issue << "\n";
        }
    }
}

int main() {
    AIDebugger debugger;
    debugger.loadCode("sample.cpp");  // Replace with your file
    debugger.analyzeCode();
    debugger.reportIssues();
    return 0;
}
