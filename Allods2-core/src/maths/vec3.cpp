#include "vec3.h"
#include "vec2.h"

namespace Allods2 {namespace maths {

	vec3::vec3() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	vec3::vec3(const float& x, const float& y, const float& z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec3::vec3(const vec2& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = 0.0f;
	}

	vec3& vec3::add(const vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vec3& vec3::subtract(const vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	vec3& vec3::multiply(const vec3& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	vec3& vec3::devide(const vec3& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	vec3 operator+(vec3 left, const vec3& right) {
		return left.add(right);
	}

	vec3 operator-(vec3 left, const vec3& right) {
		return left.subtract(right);
	}

	vec3 operator*(vec3 left, const vec3& right) {
		return left.multiply(right);
	}

	vec3 operator/(vec3 left, const vec3& right) {
		return left.devide(right);
	}

	vec3& vec3::operator+=(const vec3& other) {
		return add(other);
	}

	vec3& vec3::operator-=(const vec3& other) {
		return subtract(other);
	}

	vec3& vec3::operator*=(const vec3& other) {
		return multiply(other);
	}

	vec3& vec3::operator/=(const vec3& other) {
		return devide(other);
	}

	bool vec3::operator==(const vec3& other) {
		return x == other.x && y == other.y && z == other.z;
	}

	bool vec3::operator!=(const vec3& other) {
		return !(*this == other);
	}

	float vec3::distance(const vec3& other) const
	{
		float a = x - other.x;
		float b = y - other.y;
		float c = z - other.z;
		return sqrt(a * a + b * b + c * c);
	}

	std::ostream& operator<<(std::ostream& stream, const vec3& vector) {
		stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return stream;
	}


} }