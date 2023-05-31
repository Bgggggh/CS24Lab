#include "Dictionary.h"
#include <cctype>
#include <queue>
// #include <stack>
#include "Errors.h"

double func(std::string from,std::string to){
    double result=0;
    for(size_t i=0;i<from.size();i++){
        result=result+pow((double)from.at(i)-(double)to.at(i),2);
    }
    return sqrt(result);
}

struct Node{
    double i;
    std::string cur;
    std::string pa;
    Node(const std::string& cu,const std::string& p,const std::string& to){
        cur=cu;
        pa=p;
        i=func(cur,to);
    }

};
bool operator>(Node a, Node b){
    return a.i>b.i;
}

struct Word{
  bool isWord;
  std::string wo;
  Word* pa;
  std::vector<Word*> ch;
  Word(){
    isWord=false;
    pa=nullptr;
    wo="";
    for(int i=0;i<26;i++){
      ch.push_back(nullptr);
    }
  }

};

void freeW(Word* word){
  for(size_t i=0;i<26;i++){
    if(word->ch.at(i)!=nullptr){
      freeW(word->ch.at(i));
    }
  }
 free(word);
}

Dictionary::Dictionary(std::istream& stream){
    std::string line;
    Word* origin=new Word();
    while(std::getline(stream,line)){
        bool a=true;
        for(size_t i=0;i<line.size();i++){
            if(!islower(line.at(i))){
                a=false;
                continue;
            }
        }
        if(a==true){
            Word* index=origin;
            size_t len=line.size();
            if(len>dict.size()){
                size_t a=len-dict.size();
                for(size_t i=0;i<a;i++){
                    dict.push_back(nullptr);
                }
            }
            if(dict[len-1]==nullptr){
                dict[len-1]=new std::unordered_map<std::string,std::vector<std::string>>;
            }
            // std::vector<std::string> b;
            dict[len-1]->insert( std::pair<std::string,std::vector<std::string>>(line,std::vector<std::string>()));

            for(size_t i=0;i<len;i++){
                size_t a=(size_t)line.at(i)-97;
                auto x=index->ch.at(a);
                if(x==nullptr){
                    Word* n=new Word();
                    n->wo=index->wo+(char)(a+97);
                    n->pa=index;
                    if(i==len-1){
                        n->isWord=true;
                    }
                    index->ch.at(a)=n;
                    index=n;
                }else{
                    index=x;
                    if(i==len-1){
                        index->isWord=true;
                        break;
                    }
                }
            }
            

            for(size_t i=0;i<len;i++){
                Word* tem=origin;
                for(size_t j=0;j<i;j++){
                    tem=tem->ch.at((size_t)line.at(j)-97);
                }
                for(size_t j=0;j<26;j++){
                    if(tem->ch.at(j)==nullptr||j==(size_t)line.at(i)-97){
                        continue;
                    }
                    Word* cur=tem;
                    cur=cur->ch.at(j);
                    for(size_t k=i+1;k<len;k++){
                        if(cur->ch.at((size_t)line.at(k)-97)==nullptr){
                            break;
                        }
                        cur=cur->ch.at((size_t)line.at(k)-97);
                    }
                    if(cur->wo.length()!=len){
                        continue;
                    }
                    if(cur->isWord){
                        dict[len-1]->at(line).push_back(cur->wo);
                        dict[len-1]->at(cur->wo).push_back(line);
                    }
                }
            }
            
        }

    }
    freeW(origin);
}

Dictionary* Dictionary::create(std::istream& stream){
    Dictionary* result=new Dictionary(stream);
    return result;
}

std::vector<std::string> Dictionary::hop(const std::string& from, const std::string& to){
    if(from.size()!=to.size()){
        // throw InvalidWord("dif length");
        throw NoChain();
    }
    size_t len=from.size();
    auto q=dict[len-1]->find(from);
    if(q==dict[len-1]->end()){
        throw InvalidWord("invalid from");
    }
    if(dict[len-1]->find(to)==dict[len-1]->end()){
        throw InvalidWord("invalid to");
    }
    if(from==to){
        std::vector<std::string> result;
        result.push_back(from);
        return result;
    }
    else{
        std::unordered_map<std::string,std::string> record;
        std::priority_queue<Node,std::vector<Node>,std::greater<Node>> qu;
        record.insert(std::pair<std::string,std::string>(from,""));
        for(size_t i=0;i<q->second.size();i++){
            qu.push(Node(q->second.at(i),from,to));
        }
        while(!qu.empty()){
            Node cur=qu.top();
            qu.pop();
            auto w=record.find(cur.cur);
            if(w!=record.end()){
               
                continue;
            }
            record.insert(std::pair<std::string,std::string>(cur.cur,cur.pa));
            if(cur.cur==to){
                break;
            }
            for(size_t i=0;i<dict[len-1]->at(cur.cur).size();i++){
                std::string tem=dict[len-1]->at(cur.cur).at(i);
                if(tem==cur.pa){
                    continue;
                }
                qu.push(Node(tem,cur.cur,to));
            }
        }
        auto e=record.find(to);
        if(e==record.end()){
            throw NoChain();
        }
        std::vector<std::string> result;
        std::string ind=e->second;
        while(ind!=""){
            auto it=result.begin();
            result.insert(it,ind);
            ind=record.at(ind);
        }
        result.push_back(to);
        return result;

        
    }
    
}

Dictionary::~Dictionary(){
    for(size_t i=0;i<dict.size();i++){
        delete dict[i];
        dict[i]=nullptr;
    }
}
