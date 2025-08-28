#include <iostream>                                                                                                                         
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <functional>

class Student {
public:
  Student(std::string n, double g);
  /* const member function
   * The const keyword tells the compiler to enforce that no member variables
   * are modified within print. If you accidentally try to modify name or grade
   * inside print, the compiler will issue an error.
   */
  void print() const;
  std::string name;
  double grade;
private:
};

class FileProcessor {
private:
  std::vector<std::shared_ptr<Student>> students;

public:
  /* Pass by reference
   */
  void readFile(const std::string& filename);
  void transformGrades(const std::function<double(double)>& transform);
  void writeFile(const std::string& filename);
  void printSummary();
  void displaySorted();
}; 
