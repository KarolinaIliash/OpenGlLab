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


bool Ray::TestRayOBBIntersection(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3 minBox, glm::vec3 maxBox, glm::mat4 ModelMatrix, float& intersectionDistance ) {
	float tMin = 0.0f;
	float tMax = 100000.0f;

	glm::vec3 OBBpositionWorldSpace(ModelMatrix[3].x, ModelMatrix[3].y, ModelMatrix[3].z);

	glm::vec3 delta = OBBpositionWorldSpace - rayOrigin;
	// Test intersection with the 2 planes perpendicular to the OBB's X axis
		glm::vec3 xAxis(ModelMatrix[0].x, ModelMatrix[0].y, ModelMatrix[0].z);
		float e = glm::dot(xAxis, delta);
		float f = glm::dot(rayDirection, xAxis);

		if (fabs(f) > 0.001f) { // Standard case
			float t1 = (e + minBox.x) / f; // Intersection with the "left" plane
			float t2 = (e + maxBox.x) / f; // Intersection with the "right" plane
											 // t1 and t2 now contain distances betwen ray origin and ray-plane intersections
											 // We want t1 to represent the nearest intersection, 
											 // so if it's not the case, invert t1 and t2
			if (t1 > t2) {
				float w = t1; t1 = t2; t2 = w; // swap t1 and t2
			}
			// tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
			if (t2 < tMax)
				tMax = t2;
			// tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
			if (t1 > tMin)
				tMin = t1;

			// If "far" is closer than "near", then there is NO intersection.
			if (tMax < tMin)
				return false;
		}
		else { // Rare case : the ray is almost parallel to the planes, so they don't have any "intersection"
			if (-e + minBox.x > 0.0f || -e + maxBox.x < 0.0f)
				return false;
		}


	// Test intersection with the 2 planes perpendicular to the OBB's Y axis
		tMin = 0.0f;
		tMax = 100000.0f;
		glm::vec3 Yaxis(ModelMatrix[1].x, ModelMatrix[1].y, ModelMatrix[1].z);
		 e = glm::dot(Yaxis, delta);
		 f = glm::dot(rayDirection, Yaxis);
		if (fabs(f) > 0.001f) {
			float t1 = (e + minBox.y) / f;
			float t2 = (e + maxBox.y) / f;
			if (t1>t2) { float w = t1; t1 = t2; t2 = w; }
			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
				tMin = t1;
			if (tMin > tMax)
				return false;
		}
		else {
			if (-e + minBox.y > 0.0f || -e + maxBox.y < 0.0f)
				return false;
		}
	// Test intersection with the 2 planes perpendicular to the OBB's Z axis
		tMin = 0.0f;
		tMax = 100000.0f;
		glm::vec3 Zaxis(ModelMatrix[2].x, ModelMatrix[2].y, ModelMatrix[2].z);
		 e = glm::dot(Zaxis, delta);
		 f = glm::dot(rayDirection, Zaxis);

		if (fabs(f) > 0.001f) {
			float t1 = (e + minBox.z) / f;
			float t2 = (e + maxBox.z) / f;
			if (t1>t2) { float w = t1; t1 = t2; t2 = w; }
			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
				tMin = t1;
			if (tMin > tMax)
				return false;
		}
		else {
			if (-e + minBox.z > 0.0f || -e + maxBox.z < 0.0f)
				return false;
		}
	intersectionDistance = tMin;
	return true;
}