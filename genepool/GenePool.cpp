#include "GenePool.h"
#include <iostream>
#include <sstream>
#include "Person.cpp"
using namespace std;

// GenePool Member Functions

set<Person*> GenePool::everyone() const{
    set<Person*>allPeople;
    for(auto it=people.begin();it!=people.end();it++){
        allPeople.insert(it->second);
    }
    return allPeople;
}

Person* GenePool::find(const std::string& name) const{
    if(people.count(name) == 0){
        return nullptr;
    }
    return people.find(name)->second;
}

GenePool::GenePool(istream& stream){
    string line;
    while(getline(stream, line)){
        if(line.length() == 0 || line[0] == '#'){
            continue;
        }
        istringstream iss(line);
        string name;
        string gender;
        Gender g;
        if(gender=="male")
            g=Gender::MALE;
        else
            g=Gender::FEMALE;
        string motherName;
        string fatherName;
        getline(iss, name, '\t');
        getline(iss, gender, '\t');
        getline(iss, motherName, '\t');
        Person* mother_;
        if(motherName == "???"){
            mother_ = nullptr;
        }
        else{
            mother_ = people[motherName];}
        

        getline(iss, fatherName, '\t');
        Person* father_;
        if(fatherName == "???"){
            father_ = nullptr;
        }
        else{
            father_ = people[fatherName];}

        Person* person = new Person(name, g, mother_, father_);
        
        people[name]=person;
        if(mother_ != nullptr){
            mother_->addChild(person);
        }
        if(father_ != nullptr){
            father_->addChild(person);
        }


    }
}

GenePool::~GenePool(){
    for(auto& it : people){
        delete it.second;
    }
    people.clear();
}



