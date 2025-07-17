#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include "FunctionPack.hpp"
#include <vector>

using std::cout;
using std::endl;
using std::string;
namespace fs = std::filesystem;

string InputFileName = "./InputMaterial/";
string OutputMaterial = "./OutputMaterial/";

void ModMaterial(string _InputFileName, string _OutputMaterial){
    string EachLineOpen = "";
    bool CancelOperation = false;
    int TargetTextureIteration = -1;
    int TargetEmissiveTexIteration = -1;
    bool AlreadyGotMaterialName = false;
    bool AlreadyGotShaderPath = false;
    bool AlreadyGotTexture = false;
    bool AlreadyGotEmissiveTex = false;
    bool RejectEmissive = false;
    bool RejectPlayerOutlineCon = false;
    bool GotGoldMaterial = false;
    bool GotGoldHasTexMat = false;
    bool GotRingMaterial = false;
    bool GotMedal = false;
    int Iteration = 0;
    string MaterialName = "";
    string ShaderPathId = "";
    string EmissivePathId = "";
    string TexturePath = "";
    
    vector<string> MaterialShaderChace, ThisMaterial;
    ifstream            MaterialShader, 
                        RejectMaterial,
                        TextureAlbedoFile, 
                        EmissiveFile, 
                        RejectEmissiveFile, 
                        RejectPlayerFile,
                        GoldMaterialFile,
                        GoldHasTexMatFile,
                        GoldTexPathFile,
                        RingMaterialFile,
                        MedalFile;
    std::vector<string> AlbedoText, 
                        RejectedMaterialList, 
                        EmissiveList, 
                        RejectEmissiveList, 
                        RejectPlayerList,
                        GoldMaterialList,
                        GoldHasTexMatList,
                        GoldTexPathList,
                        RingMaterialList,
                        MedalList;

    //cout << "Find: " << (AlbedoTest.find("_AlbedoMap") != string::npos) << endl;
    //cout << char(0x22) << endl;
    //cout << "File: ";
    //cin >> _InputFileName;
    //cout << "File: " << _InputFileName << endl;

    MaterialShader.open     (_InputFileName);
    RejectMaterial.open     ("./Rejected.txt");
    TextureAlbedoFile.open  ("./TextureAlbedo.txt");
    EmissiveFile.open       ("./EmissiveMap.txt");
    RejectEmissiveFile.open ("./RejectEmissive.txt");
    RejectPlayerFile.open   ("./RejectPlayerOutline.txt");
    GoldMaterialFile.open   ("./GoldMaterial.txt");
    GoldHasTexMatFile.open  ("./GoldHasTexMat.txt");
    GoldTexPathFile.open    ("./GoldTexturePath.txt");
    RingMaterialFile.open   ("./RingMaterial.txt");
    MedalFile.open          ("./MedalList.txt");

    //Read Reject Player Outline
    if(RejectPlayerFile.is_open()){
        string EachLine;
        while(getline(RejectPlayerFile, EachLine)){
            RejectPlayerList.push_back(EachLine);
        }
    }
    RejectPlayerFile.close();
    //Read Medal List
    if(MedalFile.is_open()){
        string EachLine;
        while(getline(MedalFile, EachLine)){
            MedalList.push_back(EachLine);
        }
    }
    MedalFile.close();
    //Read Gold Material List
    if(GoldMaterialFile.is_open()){
        string EachLine;
        while(getline(GoldMaterialFile, EachLine)){
            GoldMaterialList.push_back(EachLine);
        }
    }
    GoldMaterialFile.close();
    //Read Gold Has Texture Material
    if(GoldHasTexMatFile.is_open()){
        string EachLine;
        while(getline(GoldHasTexMatFile, EachLine)){
            GoldHasTexMatList.push_back(EachLine);
        }
    }
    GoldHasTexMatFile.close();
    //Gold Texture Path
    if(GoldTexPathFile.is_open()){
        string EachLine;
        while(getline(GoldTexPathFile, EachLine)){
            GoldTexPathList.push_back(EachLine);
        }
    }
    GoldTexPathFile.close();
    //Read Texture Albedo
    if(TextureAlbedoFile.is_open()){
        string EachLine;
        while(getline(TextureAlbedoFile, EachLine)){
            AlbedoText.push_back(EachLine);
        }
    }
    TextureAlbedoFile.close();

    //Read Emissive List
    if(EmissiveFile.is_open()){
        string EachLine;
        while(getline(EmissiveFile, EachLine)){
            EmissiveList.push_back(EachLine);
        }
    }
    EmissiveFile.close();

    //Read Reject Emissive List
    if(RejectEmissiveFile.is_open()){
        string EachLine;
        while(getline(RejectEmissiveFile, EachLine)){
            RejectEmissiveList.push_back(EachLine);
        }
    }
    RejectEmissiveFile.close();

    //Rejeced Material Listing
    if(RejectMaterial.is_open()){
        string STR_Iteration;
        while(getline(RejectMaterial, STR_Iteration)){
            RejectedMaterialList.push_back(STR_Iteration);
        }
    }
    RejectMaterial.close();
    //Read Ring Material
    if(RingMaterialFile.is_open()){
        string EachLine;
        while(getline(RingMaterialFile, EachLine)){
            RingMaterialList.push_back(EachLine);
        }
    }
    RingMaterialFile.close();

    //Read Material
    if(MaterialShader.is_open()){
        while(getline(MaterialShader, EachLineOpen)){
            //Get Filter Player Material & Ring Material
            if(Iteration == 1) MaterialName = FindVal(EachLineOpen);
            for(string& a : RejectPlayerList){
                if(Iteration == 1 && FindBySpecText(EachLineOpen, a)){
                    RejectPlayerOutlineCon = true;
                }
            }
            // Check Gold Material Name
            for(string& a : GoldMaterialList){
                if(FindBySpecText(EachLineOpen, a) && !GotGoldMaterial){
                    GotGoldMaterial = true;
                }
            }
            // Check Medal
            for(string& a : MedalList){
                if(FindBySpecText(EachLineOpen, a) && !GotMedal){
                    GotMedal = true;
                }
            }
            //
            for(string& a : GoldHasTexMatList){
                if(FindBySpecText(EachLineOpen, a) && !GotGoldHasTexMat) GotGoldHasTexMat = true;
            }
            // Check Ring Material
            if(Iteration == 1){
                for(string& a : RingMaterialList){
                    if(FindBySpecText(EachLineOpen, a) && !GotRingMaterial) GotRingMaterial = true;
                }
            }
            if(Iteration == 3) ShaderPathId =  FindVal(EachLineOpen);
            //Check Emissive Path
            for(string& a : EmissiveList){
                if(FindBySpecText(EachLineOpen, a) && !AlreadyGotEmissiveTex){
                    TargetEmissiveTexIteration = Iteration + 4;
                    AlreadyGotEmissiveTex = true;
                }
            }
            //Check Texture Path
            for(string& a : AlbedoText){
                if(FindBySpecText(EachLineOpen, a) && !AlreadyGotTexture){
                    TargetTextureIteration = Iteration + 4;
                    AlreadyGotTexture = true;
                }
            }

            //Check Rejected Emissive
            for(string& a : RejectEmissiveList){
                if(FindBySpecText(EachLineOpen, a) && !RejectEmissive){
                    RejectEmissive = true;
                }
            }

            //Set Texture Path Var
            if(Iteration == TargetTextureIteration){
                TexturePath = FindVal(EachLineOpen);
            }
            //Set Emissive Path Var
            if(Iteration == TargetEmissiveTexIteration){
                EmissivePathId = FindVal(EachLineOpen);
            }

            for(string& a : RejectedMaterialList){
                if(!CancelOperation) CancelOperation = (EachLineOpen.find(a) != string::npos);
            }
            ThisMaterial.push_back(EachLineOpen);
            Iteration++;
        }
    }
    Iteration = 0;
    MaterialShader.close();

    // cout << MaterialName << endl;
    // cout << ShaderPathId << endl;
    // cout << TexturePath << endl;
    if(TexturePath.length() < 2){
        CancelOperation = true;
    }

    //Open Template
    if(RejectPlayerOutlineCon){
        MaterialShader.open("./Material_Player.txt");
    }else if(GotRingMaterial){
        MaterialShader.open("./RingMaterialTemplate.txt");
    }else if(GotMedal){
        MaterialShader.open("./MedalTemplate.txt");
    }else{
        MaterialShader.open("./Material.txt");
    }
    
    if(MaterialShader.is_open()){
        while (getline(MaterialShader, EachLineOpen))
        {
            MaterialShaderChace.push_back(EachLineOpen);
        }
    }
    else{
        cout << "Error Open File" << endl;
    }
    MaterialShader.close();

    //Gold Texture Prod
    if(GotGoldMaterial && !GotGoldHasTexMat){
        CancelOperation = false;
        EmissivePathId = TexturePath = GoldTexPathList[0];
    }else if(!GotGoldMaterial && GotGoldHasTexMat){
        CancelOperation = false;
        EmissivePathId = TexturePath = GoldTexPathList[1];
    }

    //Replacing
    for(int i = 0; i < MaterialShaderChace.size(); i++){
        ReplaceString(MaterialShaderChace[i], "$NAME_MATERIAL$", MaterialName);
        ReplaceString(MaterialShaderChace[i], "$SHADER_PATH_ID$", ShaderPathId);
        if(EmissivePathId.length() > 1 && !RejectEmissive){
            ReplaceString(MaterialShaderChace[i], "$TEXTURE_CODE$", EmissivePathId);
        }else{
            ReplaceString(MaterialShaderChace[i], "$TEXTURE_CODE$", TexturePath);
        }
    }

    //Write
    ofstream WriteFile;
    WriteFile.open(_OutputMaterial);
    if(!CancelOperation){
        for(string& a : MaterialShaderChace){
            WriteFile << a << endl;
        }
        cout << "Write Mod" << endl;
    }else{
        for(string& a : ThisMaterial){
            WriteFile << a << endl;
        }
        cout << "Write Original" << endl;
    }
    WriteFile.close();
}

int main(){
    vector<string> DirectoryList;
    fs::create_directories("./InputMaterial");
    fs::create_directories("./OutputMaterial");
    for(const auto& entry : fs::directory_iterator(InputFileName)){
       DirectoryList.push_back(entry.path().filename().generic_string());
    }
    for(string& a : DirectoryList){
        ModMaterial(InputFileName + a, OutputMaterial + a);
    }
    // ModMaterial("D:/PROJECT/MODDING/Sonic Superstars/Complete Cel Shaded/Code/InputMaterial/aig001_body01a_Mt-CAB-4f5971df289580e566aff9d7e52556bc-8981268025396286309.txt",
    // "D:/PROJECT/MODDING/Sonic Superstars/Complete Cel Shaded/Code/OutputMaterial/aig001_body01a_Mt-CAB-4f5971df289580e566aff9d7e52556bc-8981268025396286309.txt");
    cout << "Done!" << endl;
    return 0;
}