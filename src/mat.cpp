#include "include/scop.hpp"

#define M_PI 3.14159265358979323846

class Mat4 {
public:
	float data[16];

	Mat4() {
		for (int i = 0; i < 16; i++) {
			data[i] = 0.0f;
		}
	}

	Mat4(float p) {
		for (int i = 0; i < 16; i++) {
			data[i] = 0.0f;
		}
		data[0] = data[5] = data[10] = p;
		data[15] = 1.0f;
	}

	Mat4(float x, float y, float z) {
		for (int i = 0; i < 16; i++) {
			data[i] = 0.0f;
		}
		data[0] = x;
		data[5] = y;
		data[10] = z;
		data[15] = 1.0f;
	}

	Mat4& operator=(const Mat4& other)
	{
		if (this != &other) {
			for (int i = 0; i < 16; i++) {
				data[i] = other.data[i];
			}
		}
		return *this;
	}

	static Mat4 identity() {
		Mat4 m;
		m.data[0] = m.data[5] = m.data[10] = m.data[15] = 1.0f;
		return m;
	}

	Mat4 operator*(const Mat4& other) const {
		Mat4 result;
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				float sum = 0.0f;
				for (int e = 0; e < 4; e++) {
					sum += data[e + y * 4] * other.data[x + e * 4];
				}
				result.data[x + y * 4] = sum;
			}
		}
		return result;
	}

	static Mat4 translate(float x, float y, float z) {
		Mat4 m = identity();
		m.data[12] = x;
		m.data[13] = y;
		m.data[14] = z;
		return m;
	}

	static Mat4 scale(float x, float y, float z) {
		Mat4 m = identity();
		m.data[0] = x;
		m.data[5] = y;
		m.data[10] = z;
		return m;
	}

	// Helper function to convert degrees to radians
	static float toRadians(float degrees) {
		return degrees * M_PI / 180.0f;
	}

	// Updated rotate function
	static Mat4 rotate(float angleX, float angleY, float angleZ)
	{
		angleX = toRadians(angleX);
		angleY = toRadians(angleY);
		angleZ = toRadians(angleZ);

		Mat4 m = identity();

		// Rotation matrix for x-axis
		if (angleX != 0.0f)
		{
			m.data[5] = cos(angleX);
			m.data[6] = -sin(angleX);
			m.data[9] = sin(angleX);
			m.data[10] = cos(angleX);
		}
		// Rotation matrix for y-axis
		if (angleY != 0.0f)
		{
			m.data[0] = cos(angleY);
			m.data[2] = sin(angleY);
			m.data[8] = -sin(angleY);
			m.data[10] = cos(angleY);
		}
		// Rotation matrix for z-axis
		if (angleZ != 0.0f)
		{
			m.data[0] = cos(angleZ);
			m.data[1] = -sin(angleZ);
			m.data[4] = sin(angleZ);
			m.data[5] = cos(angleZ);
		}
		return m;
	}
};