# OpenGL

1. vc++directories 에서 include, lib세팅
2. linker 옵션에서 additinoal dependencies에 opengl32.lib, glfw3.lib추가
(추후에 dll이 필요하면 일일이 여기다가 넣어줘야함)
3. glad.c를 프로젝트안에다가도 넣고 include/glad/src/glad.c에도 넣어줘야함.
4. glfw빌드후 glfw3.pdb 또한 lib/ 경로에 glfw3.lib포함 같이 넣어줘야함.

https://stackoverflow.com/questions/27883940/can-we-change-all-the-word-at-once-in-visual-studio