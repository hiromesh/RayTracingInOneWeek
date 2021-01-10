#include "sphere.h"

sphere::sphere()
{
}

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const{
	vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius*radius;

	auto discriminant = half_b*half_b - a*c;
	if (discriminant < 0) return false;

	auto sqrtd = sqrt(discriminant);

	//找到可接受范围内最近的点
	auto root = (-half_b - sqrtd) / a;
	if (root<t_min || root>t_max) {
		root = (-half_b + sqrtd) / a;
		if (root<t_min || root>t_max) {
			return false;
		}
	}
	rec.t = root;
	rec.p = r.at(rec.t);
	rec.normal=(rec.p - center) / radius;
	return true;
}
