#pragma once
#include <cmath>
#include<iostream>
#include<memory.h>
#include<io.h>
#include<fstream>
using std::sqrt;

class vec3 {
public:
	double e[3];
public:
	vec3() :e{ 0,0,0 } {}
	vec3(double e0, double e1, double e2) :e{ e0,e1,e2 } {}

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	vec3 operator -() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator [](int i)const { return e[i]; }
	double& operator [](int i) { return e[i]; }

	vec3& operator +=(const vec3 &v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	vec3& operator *=(const double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
	}

	vec3& operator /=(const double t) {
		if (t == 0)return vec3(0, 0, 0);
		return *this *= 1 / t;
	}

	double length_squared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	double length() const {
		return sqrt(length_squared());
	}

};
using color = vec3;
using point3 = vec3;
// vec3 Utility Functions

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}
inline vec3 operator+(const vec3 &u, const vec3 &v) {
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
	return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
	return t * v;
}

inline vec3 operator/(vec3 v, double t) {
	return (1 / t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}

inline void store_to_ppm(std::ostream &out, color pixel_color) {
	out << static_cast<int>(255.999*pixel_color.x()) << " "
		<< static_cast<int>(255.999*pixel_color.y()) << " "
		<< static_cast<int>(255.999*pixel_color.z()) << "\n";
}

inline void write_ppm_head(std::string path,int img_w,int img_h) {
	std::fstream out(path);
	out<<"P3\n" << img_w << " " << img_h << "\n255\n";
	out.close();
}

inline void write_color(std::ostream &out, color pixel_color,std::string path="") {
	//Ð´Ò»¸öÏñËØ
	out << static_cast<int>(255.999*pixel_color.x()) << " "
		<< static_cast<int>(255.999*pixel_color.y()) << " "
		<< static_cast<int>(255.999*pixel_color.z()) << "\n";
	//if (path == "" || path.size() <= 0)return;
	//std::ofstream out_(path, std::ios::app);
	//store_to_ppm(out_, pixel_color);
	//out_.close();
}