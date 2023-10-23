#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib> 
#include "Fastnoise/FastNoiseLite.h"
#include <vector>


// Función para inicializar OpenGL
bool InitOpenGL()
{
    if (!glfwInit())
    {
        std::cerr << "Error al inicializar GLFW." << std::endl;
        return false;
    }

    // Configura la versión de OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Crea una ventana GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "Terreno Aleatorio", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Error al crear la ventana GLFW." << std::endl;
        glfwTerminate();
        return false;
    }

    // Hace que el contexto OpenGL sea actual
    glfwMakeContextCurrent(window);

    // Inicializa glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Error al inicializar glad." << std::endl;
        glfwTerminate();
        return false;
    }

    return true;
}

int main()
{
    if (!InitOpenGL())
    {
        return -1;
    }

    // Bucle principal de renderización
    while (!glfwWindowShouldClose(glfwGetCurrentContext()))
    {
        // Create and configure FastNoise object
        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

        // Gather noise data
        std::vector<float> noiseData(128 * 128);
        int index = 0;

        for (int y = 0; y < 128; y++)
        {
            for (int x = 0; x < 128; x++)
            {
                noiseData[index++] = noise.GetNoise((float)x, (float)y);
            }
        }

        // Intercambia los buffers
        glfwSwapBuffers(glfwGetCurrentContext());

        // Captura eventos y realiza actualizaciones
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}