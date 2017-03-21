#include <iostream>
#include <SDL/SDL.h>
#include "display.h"
//#include "mesh.h"
//#include "shader.h"
#include "texture.h"
//#include "transform.h"
//#include "camera.h"
#include"Ray.h"
#include"object.h"

//static const int DISPLAY_WIDTH = 900;
//static const int DISPLAY_HEIGHT = 600;
//static Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);

//void DrawPyramide();
//void DrawCone(float radiusBottom, float radiusTop, Vertex centerBottom, Vertex centerTop);
//void FindVerticesCone(float radiusBottom, float radiusTop, Vertex centerBottom, Vertex centerTop,
//				  std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
void DrawAxes();
//void FindVerticesPyramid(glm::vec3 posTop, glm::vec3 posBase, glm::vec3 posVertexSquare1, glm::vec3& posVertexSquare2,
//	glm::vec3& posVertexSquare3, glm::vec3& posVertexSquare4);




int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	Ray ray(camera);

	std::vector<Object *> objects;

	enum class MODE {
		DrawingPyramid,
		DrawingCone,
		ChoosingEdit,
		Rotation,
		Translating,
		Scaling,
		ChangingColor,
		PickingObject
	};
	SDL_Event e;
	MODE mode = MODE::DrawingPyramid;
	bool isRunning = true;
	float counter = 0.0f;
	display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
	float height;
	float halfDiagonal;
	glm::vec3 posBase;
	glm::vec3 posTop;
	glm::vec3 posVertex1;
	bool isDrawing = true;
	glm::vec3 posBottomCenter;
	glm::vec3 posTopCenter;
	float bottomRadius;
	float topRadius;
	float coneHeight;
	Object* obj;
	bool isFirstPointTR = false;
	bool isSecondPointTR = false;
	std::vector<Object*> chosenObjects;
	glm::vec3 toTranslate(0, 0, 0);
	glm::vec3 firstPoint(0, 0, 0);
	glm::vec3 secondPoint(0, 0, 0);
	//std::cout << "Drawing pyramids. If you want go next - click right mouse button\n";
	while (isRunning) {
		//void DrawAxes();
		switch (mode) {
		case MODE::DrawingPyramid:
			display.ChangeTitle("Drawing pyramids. Click left mouse button - base of pyramid. Click right mouse button - go to drawing cones");
			//std::cout << "Click by right mouse button on the base of pyramid\nIf you want go to drawing cones - click somewhere by left mouse button\n";
			break;
		case MODE::DrawingCone:
			display.ChangeTitle("Drawing cones. Click left mouse button - centre of bottom circle of cone. Click right - go to editing");
			//std::cout << "Click by right mouse button on the center of bottom circle of cone\nIf you want go to editing - click somewhere by left mouse button\n";
			break;
		case MODE::PickingObject:
			display.ChangeTitle("Pick the objects by clicking left mouse button on them. Click right - go to choosing what you wqnt to edit");
			break;
		case MODE::ChoosingEdit:
			display.ChangeTitle("Enter s - to scale, r - to rotation, t - to translation, c - to change color");
			break;
		case MODE::Translating:
			display.ChangeTitle("Click first and the second point of translating vector");
			break;
		}
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_MOUSEBUTTONUP:
				switch (mode) {
				case MODE::DrawingPyramid:
					if (e.button.button == SDL_BUTTON_LEFT) {
						std::cout << "Enter height of pyramid\n";
						std::cin >> height;
						std::cout << "Enter half of diagonal of square of  pyramid\n";
						std::cin >> halfDiagonal;
	
						glm::vec3 mouseRay = ray.GetRay(e.button.x, e.button.y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
						float t = cameraPosition.y / (mouseRay - cameraPosition).y;
						glm::vec3 pointScreen;
						pointScreen.x = cameraPosition.x + t * (mouseRay - cameraPosition).x;
						pointScreen.y = cameraPosition.y + t * (mouseRay - cameraPosition).y;
						pointScreen.z = cameraPosition.z + t * (mouseRay - cameraPosition).z;
					//	glm::vec3 pointNearPlane = ray.RayUnProj(e.button.x, e.button.y, 0.0f, DISPLAY_WIDTH, DISPLAY_HEIGHT);
						//glm::vec3 pointFarPlane = ray.RayUnProj(e.button.x, e.button.y, 1.0f, DISPLAY_WIDTH, DISPLAY_HEIGHT);
						/*float t = pointFarPlane.y / (pointFarPlane - pointNearPlane).y;
						glm::vec3 pointScreen;
						pointScreen.x = pointFarPlane.x + t*(pointFarPlane - pointNearPlane).x;
						pointScreen.y = pointFarPlane.y + t*(pointFarPlane - pointNearPlane).y;
						pointScreen.z = pointFarPlane.z + t*(pointFarPlane - pointNearPlane).z;*/
						//glm::vec3 pointScreen = glm::vec3(pointNearPlane.x, pointNearPlane.y, -(pointNearPlane.z + pointFarPlane.z) / 2.0f);
					//	glm::vec3 pointScreen = cameraPosition - glm::vec3(5*rayUnProj.x, 5*rayUnProj.y, 5*rayUnProj.z);
						//Vertex rayVertex(pointNearPlane, glm::vec2(1.0, 0.0), glm::vec3(1, 1, 1), glm::vec4(1.0, 1.0, 1.0, 1.0));
						//Vertex cameraVertex(pointFarPlane, glm::vec2(1.0, 0.0), glm::vec3(1, 1, 1), glm::vec4(0.9, 1.0, 1.0, 1.0));
						//Vertex raypoint1(glm::vec3(cameraPosition.x + 5 * mouseRay.x, cameraPosition.y + 5 * mouseRay.y, cameraPosition.z + 5 * mouseRay.z),
						//	glm::vec2(1.0, 0.0), glm::vec3(1, 1, 1), glm::vec4(1.0, 1.0, 1.0, 1.0));
						//Vertex raypoint2(glm::vec3(cameraPosition.x + 7 * mouseRay.x, cameraPosition.y + 7 * mouseRay.y, cameraPosition.z + 7 * mouseRay.z),
						//	glm::vec2(1.0, 0.0), glm::vec3(1, 1, 1), glm::vec4(1.0, 1.0, 1.0, 1.0));
						////Vertex verticeray[] = { rayVertex, cameraVertex };
						//Vertex verticeray[] = { raypoint1, raypoint2 };
						//unsigned int indiceray[] = { 0,1 };
						//Mesh rayMesh(verticeray, 2, indiceray, 2);
						//Shader shader("./res/basicShader");
						//Transform transform;
						//shader.Bind();
						//transform.EditScale(glm::vec3(100, 100, 100));
						//camera.set_pos(glm::vec3(2, 10, 10));
						//	shader.Update(transform, camera);
						//rayMesh.Draw(GL_LINES);
						//camera.set_pos(glm::vec3(-2, 10, 10));
						obj = new Pyramid();
						//obj->EditPosTransfrom(pointScreen);
						//obj->EditPosTransfrom(glm::vec3(2, 2, 15));
						//obj->EditScaleTransform(glm::vec3(halfDiagonal, height, halfDiagonal));
						objects.push_back(obj);
					
					}
					else {
						if (e.button.button == SDL_BUTTON_RIGHT) {
							mode = MODE::DrawingCone;
						}
					}
					break;
				case MODE::DrawingCone:
					if (e.button.button == SDL_BUTTON_LEFT) {
						//glm::vec3 mouseRay = ray.GetRay(e.button.x, e.button.y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
					//	glm::vec3 rayUnProj = ray.RayUnProj(e.button.x, e.button.y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
					//	glm::vec3 pointScreen = (3.0f / rayUnProj.z)*rayUnProj + glm::vec3(0.0f, 0.0f, -3.0f);
						//glm::vec3 pointScreen = cameraPosition + rayUnProj;
					/*	posBottomCenter.x = pointScreen.x;
						posBottomCenter.y = -pointScreen.y;
						posBottomCenter.z = pointScreen.z;*/
						std::cout << "Enter radius of bottom circle for this cone\n";
						std::cin >> bottomRadius;
						std::cout << "Enter radius of top circle for this cone\n";
						std::cin >> topRadius;
						std::cout << "Enter height of this cone\n";
						std::cin >> coneHeight;
					/*	posTopCenter.x = posBottomCenter.x;
						posTopCenter.y = posBottomCenter.y - coneHeight;
						posTopCenter.z = posBottomCenter.z;*/
						obj = new Cone(bottomRadius/topRadius);
					//	obj->EditPosTransfrom(pointScreen);
						obj->EditScaleTransform(glm::vec3(bottomRadius, coneHeight, topRadius));
						objects.push_back(obj);
						//obj->Draw();
						//display.SwapBuffers();
					}
					else {
						if (e.button.button == SDL_BUTTON_RIGHT) {
							mode = MODE::PickingObject;
						}
					}
					break;
				case MODE::PickingObject:
					if (e.button.button == SDL_BUTTON_LEFT) {
					////	glm::vec3 rayDirection = ray.RayUnProj(e.button.x, e.button.y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
					//	glm::vec3 rayDirection = ray.GetRay(e.button.x, e.button.y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
					//	float intersectionDistance;
						//for (int i = 0; i < objects.size(); i++) {
						//	/*if (ray.TestRayOBBIntersection(glm::vec3(0.0f, 0.0f, 3.0f), rayDirection, objects[i]->GetMinBox(), objects[i]->GetMaxBox(),
						//	objects[i]->GetModel(), intersectionDistance)) {
						//	if (objects[i]->TriangleIntersection(glm::vec3(0.0f, 0.0f, 3.0f), rayDirection, ray)) {
						//	chosenObjects.push_back(objects[i]);
						//	}
						//	}*/
						//	/*if (objects[i]->TriangleIntersection(cameraPosition, rayDirection, ray)) {
						//		chosenObjects.push_back(objects[i]);
						//	}*/

						//}
					GLbyte color[4];
					GLfloat depth;
					GLuint index;

					glReadPixels(e.button.x, DISPLAY_HEIGHT - e.button.y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
					glReadPixels(e.button.x, DISPLAY_HEIGHT - e.button.y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
					glReadPixels(e.button.x, DISPLAY_HEIGHT - e.button.y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
					if (index) {
						chosenObjects.push_back(objects[index-1]);
					}
					}
					else {
						if (e.button.button == SDL_BUTTON_RIGHT) {
							mode = MODE::ChoosingEdit;
						}
					}
					break;
				case MODE::Translating:

					if (!isFirstPointTR) {
					//	firstPoint = ray.RayUnProj(e.button.x, e.button.y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
					//	firstPoint = (3.0f / firstPoint.z)*firstPoint + glm::vec3(0.0f, 0.0f, -3.0f);
						isFirstPointTR = true;
					}
					else {
						if (!isSecondPointTR) {
						//	secondPoint = ray.RayUnProj(e.button.x, e.button.y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
						//	secondPoint = (3.0f / secondPoint.z)*secondPoint + glm::vec3(0.0f, 0.0f, -3.0f);
							isSecondPointTR = true;
						}
					}
					if (isSecondPointTR) {
						toTranslate = secondPoint - firstPoint;
						//		toTranslate = glm::normalize(toTranslate);
						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
							chosenObjects[i]->EditPosTransfrom(toTranslate);
						}
						chosenObjects.resize(0);
						mode = MODE::PickingObject;
					}
					break;
					/*case MODE::Scaling:
					glm::vec3 scale;
					std::cout << "Enter in how many times you want to scale object(s)\nx = ";
					std::cin >> scale.x;
					std::cout << "y = ";
					std::cin >> scale.y;
					std::cout << "z = ";
					std::cin >> scale.z;
					for (unsigned int i = 0; i < chosenObjects.size(); i++) {
					chosenObjects[i]->EditScaleTransform(scale);
					}
					chosenObjects.resize(0);
					mode = MODE::PickingObject;
					break;*/
					//case MODE::Rotation: //choosing object in order to find axes to do rotation

					//	break;
				}
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
				case SDLK_c:
					if (mode == MODE::ChoosingEdit) {
						mode = MODE::ChangingColor;
					}
					break;
				case SDLK_t:
					if (mode == MODE::ChoosingEdit) {
						mode = MODE::Translating;
						isFirstPointTR = false;
						isSecondPointTR = false;
					}
					break;
				case SDLK_r:
					if (mode == MODE::ChoosingEdit) {
						mode = MODE::Rotation;
					}
					break;
				case SDLK_s:
					if (mode == MODE::ChoosingEdit) {
						mode = MODE::Scaling;
					}
				}
			}
		}
		display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
		glClearStencil(0);
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		
		for (int i = 0; i < objects.size(); i++) {
			glStencilFunc(GL_ALWAYS, i + 1, -1);
			objects[i]->DrawStandart();
		}
		DrawAxes();
		display.SwapBuffers();
		SDL_Delay(100);
	}

	return 0;
}




void DrawAxes() {
	Vertex vertices[]{
		Vertex(glm::vec3(0.0f,0.0f,-1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)),
		Vertex(glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))
	};
	unsigned int indices[]{
		0, 1
	};
	Transform transform;
	float count = 10;
	transform.EditScale(glm::vec3(100, 100, 100));
	Shader shader("./res/basicShader");
	Mesh meshZ(vertices, 2, indices, 2);
	shader.Bind();
	shader.Update(transform, camera);
	meshZ.Draw(GL_LINES);
	vertices[0] = Vertex(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	vertices[1] = Vertex(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	Mesh meshY(vertices, 2, indices, 2);
	meshY.Draw(GL_LINES);
	vertices[0] = Vertex(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	vertices[1] = Vertex(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	Mesh meshX(vertices, 2, indices, 2);
	meshX.Draw(GL_LINES);
}