#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Student {
    std::string name;
    int rollNo;
    std::vector<int> marks;
    int totalMarks;
    int schoolRank;
    int classRank;
};

// Function to calculate the total marks for a student
int calculateTotalMarks(const std::vector<int>& marks) {
    int total = 0;
    for (int mark : marks) {
        total += mark;
    }
    return total;
}

// Function to rank the students based on total marks
void rankStudents(std::vector<Student>& students) {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.totalMarks > b.totalMarks;
    });
    
    int rank = 1;
    for (auto& student : students) {
        student.classRank = rank++;
    }
}

// Function to print student details
void printStudentDetails(const std::vector<Student>& students) {
    for (const auto& student : students) {
        std::cout << "Name: " << student.name << std::endl;
        std::cout << "Roll No: " << student.rollNo << std::endl;
        std::cout << "Total Marks: " << student.totalMarks << std::endl;
        std::cout << "School Rank: " << student.schoolRank << std::endl;
        std::cout << "Class Rank: " << student.classRank << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
}

// Function to write student details to a file
void writeStudentDetails(const std::vector<Student>& students, const std::string& fileName) {
    std::ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        for (const auto& student : students) {
            outputFile << "Name: " << student.name << std::endl;
            outputFile << "Roll No: " << student.rollNo << std::endl;
            outputFile << "Total Marks: " << student.totalMarks << std::endl;
            outputFile << "School Rank: " << student.schoolRank << std::endl;
            outputFile << "Class Rank: " << student.classRank << std::endl;
            outputFile << "----------------------------------------" << std::endl;
        }
        outputFile.close();
        std::cout << "Student details written to file: " << fileName << std::endl;
    } else {
        std::cout << "Unable to open the file: " << fileName << std::endl;
    }
}

int main() {
    std::vector<Student> students;
    
    // Read student details from file(s) and calculate total marks
    std::ifstream inputFile("student_marks.txt");
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::stringstream ss(line);
            Student student;
            ss >> student.name >> student.rollNo;
            int mark;
            while (ss >> mark) {
                student.marks.push_back(mark);
            }
            student.totalMarks = calculateTotalMarks(student.marks);
            students.push_back(student);
        }
        inputFile.close();
    } else {
        std::cout << "Unable to open the file: student_marks.txt" << std::endl;
        return 1;
    }
    
    // Rank the students
    rankStudents(students);
    
    // Set school ranks
    int schoolRank = 1;
    for (auto& student : students) {
        student.schoolRank = school