//#include <iostream>
//#include <SDL/SDL.h>
//#include "display.h"
////#include "mesh.h"
////#include "shader.h"
//#include "texture.h"
////#include "transform.h"
////#include "camera.h"
//#include"Ray.h"
//#include"object.h"
//
////static const int DISPLAY_WIDTH = 900;
////static const int DISPLAY_HEIGHT = 600;
////static Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
//
////void DrawPyramide();
////void DrawCone(float radiusBottom, float radiusTop, Vertex centerBottom, Vertex centerTop);
////void FindVerticesCone(float radiusBottom, float radiusTop, Vertex centerBottom, Vertex centerTop,
//	//				  std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
//void DrawAxes();
////void FindVerticesPyramid(glm::vec3 posTop, glm::vec3 posBase, glm::vec3 posVertexSquare1, glm::vec3& posVertexSquare2,
////	glm::vec3& posVertexSquare3, glm::vec3& posVertexSquare4);
//
//
//
//
//int main(int argc, char** argv)
//{
//	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
//	Ray ray(camera);
//
//	std::vector<Object *> objects;
//
//	enum class MODE{
//		DrawingPyramid,
//		DrawingCone,
//		ChoosingEdit,
//		Rotation,
//		Translating,
//		Scaling,
//		ChangingColor,
//		PickingObject
//	};
//	SDL_Event e;
//	MODE mode = MODE::DrawingPyramid;
//	bool isRunning = true;
//	float counter = 0.0f;
//	display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
//	float height;
//	float halfDiagonal;
//	glm::vec3 posBase;
//	glm::vec3 posTop;
//	glm::vec3 posVertex1;
//	bool isDrawing = true;
//	glm::vec3 posBottomCenter;
//	glm::vec3 posTopCenter;
//	float bottomRadius;
//	float topRadius;
//	float coneHeight;
//	Object* obj;
//	bool isFirstPointTR = false;
//	bool isSecondPointTR = false;
//	std::vector<Object*> chosenObjects;
//	glm::vec3 toTranslate(0, 0, 0);
//	glm::vec3 firstPoint(0, 0, 0);
//	glm::vec3 secondPoint(0, 0, 0);
//	//std::cout << "Drawing pyramids. If you want go next - click right mouse button\n";
//	while(isRunning) {
//		void DrawAxes();
//		switch (mode) {
//		case MODE::DrawingPyramid:
//			display.ChangeTitle("Drawing pyramids. Click left mouse button - base of pyramid. Click right mouse button - go to drawing cones");
//			//std::cout << "Click by right mouse button on the base of pyramid\nIf you want go to drawing cones - click somewhere by left mouse button\n";
//			break;
//		case MODE::DrawingCone:
//			display.ChangeTitle("Drawing cones. Click left mouse button - centre of bottom circle of cone. Click right - go to editing");
//			//std::cout << "Click by right mouse button on the center of bottom circle of cone\nIf you want go to editing - click somewhere by left mouse button\n";
//			break;
//		case MODE::PickingObject:
//			display.ChangeTitle("Pick the objects by clicking left mouse button on them. Click right - go to choosing what you wqnt to edit");
//			break;
//		case MODE::ChoosingEdit:
//			display.ChangeTitle("Enter s - to scale, r - to rotation, t - to translation, c - to change color");
//			break;
//		case MODE::Translating:
//			display.ChangeTitle("Click first and the second point of translating vector");
//			break;
//		}
//		while (SDL_PollEvent(&e)) {
//			switch (e.type) {
//			case SDL_QUIT: 
//				isRunning = false; 
//				break; 
//			case SDL_MOUSEBUTTONUP:
//				switch (mode) {
//				case MODE::DrawingPyramid:
//					if (e.button.button == SDL_BUTTON_LEFT) {
//						std::cout << "Enter height of pyramid\n";
//						std::cin >> height;
//						std::cout << "Enter half of diagonal of square of  pyramid\n";
//						std::cin >> halfDiagonal;
//						//std::cout << "Click position of base of pyramid by left button\n"; 
//						//posBase.x = e.button.x;// / (sqrt(e.button.x*e.button.x + e.button.y*e.button.y));
//						//posBase.y = e.button.y;// / (sqrt(e.button.x*e.button.x + e.button.y*e.button.y));
//						glm::vec3 mouseRay = ray.GetRay(e.button.x, e.button.y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
//						glm::vec3 rayUnProj = ray.RayUnProj(e.button.x, e.button.y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
//						//	posBase.x = mouseRay.x;
//							//posBase.y = mouseRay.y;
//						glm::vec3 pointScreen = (3.0f / rayUnProj.z)*rayUnProj + glm::vec3(0.0f, 0.0f, -3.0f);
//						//posBase.x = (rayUnProj.x);
//						//posBase.y = rayUnProj.y;
//						//posBase.z = 0.0f;
//						posBase.x = pointScreen.x;
//						posBase.y = -pointScreen.y;//i don't understand why but it's necessary..
//						posBase.z = pointScreen.z;
//						posTop.x = posBase.x;
//						posTop.y = posBase.y - height;
//						posTop.z = posBase.z;
//						posVertex1.x = posBase.x + halfDiagonal;
//						posVertex1.y = posBase.y;
//						posVertex1.z = posBase.z;
//						obj = new Pyramid(Vertex(posTop, glm::vec2(1, 0), glm::vec3(1, 0, 0), glm::vec4(0.6, 0.0, 0.0, 1.0)),
//							Vertex(posBase, glm::vec2(1, 0), glm::vec3(1, 0, 0), glm::vec4(0.6, 0.0, 0.0, 1.0)),
//							Vertex(posVertex1, glm::vec2(1, 0), glm::vec3(1, 0, 0), glm::vec4(0.6, 0.0, 0.0, 1.0)));
//						objects.push_back(obj);
//						//obj->Draw();
//					//	display.SwapBuffers();
//					}
//					else {
//						if (e.button.button == SDL_BUTTON_RIGHT) {
//							mode = MODE::DrawingCone;
//						}
//					}
//					break;
//				case MODE::DrawingCone:
//					if (e.button.button == SDL_BUTTON_LEFT) {
//						//glm::vec3 mouseRay = ray.GetRay(e.button.x, e.button.y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
//						glm::vec3 rayUnProj = ray.RayUnProj(e.button.x, e.button.y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
//						glm::vec3 pointScreen = (3.0f / rayUnProj.z)*rayUnProj + glm::vec3(0.0f, 0.0f, -3.0f);
//						posBottomCenter.x = pointScreen.x;
//						posBottomCenter.y = -pointScreen.y;
//						posBottomCenter.z = pointScreen.z;
//						std::cout << "Enter radius of bottom circle for this cone\n";
//						std::cin >> bottomRadius;
//						std::cout << "Enter radius of top circle for this cone\n";
//						std::cin >> topRadius;
//						std::cout << "Enter height of this cone\n";
//						std::cin >> coneHeight;
//						posTopCenter.x = posBottomCenter.x;
//						posTopCenter.y = posBottomCenter.y - coneHeight;
//						posTopCenter.z = posBottomCenter.z;
//						obj = new Cone(bottomRadius, topRadius, posBottomCenter, posTopCenter);
//						objects.push_back(obj);
//						//obj->Draw();
//						//display.SwapBuffers();
//					}
//					else {
//						if (e.button.button == SDL_BUTTON_RIGHT) {
//							mode = MODE::PickingObject;
//						}
//					}
//					break;
//				case MODE::PickingObject:
//					if (e.button.button == SDL_BUTTON_LEFT) {
//						glm::vec3 rayDirection = ray.RayUnProj(e.button.x, e.button.y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
//						float intersectionDistance;
//						for (int i = 0; i < objects.size(); i++) {
//							/*if (ray.TestRayOBBIntersection(glm::vec3(0.0f, 0.0f, 3.0f), rayDirection, objects[i]->GetMinBox(), objects[i]->GetMaxBox(),
//								objects[i]->GetModel(), intersectionDistance)) {
//								if (objects[i]->TriangleIntersection(glm::vec3(0.0f, 0.0f, 3.0f), rayDirection, ray)) {
//									chosenObjects.push_back(objects[i]);
//								}
//							}*/
//							if (objects[i]->TriangleIntersection(glm::vec3(0.0f, 0.0f, -3.0f), rayDirection, ray)) {
//								chosenObjects.push_back(objects[i]);
//							}
//						}
//					}
//					else {
//						if (e.button.button == SDL_BUTTON_RIGHT) {
//							mode = MODE::ChoosingEdit;
//						}
//					}
//					break;
//				case MODE::Translating:
//					
//					if (!isFirstPointTR) {
//						firstPoint = ray.RayUnProj(e.button.x, e.button.y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
//						firstPoint = (3.0f / firstPoint.z)*firstPoint + glm::vec3(0.0f, 0.0f, -3.0f);
//						isFirstPointTR = true;
//					}
//					else {
//						if (!isSecondPointTR) {
//							secondPoint = ray.RayUnProj(e.button.x, e.button.y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
//							secondPoint = (3.0f / secondPoint.z)*secondPoint + glm::vec3(0.0f, 0.0f, -3.0f);
//							isSecondPointTR = true;
//						}
//					}
//					if (isSecondPointTR) {
//						toTranslate = secondPoint - firstPoint;
//				//		toTranslate = glm::normalize(toTranslate);
//						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
//							chosenObjects[i]->EditPosTransfrom(toTranslate);
//						}
//						chosenObjects.resize(0);
//						mode = MODE::PickingObject;
//					}
//					break;
//				/*case MODE::Scaling:
//					glm::vec3 scale;
//					std::cout << "Enter in how many times you want to scale object(s)\nx = ";
//					std::cin >> scale.x;
//					std::cout << "y = ";
//					std::cin >> scale.y;
//					std::cout << "z = ";
//					std::cin >> scale.z;
//					for (unsigned int i = 0; i < chosenObjects.size(); i++) {
//						chosenObjects[i]->EditScaleTransform(scale);
//					}
//					chosenObjects.resize(0);
//					mode = MODE::PickingObject;
//					break;*/
//				//case MODE::Rotation: //choosing object in order to find axes to do rotation
//
//				//	break;
//				}
//			case SDL_KEYDOWN:
//				switch (e.key.keysym.sym) {
//				case SDLK_c:
//					if (mode == MODE::ChoosingEdit) {
//						mode = MODE::ChangingColor;
//					}
//					break;
//				case SDLK_t:
//					if (mode == MODE::ChoosingEdit) {
//						mode = MODE::Translating;
//						isFirstPointTR = false;
//						isSecondPointTR = false;
//					}
//					break;
//				case SDLK_r:
//					if (mode == MODE::ChoosingEdit) {
//						mode = MODE::Rotation;
//					}
//					break;
//				case SDLK_s:
//					if (mode == MODE::ChoosingEdit) {
//						mode = MODE::Scaling;
//					}
//				}
//			}
//		}
//		display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
//		DrawAxes();
//		for (int i = 0; i < objects.size(); i++) {
//			objects[i]->Draw();
//		}
//		display.SwapBuffers();
//		SDL_Delay(100);
//	}
//
//	return 0;
//}
//
////void DrawPyramide() {//Vertex* vertices) {
////	/*Vertex vertices[]{
////		Vertex(glm::vec3(0, 0 ,0.5), glm::vec2(1,0), glm::vec3(0, 0 ,1)),
////		Vertex(glm::vec3(-0.5, 0, 0), glm::vec2(1,0), glm::vec3(0, 0 ,1)),
////		Vertex(glm::vec3(0, 0, -0.5), glm::vec2(1, 0), glm::vec3(0, 0, 1)),
////		Vertex(glm::vec3(0.5, 0, 0), glm::vec2(1,0), glm::vec3(0, 0 , 1)),
////		Vertex(glm::vec3(0, 2.0 , 0), glm::vec2(1,0), glm::vec3(0, 0, 1))
////	};
////	unsigned int indices[] = 
////	{
////		0, 1, 2,
////		0, 3, 2,
////		0, 1, 4,
////		1, 2, 4,
////		2, 3, 4,
////		0, 3, 4
////	};*/
//////	Vertex vertices[]{
////		//Vertex(glm::vec3(0, 0 ,0.5), glm::vec2(1,0), glm::vec3(0, 0 ,1)),
////		//Vertex(glm::vec3(-0.5, 0, 0), glm::vec2(1,0), glm::vec3(0, 0 ,1)),
////	//	Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(1, 0), glm::vec3(0, 0, 1)),
////		//Vertex(glm::vec3(0, 0.5, 0), glm::vec2(1,0), glm::vec3(0, 0 , 1)),
////		//Vertex(glm::vec3(0.5, -0.5 , 0), glm::vec2(1,0), glm::vec3(0, 0, 1))
////	//};
////	//unsigned int indices[] =
////	//{
////		//0, 1, 2,
////		//0, 3, 2,
////		//0, 1, 4,
////		//1, 2, 4,
////		//2, 3, 4,
////		//0, 3, 4
////	//};
////	//static float counter = 0.0f;
////	//Mesh mesh(vertices, 5, indices, sizeof(indices) / sizeof(indices[0]));
////	//Shader shader("./res/basicShader");
////	//Texture texture("./res/bricks.jpg");
////	//Transform transform;
////	//Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
////	//transform.GetRot()->y = 0.5*counter;
////	//transform.GetRot()->x = 0.5*counter;
////	//transform.GetRot()->z = 0.5*counter;
////	//float count = counter*0.5;
////	//transform.SetRotAngle(count);
////	//transform.GetRotAxis()->x = 0.0;
////
////	//transform.GetScale()->x = absSinCounter;
////	//transform.GetScale()->y = absSinCounter;
////
////
////	//shader.Bind();
////	//texture.Bind();
////	//shader.Update(transform, camera);
////	//monkey.Draw();
////	//mesh.Draw();
////	//counter += 0.01f;
////
////			Vertex vertices[]{
////				Vertex(glm::vec3(0, 0 ,0.5), glm::vec2(1,0), glm::vec3(0, 0 ,1), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)),
////				Vertex(glm::vec3(-0.5, 0, 0), glm::vec2(1,0), glm::vec3(0, 0 ,1), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)),
////				Vertex(glm::vec3(0, 0, -0.5), glm::vec2(1, 0), glm::vec3(0, 0, 1), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)),
////				Vertex(glm::vec3(0.5, 0, 0), glm::vec2(1,0), glm::vec3(0, 0 , 1), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)),
////				Vertex(glm::vec3(0, 0.9, 0), glm::vec2(1,0), glm::vec3(0, 0, 1), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f))
////		};
////		unsigned int indices[] =
////		{
////			0, 1, 2,
////			0, 3, 2,
////			0, 1, 4,
////			1, 2, 4,
////			2, 3, 4,
////			0, 3, 4
////		};
////
////		static float counter = 0.0f;
////		Mesh mesh(vertices, 5, indices, 18);
////		//Mesh mesh(vertices, counterVertices+1, indices, counterIndices+1);
////
////		Shader shader("./res/basicShader");
////		Texture texture("./res/bricks.jpg");
////		Transform transform;
////		Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
////		//transform.GetRot()->y = 100*cos(counter);
////		//	transform.GetRot()->x = 100*cos(counter);
////		//transform.GetRot()->z = 40*cos(counter);
////		//transform.GetScale()->x = absSinCounter;
////		//transform.GetScale()->y = absSinCounter;
////		float count = 100 * cos(counter);
////		transform.SetRotAngle(count);
////		transform.GetRotAxis()->x = 0.0;
////		transform.GetRotAxis()->y = 1.0;
////		transform.GetRotAxis()->z = 1.0;
////		shader.Bind();
////		texture.Bind();
////		shader.Update(transform, camera);
////		//monkey.Draw();
////		mesh.Draw(GL_TRIANGLE_STRIP);
////		counter += 0.01f;
////}
////
////void DrawCone(float radiusBottom, float radiusTop, Vertex centerBottom, Vertex centerTop) {
////	const int N = 10000;
////	Vertex vertices[N];
////	glm::vec3 positions;
////	glm::vec2 texCoords;
////	glm::vec3 normals;
////	glm::vec4 colors;
////	positions.x = 0.0;
////	positions.y = 1.0;
////	positions.z = 0.0;
////	texCoords.x = 1;
////	texCoords.y = 0;
////
////	normals.x = 0;
////	normals.y = 0;
////	normals.z = 1;
////
////	colors[0] = 0.5f;
////	colors[1] = 0.0f;
////	colors[2] = 0.0f;
////	colors[3] = 1.0f;
////
////	vertices[0] = Vertex(positions, texCoords, normals, colors);
////
////	positions.x = 0.0;
////	positions.y = 0.0;
////	positions.z = 0.0;
////	vertices[1] = Vertex(positions, texCoords, normals, colors);
////	
////	unsigned int indices[N];
////	int slices = 400;
////	int counterVertices = 1;
////	int counterIndices = -1;
////	for (unsigned int i = 0; i < slices; i++) {
////		float theta = ((float)i)*2.0*M_PI/float(slices);
////		float nextTheta = ((float)i + 1)*2.0*M_PI/float(slices);
////		//positions.x = centerTop.GetPos()->x + radiusTop*cos(theta);
////		//positions.y = centerTop.GetPos()->y;
////		//positions.z = centerTop.GetPos()->z + radiusTop*sin(theta);
////		positions.x = radiusTop*cos(theta);
////		positions.y = 1.0;
////		positions.z = radiusTop*sin(theta);
////		
////		texCoords.x = 1;
////		texCoords.y = 0;
////
////		normals.x = 0;
////		normals.y = 0;
////		normals.z = 1;
////
////		vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
////
////
////		//positions.x = centerTop.GetPos()->x + radiusTop*cos(nextTheta);
////		//positions.y = centerTop.GetPos()->y;
////		//positions.z = centerTop.GetPos()->z + radiusTop*sin(nextTheta);
////
////		positions.x = radiusTop*cos(nextTheta);
////		positions.y = 1.0;
////		positions.z = radiusTop*sin(nextTheta);
////
////		vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
////
////
////		//positions.x = centerBottom.GetPos()->x + radiusBottom*cos(theta);
////		//positions.y = centerBottom.GetPos()->y;
////		//positions.z = centerBottom.GetPos()->z + radiusBottom*sin(theta);
////		//vertices[++counterVertices].MakeVertex(positions, texCoords, normals);
////		positions.x = radiusBottom*cos(theta);
////		positions.y = 0.0;
////		positions.z = radiusBottom*sin(theta);
////		vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
////
////
////
////		//positions.x = centerBottom.GetPos()->x + radiusBottom*cos(nextTheta);
////		//positions.y = centerBottom.GetPos()->y;
////		//positions.z = centerBottom.GetPos()->z + radiusBottom*sin(nextTheta);
////		positions.x = radiusBottom*cos(nextTheta);
////		positions.y = 0.0;
////		positions.z = radiusBottom*sin(nextTheta);
////		vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
////
////
////
////		indices[++counterIndices] = 0;
////		indices[++counterIndices] = counterVertices - 3;
////		indices[++counterIndices] = counterVertices - 2;
////
////		indices[++counterIndices] = counterVertices - 3;
////		indices[++counterIndices] = counterVertices - 2;
////		indices[++counterIndices] = counterVertices - 1;
////
////		indices[++counterIndices] = counterVertices - 2;
////		indices[++counterIndices] = counterVertices - 1;
////		indices[++counterIndices] = counterVertices;
////
////		indices[++counterIndices] = counterVertices - 1;
////		indices[++counterIndices] = counterVertices;
////		indices[++counterIndices] = 1;
////	}
////	///////////////////////////////////////
////	/*Vertex vertices[]{
////		//Vertex(glm::vec3(0, 0 ,0.5), glm::vec2(1,0), glm::vec3(0, 0 ,1)),
////		//Vertex(glm::vec3(-0.5, 0, 0), glm::vec2(1,0), glm::vec3(0, 0 ,1)),
////		Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(1, 0), glm::vec3(0, 0, 1)),
////		Vertex(glm::vec3(0, 0.5, 0), glm::vec2(1,0), glm::vec3(0, 0 , 1)),
////		Vertex(glm::vec3(0.5, -0.5 , 0), glm::vec2(1,0), glm::vec3(0, 0, 1))
////	};
////	unsigned int indices[] =
////	{
////		0, 1, 2,
////		//0, 3, 2,
////		//0, 1, 4,
////		//1, 2, 4,
////		//2, 3, 4,
////		//0, 3, 4
////	};
////	*/
////	static float counter = 0.0f;
////	//Mesh mesh(vertices, 3, indices, 3);
////	Mesh mesh(vertices, counterVertices+1, indices, counterIndices+1);
////
////	Shader shader("./res/basicShader");
////	//Texture texture("./res/bricks.jpg");
////	Transform transform;
////	Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
////	//transform.GetRot()->y = 100*cos(counter);
//////	transform.GetRot()->x = 100*cos(counter);
////	//transform.GetRot()->z = 40*cos(counter);
////	//transform.GetScale()->x = absSinCounter;
////	//transform.GetScale()->y = absSinCounter;
////	float count = 100 * cos(counter);
////	transform.SetRotAngle(count);
////	transform.GetRotAxis()->x = 0.0;
////	transform.GetRotAxis()->y = 1.0;
////	transform.GetRotAxis()->z = 0.0;
////	shader.Bind();
////	//texture.Bind();
////	shader.Update(transform, camera);
////	//monkey.Draw();
////	mesh.Draw(GL_TRIANGLE_STRIP);
////	counter += 0.01f;
////}
//
//
//
////void FindVerticesCone(float radiusBottom, float radiusTop, Vertex centerBottom, Vertex centerTop, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
////	glm::vec3 positions;
////	glm::vec2 texCoords;
////	glm::vec3 normals;
////	glm::vec4 colors;
////	
////
////	texCoords.x = 1;
////	texCoords.y = 0;
////
////	normals.x = 0;
////	normals.y = 0;
////	normals.z = 1;
////
////	colors[0] = 0.5f;
////	colors[1] = 0.0f;
////	colors[2] = 0.0f;
////	colors[3] = 1.0f;
////
////	float height = sqrt(pow(centerBottom.GetPos()->x - centerTop.GetPos()->x, 2) + pow(centerBottom.GetPos()->y - centerTop.GetPos()->y, 2) +
////						pow(centerBottom.GetPos()->z - centerTop.GetPos()->z, 2));
////
////	positions.x = centerBottom.GetPos()->x;
////	positions.y = centerBottom.GetPos()->y + height;
////	positions.z = centerBottom.GetPos()->z;
////
////	vertices.push_back(Vertex(positions, texCoords, normals, colors));
////
////	//positions.x = 0.0;
////	//positions.y = 0.0;
////	//positions.z = 0.0;
////	positions.x = centerTop.GetPos()->x;
////	positions.y = centerTop.GetPos()->y;
////	positions.z = centerTop.GetPos()->z;
////	vertices.push_back(Vertex(positions, texCoords, normals, colors));
////
////	int slices = 400;
////	//int counterVertices = 1;
////	//int counterIndices = -1;
////	for (unsigned int i = 0; i < slices; i++) {
////		float theta = ((float)i)*2.0*M_PI / float(slices);
////		float nextTheta = ((float)i + 1)*2.0*M_PI / float(slices);
////		//positions.x = centerTop.GetPos()->x + radiusTop*cos(theta);
////		//positions.y = centerTop.GetPos()->y;
////		//positions.z = centerTop.GetPos()->z + radiusTop*sin(theta);
////		positions.x = radiusTop*cos(theta);
////		positions.y = 1.0;
////		positions.z = radiusTop*sin(theta);
////
////		texCoords.x = 1;
////		texCoords.y = 0;
////
////		normals.x = 0;
////		normals.y = 0;
////		normals.z = 1;
////
////		//vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
////		vertices.push_back(Vertex(positions, texCoords, normals, colors));
////
////		//positions.x = centerTop.GetPos()->x + radiusTop*cos(nextTheta);
////		//positions.y = centerTop.GetPos()->y;
////		//positions.z = centerTop.GetPos()->z + radiusTop*sin(nextTheta);
////
////		positions.x = radiusTop*cos(nextTheta);
////		positions.y = 1.0;
////		positions.z = radiusTop*sin(nextTheta);
////
////		//vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
////		vertices.push_back(Vertex(positions, texCoords, normals, colors));
////
////		//positions.x = centerBottom.GetPos()->x + radiusBottom*cos(theta);
////		//positions.y = centerBottom.GetPos()->y;
////		//positions.z = centerBottom.GetPos()->z + radiusBottom*sin(theta);
////		//vertices[++counterVertices].MakeVertex(positions, texCoords, normals);
////		positions.x = radiusBottom*cos(theta);
////		positions.y = 0.0;
////		positions.z = radiusBottom*sin(theta);
////	//	vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
////		vertices.push_back(Vertex(positions, texCoords, normals, colors));
////
////
////		//positions.x = centerBottom.GetPos()->x + radiusBottom*cos(nextTheta);
////		//positions.y = centerBottom.GetPos()->y;
////		//positions.z = centerBottom.GetPos()->z + radiusBottom*sin(nextTheta);
////		positions.x = radiusBottom*cos(nextTheta);
////		positions.y = 0.0;
////		positions.z = radiusBottom*sin(nextTheta);
////		//vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
////		vertices.push_back(Vertex(positions, texCoords, normals, colors));
////
////
////		indices.push_back(0); 
////		indices.push_back(vertices.size() - 4);
////		indices.push_back(vertices.size() - 3);
////
////		indices.push_back(vertices.size() - 4);
////		indices.push_back(vertices.size() - 3);
////		indices.push_back(vertices.size() - 2);
////
////		indices.push_back(vertices.size() - 3);
////		indices.push_back(vertices.size() - 2);
////		indices.push_back(vertices.size() - 1);
////
////		indices.push_back(vertices.size() - 2);
////		indices.push_back(vertices.size() - 1);
////		indices.push_back(1);
////	}
////}
//
//
//void DrawAxes() {
//	Vertex vertices[]{
//		Vertex(glm::vec3(0.0f,0.0f,-10.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)),
//		Vertex(glm::vec3(0.0f, 0.0f, 10.0f),  glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))
//	};
//	unsigned int indices[]{
//		0, 1
//	};
//	Transform transform;
//	float count = 10;
//	//transform.SetRotAngle(count);
//	//transform.GetRotAxis()->x = 0.1f;
//	//transform.GetRotAxis()->y = 0.0f;
//	//transform.GetRotAxis()->z = 0.5f;
//	Shader shader("./res/basicShader");
//	Mesh meshZ(vertices, 2, indices, 2);
//	shader.Bind();
//	shader.Update(transform, camera);
//	meshZ.Draw(GL_LINES);
//	vertices[0] = Vertex(glm::vec3(0.0f, -10.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
//	vertices[1] = Vertex(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
//	Mesh meshY(vertices, 2, indices, 2);
//	meshY.Draw(GL_LINES);
//	vertices[0] = Vertex(glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
//	vertices[1] = Vertex(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
//	Mesh meshX(vertices, 2, indices, 2);
//	meshX.Draw(GL_LINES);
//}