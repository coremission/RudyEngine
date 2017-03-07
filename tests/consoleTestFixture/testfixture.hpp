#ifndef TEST_FIXTURE_HPP
#define TEST_FIXTURE_HPP

#include <iostream>
#include <Dependencies/glm/detail/type_vec3.hpp>
#include <Rendering/Camera.h>
#include <Model/GameObject.h>

using namespace std;
using namespace glm;

std::ostream& operator <<(std::ostream& stream, const vec4& vec) {
	stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
	return stream;
}

std::ostream& operator <<(std::ostream& stream, const vec3& vec) {
	stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	return stream;
}

glm::vec4& operator *(const glm::mat4& matrix, const glm::vec3& point) {
	return matrix * glm::vec4(point.x, point.y, point.z, 1.0f);
}

std::ostream& operator <<(std::ostream& stream, const mat4& matrix) {

	stream << matrix[0] << endl;
	stream << matrix[1] << endl;
	stream << matrix[2] << endl;
	stream << matrix[3] << endl;
	return stream;
}

template<typename T>
void assert_equal(T expected, T actual)
{
	if (expected != actual)
		cout << "FAILED : (expected - " << expected << ", actual - " << actual << ")" << endl;
	else
		cout << "TEST - OK" << endl;
}
#endif //TEST_FIXTURE_HPP