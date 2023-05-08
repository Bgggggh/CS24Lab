#include "Person.h"
#include "Enums.h"

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
    if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        parents.insert(mother_);
    }
    if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        parents.insert(father_);
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
        if (child->gender_ == Gender::MALE) {
            grands.insert(child->children_.begin(), child->children_.end());
        }
    }
    return grands;
}

set<Person*> Person::granddaughters(){
    set<Person*> grandd;
    for(auto child : children_){
        if(child->gender_ == Gender::FEMALE){
            grandd.insert(child->children_.begin(), child->children_.end());
        }
    }
    return grandd;
}

set<Person*> Person::siblings(PMod pmod, SMod smod) {
    set<Person*> siblings;
    if (mother_ != nullptr) {
        for (auto child : mother_->children_) {
            if (child != this && child->gender_ == gender_) {
                if (smod == SMod::FULL || (smod == SMod::HALF && mother_ == child->mother_ && father_ == child->father_)) {
                    siblings.insert(child);
                }
            }
        }
    }
    if (father_ != nullptr) {
        for (auto child : father_->children_) {
            if (child != this && child->gender_ == gender_) {
                if (smod == SMod::FULL || (smod == SMod::HALF && mother_ == child->mother_ && father_ == child->father_)) {
                    siblings.insert(child);
                }
            }
        }
    }
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
        if(sib->gender_ == Gender::FEMALE){
            sis.insert(sib);
        }
    }
    return sis;
}

set<Person*> Person::nieces(PMod pmod, SMod smod) {
    set<Person*> nie;
    set<Person*> siblings_ = siblings(pmod, SMod::ANY);
    for (auto sib : siblings_) {
        set<Person*> children_ = sib->children_;
        for (auto child : children_) {
            if (child->gender_ == Gender::FEMALE) {
                if (smod == SMod::FULL && child->mother_ == mother_ && child->father_ == father_) {
                    nie.insert(child);
                } else if (smod == SMod::HALF && (child->mother_ == mother_ || child->father_ == father_)) {
                    nie.insert(child);
                } else if (smod == SMod::ANY) {
                    nie.insert(child);
                }
            }
        }
    }
    return nie;
}

set<Person*> Person::nephews(PMod pmod, SMod smod) {
    set<Person*> nep;
    set<Person*> siblings_ = siblings(pmod, SMod::ANY);
    for (auto sib : siblings_) {
        set<Person*> children_ = sib->children_;
        for (auto child : children_) {
            if (child->gender_ == Gender::MALE) {
                if (smod == SMod::FULL && child->mother_ == mother_ && child->father_ == father_) {
                    nep.insert(child);
                } else if (smod == SMod::HALF && (child->mother_ == mother_ || child->father_ == father_)) {
                    nep.insert(child);
                } else if (smod == SMod::ANY) {
                    nep.insert(child);
                }
            }
        }
    }
    return nep;
}

set<Person*> Person::aunts(PMod pmod, SMod smod) {
  std::set<Person*> aunts;
  if (mother_ != nullptr) {
    std::set<Person*> motherSiblings = mother_->siblings(pmod, smod);
    for (Person* aunt : motherSiblings) {
      if (aunt->gender() == Gender::FEMALE) {
        aunts.insert(aunt);
      }
    }
  }
  if (father_ != nullptr) {
    std::set<Person*> fatherSiblings = father_->siblings(pmod, smod);
    for (Person* aunt : fatherSiblings) {
      if (aunt->gender() == Gender::FEMALE) {
        aunts.insert(aunt);
      }
    }
  }

  return aunts;
}

set<Person*> Person::uncles(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) {
  std::set<Person*> unc;
  if (mother_ != nullptr) {
    std::set<Person*> motherSiblings = mother_->siblings(pmod, smod);
    for (Person* uncl : motherSiblings) {
      if (uncl->gender() == Gender::MALE) {
        unc.insert(uncl);
      }
    }
  }
  if (father_ != nullptr) {
    std::set<Person*> fatherSiblings = father_->siblings(pmod, smod);
    for (Person* uncl : fatherSiblings) {
      if (uncl->gender() == Gender::MALE) {
        unc.insert(uncl);
      }
    }
  }
  return unc;
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







