#include "Person.h"
#include "Enums.h"
using namespace std;

// Person Member Functions
Person::Person(const string& name, Gender gender,Person* mother_, Person* father_){
    this->name_ = name;
    this->gender_ = gender;
    this->mother_ = mother_;
    this->father_ = father_;
 }
Person::Person(){
    name_ = "";
    gender_ = Gender::ANY;
    mother_ = nullptr;
    father_ = nullptr;
}

Person::~Person(){
    if(mother_){
        mother_->children_.erase(this);
        }
    if(father_){
        father_->children_.erase(this);
    }

    for(auto child : children_){
        if(child->mother_ == this){
            child->mother_ = nullptr;
        }
        if(child->father_ == this){
            child->father_= nullptr;
        }
    }
}

void Person::addChild(Person* child){
    children_.insert(child) ;
}

const std::string& Person::name()   const{
    return name_;
}

Gender Person::gender() const{
    return gender_;
}

Person* Person::mother(){
    return mother_;
}

Person* Person::father(){
    return father_;
}

set<Person*> Person::parents(PMod pmod) {
    set<Person*> parents;
    if (father_ != nullptr && pmod != PMod::MATERNAL) {
        parents.insert(father_);
    }
    if (mother_ != nullptr && pmod != PMod::PATERNAL) {
        parents.insert(mother_);
    }
    return parents;
}

set<Person*> Person::grandfathers(PMod pmod) {
    set<Person*> grandf;
    if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        if (mother_ != nullptr && mother_->father_ != nullptr) {
            grandf.insert(mother_->father_);
        }
    }
    if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        if (father_ != nullptr && father_->father_ != nullptr) {
            grandf.insert(father_->father_);
        }
    }
    return grandf;
}

set<Person*> Person::grandmothers(PMod pmod) {
    set<Person*> grandm;
    if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        if (mother_ != nullptr && mother_->mother_ != nullptr) {
            grandm.insert(mother_->mother_);
        }
    }
    if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        if (father_ != nullptr && father_->mother_ != nullptr) {
            grandm.insert(father_->mother_);
        }
    }
    return grandm;
}

set<Person*> Person::grandparents(PMod pmod) {
    set<Person*> gps;
    set<Person*> grandf = grandfathers(pmod);
    set<Person*> grandm = grandmothers(pmod);
    gps.insert(grandf.begin(), grandf.end());
    gps.insert(grandm.begin(), grandm.end());
    return gps;
}

set<Person*> Person::children() {
    return children_;
}

set<Person*> Person::daughters() {
    set<Person*> daughters;
    for (auto child : children_) {
        if (child->gender_ == Gender::FEMALE) {
            daughters.insert(child);
        }
    }
    return daughters;
}

set<Person*> Person::sons() {
    set<Person*> sons;
    for (auto child : children_) {
        if (child->gender_ == Gender::MALE) {
            sons.insert(child);
        }
    }
    return sons;
}

set<Person*> Person::grandchildren() {
    set<Person*> grandc;
    for (auto child : children_) {
        grandc.insert(child->children_.begin(), child->children_.end());
    }
    return grandc;
}

set<Person*> Person::grandsons() {
    set<Person*> grands;
    for (auto child : children_) {
        for(auto grandchild : child ->children_){
            if(grandchild->gender_ == Gender::MALE){
                grands.insert(grandchild);
            }
        }
    }
    return grands;
}

set<Person*> Person::granddaughters(){
    set<Person*> grandd;
    for (auto child : children_) {
        for(auto grandchild : child->children_){
            if(grandchild->gender_ == Gender::FEMALE){
                grandd.insert(grandchild);
            }
        }
    }
    return grandd;
}

set<Person*> Person::siblings(PMod pmod, SMod smod) {
    set<Person*> allsiblings;
    for(Person* parent: parents(pmod)) {
        allsiblings.merge(parent->children());
    }

    // Filter siblings by FULL/HALF/WHATEVER
    
    set<Person*> siblings;
    for(Person* sibling: allsiblings) {
        int shared = 0; // count shared parents
        if(mother_ != nullptr && sibling->mother() == mother()) {
            shared += 1;
        }
        if(father_ != nullptr && sibling->father() == father()) {
            shared += 1;
        }
        
        // do we want this sibling?
        if(shared == 1) {
            if(smod != SMod::FULL) {
                siblings.insert(sibling);
            }
        }
        else {
            if(pmod == PMod::MATERNAL){
                if(smod == SMod::FULL){
                    for(Person* childs: mother_->children_){
                        if(childs!= this&& childs->father_ == father_){
                            siblings.insert(childs);
                        }
                    }
                }
                else if(smod == SMod::HALF){
                    for(Person* childs: mother_->children_){
                        if(childs!= this && childs->father_ != father_){
                            siblings.insert(childs);
                        }
                    }
                }
                else{
                    for(Person* childs: mother_->children_){
                        if(childs!= this){
                            siblings.insert(childs);
                        }
                    }
                }

            }
            else if(pmod == PMod::PATERNAL){
                if(smod == SMod::FULL){
                    for(Person* childs: father_->children_){
                        if(childs!= this&& childs->mother_ == mother_){
                            siblings.insert(childs);
                        }
                    }
                }
                else if(smod == SMod::HALF){
                    for(Person* childs: father_->children_){
                        if(childs!= this&& childs->mother_ != mother_){
                            siblings.insert(childs);
                        }
                    }
                }
                else{
                    for(Person* childs: father_->children_){
                        if(childs!= this){
                            siblings.insert(childs);
                        }
                    }
                }
            }
            else{
                if(smod == SMod::FULL){
                    for(Person* childs: mother_->children_){
                        if(childs!= this && childs->father_ == father_){
                            siblings.insert(childs);
                        }
                    }
                    for(Person* childs: father_->children_){
                        if(childs!= this && childs->mother_ == mother_){
                            siblings.insert(childs);
                        }
                    }
                }
                else if(smod == SMod::HALF){
                    for(Person* childs: mother_->children_){
                        if(childs!= this && childs->father_ != father_){
                            siblings.insert(childs);
                        }
                    }
                    for(Person* childs: father_->children_){
                        if(childs!= this && childs->mother_ != mother_){
                            siblings.insert(childs);
                        }
                    }
                }
                else{
                    for(Person* childs: mother_->children_){
                        if(childs!= this){
                            siblings.insert(childs);
                        }
                    }
                    for(Person* childs: father_->children_){
                        if(childs!= this){
                            siblings.insert(childs);
                        }
                    }
                }
            }
        }
    }
    
    siblings.erase(this);
    return siblings;
    
}

set<Person*> Person::brothers(PMod pmod, SMod smod) {
    set<Person*> bros;
    set<Person*> sibs = siblings(pmod, smod);
    for (auto sib : sibs) {
        if (sib->gender_ == Gender::MALE) {
            bros.insert(sib);
        }
    }
    return bros;
}

set<Person*> Person::sisters(PMod pmod, SMod smod){
    set<Person*> sis;
    set<Person*> sibs = siblings(pmod,smod);
    for(auto sib : sibs){
        if(sib->gender_ == Gender::FEMALE && sib != this){
            sis.insert(sib);
        }
    }
    return sis;
}

set<Person*> Person::nieces(PMod pmod, SMod smod) {
    set<Person*> nie;
    for (auto sib : siblings(pmod, smod)) {
        for (auto child : sib->children_) {
            if (child->gender_ == Gender::FEMALE) {
                nie.insert(child);
            }
        }
    }
    return nie;
}

set<Person*> Person::nephews(PMod pmod, SMod smod) {
    set<Person*> nep;
    for (auto sib : siblings(pmod, smod)) {
        for (auto child : sib->children_) {
            if (child->gender_ == Gender::MALE) {
                nep.insert(child);
            }
        }
    }
    return nep;
}

set<Person*> Person::aunts(PMod pmod, SMod smod){
    set<Person*> aunts;

    set<Person*> parents = this->parents(pmod);

    for(auto parent : parents){
        set<Person*> siblings = parent->siblings(PMod::ANY, smod);
        for(auto sibling : siblings){
            if(sibling->gender() == Gender::FEMALE){
                aunts.insert(sibling);
            }
        }
    }

    return aunts;
}


set<Person*> Person::uncles(PMod pmod, SMod smod){
    set<Person*> uncls;

    set<Person*> parents = this->parents(pmod);

    for(auto parent : parents){
        set<Person*> siblings = parent->siblings(PMod::ANY, smod);
        for(auto sibling : siblings){
            if(sibling->gender() == Gender::MALE){
                uncls.insert(sibling);
            }
        }
    }

    return uncls;
}

set<Person*> Person::cousins(PMod pmod, SMod smod) {
  set<Person*> cousins;
  set<Person*> parentsSet = parents(pmod);
  set<Person*> grandparentsSet = grandparents(pmod);
  for (auto grandparent : grandparentsSet) {
    set<Person*> siblingsSet = grandparent->siblings(pmod, smod);
    for (auto sibling : siblingsSet) {
      set<Person*> childrenSet = sibling->children();
        if (childrenSet.find(this) != childrenSet.end()) {
            for (auto child : childrenSet) {
                if (child != this) {
                    cousins.insert(child);}
            }
        }
    }
  }
 return cousins;
}

set<Person*> Person::descendants() {
  set<Person*> descendants;
  set<Person*> children = this->children();
  for (auto child : children) {
    descendants.insert(child);
    set<Person*> grandChildren = child->descendants();
    descendants.insert(grandChildren.begin(), grandChildren.end());
  }
  return descendants;
}

set<Person*> Person::ancestors(PMod pmod) {
  set<Person*> ancestors;
  if (pmod == PMod::ANY || pmod == PMod::MATERNAL || pmod == PMod::ANY) {
    if (mother_) {
      ancestors.insert(mother_);
      set<Person*> mother_ancestors = mother_->ancestors();
      ancestors.insert(mother_ancestors.begin(), mother_ancestors.end());
    }
  }
  if (pmod == PMod::ANY || pmod == PMod::PATERNAL || pmod == PMod::ANY) {
    if (father_) {
      ancestors.insert(father_);
      set<Person*> father_ancestors = father_->ancestors();
      ancestors.insert(father_ancestors.begin(), father_ancestors.end());
    }
  }
  return ancestors;
}







