#include <iostream>                                                                                                                         
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <numeric>
#include <stdexcept>

#include "FileProcessor_cj.hpp"

/* The parameter n is a std::string passed by value. When initializing the member
 * name (also a std::string), using std::move(n) enables move semantics instead of
 * copying.  Without std::move, the std::string n would be copied into name, which
 * involves allocating new memory and copying the string's contents. This is
 * expensive, especially for large strings.  std::move(n) casts n to an rvalue
 * reference (std::string&&), allowing the name member to take ownership of n's
 * internal buffer via the std::string move constructor. This avoids unnecessary
 * copying and is more efficient (typically O(1) vs. O(n) for copying)
 */
Student::Student(std::string n, double g) : 
    name(std::move(n)),
    grade(g)
{
  if(grade < 0 || grade > 100) {
    throw std::invalid_argument("Grade must be 0-100");
  }
}

void Student::print() const {
  std::cout << "Name: " << name << ", Grade: " << grade << std::endl;
}

void FileProcessor::readFile(const std::string& filename){
  // create an input file stream and read in binary mode
  std::ifstream in(filename, std::ios::binary);
  if(!in) {
    std::cerr << "Cannot open file: " << filename << std::endl;
  }

  int n;
  // reads a 4-byte integer n from the beginning of the file, which specifies
  // the number of student records.
  in.read(reinterpret_cast<char*>(&n), sizeof(n));
  students.reserve(n);

  for(int i = 0; i < n ; ++i) {
    int len;
    // Reads the 4-byte integer len specifying the length of the student’s name.
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    // Creates a std::string called name with len characters, initialized to null bytes ('\0').
    std::string name(len, '\0');
    // read in the name to the name string variable
    in.read(&name[0], len);

    double grade;
    // use reinterpret_cast to treat &grade as a char* for in.read
    in.read(reinterpret_cast<char*>(&grade), sizeof(grade));

    students.push_back(std::make_shared<Student>(name, grade));
  }
}

void FileProcessor::transformGrades(const std::function<double(double)>& transform){
  for(auto& student : students) {
    student->grade = transform(student->grade);
  }
}

void FileProcessor::writeFile(const std::string& filename){
  std::ofstream out(filename, std::ios::binary);
  if(!out) {
    throw std::runtime_error("Cannot open output file: " + filename);
  }

  int n = students.size();
  out.write(reinterpret_cast<const char*>(&n), sizeof(n));
  for(const auto& student : students) {
    int len = student->name.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(student->name.c_str(), len);
    out.write(reinterpret_cast<const char*>(&student->grade), sizeof(student->grade));
  }
}

void FileProcessor::printSummary(){
  if(students.empty()) {
    std::cout << "No students" << std::endl;
    return;
  }

  double avg = std::accumulate(students.begin(), students.end(), 0.0,
    [](double sum, const auto& s) {return sum + s->grade;}) / students.size();

  auto max_it = std::max_element(students.begin(), students.end(),
    [](const auto& a, const auto& b) {return a->grade < b->grade;});

  std::cout << "Avg  Grade: " << avg << std::endl;
  std::cout << "High Grade: " << (*max_it)->grade << " (" << (*max_it)->name << ")" << std::endl;
}

void FileProcessor::displaySorted(){
  std::sort(students.begin(), students.end(),[](const auto& a, const auto& b){return a->grade > b->grade;});

  for(const auto& student : students) {
    student->print();
  }
}
