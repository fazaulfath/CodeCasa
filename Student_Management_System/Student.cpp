#include<iostream>
#include<string>
#include<iomanip>
#include<cstdio>
using namespace std;
class Student
{
    public:
        string name;
        string rollNumber;
        double totalScore;
        double pendingAssignmentScores[10];
        string pendingAssignmentNames[10];
        int pendingAssignmentCount = 0;
    public:
        Student(const string& n, const string& r) : name(n), rollNumber(r), totalScore(0.0) {}
        Student() : name(""), rollNumber(""), totalScore(0.0) {}

        void changePersonalInfo(const string& n, const string& r)
        {
            name = n;
            rollNumber = r;
        }

        void viewPendingAssignments() const
        {
            cout << "Pending Assignments: " << pendingAssignmentCount << "\n";
            for (int i = 0; i < pendingAssignmentCount; i++) 
            {
                cout <<"\nAssignment"<<(i+1)<<": "<<pendingAssignmentNames[i]<<"(Score: "<<pendingAssignmentScores[i]<<")\n";
            }
        }

        void submitAssignment(string name)
        {
            pendingAssignmentCount--;
        }

        void takeExamination(const string& examName)
        {
            submitAssignment(examName);        // For simplicity, I am treating examinations the same way as assignments.
        }

        double viewGrade() const
        {
            return totalScore;
        }

        void displayInfo() const
        {
            cout << "Name: " << name << endl;
            cout << "Roll Number: " << rollNumber << endl;
            cout << "Grade: " << totalScore << endl;
            viewPendingAssignments();
        }

        int assign(string& name, double score)
        {
            if (pendingAssignmentCount < 10)
            {
                pendingAssignmentNames[pendingAssignmentCount] = name;
                pendingAssignmentScores[pendingAssignmentCount] = score;
                pendingAssignmentCount++;
            }
            else
            {
                cout << "Cannot assign more tasks. Limit reached.\n";
            }
            return pendingAssignmentCount;   
        }

        int exam(string& name, double score)
        {
            totalScore += score;
            return totalScore;
        }

        void performTasks();
};

class Teacher
{
    protected:
        string TeacherId;
        Student students[10];
        int studentCount;

    public:
        Teacher(const string& Id) : TeacherId(Id), studentCount(0) {}

        void assignTask(Student& student, string name, double score)
        {
            student.assign(name, score);
        }

        void gradeTask(Student& student, string name, double score)
        {
            student.exam(name, score);
        }

        void addStudent(const Student& student)
        {
            if (studentCount < 10)
            {
                students[studentCount] = student;
                studentCount++;
            }
            else
            {
                cout << "Teacher can only manage up to 10 students. Cannot add more students.\n";
            }
        }

        void displayStudentsInfo() const
        {
            cout << "Teacher: " << TeacherId << endl;
            cout << "Students Information: " << endl;
            for (int i = 0; i < studentCount; i++)
            {
                cout << "Student " << (i + 1) << ":\n";
                students[i].displayInfo();
            }
        }

        void performTasks(Student students[], int studentCount);
};

void Student::performTasks()
{
    int choice;
    while (true)
    {
        cout << "\nStudent Menu:\n";
        cout << "1. Change personal information\n";
        cout << "2. Submit an assignment\n";
        cout << "3. Take an examination\n";
        cout << "4. View grade\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
            {
                string newName, newRollNumber;
                cout << "Enter new name: ";
                cin >> newName;
                cout << "Enter new roll number: ";
                cin >> newRollNumber;
                changePersonalInfo(newName, newRollNumber);
                cout << "Data saved successfully\n";
                break;
            }
            case 2:
            {
                double assignmentScore;
                string assignmentName;
                if(pendingAssignmentCount>0)
                {
                    viewPendingAssignments();
                    cout << "Enter assignment name: ";
                    cin >> assignmentName;
                    submitAssignment(assignmentName);
                    cout << "Assignment submitted successfully\n";
                }
                else
                {
                    cout<<"No pending assignment\n";
                }
                break;
            }
            case 3:
            {
                string examName;
                cout << "Enter exam name: ";
                cin >> examName;
                takeExamination(examName);
                cout << "Exam Completed!\n";
                break;
            }
            case 4:
            {
                double currentGrade = viewGrade();
                cout << "Current grade: " << currentGrade << "\n";
                break;
            }
            case 5:
            {
                cout << "Exiting Student Menu...\n";
                return;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

void Teacher::performTasks(Student students[], int studentCount)
{
    int choice;
    while (true)
    {
        cout << "\nTeacher Menu:\n";
        cout << "1. Assign an assignment\n";
        cout << "2. Grade an assignment\n";
        cout << "3. Add or edit student information\n";
        cout << "4. View overall class statistics\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
            {
                double assignmentScore;
                string assignmentName;
                cout << "Enter assignment name: ";
                cin >> assignmentName;
                cout << "Enter assignment score: ";
                cin >> assignmentScore;

                int studentChoice;
                cout << "Select a student to assign the task (1-" << studentCount << "): ";
                cin >> studentChoice;
                
                if (studentChoice >= 1 && studentChoice <= studentCount)
                {
                    assignTask(students[studentChoice - 1], assignmentName, assignmentScore);
                    cout << "Task assigned successfully\n";
                }
                else
                {
                    cout << "Invalid student choice. Please try again.\n";
                }

                break;
            }
            case 2:
            {
                double assignmentScore;
                string assignmentName;
                cout << "Enter assignment name: ";
                cin >> assignmentName;
                cout << "Enter assignment score: ";
                cin >> assignmentScore;

                int studentChoice;
                cout << "Select a student to grade the task (1-" << studentCount << "): ";
                cin >> studentChoice;
                
                if (studentChoice >= 1 && studentChoice <= studentCount)
                {
                    gradeTask(students[studentChoice - 1], assignmentName, assignmentScore);
                    cout << "Marks allotted successfully\n";
                }
                else
                {
                    cout << "Invalid student choice. Please try again.\n";
                }

                break;
            }
            case 3:
            {
                string studentName, rollNumber;
                cout << "Enter student name: ";
                cin >> studentName;
                cout << "Enter student roll number: ";
                cin >> rollNumber;
                Student newStudent(studentName, rollNumber);

                if (studentCount < 10)
                {
                    addStudent(newStudent); // Add the new student to the teacher's list
                    cout << "Student added successfully\n";
                    studentCount++;
                }
                else
                {
                    cout << "Maximum number of students reached. Cannot add more students.\n";
                }

                break;
            }
            case 4:
            {
                displayStudentsInfo();
                break;
            }
            case 5:
            {
                cout << "Exiting Teacher Menu...\n";
                return;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

int main()
{
    Student students[10]; 
    int studentCount = 0;  
    string teacherId;
    students[studentCount] = Student("ABC", "S001");
    studentCount++;
    Teacher teacher("T001");
    system("cls");
    cout << "========WELCOME TO STUDENT MANAGEMENT SYSTEM========\n";
    int choice;
    while (true)
    {
        cout << "\n";
        cout << "1. Student Login\n";
        cout << "2. Teacher Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                system("cls");
                cout<<"========STUDENT LOGIN========\n";
                if(studentCount < 10) 
                {
                    string studentName, studentRollNumber;
                    int studentChoice;
                    cout<<"Enter student name: ";
                    cin>>studentName;
                    cout << "Enter student roll number: ";
                    cin >> studentRollNumber;
                    Student* selectedStudent = nullptr;         // Find the student with the given roll number
                    for (int i = 0; i < studentCount; i++)
                    {
                        if (students[i].rollNumber == studentRollNumber)
                        {
                            selectedStudent = &students[i];
                            break;
                        }
                    }
                    if (selectedStudent != nullptr)
                    {
                        selectedStudent->performTasks();
                    }
                    else
                    {
                        cout << "Student with roll number " << studentRollNumber << " not found.\n";
                    }
                }
                else
                {
                    cout << "Maximum number of students reached. Cannot add more students.\n";
                }
                break;
            }
            case 2:
            {
                system("cls");
                cout<<"========TEACHER LOGIN========\n";
                if (studentCount > 0)
                {
                    teacher.performTasks(students, studentCount);  
                }
                else
                {
                    cout << "No students available. Please add students first.\n";
                }
                break;
            }
            case 3:
            {
                cout << "Exiting the program...\n";
                return 0;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}
