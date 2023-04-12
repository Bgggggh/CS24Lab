#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    int num, newnum;
    string strN;

    
    num  = atoi(argv[argc - 1]);
    
    getline(cin, strN);
    
    string k;
    k = strN;
    long strNLength = k.length();
    
    if(num > strNLength){
        num = num%strNLength;
    }
    
    if(num > strNLength){
        num = num%strNLength;
    }
    
    for(int i = 0; i < strNLength; ++i){
        if(isupper(k[i])){
            k[i] = tolower(k[i]);
            
        }
    }
    if(num > 0){
        for(int i = 0; i < strNLength - num; ++i){
            
            if(isupper(strN[i])){
                k[i + num] = toupper(k[i + num]);
            }
        }
        
        for(int i = k.length() - num; i < strNLength; ++i){
            
            if(isupper(strN[i])){
                k[i + num - k.length()] = toupper(k[i + num - k.length()]);
            }
        }
        
       
    }
    else if(num < 0){
        
        newnum = -num;
        for(int i = (strNLength - 1); i >= newnum; --i){
            if(isupper(strN[i])){
                k[i - newnum] = toupper(k[i - newnum]);
            }
        }
        for(int i = 0; i < newnum; ++i){
            if(isupper(strN[i])){
                k[i + strNLength - newnum] = toupper(k[i + strNLength - newnum]);
            }
        }
        
    }
    
    cout << k << endl;
    return 0;
}

