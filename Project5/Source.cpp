#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <string.h>
#include <shader_s.h>
const char *PRONAME = "Project4";
struct tm *logtime;
void REFRESHLOGTIME()
{
    time_t timer;
    time(&timer);
    logtime = localtime(&timer);
}
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
int main()
{
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
        REFRESHLOGTIME();
        printf("[%s](%d:%d:%d): Failed to initialize GLAD\n", PRONAME, logtime->tm_hour, logtime->tm_min, logtime->tm_sec);
        return -1;
    }
    REFRESHLOGTIME();
    printf("[%s](%d:%d:%d): Initialize GLAD success\n", PRONAME, logtime->tm_hour, logtime->tm_min, logtime->tm_sec);
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //--------------------------------------
    Shader shader("shader.vs", "shader.fs");
    float texCoords[] = {
        0.0f, 0.0f, // 左下角
        1.0f, 0.0f, // 右下角
        0.5f, 1.0f  // 上中
    };
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // 1. 绑定VAO
    glBindVertexArray(VAO);
    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 4. 设置顶点属性指针
    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    shader.use();
    //--------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    REFRESHLOGTIME();
    printf("[%s](%d:%d:%d): User close the window\n", PRONAME, logtime->tm_hour, logtime->tm_min, logtime->tm_sec);
    glfwTerminate();
    return 0;
}