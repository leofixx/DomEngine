#include <iostream>
#include "stdafx.h"
#include "display.h"
#include <GL/glew.h>
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"



#define WIDTH 800
#define HEIGHT 600



int main(int argc, char** argv)
{
	Display display(800, 600, "Dom Engine");

	Vertex vertices[] = { 
		Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 0.0)),
		Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 1.0)) 
	};

	unsigned int indicies[] = { 0, 1, 2 };

	
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indicies, sizeof(indicies)/sizeof(indicies)[0]);
	Mesh mesh2("../res/monkey3.obj");
	Shader shader("../res/basicShader.fs.txt");
	Texture texture("../res/dirty-metal-texture_1048-4784.jpg");
	Camera camera(glm::vec3(0, 0, -1), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	Transform transform;

	float counter = 0.0f;
	
	
	while (!display.IsClosed())
	{
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		//transform.GetPos().x = sinf(counter);
		//transform.GetPos().z = cos(counter);
		transform.GetRot().z = counter * 2;
		transform.GetRot().y = counter * 2;
		//transform.GetRot().x = counter * 2;
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		texture.Bind(0);
		shader.Update(transform, camera);
		shader.Bind();
		
		mesh2.Draw();
		
	
		display.UpdateBuffers();
		counter += 0.01f;
	}

	return 0;
}

