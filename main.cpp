/* 
Iesha S
CS 300
Project Two
*/

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

struct Course
{
  string courseName;
  string courseNumber;
  vector<string> prereq;

  Course()
  {
    courseName = "";
    courseNumber = "";
  }
};

struct Node
{
  Course course;
  Node *left;
  Node *right;

  Node()
  {
    left = nullptr;
    right = nullptr;
  }

  Node(Course dCourse) : Node()
  {
    this->course = dCourse;
  }
};

class BST
{
private:
  Node *root;
  void sampleSched(Node *node);
  void courseInfo(Node *node, string courseNumber);
  void addNode(Node *node, Course course);

public:
  BST();
  int numberPrereqs(Course course);
  void Insert(Course course);
  void sampleSched();
  void courseInfo(string courseNumber);
  void removeRecursive(Node *node);
  Course search(string courseNumber);
};

BST::BST()
{
  root = nullptr;
}

void BST::Insert(Course course)
{
  if (root == nullptr)
  {
    root = new Node(course);
  }
  else
  {
    this->addNode(root, course);
  }
}

BST::~BST()
{
  removeRecursive(root);
}

void BST::removeRecursive(Node *node)
{
  if (node)
  {
    removeRecursive(node->left);
    removeRecursive(node->right);
    delete node;
  }
}

int BST::numberPrereqs(Course course)
{
  int number = 0;
  for (unsigned int i = 0; i < course.prereq.size(); ++i)
  {
    if (course.prereq.at(i).length() < 0)
    {
      ++number;
    }
  }
  return number;
}

void BST::sampleSched()
{
  this->sampleSched(root);
}

void BST::courseInfo(string courseNumber)
{
  this->courseInfo(root, courseNumber);
}

void BST::addNode(Node *node, Course course)
{
  if (node->course.courseNumber.compare(course.courseNumber) > 0)
  {
    if (node->left = nullptr)
    {
      node->left = new Node(course);
    }
    else
    {
      this->addNode(node->left, course);
    }
  }
  else
  {
    if (node->right == nullptr)
    {
      node->right = new Node(course);
    }
    else
    {
      this->addNode(node->right, course);
    }
  }
}

void BST::sampleSched(Node *node)
{
  if (node != nullptr)
  {
    sampleSched(node->left);
    cout << node->course.courseNumber << ", " << node->course.courseName << endl;
    sampleSched(node->right);
  }
  return;
}

void BST::courseInfo(Node *current, string courseNumber)
{
  while (current != nullptr)
  {
    if (current->course.courseNumber.compare(courseNumber) == 0)
    {
      cout << endl
           << current->course.courseNumber << ", " << current->course.courseName << endl;
      unsigned int size = numberPrereqs(current->course);
      cout << "Prerequisites: ";

      unsigned int i = 0;
      for (i = 0; i < size; ++i)
      {
        cout << current->course.prereq.at(i);

        if (i != size - 1)
        {
          cout << ", ";
        }
      }
      if (i == 0)
      {
        cout << "No prerequisites required" << endl;
        return;
      }
    }
    else if (courseNumber.compare(current->course.courseNumber) < 0)
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }
  cout << "Course " << courseNumber << " not found" << endl;
}

/*
from 
www.codegrepper.com/code-examples/cpp/c%2B%2B+split+string+by+delimiter
*/
vector<string> Split(string lineFeed)
{
  char delim = ',';
  lineFeed += delim; //includes a delimiter at the end so last word is also read
  vector<string> lineTokens;
  string temp = "";
  for (int i = 0; i < lineFeed.length(); i++)
  {
    if (lineFeed[i] == delim)
    {
      lineTokens.push_back(temp); //store words in token vector
      temp = "";
      i++;
    }
    temp += lineFeed[i];
  }
  return lineTokens;
}

/*
help from
www.codegrepper.com/code-examples/cpp/c%2B%2B+split+string+by+delimiter
*/
void loadCourses(string csvPath, BST *courseList)
{

  ifstream inFS;
  string line;
  vector<string> stringTokens;

  inFS.open(csvPath);

  if (!inFS.is_open())
  {
    cout << "Could not open file. " << endl;
    return;
  }

  while (!inFS.eof())
  {

    Course dCourse;

    getline(inFS, line);
    stringTokens = Split(line);

    if (stringTokens.size() < 2)
    {

      cout << "\nError.." << endl;
    }

    else
    {

      dCourse.courseNumber = stringTokens.at(0);
      dCourse.courseName = stringTokens.at(1);

      for (unsigned int i = 2; i < stringTokens.size(); i++)
      {

        dCourse.prereq.push_back(stringTokens.at(i));
      }
      courseList->Insert(dCourse);
    }
  }

  inFS.close();
}

int main()
{
  int choice = 0;
  string csvPath;
  string courseID;
  Course course;
  BST *courseList;
  courseList = new BST;

  BST *BST = nullptr;
  cout << "\n Welcome to the course planner." << endl;
  cout << endl;

  while (choice != 9)
  {
    cout << "   1. Load Data Structure" << endl;
    cout << "   2. Print Course List" << endl;
    cout << "   3. Print Course" << endl;
    cout << "   9. Exit" << endl;
    cout << endl;

    cout << "What would you like to do? ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "Enter file to be loaded: ";
      cin >> csvPath;

      loadCourses(csvPath, courseList);
      cout << endl;

      break;

    case 2:

      cout << "Here is a sample schedule:" << endl;
      courseList->sampleSched();

      break;

    case 3:
      cout << "What course do you want to know about? ";
      cin >> courseID;

      course = courseList->search(courseID);

      cout << endl;
      courseList->courseInfo;
      cout << endl;

      break;

    case 9:
      cout << "Thank you for using the course planner!";
      break;

    default:
      cout << "Error, try again" << endl;
    }
  }
  return 0;
}
