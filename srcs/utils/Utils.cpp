#include <string>
#include <vector>
#include "Utils.hpp"

std::vector<std::string> split(std::string str, char del)
{
      std::string temp = "";
      std::vector<std::string> vect;

      for(int i=0; i<(int)str.size(); i++){
         if(str[i] != del){
            temp += str[i];
        }
          else{
              vect.push_back(temp);
              temp = "";
        }
    }
    vect.push_back(temp);
    return vect;
}


std::string& rtrim(std::string& s, const char* t)
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

std::string& ltrim(std::string& s, const char* t)
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

std::string& trim(std::string& s, const char* t)
{
    return ltrim(rtrim(s, t), t);
}