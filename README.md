# SonicSuperstars-Cell-Shaded-Material-Zone-Editor
Hey, you can download the modded zone here: 
https://www.mediafire.com/file/wskig04tv21dvpu/Sonic_Superstars_-_Comic_Book_Zone.zip/file
And the showcase here:
https://www.youtube.com/watch?v=cL_v4q6Y9a0

To use this tool, you can compile "CelShadedShader.cpp" into executable using any compiler and don't forget to put "FunctionPack.hpp" beside .cpp file.
I'am using "Visual Studio Code" with extension called "Code Runner", you can download here:
https://marketplace.visualstudio.com/items?itemName=formulahendry.code-runner

About the TXT Files, they are a collection of text lists that filter out which files will be skipped, material template, and some checks if the file has an albedo map/texture path.
I have already made for each zone inside "FilteringMaterial and CustomTexture" folder.

How to Use It:
1. Use UABEA: https://github.com/nesrak1/UABEA
2. Import the zone file (assetbundle), for example "Bridge Island Zone 1 & 2" the file is "zone01data_assets_all.bundle"
3. Filter by material, select all, then export dump, and use "UABEA text dump". You will see a bunch of .txt files
4. Put the executable that already compiled into "FilteringMaterial and CustomTexture/'Zone You Want to Modify'". For example Bridge Island Zone 1 & 2 inside of folder "Zone 1"
5. Create folder "InputMaterial" & "OutputMaterial" inside that folder zone
6. Move all dumped material files into "InputMaterial"
7. Run the executable and the processed files will appear in the "OutputMaterial" folder
8. Back to UABEA, select all material, then "Import Dump", select the "OutputMaterial"
9. Each zone already has a custom texture file that I created inside "Texture2D", you can change every texture with that
10. Save the assetbundle

Ah yes, about "ChangeRenderQueue.cpp" or any "Render Queue" things, this is not too important.
But you can try it in the same way as before, but the InputMaterial use OutputMaterial that processed before.

This may not be perfect, but yeah this is just my coding test and worth to try.
I hope my English understandable bruh. What the hell I'm writing here.
Well stay safe, be carefull when sailin' through the internet✌️.
