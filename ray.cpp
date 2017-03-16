#include"Ray.h"

glm::vec3 Ray::GetRay(float mouseX, float mouseY, int width, int height) {
	float x = (2.0f * mouseX) / float(width) - 1.0f; //transforming x, y mouse coordinates
	float y = 1.0f - (2.0f * mouseY) / float(height);//into normal device coordinates
	float z = 1.0f;//it's only for doing vector, it's not final
	glm::vec3 rayNdc = glm::vec3(x, y, z);
	glm::vec4 rayClip = glm::vec4(rayNdc.x, rayNdc.y, -1.0f, 1.0f);
	glm::vec4 rayEye = glm::inverse(camera.GetProjection()) * rayClip;
	rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
	//glm::vec3 rayWorld((glm::inverse(glm::lookAt(camera.pos, camera.pos + camera.forward, camera.up))) *rayEye.x,
		//(glm::inverse(glm::lookAt(camera.pos, camera.pos + camera.forward, camera.up))) * rayEye.y,
		//(glm::inverse(glm::lookAt(camera.pos, camera.pos + camera.forward, camera.up))) *rayEye.x);
	glm::vec3 rayWorld((glm::inverse(camera.GetView()) * rayEye).x, (glm::inverse(camera.GetView()) * rayEye).y, (glm::inverse(camera.GetView()) * rayEye).z);
	rayWorld = glm::normalize(rayWorld);
	return rayWorld;
}

#define EPSILON 0.000001

bool Ray::TriangleIntersection(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3, glm::vec3 rayOrigin, glm::vec3 rayDirection, float* out){
	glm::vec3 P, Q;
	float det, inv_det, u, v;
	float t;
	glm::vec3 edge1(vertex2.x - vertex1.x, vertex2.y - vertex1.y, vertex2.z - vertex1.z);
	glm::vec3 edge2(vertex3.x - vertex1.x, vertex3.y - vertex1.y, vertex3.z - vertex1.z);
	P = glm::cross(rayDirection, edge2);
	//if determinant is near zero, ray lies in plane of triangle or ray is parallel to plane of triangle
	det = glm::dot(edge1, P);
	if (det > -EPSILON && det < EPSILON) return 0;
	inv_det = 1.0f / det;
	glm::vec3 T(rayOrigin.x - vertex1.x, rayOrigin.y - vertex1.y, rayOrigin.z - vertex1.z);
	u = glm::dot(T, P) * inv_det;
	//The intersection lies outside of the triangle
	if (u < 0.f || u > 1.f) return 0;
	Q = glm::cross(T, edge1);

	//Calculate V parameter and test bound
	v = glm::dot(rayDirection, Q) * inv_det;
	//The intersection lies outside of the triangle
	if (v < 0.f || u + v  > 1.f) return 0;

	t = glm::dot(edge2, Q) * inv_det;

	if (t > EPSILON) { //ray intersection
		//*out = t;
		return 1;
	}
	return 0;
}