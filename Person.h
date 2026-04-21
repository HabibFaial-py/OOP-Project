#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person {
private:
    string name;
    string id;
    string phone;
    int age;

public:
    Person();
    Person(string name, string id, string phone, int age);
    virtual ~Person() {}

    // Getters
    string getName() const;
    string getId() const;
    string getPhone() const;
    int getAge() const;

    // Setters
    void setName(const string& name);
    void setId(const string& id);
    void setPhone(const string& phone);
    void setAge(int age);

    // Pure virtual function — makes Person abstract
    virtual void displayInfo() const = 0;
};

#endif
