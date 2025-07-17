#include <iostream>
#include <string>
#include <filesystem>

using namespace std;

string RemoveSpecificChar(string CurrentString, char TargetString){
    string Str;
    for(int i = 0; i < CurrentString.length(); i++){
        if(CurrentString[i] != TargetString){
            Str += CurrentString[i];
        }
    }
    return Str;
}

bool ReplaceString(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

string FindValByTargetIteration(int TargetIteration, int Iteration, string Text){
    string TargetText;
    if(Iteration == TargetIteration){
        for(int i = 0; i < Text.length(); i++){
            if(Text[i] == '='){
                for(int j = i + 1; j < Text.length(); j++){
                    TargetText += Text[j];
                }
            }
        }
        TargetText = RemoveSpecificChar(TargetText, ' ');
        TargetText = RemoveSpecificChar(TargetText, '"');
        return TargetText;
    }
    return "Nothing";
}

string FindVal(string Text){
    string TargetText;
    for(int i = 0; i < Text.length(); i++){
        if(Text[i] == '='){
            for(int j = i + 1; j < Text.length(); j++){
                TargetText += Text[j];
            }
        }
    }
    TargetText = RemoveSpecificChar(TargetText, ' ');
    TargetText = RemoveSpecificChar(TargetText, '"');
    
    return TargetText;
}

string ReplaceVal(string Text, string Value){
    string TargetText;
    for(int i = 0; i < Text.length(); i++){
        if(Text[i] == '='){
            for(int j = i + 1; j < Text.length(); j++){
                TargetText += Text[j];
            }
        }

    }
    TargetText = RemoveSpecificChar(TargetText, ' ');
    TargetText = RemoveSpecificChar(TargetText, '"');
    
    ReplaceString(Text, TargetText, Value);
    return Text;
}

bool FindBySpecText(string CurrentText, string TargetText){

    if(CurrentText.find(TargetText) != string::npos){
        return true;
    }
    return false;
}