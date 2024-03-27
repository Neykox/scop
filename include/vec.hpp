#ifndef VEC_HPP
# define VEC_HPP
#include "../include/scop.hpp"
#include <cmath>
#include <ostream>

class Vec
{
	public:
	float x, y, z;

	public:
		// Default constructor
		Vec() : x(0), y(0), z(0) {}

		// Parameterized constructor
		Vec(float x, float y, float z) : x(x), y(y), z(z) {}

		// Copy constructor
		Vec(const Vec& other) : x(other.x), y(other.y), z(other.z) {}

		// Destructor
		~Vec() {}

		// Assignment operator
		Vec& operator=(const Vec& other) {
			if (this != &other) {
				x = other.x;
				y = other.y;
				z = other.z;
			}
			return *this;
		}

		// Normalize the vector
		void normalize() {
			float length = sqrt(x * x + y * y + z * z);
			x /= length;
			y /= length;
			z /= length;
		}

		// Overload operator<<
		friend std::ostream& operator<<(std::ostream& os, const Vec& vec) {
			os  << vec.x << ", " << vec.y << ", " << vec.z;
			return os;
		}
};

#endif