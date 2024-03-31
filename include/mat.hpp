#ifndef MAT_HPP
# define MAT_HPP

#include "scop.hpp"

#define M_PI 3.14159265358979323846

class Mat4 {
public:
	float data[4][4];

	Mat4() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				data[i][j] = 0.0f;
			}
		}
	}

	Mat4(float p) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				data[i][j] = 0.0f;
			}
		}
		data[0][0] = data[1][1] = data[2][2] = p;
		data[3][3] = 1.0f;
	}

	Mat4(float x, float y, float z) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				data[i][j] = 0.0f;
			}
		}
		data[0][0] = x;
		data[1][1] = y;
		data[2][2] = z;
		data[3][3] = 1.0f;
	}

	Mat4& operator=(const Mat4& other) {
		if (this != &other) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					data[i][j] = other.data[i][j];
				}
			}
		}
		return *this;
	}

	static Mat4 identity() {
		Mat4 m;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m.data[i][j] = i == j ? 1.0f : 0.0f;
			}
		}
		return m;
	}

	Mat4 operator*(const Mat4& other) const {
		Mat4 result;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				result.data[i][j] = 0.0f;
				for (int k = 0; k < 4; ++k) {
					result.data[i][j] += this->data[i][k] * other.data[k][j];
				}
			}
		}
		return result;
}

	static Mat4 translate(float tx, float ty, float tz) {
		Mat4 m = identity();
		m[3][0] = tx;
		m[3][1] = ty;
		m[3][2] = tz;
		return m;
	}

	static Mat4 scale(float sx, float sy, float sz) {
		Mat4 m = identity();
		m[0][0] = sx;
		m[1][1] = sy;
		m[2][2] = sz;
		return m;
	}

	// Helper function to convert degrees to radians
	static float toRadians(float degrees) {
		return degrees * M_PI / 180.0f;
	}

	// Updated rotate function
	static Mat4 rotate(float rx, float ry, float rz) {
		Mat4 m = identity();
		float cosx = cos(rx), sinx = sin(rx);
		float cosy = cos(ry), siny = sin(ry);
		float cosz = cos(rz), sinz = sin(rz);

		m[0][0] = cosy * cosz;
		m[0][1] = -cosy * sinz;
		m[0][2] = siny;
		m[1][0] = sinx * siny * cosz + cosx * sinz;
		m[1][1] = -sinx * siny * sinz + cosx * cosz;
		m[1][2] = -sinx * cosy;
		m[2][0] = -cosx * siny * cosz + sinx * sinz;
		m[2][1] = cosx * siny * sinz + sinx * cosz;
		m[2][2] = cosx * cosy;

		return m;
	}

	// Projection matrix
	static Mat4 perspective(float fov, float aspect, float near, float far) {
		Mat4 m;
		float tanHalfFov = tan(fov / 2.0f);

		m.data[0][0] = 1.0f / (aspect * tanHalfFov);
		m.data[1][1] = 1.0f / tanHalfFov;
		m.data[2][2] = -(far + near) / (far - near);
		m.data[2][3] = -1.0f;
		m.data[3][2] = -(2.0f * far * near) / (far - near);
		return m;
	}

	// View matrix
	static Mat4 lookAt(const Vec& position, const Vec& target, const Vec& up) {
		Vec zaxis = (position - target).normalized();
		Vec xaxis = up.cross(zaxis).normalized();
		Vec yaxis = zaxis.cross(xaxis);

		Mat4 m;
		m.data[0][0] = xaxis.x;
		m.data[1][0] = yaxis.x;
		m.data[2][0] = zaxis.x;
		m.data[3][0] = 0.0f;
		m.data[0][1] = xaxis.y;
		m.data[1][1] = yaxis.y;
		m.data[2][1] = zaxis.y;
		m.data[3][1] = 0.0f;
		m.data[0][2] = xaxis.z;
		m.data[1][2] = yaxis.z;
		m.data[2][2] = zaxis.z;
		m.data[3][2] = 0.0f;
		m.data[0][3] = -xaxis.dot(position);
		m.data[1][3] = -yaxis.dot(position);
		m.data[2][3] = -zaxis.dot(position);
		m.data[3][3] = 1.0f;
		return m;
	}

	// Model matrix
	static Mat4 model(const Vec& position, const Vec& _scale, const Vec& rotation) {
		Mat4 m = translate(position.x, position.y, position.z);
		m = m * scale(_scale.x, _scale.y, _scale.z);
		m = m * rotate(rotation.x, rotation.y, rotation.z);
		return m;
	}

	static float radians(float degrees) {
		return degrees * (M_PI / 180.0f);
	}

	// float& operator[](int index) {
	// 	return data[index];
	// }

	// const float& operator[](int index) const {
	// 	return data[index];
	// }

	// float* operator[](int index) {
	// 	return data + index * 4;
	// }

	// const float* operator[](int index) const {
	// 	return data + index * 4;
	// }

	float* operator[](int index) {
		return data[index];
	}

	const float* operator[](int index) const {
		return data[index];
	}
};

#endif