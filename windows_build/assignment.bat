cl /EHsc /I..\windows/include /I..\include /I..\windows/include/SDL2 /c ..\src\app.cpp ..\src\context.cpp ..\assignment\assignment.cpp ..\src\SDL_FontCache.c
link /SUBSYSTEM:CONSOLE /LIBPATH:..\windows\lib\x64 assignment.obj .\context.obj .\app.obj .\SDL_FontCache.obj SDL2.lib SDL2main.lib /NODEFAULTLIB:libcmtd.lib opengl32.lib shell32.lib SDL2_ttf.lib SDL2_image.lib freetype.lib
