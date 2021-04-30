# 3D Texture Viewer

# What is it?
Viewer is a program for Windows that allows you to open and view textures on a 3D object with a clean and simple user interface.

![showcase image](texview.png)

# Using Viewer
## Visual Studio
1. Open the Viewer.sln solution file.
2. Launch the debugger by pressing F5 (recommended), or build the project.
3. Open the program.
4. Inside the Viewer program, go to File -> Load Texture.
5. Select a texture you like.
## Releases
1. Ensure you have the [latest Visual C++ redistributable downloaded.](https://support.microsoft.com/en-us/topic/the-latest-supported-visual-c-downloads-2647da03-1eea-4433-9aff-95f26a218cc0)
2. Run the Viewer.exe file.
3. If the application fails to load or throws an error, repeat step 1. If you have already done that, [open an issue.](https://github.com/wmcnamara/viewer/issues/new)

![showcase gif](showcase.gif)

# More Info
 - 3D rendering techniques adapted from the [Learn OpenGL](https://learnopengl.com) website.
 - Support Windows's "Open File With" functionality.
 - Uses the Dear IMGUI library to render a fast and responsive GUI.
 - Uses a cool event system implementation that I wrote previously. It can be found [here.](https://github.com/wmcnamara/delegate)
 - Uses COM objects and the WINAPI to display a simple and clean file picker for Windows.