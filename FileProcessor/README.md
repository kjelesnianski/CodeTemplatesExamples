C++11 Programming Assignment: File Processor with Smart Pointers and Lambda FunctionsObjectiveCreate a C++11 program that processes a binary file containing records of student grades, performs modifications based on user-defined criteria, and outputs a summary. The program must demonstrate the use of smart pointers, lambda functions, standard library file operations, initialization lists, and other C++11 features such as range-based for loops and auto.Assignment RequirementsProgram Description:The program reads a binary file containing student records (name and grade).
It applies a user-defined transformation to the grades (e.g., scaling or filtering) using a lambda function.
It writes the modified records to a new binary file.
It generates a summary of the processed data (e.g., average grade, highest grade).
The program must use smart pointers to manage memory, initialization lists for data structures, and standard library functions for file operations.

Student Record Structure:Define a Student class with:A std::string for the student's name.
A double for the student's grade (0.0 to 100.0).
An initialization list constructor.
A method to print the student's details.

Use std::shared_ptr<Student> to manage Student objects.

File Format:The input binary file contains:A 4-byte integer n (number of records).
n records, each with:A 4-byte integer len (length of the name string).
len bytes for the name (ASCII characters, no null terminator).
An 8-byte double for the grade.

The output binary file follows the same format but contains modified records.

Processing Requirements:Read the input binary file using std::ifstream.
Store student records in a std::vector<std::shared_ptr<Student>>.
Use a lambda function to define a grade transformation (e.g., scale grades by a factor or cap them at a threshold).
Write the modified records to an output binary file using std::ofstream.
Compute a summary (average grade and highest grade) using std::accumulate and a lambda function.
Use std::sort with a lambda function to sort students by grade in descending order for display.

C++11 Features to Include:Smart Pointers: Use std::shared_ptr for managing Student objects.
Lambda Functions: For grade transformation and sorting criteria.
Standard Library File Operations: Use std::ifstream and std::ofstream for binary file I/O.
Initialization Lists: For constructing Student objects and initializing data structures.
Other Features: Use auto, range-based for loops, std::vector, std::accumulate, and std::sort.

Error Handling:Check for file open failures and invalid data (e.g., negative grades).
Use exceptions to handle errors gracefully.

Deliverables:A complete C++11 program (main.cpp).
A sample binary input file generator (optional, for testing).
A report (comments or separate document) explaining how each C++11 feature is used.

Tasks for CompletionImplement and Test:Complete the FileProcessor class to handle all requirements.
Test with various input files, including edge cases (empty file, invalid grades).

Extend Functionality:Add a lambda function option to filter out students with grades below a threshold.
Allow the user to specify the transformation lambda via command-line input (e.g., scale factor).

Documentation:Comment the code to explain where each C++11 feature is used.
Write a brief report (or include in comments) describing how smart pointers, lambdas, file operations, initialization lists, and other features are implemented.

Evaluation CriteriaCorrect use of std::shared_ptr for memory management.
Proper implementation of lambda functions for transformations and sorting.
Robust binary file reading/writing with error handling.
Use of initialization lists in constructors and data structures.
Effective use of auto, range-based for loops, std::accumulate, and std::sort.
Code clarity, organization, and documentation.

Example OutputFor an input file with students {Alice, 85.5}, {Bob, 92.0}, {Charlie, 78.5} and a scaling factor of 1.1:

Average Grade: 88.83
Highest Grade: 100.0 (Bob)
Sorted Students:
Name: Bob, Grade: 100.0
Name: Alice, Grade: 94.05
Name: Charlie, Grade: 86.35


