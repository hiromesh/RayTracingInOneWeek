//https://raytracing.github.io/books/RayTracingInOneWeekend.html
#include "stdafx.h"
#include <iostream>
#include"vec3.h"
#include"color.h"
#include"ray.h"

using namespace std;

color ray_color(const ray& r);
double hit_sphere(const point3& center, double radius, const ray&r);

double hit_sphere(const point3& center, double radius, const ray&r) {
	//球和射线相交的方程是否有解
	vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius*radius;
	auto discriminant = half_b*half_b - a*c;

	if (discriminant < 0) {
		return -1.0;
	}
	else {
		return (-half_b - sqrt(discriminant)) / a;
	}

}

//返回简单的渐变背景色
color ray_color(const ray& r) {
	auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
	if (t > 0.0) {
		//计算法线
		vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
		return 0.5*color(N.x() + 1, N.y() + 1,N.z() + 1);
	}
	vec3 unit_direction = unit_vector(r.direction());
	t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}


int main()
{
	//image
	const auto aspect_ratio = 16.0 / 9.0;
	const int img_w = 400;
	const int img_h = static_cast<int>(img_w / aspect_ratio);

	//camera
	auto viewport_h = 2.0;
	auto viewport_w = aspect_ratio*viewport_h;
	auto focal_length = 1.0;

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_w, 0, 0);
	auto vertical = vec3(0, viewport_h, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	//render
	std::cout << "P3\n" << img_w << " " << img_h << "\n255\n";
	//write_ppm_head("./img.ppm", img_w, img_h);
	for (int j = img_h - 1; j >= 0; --j) {
		for (int i = 0; i < img_w; i++) {
			auto u = double(i) / (img_w - 1);
			auto v = double(j) / (img_h - 1);
			ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
			color pixel = ray_color(r);
			write_color(std::cout, pixel, "./img.ppm");
		}
	}
	//std::cout << "finish";
	return 0;
}

