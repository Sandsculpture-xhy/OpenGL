#include <stdio.h>
#include <GL/gl.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <time.h>
const char *PRONAME = "Project1";
const char *LOGNAME = "Project1.log";
struct tm *logtime;
void REFRESHLOGTIME()
{
    time_t timer;
    time(&timer);
    logtime = localtime(&timer);
}
int main()
{
    freopen(LOGNAME, "w", stdout);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(800, 600, PRONAME, NULL, NULL);
    if (window == NULL)
    {
        REFRESHLOGTIME();
        printf("[%s](%d:%d:%d): Failed to create GLFW window\n", PRONAME, logtime->tm_hour, logtime->tm_min, logtime->tm_sec);
        glfwTerminate();
        return -1;
    }
    REFRESHLOGTIME();
    printf("[%s](%d:%d:%d): Create GLFW window success\n", PRONAME, logtime->tm_hour, logtime->tm_min, logtime->tm_sec);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        // std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    return 0;
}