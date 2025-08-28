#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <numeric>
#include <stdexcept>

class Student {
public:
    std::string name;
    double grade;

    // Constructor with initialization list
    Student(std::string n, double g) : name(std::move(n)), grade(g) {
        if (grade < 0.0 || grade > 100.0) {
            throw std::invalid_argument("Grade must be between 0.0 and 100.0");
        }
    }

    void print() const {
        std::cout << "Name: " << name << ", Grade: " << grade << '\n';
    }
};

class FileProcessor {
private:
    std::vector<std::shared_ptr<Student>> students;

public:
    // Read binary file
    void readFile(const std::string& filename) {
        std::ifstream in(filename, std::ios::binary);
        if (!in) {
            throw std::runtime_error("Cannot open input file: " + filename);
        }

        int n;
        in.read(reinterpret_cast<char*>(&n), sizeof(n));
        students.reserve(n);

        for (int i = 0; i < n; ++i) {
            int len;
            in.read(reinterpret_cast<char*>(&len), sizeof(len));
            std::string name(len, '\0');
            in.read(&name[0], len);
            double grade;
            in.read(reinterpret_cast<char*>(&grade), sizeof(grade));
            students.push_back(std::make_shared<Student>(name, grade));
        }
    }

    // Apply transformation using lambda
    void transformGrades(const std::function<double(double)>& transform) {
        for (auto& student : students) {
            student->grade = transform(student->grade);
        }
    }

    // Write to binary file
    void writeFile(const std::string& filename) {
        std::ofstream out(filename, std::ios::binary);
        if (!out) {
            throw std::runtime_error("Cannot open output file: " + filename);
        }

        int n = students.size();
        out.write(reinterpret_cast<const char*>(&n), sizeof(n));
        for (const auto& student : students) {
            int len = student->name.size();
            out.write(reinterpret_cast<const char*>(&len), sizeof(len));
            out.write(student->name.c_str(), len);
            out.write(reinterpret_cast<const char*>(&student->grade), sizeof(student->grade));
        }
    }

    // Compute summary
    void printSummary() {
        if (students.empty()) {
            std::cout << "No students to summarize.\n";
            return;
        }

        double avg = std::accumulate(students.begin(), students.end(), 0.0,
            [](double sum, const auto& s) { return sum + s->grade; }) / students.size();

        auto max_it = std::max_element(students.begin(), students.end(),
            [](const auto& a, const auto& b) { return a->grade < b->grade; });

        std::cout << "Average Grade: " << avg << '\n';
        std::cout << "Highest Grade: " << (*max_it)->grade << " (" << (*max_it)->name << ")\n";
    }

    // Sort and display students
    void displaySorted() {
        std::sort(students.begin(), students.end(),
            [](const auto& a, const auto& b) { return a->grade > b->grade; });

        for (const auto& student : students) {
            student->print();
        }
    }
};

int main() {
    try {
        FileProcessor processor;

        // Read input file
        processor.readFile("input.bin");

        // Example lambda: Scale grades by 1.1, cap at 100.0
        auto scale = [](double g) { return std::min(g * 1.1, 100.0); };
        processor.transformGrades(scale);

        // Write to output file
        processor.writeFile("output.bin");

        // Print summary
        processor.printSummary();

        // Display sorted students
        std::cout << "\nSorted Students:\n";
        processor.displaySorted();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
