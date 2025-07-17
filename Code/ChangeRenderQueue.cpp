#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include "FunctionPack.hpp"
#include <vector>
#include <cstdio>
#include <cstdlib>

namespace fs = std::filesystem;

string InputFileName = "./InputMaterial_Render/";
string OutputMaterial = "./OutputMaterial_Render/";
string RejectFileList = "./RejectRenderMaterial.txt";

void MainCode(string _InputPath, string _OutputPath){
    //Some Variables
    vector<string> ReadMaterial, RejectRenderMaterialList, AlbedoText;
    vector<bool> HasTextureAlbedo;
    bool gotRenderQueueValue = false;
    bool CancelOperation = false;
    bool HasTextureAlbedoFound = false;
    string renderQueueValueAfter = "2000";
    string findRenderQueueStr = "m_CustomRenderQueue";
    int Iteration = 0;

    ifstream InputPath, RejectRenderMaterialFile, TextureAlbedoFile, DeleteOutputFile;
    ofstream OutputPath;
    InputPath.open(_InputPath);
    TextureAlbedoFile.open("./TextureAlbedo.txt");

    RejectRenderMaterialFile.open(RejectFileList);

    //Read Reject Material List
    if(RejectRenderMaterialFile.is_open()){
        string EachLine;
        while(getline(RejectRenderMaterialFile, EachLine)){
            RejectRenderMaterialList.push_back(EachLine);
        }
    }
    RejectRenderMaterialFile.close();
    //Read Texture Albedo
    if(TextureAlbedoFile.is_open()){
        string EachLine;
        while(getline(TextureAlbedoFile, EachLine)){
            AlbedoText.push_back(EachLine);
        }
    }
    TextureAlbedoFile.close();
    //Read & Checking Name Material
    if(InputPath.is_open()){
        string EachLine;
        while(getline(InputPath, EachLine)){
            ReadMaterial.push_back(EachLine);
            for(string& a : RejectRenderMaterialList){
                if(FindBySpecText(EachLine, a)) CancelOperation = true;
            }
            for(string& a : AlbedoText){
                HasTextureAlbedo.push_back(FindBySpecText(EachLine, a));
            }
        }
    }
    InputPath.close();
    //Checking Has Texture Albedo
    for(bool b : HasTextureAlbedo){
        if(b) HasTextureAlbedoFound = true;
    }
    //Checking and Replace Custom Render Queue
    for(string& a : ReadMaterial){
        if(FindBySpecText(a, findRenderQueueStr) && !gotRenderQueueValue) {
            ReadMaterial[Iteration] = ReplaceVal(a, renderQueueValueAfter);
            gotRenderQueueValue = true;
        }
        Iteration++;
    }

    //Writing Output
    if(!CancelOperation && HasTextureAlbedoFound){
        OutputPath.open(_OutputPath);
        for(string& a : ReadMaterial){
            OutputPath << a << endl;
        }
        OutputPath.close();
    }
    
}

int main(){
    vector<string> DirectoryList;
    fs::create_directories(InputFileName);
    fs::create_directories(OutputMaterial);
    for(const auto& entry : fs::directory_iterator(InputFileName)){
       DirectoryList.push_back(entry.path().filename().generic_string());
    }
    for(string& a : DirectoryList){
        MainCode(InputFileName + a, OutputMaterial + a);
        cout << a << endl;
    }

    cout << endl << "Done!" << endl;
    return 0;
}