#include "Person.h"
using namespace std;

Person::Person() : name(""), id(""), phone(""), age(0) {}

Person::Person(string name, string id, string phone, int age)
    : name(name), id(id), phone(phone), age(age) {}

string Person::getName()  const { return name; }
string Person::getId()    const { return id; }
string Person::getPhone() const { return phone; }
int    Person::getAge()   const { return age; }

void Person::setName(const string& n)  { name  = n; }
void Person::setId(const string& i)    { id    = i; }
void Person::setPhone(const string& p) { phone = p; }
void Person::setAge(int a)             { age   = a; }
