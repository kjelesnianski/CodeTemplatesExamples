#include <fstream>
#include <string>
#include <vector>

void generateSampleFile(const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    int n = 3; // Number of records
    out.write(reinterpret_cast<const char*>(&n), sizeof(n));

    std::vector<std::pair<std::string, double>> data = {
        {"Alice", 85.5},
        {"Bob", 92.0},
        {"Charlie", 78.5}
    };

    for (const auto& [name, grade] : data) {
        int len = name.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(name.c_str(), len);
        out.write(reinterpret_cast<const char*>(&grade), sizeof(grade));
    }
}

int main() {
    generateSampleFile("input.bin");
    return 0;
}
