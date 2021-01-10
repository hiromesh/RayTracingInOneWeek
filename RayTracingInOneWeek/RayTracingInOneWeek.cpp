// RayTracingInOneWeek.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include"vec3.h"
#include"color.h"
#include"ray.h"

//返回简单的渐变背景色3
color ray_color(const ray& r) {
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main()
{
	//image
	const auto aspect_ratio = 16.0 / 9.0;
	const int img_w = 400;
	const int img_h = static_cast<int>(img_w/aspect_ratio);

	//camera
	auto viewport_h = 2.0;
	auto viewport_w = aspect_ratio*viewport_h;
	auto focal_length = 1.0;

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_w, 0, 0);
	auto vertical = vec3(0, viewport_h, 0);
	auto lower_left_corner = origin - horizontal / 2 = vertical / 2 - vec3(0, 0, focal_length);

	//render
	std::cout << "P3\n" << img_w << " " << img_h << "\n255\n";
	for (int j = img_h - 1; j >= 0; --j) {
		for (int i = 0; i < img_w; i++) {
			auto u = double(i) / (img_w - 1);
			auto v = double(j) / (img_h - 1);
			ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
			color pixel = ray_color(r);
			write_color(std::cout, pixel);
		}
	}
    return 0;
}

