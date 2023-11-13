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
    // Definir las dimensiones de la malla
    const int gridSize = 128;

    // Recopilar datos de ruido Perlin
    std::vector<float> noiseData(128 * 128 * 128);
    int index = 0;

    // Create and configure FastNoise object
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);


    for (int y = 0; y < 128; y++)
    {
        for (int x = 0; x < 128; x++)
        {
            for (int z = 0; z < 128; z++)
            {
                noiseData[index++] = noise.GetNoise((float)x, (float)y, (float)z);
            }
        }
    }

    // Crear una malla 3D con vértices
    std::vector<GLfloat> vertices;
    for (int z = 0; z < gridSize; z++) {
        for (int y = 0; y < gridSize; y++) {
            for (int x = 0; x < gridSize; x++) {
                float xf = static_cast<float>(x) / static_cast<float>(gridSize);
                float yf = static_cast<float>(y) / static_cast<float>(gridSize);
                float zf = static_cast<float>(z) / static_cast<float>(gridSize);

                // Obtener el valor de ruido Perlin correspondiente
                float noiseValue = noiseData[x + y * gridSize + z * gridSize * gridSize];

                // Ajustar el valor de ruido según tus necesidades
                float scaleFactor = 10.0f;
                float height = noiseValue * scaleFactor;

                // Agregar el vértice a la lista de vértices
                vertices.push_back(x);
                vertices.push_back(height);
                vertices.push_back(z);
            }
        }
    }



    ///GLWF STUFF

    if (!InitOpenGL())
    {
        return -1;
    }

    // Bucle principal de renderización
    while (!glfwWindowShouldClose(glfwGetCurrentContext()))
    {

        // Intercambia los buffers
        glfwSwapBuffers(glfwGetCurrentContext());

        // Captura eventos y realiza actualizaciones
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}