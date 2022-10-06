#pragma once
#include "iostream"
#include "string"
class file{
private:
    std::string* f;
    int l = 0;
    int maxLines = 100;
    int r = 0;
public:
    file(){
        f = new std::string[maxLines];
    }

    void expandStorage(){
        maxLines *=2;
        std::string* temp = new std::string[maxLines];
        for(int i = 0; i < maxLines/2; i++){
            temp[i] = f[i];
        }
        delete[] f;
        f = temp;
    }

    void addline(std::string line){
        if(l>=maxLines){
            expandStorage();
        }
        f[l] = line;
        l++;
    };

    int getlinecount(){
        return l;
    }

    std::string getline(int i){
        r = 0;
        if(i < l && l >= 0){
            return f[i];
        }
        std::cout << "ERROR: line out of range";
        exit(0);
    }

    std::string addtoline(int i, int c, std::string addition){
        if(c +r < (int)f[i].length()){
            f[i] = f[i].substr(0,c+r) + addition + "" + f[i].substr(c+r);
            r++;
        }
        if(c+r >= (int)f[i].length()){
            f[i] += addition;
        }
        return getline(i);
    }

    std::string removefromline(int i, int c){
        if(c == 0){
            f[i] = f[i].substr(1);
        }
        else if(c+r < (int)f[i].length()){
            f[i] = f[i].substr(0,c) + "" + f[i].substr(c+1);
            r--;
        }
        return getline(i);
    }

    void addline(int lineNumber) {
        if(lineNumber>=l) return void();
        if(l>=maxLines){
            expandStorage();
        }     
        for(int i = lineNumber; i <= l; i++)   {
            f[i+1] = f[i];
        }
        f[lineNumber] = "";
        l++;
        std::cout << this->getline(0) << std::endl;
        /*if(l>=maxLines){
            expandStorage();
        }
        f[l] = line;
        l++;*/
    }
};
