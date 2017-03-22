#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
//#include "obj_loader.h"

struct Vertex
{
public:
	Vertex() 
	{
	}
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal, const glm::vec4& color)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
		this->color = color;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }
	glm::vec4* GetColor() { return &color; }


	void MakeVertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal, const glm::vec4& color = glm::vec4(0.5f, 0.0f, 0.0f, 1.0f))
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
		this->color = color;
	}

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
	glm::vec4 color;
};

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	COLOR_VB,
	INDEX_VB,
	

	NUM_BUFFERS = 4
};

class Mesh
{
public:
//	Mesh(const std::string& fileName);
	Mesh(std::vector<Vertex>vertices, unsigned int numVertices, std::vector<unsigned int> indices, unsigned int numIndices);

	void Draw(GLenum mode);

	virtual ~Mesh();
protected:
private:
//	static const unsigned int NUM_BUFFERS = 4;
	void operator=(const Mesh& mesh) {}
	Mesh(const Mesh& mesh) {}

//	void InitMesh(const IndexedModel& model);

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_numIndices;
};

#endif