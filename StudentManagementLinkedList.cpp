#include <iostream>
#include <limits>
#include <sstream>

/**
 * Class that provides access to next pointer and student information: 
 * id, grade, first name, last name, course, and grade
 */
class Node
{
    public: 
        Node *next;
        int id, grade;
        std::string firstName;
        std::string lastName;
        std::string course;
};

/**
 * Class for the linked list which initializes the head and contains methods to
 * add students, search for students, check for duplicate students with the 
 * same id to prevent multiple instances of the same student on file, delete 
 * students, and print student records.
 */
class LL
{
    Node *head;
    public:
        LL()
        {
            head = NULL;
        }
        bool findDuplicate(int id);
        void searchStudent(int id);
        void addStudent(int id, std::string firstName, std::string lastName, 
                        std::string course, int grade);
        void deleteStudent(int id);
        void print();
};

/**
 * Method that finds if a student had already been added to the linked list
 * @param id the id of the student being searched
 * @return true if the student is in the linked list
 * @return false if the student if not in the linked list
 */ 
bool LL::findDuplicate(int id)
{
    //base case: list is empty returns false
    if(head == NULL)
    {
        return false; 
    }
    Node *newNode = new Node();
    newNode = head;
    //iterate through list
    while(newNode != NULL)
    {
        //if id is found, return true
        if(newNode->id == id)
        {
            return true;
        }
        newNode = newNode->next;
    }
    //otherwise, returns false
    return false;
}

/**
 * Method that searches and returns student information
 * @param id the id of the student being searched
 */
void LL::searchStudent(int id)
{
    //base case: list is empty
    if(head == NULL)
    {
        std::cout << "Student not found. \n";
        return;
    }
    //otherwise iterate
    else
    {
        Node* newNode = head;
        while(newNode != NULL)
        {
            //if student id exists in linked list, output information
            if(newNode->id == id)
            {
                std::cout << "Student ID: \t" << newNode->id 
                          << "\nFirst Name: \t" << newNode->firstName 
                          << "\nLast Name: \t" << newNode->lastName 
                          << "\nCourse: \t" << newNode->course 
                          << "\nGrade: \t\t" << newNode->grade << std::endl;
                return;
            }
            newNode = newNode->next;
        }
        //if student information does not exist
        if(newNode == NULL)
        {
            std::cout << "Student not found." << std::endl;
        }
    }
}

/**
 * Method that adds student to the linked list
 * @param id the id of the student
 * @param firstName the first name of the student
 * @param lastName the last name of the student
 * @param course the course the student is in enrolled in
 * @param grade grade student has in course
 */ 
void LL::addStudent(int id, std::string firstName, std::string lastName, 
             std::string course, int grade)
{
    //Student information added to newNode
    Node* newNode = new Node();
    newNode->id = id;
    newNode->firstName = firstName;
    newNode->lastName = lastName;
    newNode->course = course;
    newNode->grade = grade;
    newNode->next = head;

    //base case: linked list is empty
    if(head == NULL)
    {
        newNode->next = head;
        head = newNode;
    }
    //otherwise iterate and add after
    else
    {
        Node* addAfter = head;
        while(addAfter->next != NULL)
        {
            addAfter = addAfter->next;       
        }
        newNode->next = addAfter->next;
        addAfter->next = newNode;
    }
}

/**
 * Method that deletes student from linked list
 * @param id the id of the student
 */
void LL::deleteStudent(int id)
{
    //base case: linked list is empty
    if(head == NULL)
    {
        std::cout << "Student list is empty. \n";
    }
    Node* front = head;
    Node* tail = NULL;
    //otherwise, check if the id is in the front of the linked list
    if(front != NULL && front->id == id)
    {
        head = front->next;
        delete front;
        std::cout << "Student deleted. \n";
        return;
    }
    //if not, iterate through list until end
    while(front != NULL && front->id != id)
    {
        tail = front; 
        front = front->next;
    }
    //if front is equal to NULL, then student is not in list
    if(front == NULL)
    {
        std::cout << "Student not found. \n";
        return;
    }
    //if front is not equal to NULL, then student is in list and is deleted
    else if(front != NULL)
    {
        tail->next = front->next;
        delete front;
        std::cout << "Student deleted. \n";
        return;
    }
}

/**
 * Method that prints out linked list
 */
void LL::print()
{
    Node* node = head;
    //base case: linked list is empty
    if(node == NULL)
    {
        std::cout << "No records on file. \n\n";
    }
    //otherwise, iterate until list is empty and print out its contents
    while(node != NULL)
    {
        std::cout << node->id << " " << node->firstName << " " << node->lastName 
             << " " << node->course << " " << node->grade << " " << std::endl;
        node = node->next;
    }
}

int main()
{
    LL link;
    int id, grade, input;
    std::string firstName;
    std::string lastName;
    std::string course;
    
    while(true)
    {
        std::cout << "Welcome to the Student Management System.\n";
        std::cout << "\n";
        std::cout << "Please select a number from the following options: \n1) "
             << "Add a student record \n2) Find a student record \n3) "
             << "Delete a student record \n4) Print all student records \n"
             << "5) Quit \n\nOption Selected: " << std::endl;
        std::cin >> input;
        std::cout << "\n";
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. \n";
            std::cout << "Please select a number from the following options: \n"
                      << "1) Add a student record \n2) Find a student record \n"
                      << "3) Delete a student record \n4) Print all student "
                      << "records \n5) Quit \n\nOption Selected: " << std::endl;
            std::cin >> input;
        }
        else if(!std::cin.fail())
        {
            if(input == 1)
            {
                std::cout << "ADD STUDENT \nStudent ID: ";
                std::cin >> id;
                if(!(link.findDuplicate(id)))
                {
                    std::cout << "First Name: \n";
                    std::cin >> firstName;
                    if(std::cin.fail())
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. \n";
                    }
                    else if(!std::cin.fail())
                    {
                        std::cout << "Last Name: \n";
                        std::cin >> lastName;
                        std::cout << "Course enrolled in: \n";
                        std::cin >> course;
                        std::cout << "Grade for Course: \n";
                        std::cin >> grade;
                        if(std::cin.fail())
                        {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Invalid input. \n";
                        }
                        else if(!std::cin.fail())
                        {
                            std::cout << "\n";
                            link.addStudent(id, firstName, lastName, course, grade);    
                            std::cout << "Student Added\n" << std::endl;
                        }
                    }
                }
                else
                {
                    std::cout << "Student already in system. \n\n\n";
                }
                
            }
            else if(input == 2)
            {
                std::cout << "STUDENT SEARCH\nPlease enter a Student ID:\t\n";
                std::cin >> id;
                std::cout << "\n";
                link.searchStudent(id);
                std::cout << "\n";
            }
            else if(input == 3)
            {
                std::cout << "DELETE STUDENT\nPlease enter a Student ID: \t\n";
                std::cin >> id;
                std::cout << "\n";
                link.deleteStudent(id);
                std::cout << "\n";
            }
            else if(input == 4)
            {
                std::cout << "PRINT STUDENT RECORDS\n";
                link.print();
                std::cout << "\n";
            }
            else if(input == 5)
            {
                exit(0);
            }
        }
    }
    return 0;
}