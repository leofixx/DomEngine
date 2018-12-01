#include "stdafx.h"
#include "mesh.h"
#include "obj_loader.h"
#include <vector>



Mesh::Mesh(const std::string& fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	InitMesh(model);
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indicies, unsigned int numIndicies)
{

	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormals());
	}

	for (unsigned int i = 0; i < numIndicies; i++)
	{
		model.indices.push_back(indicies[i]);
	}
	InitMesh(model);
	


	//m_drawcount = numVertices;
	//m_drawcount = numIndicies;

	//glGenVertexArrays(1, &m_VertexArrayObject);
	//glBindVertexArray(m_VertexArrayObject);

	//std::vector<glm::vec3> positions;
	//std::vector<glm::vec2> texcoords;
	
	//positions.reserve(numVertices);
	//texcoords.reserve(numVertices);

	//for (unsigned int i = 0; i < numVertices; i++)
	//{
		//positions.push_back(*vertices[i].GetPos());
		//texcoords.push_back(*vertices[i].GetTexCoord());
	//}

	//glGenBuffers(NUM_BUFFERS, m_VertexArrayBuffers);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffers[POSITION_VB]);
	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffers[TEXCOORD_VB]);
	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texcoords[0]), &texcoords[0], GL_STATIC_DRAW);

	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VertexArrayBuffers[INDEX_VB]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, numVertices * sizeof(indicies[0]), &indicies[0], GL_STATIC_DRAW);

	//glBindVertexArray(1);
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VertexArrayObject);
}

void Mesh::InitMesh(const IndexedModel& model)
{
	m_drawcount = model.indices.size();

	glGenVertexArrays(1, &m_VertexArrayObject);
	glBindVertexArray(m_VertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_VertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.positions[0]) * model.positions.size(), &model.positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.texCoords[0]) * model.texCoords.size(), &model.texCoords[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() *sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh::Draw()
{
	glBindVertexArray(m_VertexArrayObject);

	glDrawElements(GL_TRIANGLES, m_drawcount, GL_UNSIGNED_INT, 0);


	//glDrawArrays(GL_TRIANGLES, 0, m_drawcount);


	glBindVertexArray(0);
}