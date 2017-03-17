#include"object.h"

#define _USE_MATH_DEFINES
#include <math.h> 

static unsigned int indicePyramid[]{
		0, 1, 2,
		0, 3, 2,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		0, 3, 4
	};


//static std::vector<unsigned int> indicesTopCircle;
//static std::vector<unsigned int> indicesBottomCircle;
//static std::vector<unsigned int> indicesBody;

Pyramid::Pyramid(Vertex Top, Vertex Base, Vertex Vertex1/*, glm::vec2 tex1Triangle, glm::vec2 tex2Triangle, 
				 glm::vec2 tex3Triangle, glm::vec2 tex4Triangle, glm::vec2 texSquare*/) {
	this->Top = Top;
	this->Base = Base;
	this->Vertex1 = Vertex1;
	/*this->textureFirstTriangle = tex1Triangle;
	this->textureSecondTriangle = tex2Triangle;
	this->textureThirdTriangle = tex3Triangle;
	this->textureFourthTriangle = tex4Triangle;
	this->textureSquare = texSquare;*/
	//this->isPyramide = isPyramide;
}
//std::vector<Vertex> GetVertices() {
//return vertices;
//}
//void SetVertices(std::vector<Vertex> vertices) {
//this->vertices = vertices;
//}



void Pyramid::FindVerticesPyramid(glm::vec3 posTop, glm::vec3 posBase, glm::vec3 posVertexSquare1, glm::vec3& posVertexSquare2,
	glm::vec3& posVertexSquare3, glm::vec3& posVertexSquare4) {
	glm::vec3 vectorHeight = glm::vec3(posTop.x - posBase.x, posTop.y - posBase.y, posTop.z - posBase.z);
	glm::vec3 vectorDiagonal = glm::vec3(posVertexSquare1.x - posBase.x, posVertexSquare1.y - posBase.y,
		posVertexSquare1.z - posBase.z);
	glm::vec3 vectorSecondDiagonal = glm::cross(vectorHeight, vectorDiagonal);
	float coeficient1;
	float coeficient2;
	float SquareHalfOfDiagonal = pow((posVertexSquare1.x - posBase.x), 2) + pow((posVertexSquare1.y - posBase.y), 2) +
		pow((posVertexSquare1.z - posBase.z), 2);
	float xExactlyVector = vectorSecondDiagonal.x - posBase.x;
	float yExactlyVector = vectorSecondDiagonal.y - posBase.y;
	float zExactlyVector = vectorSecondDiagonal.z - posBase.z;
	//Now we have quadratic equation relative to variable coeficient. let coefs of this equation = a, b, c
	float a = pow(xExactlyVector, 2) + pow(yExactlyVector, 2) + pow(zExactlyVector, 2);
	float b = -2 * (xExactlyVector*posBase.x + yExactlyVector*posBase.y + zExactlyVector*posBase.z);
	float c = -SquareHalfOfDiagonal + pow(posBase.x, 2) + pow(posBase.y, 2) + pow(posBase.z, 2);
	float Discriminant = b*b - 4 * a*c;
	coeficient1 = (-b + sqrt(Discriminant)) / (2 * a);
	coeficient2 = (-b - sqrt(Discriminant)) / (2 * a);
	posVertexSquare2 = glm::vec3(coeficient1*xExactlyVector, coeficient1*yExactlyVector, coeficient1*zExactlyVector);
	posVertexSquare3 = glm::vec3(2 * posBase.x - posVertexSquare1.x, 2 * posBase.y - posVertexSquare1.y, 2 * posBase.z - posVertexSquare1.z);
	posVertexSquare4 = glm::vec3(coeficient2*xExactlyVector, coeficient2*yExactlyVector, coeficient2*zExactlyVector);
}

static void find_min_max(std::vector<glm::vec3> points, float& minZ, float& minX, float& maxZ, float& maxX) {
	minX = 10000;
	minZ = 10000;
	maxX = -10000;
	maxZ = -10000;
	for (int i = 0; i < points.size(); i++) {
		if (points[i].x < minX) {
			minX = points[i].x;
		}
		if (points[i].x > maxX) {
			maxX = points[i].x;
		}
		if (points[i].z < minZ) {
			minZ = points[i].z;
		}
		if (points[i].z > maxZ) {
			maxZ = points[i].z;
		}
	}
}

void Pyramid::Draw(){
	glm::vec3 posVertex2;
	glm::vec3 posVertex3;
	glm::vec3 posVertex4;
	FindVerticesPyramid(*Top.GetPos(), *Base.GetPos(), *Vertex1.GetPos(), posVertex2, posVertex3, posVertex4);
	if (Top.GetPos()->y > Base.GetPos()->y) {
		maxBox.y = Top.GetPos()->y;
		minBox.y = Base.GetPos()->y;
	}
	else {
		maxBox.y = Base.GetPos()->y;
		minBox.y = Top.GetPos()->y;
	}
	std::vector<glm::vec3> points(4);
	points[0] = *Vertex1.GetPos();
	points[1] = posVertex2;
	points[2] = posVertex3;
	points[3] = posVertex4;
	find_min_max(points, minBox.z, minBox.x, maxBox.z, maxBox.x);
	Vertex2.MakeVertex(posVertex2, glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
	Vertex3.MakeVertex(posVertex3, glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
	Vertex4.MakeVertex(posVertex4, glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
	Vertex vertice[]{
		Vertex1, Vertex2, Vertex3, Vertex4, Top
	};
		
	static float counter = 0.0f;
	Shader shader("./res/basicShader");
	//Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
	Mesh mesh(vertice, 5, indicePyramid, 18);
	float count = 10 * cos(counter);
	//transform.SetRotAngle(count);
	//	transform.GetRotAxis()->x = 0.0f;
	//transform.GetRotAxis()->y = 1.0f;
	//transform.GetRotAxis()->z = 1.0f;
	shader.Bind();
	shader.Update(transform, camera);
	mesh.Draw(GL_TRIANGLE_STRIP);
	//	transform.SetQuaternion(glm::quat(0.0f, 0.0f, 0.0f, 1.0f));

	counter += 0.001f;
}

bool Pyramid::TriangleIntersection(glm::vec3 rayOrigin, glm::vec3 rayDirection, Ray ray) {
	std::vector<Vertex> vertices{ Vertex1, Vertex2, Vertex3, Vertex4, Top };
	glm::vec4 posV1 = (this->GetModel() * glm::vec4(*Vertex1.GetPos(), 1));
	glm::vec4 posV2 = (this->GetModel() * glm::vec4(*Vertex1.GetPos(), 1));
	glm::vec4 posV3 = (this->GetModel() * glm::vec4(*Vertex1.GetPos(), 1));
	glm::vec4 posV4 = (this->GetModel() * glm::vec4(*Vertex1.GetPos(), 1));
	glm::vec4 posTop = (this->GetModel() * glm::vec4(*Vertex1.GetPos(), 1));
	std::vector<glm::vec3> curPos = { glm::vec3(posV1.x, posV1.y, posV1.z), glm::vec3(posV2.x, posV2.y, posV2.z), glm::vec3(posV3.x, posV3.y, posV3.z),
									 glm::vec3(posV4.x, posV4.y, posV4.z), glm::vec3(posTop.x, posTop.y, posTop.z) };
	float* out;
	for (int i = 0; i < 18; i += 3) {
		if (ray.TriangleIntersection(curPos[indicePyramid[i]], curPos[indicePyramid[i + 1]], curPos[indicePyramid[i + 2]], rayOrigin, rayDirection, out)) {
			return true;
		};
	}
}

glm::vec3 Pyramid::GetObjectAxis() {
	glm::vec4 temp = this->GetModel() * glm::vec4(*Top.GetPos(), 1);
	glm::vec3 curPosTop(temp.x, temp.y, temp.z);
	temp = this->GetModel() * glm::vec4(*Base.GetPos(), 1);
	glm::vec3 curPosBase(temp.x, temp.y, temp.z);
	return curPosTop - curPosBase;
}



Cone::Cone(float radiusBottom, float radiusTop, glm::vec3 posBottomCenter, glm::vec3 posTopCenter) {
	this->radiusBottom = radiusBottom;
	this->radiusTop = radiusTop;
	this->posBottomCenter.x = posBottomCenter.x;
	this->posBottomCenter.y = posBottomCenter.y;
	this->posBottomCenter.z = posBottomCenter.z;
	this->posTopCenter.x = posTopCenter.x;
	this->posTopCenter.y = posTopCenter.y;
	this->posTopCenter.z = posTopCenter.z;
}

void Cone::FindVerticesCone(std::vector<Vertex>& vertices, std::vector<unsigned int>& indicesBottomCircle, std::vector<unsigned int>& indicesTopCircle, 
							std::vector<unsigned int>& indicesBody) {
	glm::vec3 positions;
	glm::vec2 texCoords;
	glm::vec3 normals;
	glm::vec4 colors;
	positions.x = posTopCenter.x;
	positions.y = posTopCenter.y;
	positions.z = posTopCenter.z;
	texCoords.x = 1;
	texCoords.y = 0;

	normals.x = 0;
	normals.y = 0;
	normals.z = 1;

	colors[0] = 0.5f;
	colors[1] = 0.0f;
	colors[2] = 0.0f;
	colors[3] = 1.0f;

	vertices.push_back(Vertex(positions, texCoords, normals, colors));

	float x = posBottomCenter.x;
	float z = posBottomCenter.z;

	positions.x = posBottomCenter.x;
	positions.y = posBottomCenter.y;
	positions.z = posBottomCenter.z;
	vertices.push_back(Vertex(positions, texCoords, normals, colors));

	int slices = 350;
	for (unsigned int i = 0; i < slices; i++) {
		float theta = (float)i * 2.0f * M_PI / float(slices);
		positions.x = x + radiusTop*cos(theta);
		positions.y = posTopCenter.y;
		positions.z = z + radiusTop*sin(theta);
		texCoords.x = 1;
		texCoords.y = 0;

		normals.x = 0;
		normals.y = 0;
		normals.z = 1;
		vertices.push_back(Vertex(positions, texCoords, normals, colors));

		if (i != 0) {
			indicesTopCircle.push_back(vertices.size() - 1);
		}
		indicesTopCircle.push_back(0);
		indicesTopCircle.push_back(vertices.size() - 1);
		if (i == slices - 1) {
			indicesTopCircle.push_back(2);
		}

		positions.x = x + radiusBottom*cos(theta);
		positions.y = posBottomCenter.y;
		positions.z = z + radiusBottom*sin(theta);

		vertices.push_back(Vertex(positions, texCoords, normals, colors));
		if (i != 0) {
			indicesBottomCircle.push_back(vertices.size() - 1);
		}
		indicesBottomCircle.push_back(0);
		indicesBottomCircle.push_back(vertices.size() - 1);
		if (i == slices - 1) {
			indicesBottomCircle.push_back(3);
		}
	}
		for (unsigned int i = 3; i < vertices.size() - 1; i++) {
			indicesBody.push_back(i - 1);
			indicesBody.push_back(i);
			indicesBody.push_back(i + 1);
		}
	indicesBody.push_back(vertices.size() - 2);
	indicesBody.push_back(vertices.size() - 1);
	indicesBody.push_back(2);
	indicesBody.push_back(vertices.size() - 1);
	indicesBody.push_back(2);
	indicesBody.push_back(3);
}

void Cone::Draw(){
	Vertex centerBottom(posBottomCenter, glm::vec2(1.0, 0.0), glm::vec3(1.0, 0.0, 1.0), glm::vec4(0.5, 0.0, 0.0, 1.0));
	Vertex centerTop(posTopCenter, glm::vec2(1.0, 0.0), glm::vec3(1.0, 0.0, 1.0), glm::vec4(0.5, 0.0, 0.0, 1.0));
	//std::vector<Vertex> vertices;
	//std::vector<unsigned int> indicesTopCircle;
	//std::vector<unsigned int> indicesBottomCircle;
	//std::vector<unsigned int> indicesBody;
	FindVerticesCone(vertices, indicesBottomCircle, indicesTopCircle, indicesBody);

	if (posBottomCenter.y > posTopCenter.y) {
		minBox.y = posTopCenter.y;
		maxBox.y = posBottomCenter.y;
	}
	else {
		minBox.y = posBottomCenter.y;
		maxBox.y = posTopCenter.y;
	}

	if (radiusBottom > radiusTop) {
		minBox.x = posBottomCenter.x - radiusBottom;
		maxBox.x = posBottomCenter.x + radiusBottom;
		minBox.z = posBottomCenter.z - radiusBottom;
		maxBox.z = posBottomCenter.z + radiusBottom;
	}

	else {
		minBox.x = posTopCenter.x - radiusTop;
		maxBox.x = posTopCenter.x + radiusTop;
		minBox.z = posTopCenter.z - radiusTop;
		maxBox.z = posTopCenter.z + radiusTop;
	}

	Vertex* vertice = new Vertex[vertices.size()];
	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertice[i] = vertices[i];
	}
	unsigned int* indiceBCircle = new unsigned int[indicesBottomCircle.size()];
	for (unsigned int i = 0; i < indicesBottomCircle.size(); i++) {
		indiceBCircle[i] = indicesBottomCircle[i];
	}
	unsigned int* indiceTCircle = new unsigned int[indicesTopCircle.size()];
	for (unsigned int i = 0; i < indicesTopCircle.size(); i++) {
		indiceTCircle[i] = indicesTopCircle[i];
	}
	unsigned int* indiceBody = new unsigned int[indicesBody.size()];
	for (unsigned int i = 0; i < indicesBody.size(); i++) {
		indiceBody[i] = indicesBody[i];
	}
	Mesh meshBCircle(vertice, vertices.size(), indiceBCircle, indicesBottomCircle.size());
	Mesh meshTCircle(vertice, vertices.size(), indiceTCircle, indicesTopCircle.size());
	Mesh meshBody(vertice, vertices.size(), indiceBody, indicesBody.size());
	Shader shader("./res/basicShader");
	shader.Bind();
	shader.Update(transform, camera);
	meshBCircle.Draw(GL_TRIANGLE_STRIP);
	meshTCircle.Draw(GL_TRIANGLE_STRIP);
	meshBody.Draw(GL_TRIANGLE_STRIP);
}


bool Cone::TriangleIntersection(glm::vec3 rayOrigin, glm::vec3 rayDirection, Ray ray) {
	std::vector<glm::vec3> curPos(vertices.size());
	glm::vec4 temp;
	for (int i = 0; i < vertices.size(); i++) {
		temp = this->GetModel() * glm::vec4(*vertices[i].GetPos(), 1);
		curPos[i] = glm::vec3(temp.x, temp.y, temp.z);
	}
	float* out;
	for (unsigned int i = 0; i < indicesBottomCircle.size(); i += 3) {
		if (ray.TriangleIntersection(curPos[indicesBottomCircle[i]], curPos[indicesBottomCircle[i + 1]], curPos[indicesBottomCircle[i + 2]], rayOrigin, rayDirection, out)) {
			return true;
		}
	}
	for (unsigned int i = 0; i < indicesTopCircle.size(); i += 3) {
		if (ray.TriangleIntersection(curPos[indicesTopCircle[i]], curPos[indicesTopCircle[i + 1]], curPos[indicesTopCircle[i + 2]], rayOrigin, rayDirection, out)) {
			return true;
		}
	}
	for (unsigned int i = 0; i < indicesBody.size(); i += 3) {
		if (ray.TriangleIntersection(curPos[indicesBody[i]], curPos[indicesBody[i + 1]], curPos[indicesBody[i + 2]], rayOrigin, rayDirection, out)) {
			return true;
		}
	}
}

glm::vec3 Cone::GetObjectAxis() {
	glm::vec4 temp = this->GetModel() * glm::vec4(posBottomCenter, 1);
	glm::vec3 curPosBottom(temp.x, temp.y, temp.z);
	temp = this->GetModel() * glm::vec4(posTopCenter, 1);
	glm::vec3 curPosTop(temp.x, temp.y, temp.z);
	return curPosTop - curPosBottom;
}