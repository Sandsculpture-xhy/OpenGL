#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <string.h>
const char *PRONAME = "Project3";
const char *LOGNAME = "Project3.log";
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";
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
        REFRESHLOGTIME();
        printf("[%s](%d:%d:%d): Failed to initialize GLAD\n", PRONAME, logtime->tm_hour, logtime->tm_min, logtime->tm_sec);
        return -1;
    }
    REFRESHLOGTIME();
    printf("[%s](%d:%d:%d): Initialize GLAD success\n", PRONAME, logtime->tm_hour, logtime->tm_min, logtime->tm_sec);
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //--------------------------------------
    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
    };

    unsigned int indices[] = {
        // 注意索引从0开始!
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        // std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<< infoLog << std::endl;
        REFRESHLOGTIME();
        printf("[%s](%d:%d:%d): ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", PRONAME, logtime->tm_hour, logtime->tm_min, logtime->tm_sec, infoLog);
        return 1;
    }
    memset(infoLog, 0, sizeof(infoLog));
    printf("[%s](%d:%d:%d): Vertex Shader GLSL compile success\n", PRONAME, logtime->tm_hour, logtime->tm_min, logtime->tm_sec);
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        REFRESHLOGTIME();
        printf("[%s](%d:%d:%d): ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s", PRONAME, logtime->tm_hour, logtime->tm_min, logtime->tm_sec, infoLog);
        return 1;
    }
    memset(infoLog, 0, sizeof(infoLog));
    printf("[%s](%d:%d:%d): Fragment Shader GLSL compile success\n", PRONAME, logtime->tm_hour, logtime->tm_min, logtime->tm_sec);
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        REFRESHLOGTIME();
        printf("[%s](%d:%d:%d): ERROR::PROGRAM::SHADER::LINK_FAILED\n%s", PRONAME, logtime->tm_hour, logtime->tm_min, logtime->tm_sec, infoLog);
        return 1;
    }
    memset(infoLog, 0, sizeof(infoLog));
    printf("[%s](%d:%d:%d): Shader program link success\n", PRONAME, logtime->tm_hour, logtime->tm_min, logtime->tm_sec);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // 1. 绑定VAO
    glBindVertexArray(VAO);
    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    //--------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    REFRESHLOGTIME();
    printf("[%s](%d:%d:%d): User close the window\n", PRONAME, logtime->tm_hour, logtime->tm_min, logtime->tm_sec);
    glfwTerminate();
    return 0;
}