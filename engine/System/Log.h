#pragma once

#include <glm/glm.hpp>
#include <iostream>

std::ostream& operator<<(std::ostream& lhs, const glm::vec4& rhs);
std::ostream& operator<<(std::ostream& lhs, const glm::vec3& rhs);