#include <GL/glew.h>

#include "AppBase/AppBase.hpp"
#include "Renderer/Renderer.hpp"
#include "GLFWWrappers/Window.hpp"
#include <iostream>

namespace Plum
{
    std::vector<float> MakeTriangle()
    {
        std::vector<float> vertecies = {
                    0.0f, 0.5f,
                    0.5f, -0.5f,
                    -0.5f, -0.5f
        };

        return vertecies;
    }

    class App final : public Plum::AppBase
    {
    public:
        virtual void Render() override;
        virtual void Run() override;
        virtual void StartUp() override;
    private:
        Renderer renderer;
        Mesh triangle;
    };

    void App::Render()
    {
        renderer.Render(triangle);
    }

    void App::Run()
    {
        glfwMakeContextCurrent(m_Window->glfwWindowPtr);

        InitGlew();
        StartUp();

        while (!m_Window->ShouldClose())
        {
            renderer.Render(triangle);
            m_Window->SwapBuffers();
            glfwWaitEvents();
        }
    }

    void App::StartUp()
    {
        //const std::string vertexShaderSourcePath = "D:\\projects\\Plum-Pie\\AppBase\\src\\vertex_shader.glsl";
        //const std::string fregemntShaderPath = "D:\\projects\\Plum-Pie\\AppBase\\src\\fragment_shader.glsl";
        //auto* vertexShader = new Shader(vertexShaderSourcePath, GL_VERTEX_SHADER);
        //auto* fragShader = new Shader(fregemntShaderPath, GL_FRAGMENT_SHADER);

        //Program program;
        //program.AttachShaders({ vertexShader, fragShader });
        //delete vertexShader;
        //delete fragShader;

        //renderer.UseProgram(program);

        //const auto& vert = MakeTriangle();

        //GLuint const indicies[] = {
        //      0, 1, 2
        //};

        //GLuint VAO;
        //glGenVertexArrays(1, &VAO);
        //glBindVertexArray(VAO);

        //GLuint VBO;
        //glGenBuffers(1, &VBO);
        //glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert.data(), GL_STATIC_DRAW);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);

        //GLuint EBO;
        //glGenBuffers(1, &EBO);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

        //GLint PositionAttribute = glGetAttribLocation(program.GetProgramID(), "position");
        //glEnableVertexAttribArray(PositionAttribute);
        //glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //glVertexAttribPointer(PositionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);

        //renderer.SetClearColor(Color(0, 0.4f, 0));
    }

}


int main()
{
	Plum::GLFW::Window window;

	glfwMakeContextCurrent(window.glfwWindowPtr);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		return -1;
	}

	GLfloat const Vertices[] = {
		0.0f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	};

	GLuint const Elements[] = {
		0, 1, 2
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Elements), Elements, GL_STATIC_DRAW);

    Plum::Shader vertexShader("D:/projects/Plum-Pie/PlumPie/src/vertex_shader.glsl", GL_VERTEX_SHADER);
    Plum::Shader fragmentShader("D:/projects/Plum-Pie/PlumPie/src/fragment_shader.glsl", GL_FRAGMENT_SHADER);

    Plum::Program shaderProgram;
    shaderProgram.AttachShaders({ vertexShader, fragmentShader });
    shaderProgram.Use();

    GLint PositionAttribute = glGetAttribLocation(shaderProgram.GetProgramID(), "position");
    glEnableVertexAttribArray(PositionAttribute);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(PositionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	while (!window.ShouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		window.SwapBuffers();
		glfwPollEvents();
	}

	glfwTerminate();

    return 0;
}