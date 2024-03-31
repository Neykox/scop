#ifndef MAT_HPP
# define MAT_HPP

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

	// Projection matrix
	static Mat4 perspective(float fov, float aspect, float near, float far) {
		Mat4 m;
		float tanHalfFov = tan(fov / 2.0f);

		m.data[0] = 1.0f / (aspect * tanHalfFov);
		m.data[5] = 1.0f / tanHalfFov;
		m.data[10] = -(far + near) / (far - near);
		m.data[11] = -1.0f;
		m.data[14] = -(2.0f * far * near) / (far - near);
		return m;
	}

	// View matrix
	static Mat4 lookAt(const Vec& position, const Vec& target, const Vec& up) {
		Vec zaxis = (position - target).normalize();
		Vec xaxis = up.cross(zaxis).normalize();
		Vec yaxis = zaxis.cross(xaxis);

		Mat4 m;
		m.data[0] = xaxis.x;
		m.data[1] = yaxis.x;
		m.data[2] = zaxis.x;
		m.data[3] = 0.0f;
		m.data[4] = xaxis.y;
		m.data[5] = yaxis.y;
		m.data[6] = zaxis.y;
		m.data[7] = 0.0f;
		m.data[8] = xaxis.z;
		m.data[9] = yaxis.z;
		m.data[10] = zaxis.z;
		m.data[11] = 0.0f;
		m.data[12] = -xaxis.dot(position);
		m.data[13] = -yaxis.dot(position);
		m.data[14] = -zaxis.dot(position);
		m.data[15] = 1.0f;
		return m;
	}

	// Model matrix
	static Mat4 model(const Vec& position, const Vec& scale, const Vec& rotation) {
		Mat4 m = translate(position.x, position.y, position.z);
		m = m * scale(scale.x, scale.y, scale.z);
		m = m * rotate(rotation.x, rotation.y, rotation.z);
		return m;
	}

	static float radians(float degrees) {
		return degrees * M_PI / 180.0f;
	}
};

#endif