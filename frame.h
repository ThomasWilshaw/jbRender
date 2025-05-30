
#include <OpenEXR/ImfRgbaFile.h>

#include "object.h"
#include "Scene.h"
#include "maths.h"

#ifndef FRAME_H
#define FRAME_H

// THe actual rendered frame. Hanldes all drawing and saving
class Frame
{
public:
	Frame(int x, int y, Imf::Rgba color, int scale = 1000);

	bool WriteFrame(const char* filename = "out.exr");

	void ClearFrame();

	void SetPixel(int x, int y, double c);

	void DrawLine(double x0, double y0, double x1, double y1);

	void DrawTo(double x, double y);
	void MoveTo(double x, double y);

	void DrawTo(vec3 point);
	void MoveTo(vec3 point);

	void DrawTo(vec4 *point);
	void MoveTo(vec4* point);

	void DrawTo(vec4 point);
	void MoveTo(vec4 point);

	void SetLineColor(Imf::Rgba color) { line_color_ = color; };
	void ResetLineColor() { line_color_.r = 0.0; line_color_.g = 0.0; line_color_.b = 0.0; }

private:
	int int_part(const double x) { return (int)floor(x); };
	double frac_part(const double x) { return x - floor(x); };
	double inv_frac_part(const double x) { return 1.0 - frac_part(x); };

	void swap(double& x, double& y)
	{
		double temp = x;
		x = y;
		y = temp;
	}


	int x_res_;
	int y_res_;
	int scale_;

	double current_x_;
	double current_y_;

	Imf::Rgba* rgba_data_;
	Imf::Rgba line_color_;
	Imf::Rgba frame_color_;
};

#endif
