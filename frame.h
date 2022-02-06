
#include <OpenEXR/ImfRgbaFile.h>

#include "object.h"

#ifndef FRAME_H
#define FRAME_H

class Frame
{
public:
	Frame(int x, int y, Imf::Rgba color);

	bool WriteFrame(const char* filename = "out.exr");

	void SetPixel(int x, int y, Imf::Rgba color);
	void SetPixel(int x, int y, double c);

	void DrawLine(double x0, double y0, double x1, double y1);

	void DrawTo(double x, double y);
	void MoveTo(double x, double y);

	void DrawObject(Object obj);

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

	double current_x_;
	double current_y_;

	Imf::Rgba* rgba_data_;
};

#endif
