#include "Log.h"

std::ostream& operator<<(std::ostream& lhs, const glm::vec4& rhs)
{
	lhs << "(" << rhs.x << "," << rhs.y << "," << rhs.z << "," << rhs.w << ")";
	return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const glm::vec3& rhs)
{
	lhs << "(" << rhs.x << "," << rhs.y << "," << rhs.z << ")";
	return lhs;
}