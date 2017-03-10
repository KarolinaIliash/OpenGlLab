#include "mesh.h"
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include<vector>

//Mesh::Mesh(const std::string& fileName)
//{
	//InitMesh(OBJModel(fileName).ToIndexedModel());
//}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)//, unsigned int* indices, unsigned int numIndices)
{
	//m_drawCount = numIndices;
	m_drawCount = numVertices;



	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	std::vector<glm::vec3> positions;

	for (unsigned int i = 0; i < numVertices; i++) {
		positions.push_back(*vertices[i].GetPos());
	}

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);


	glBindVertexArray(0);
}



Mesh::~Mesh()
{
//	glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
	//glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	//glDrawElementsBaseVertex(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0, 0);

	glBindVertexArray(0);
}