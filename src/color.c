#include <color.h>

float max_f(float a, float b, float c) {
	if ((a > b) && (a > c))
		return a;
	if ((b > a) && (b > c))
		return b;
	return c;
}

float min_f(float a, float b, float c) {
	if ((a < b) && (a < c))
		return a;
	if ((b < a) && (b < c))
		return b;
	return c;
}

void rgb2hsv(color_t rgb, color_t * hsv) {
	float r = rgb.coords[RGB_R];
	float g = rgb.coords[RGB_G];
	float b = rgb.coords[RGB_B];
	float h, s, v;
	float max = max_f(r, g, b);
	float min = min_f(r, g, b);
	v = max;
	if (max == 0.0f) {
		s = 0;
		h = 0;
	} else if (max - min == 0.0f) {
		s = 0;
		h = 0;
	} else {
		s = (max - min) / max;
		if (max == r) {
			h = 60 * ((g - b) / (max - min)) + 0;
		} else if (max == g) {
			h = 60 * ((b - r) / (max - min)) + 120;
		} else {
			h = 60 * ((r - g) / (max - min)) + 240;
		}
	}
	if (h < 0)
		h += 360.0f;
	hsv->coords[HSV_H] = h;	// dst_h : 0-360.0
	hsv->coords[HSV_S] = s;	// dst_s : 0-1.0
	hsv->coords[HSV_V] = v;	// dst_v : 0-1.0
}

void hsv2rgb(color_t hsv, color_t * rgb) {
	float h = hsv.coords[HSV_H];
	float s = hsv.coords[HSV_S];
	float v = hsv.coords[HSV_V];
	float r, g, b;		// 0.0-1.0
	int hi = (int) (h / 60.0f) % 6;
	float f = (h / 60.0f) - hi;
	float p = v * (1.0f - s);
	float q = v * (1.0f - s * f);
	float t = v * (1.0f - s * (1.0f - f));
	switch (hi) {
	case 0:
		r = v, g = t, b = p;
		break;
	case 1:
		r = q, g = v, b = p;
		break;
	case 2:
		r = p, g = v, b = t;
		break;
	case 3:
		r = p, g = q, b = v;
		break;
	case 4:
		r = t, g = p, b = v;
		break;
	case 5:
		r = v, g = p, b = q;
		break;
	}
	rgb->coords[RGB_R] = r;
	rgb->coords[RGB_G] = g;
	rgb->coords[RGB_B] = b;
}

void rgb2hsv_(color_t * color) {
	rgb2hsv(*color, color);
}

void hsv2rgb_(color_t * color) {
	hsv2rgb(*color, color);
}
