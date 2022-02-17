#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "src/Window.h"
#include "src/Scene.h"
#include <iostream>

int main() {

    Window window = Window(800, 600, "Wiktor's renderer");

    std::cout << "Window initialized successfully" << std::endl;

    // scene setup (model initialisation) should take place here
    Scene scene = Scene();

    // pass scene reference to window
    window.setScene(scene);
    // draw scene
    window.draw();

}


// Main idea
// create a window abstraction
// create a shader abstraction
// create a camera abstraction
// create a Scene class containing
// initialisation (reading all models, textures)
// add lights
// input handling
// rendering loop