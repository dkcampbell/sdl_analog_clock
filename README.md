SDL Analog Clock
================

Really basic analog clock done with SDL.

The clockface image is free clipart from: 
http://www.clipartbest.com/clipart-RcA7xKecL

Compiling
---------

Linux:
clang++ -std=c++11 Clock.cpp main.cpp -o main -lSDL2 -lSDL2_image

Windows:
Settings for Visual Studio
Set build SubSystem build to WINDOWS.
Dependencies on SDL2.lib, SDL2main.lib and SDL2_image.lib

Have to change around the C runtime the build uses to match SDL.
Of course, add the proper include directories to the project.

If you run the app in Visual Studio and the images don't load try running
it outside Visual Studio. There's something on the libSDL site in the FAQ
about what causes this.
