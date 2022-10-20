# OpenGL
Learning OpenGL

CONFIG PROP:
Output dir.: $(SolutionDir)Bin\Debug\OpenGL\
Intermed. dir.: $(SolutionDir)Bin-int\Debug\OpenGL\

C/C++:
Additional include dir.: src;src\vendor;$(SolutionDir)Dependencies\GLFW\include;$(SolutionDir)Dependencies\GLEW\include;
preprocessor def.: GLEW_STATIC;

LINKER:
Additional Library Dir.: $(SolutionDir)Dependencies\GLFW\lib-vc2022;$(SolutionDir)Dependencies\GLEW\lib\Release\Win32;
Additional Dependencies: opengl32.lib;glfw3.lib;glew32s.lib;User32.lib;Gdi32.lib;Shell32.lib
