#ifndef VEC_HPP
# define VEC_HPP
#include "../include/scop.hpp"
#include <cmath>
#include <ostream>

class Vec
{
	public:
	float x, y, z, w;

	public:
		// Default constructor
		Vec() : x(0), y(0), z(0), w(1.0f){}

		// Parameterized constructor
		Vec(float x, float y, float z) : x(x), y(y), z(z), w(1.0f){}

		// Copy constructor
		Vec(const Vec& other) : x(other.x), y(other.y), z(other.z), w(1.0f){}

		// Destructor
		~Vec() {}

		// Assignment operator
		Vec& operator=(const Vec& other) {
			if (this != &other) {
				x = other.x;
				y = other.y;
				z = other.z;
				w = 1.0f;
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