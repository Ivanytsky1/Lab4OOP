#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    Person() : name(), age(0) {}

    Person(const string& name, int age) : name(name), age(age) {}

    virtual void input() {
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
    }

    virtual void output() const {
        cout << "Name: " << name << endl << "Age: " << age << endl;
    }

    Person& operator=(const Person& other) {
        if (this == &other) {
            return *this;
        }
        name = other.name;
        age = other.age;
        return *this;
    }

    virtual void saveToFile(ofstream& file) const {
        if (file.is_open()) {
            file << name << endl;
            file << age << endl;
        }
    }

    virtual void loadFromFile(ifstream& file) {
        if (file.is_open()) {
            getline(file, name);
            file >> age;
            file.ignore(); // Ignore the newline character
        }
    }
};

class Student : public Person {
private:
    string university;

public:
    Student() : university() {}

    Student(const string& name, int age, const string& university)
        : Person(name, age), university(university) {
    }

    void input() override {
        Person::input();
        cout << "Enter university: ";
        cin.ignore(); // Clear any existing newline characters from the input buffer.
        getline(cin, university);
    }

    void output() const override {
        Person::output();
        cout << "University: " << university;
        cout << endl;
    }

    Student& operator=(const Student& other) {
        if (this == &other) {
            return *this;
        }
        Person::operator=(other);
        university = other.university;
        return *this;
    }

    void saveToFile(ofstream& file) const override {
        Person::saveToFile(file);
        if (file.is_open()) {
            file << university << endl;
        }
    }

    void loadFromFile(ifstream& file) override {
        Person::loadFromFile(file);
        if (file.is_open()) {
            getline(file, university);
        }
    }
};

class DiplomaStudent : public Student {
private:
    string thesisTopic;

public:
    DiplomaStudent() : thesisTopic() {}

    DiplomaStudent(const string& name, int age, const string& university, const string& thesisTopic)
        : Student(name, age, university), thesisTopic(thesisTopic) {
    }

    void input() override {
        Student::input();
        cout << "Enter thesis topic: ";
        getline(cin, thesisTopic);
    }

    void output() const override {
        Student::output();
        cout << "Thesis Topic: " << thesisTopic;
    }

    DiplomaStudent& operator=(const DiplomaStudent& other) {
        if (this == &other) {
            return *this;
        }
        Student::operator=(other);
        thesisTopic = other.thesisTopic;
        return *this;
    }

    void saveToFile(ofstream& file) const override {
        Student::saveToFile(file);
        if (file.is_open()) {
            file << thesisTopic << endl;
        }
    }

    void loadFromFile(ifstream& file) override {
        Student::loadFromFile(file);
        if (file.is_open()) {
            getline(file, thesisTopic);
        }
    }
};

int main() {
    DiplomaStudent student;

    // Input student information from the console
    student.input();

    // Save student information to a file
    ofstream outFile("C:/Users/Ivanytsky1/Downloads/student_data.txt");
    if (outFile.is_open()) {
        student.saveToFile(outFile);
        outFile.close();
        cout << "Student data saved to file." << endl;
    }
    else {
        cerr << "Unable to open file for writing." << endl;
        return 1;
    }

    // Load student information from the file
    DiplomaStudent loadedStudent;
    ifstream inFile("C:/Users/Ivanytsky1/Downloads/student_data.txt");
    if (inFile.is_open()) {
        loadedStudent.loadFromFile(inFile);
        inFile.close();

        // Display the loaded student information
        loadedStudent.output();
        cout << endl;
    }
    else {
        cerr << "Unable to open file for reading." << endl;
        return 1;
    }

    return 0;
}
