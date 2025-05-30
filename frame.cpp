//#include <OpenEXR/ImfInputFile.h>
//#include <OpenEXR/ImfChannelList.h>
//#include <OpenEXR/ImfFrameBuffer.h>
//#include <OpenEXR/ImfRgbaFile.h>
#include <Imath/half.h>

#include"frame.h"

Frame::Frame(int x, int y, Imf::Rgba colour, int scale) :
	x_res_(x),
	y_res_(y),
    scale_(scale),
    current_x_(0.0),
    current_y_(0.0),
    line_color_(Imf::Rgba(0.0, 0.0, 0.0)),
    frame_color_(colour)
{
    rgba_data_ = new Imf::Rgba[x_res_ * y_res_];
    for (int i = 0; i < x_res_ * y_res_; i++) {
        rgba_data_[i] = frame_color_;
    }
}

bool Frame::WriteFrame(const char* filename)
{
    try {
        Imf::RgbaOutputFile out(filename, x_res_, y_res_, Imf::WRITE_RGBA);

        out.setFrameBuffer(rgba_data_, 1, x_res_);

        out.writePixels(y_res_);

        return true;
    }
    catch (const std::exception& e) {
        std::cout << "Failed to write frame:" << e.what();

        return false;
    }
}

void Frame::ClearFrame()
{
    for (int i = 0; i < x_res_ * y_res_; i++) {
        rgba_data_[i] = frame_color_;
    }
}

void Frame::SetPixel(int x, int y, double c)
{
    if (0 <= x && x < x_res_ && 0 <= y && y < y_res_) {
        int flip_y = y_res_ - 1 - y;

        c = 1.0 - c;
        rgba_data_[flip_y * x_res_ + x].r *= line_color_.r * c + 1.0 - c;
        rgba_data_[flip_y * x_res_ + x].g *= line_color_.g * c + 1.0 - c;
        rgba_data_[flip_y * x_res_ + x].b *= line_color_.b * c + 1.0 - c;
    }
}

void Frame::DrawLine(double x0, double y0, double x1, double y1)
{
    bool steep = abs(y1 - y0) > abs(x1 - x0);

    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
    }

    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    double dx = x1 - x0;
    double dy = y1 - y0;

    double gradient;
    if (dx == 0) {
        gradient = 1.0;
    } else {
        gradient = dy / dx;
    }

    //https://stackoverflow.com/questions/68552675/what-is-the-endpoint-calculation-in-the-xiaolin-wu-algorithm-doing

    // First end point
    double x_end;
    double y_end;
    double x_gap;
    int x_pxl_1;
    int y_pxl_1;
    int x_pxl_2;
    int y_pxl_2;
    double inter_y;

    x_end = round(x0);
    y_end = y0 + gradient * (x_end - x0);
    x_gap = inv_frac_part(x0 + 0.5);
    x_pxl_1 = (int)x_end;
    y_pxl_1 = int_part(y_end);

    if (steep) {
        SetPixel(y_pxl_1, x_pxl_1, frac_part(y_end) * x_gap);
        if (frac_part(y_end) != 0) {
            SetPixel(y_pxl_1 + 1, x_pxl_1, inv_frac_part(y_end) * x_gap);
        }
    } else {
        SetPixel(x_pxl_1, y_pxl_1, frac_part(y_end) * x_gap);
        if (frac_part(y_end) != 0) {
            SetPixel(x_pxl_1, y_pxl_1 + 1, inv_frac_part(y_end) * x_gap);
        }
    }

    inter_y = y_end + gradient;

    // handle second endpoint
    x_end = round(x1);
    y_end = y1 + gradient * (x_end - x1);
    x_gap = frac_part(x1 + 0.5);
    x_pxl_2 = x_end;
    y_pxl_2 = int_part(y_end);

    if (steep) {
        SetPixel(y_pxl_2, x_pxl_2, frac_part(y_end) * x_gap);
        if (frac_part(y_end) != 0) {
            SetPixel(y_pxl_2 + 1, x_pxl_2, inv_frac_part(y_end) * x_gap);
        }
    } else {
        SetPixel(x_pxl_2, y_pxl_2, frac_part(y_end) * x_gap);
        if (frac_part(y_end) != 0) {
            SetPixel(x_pxl_2, y_pxl_2 + 1, inv_frac_part(y_end) * x_gap);
        }
    }

    if (steep) {
        for (int x = x_pxl_1 + 1; x < x_pxl_2; x++) {
            SetPixel(int_part(inter_y), x, frac_part(inter_y));
            SetPixel(int_part(inter_y) + 1, x, inv_frac_part(inter_y));
            inter_y = inter_y + gradient;
        }
    } else {
        for (int x = x_pxl_1 + 1; x < x_pxl_2; x++) {
            SetPixel(x, int_part(inter_y), frac_part(inter_y));
            SetPixel(x, int_part(inter_y) + 1, inv_frac_part(inter_y));
            inter_y = inter_y + gradient;
        }
    }
}

void Frame::DrawTo(double x, double y)
{
    double scaled_x, scaled_y;
    scaled_x = (x * scale_) + x_res_ * 0.5;
    scaled_y = (y * scale_) + y_res_ * 0.5;
    
    DrawLine(current_x_, current_y_, scaled_x, scaled_y);

    current_x_ = scaled_x;
    current_y_ = scaled_y;

    //WriteFrame();
    //std::cin.get();
}

void Frame::DrawTo(vec3 point)
{
    DrawTo(point.x, point.y);
}

void Frame::MoveTo(double x, double y)
{
    double scaled_x, scaled_y;
    scaled_x = (x * scale_) + x_res_ * 0.5;
    scaled_y = (y * scale_) + y_res_ * 0.5;
    
    current_x_ = scaled_x;
    current_y_ = scaled_y;
}

void Frame::MoveTo(vec3 point)
{
    MoveTo(point.x, point.y);
}

void Frame::DrawTo(vec4* point)
{
    DrawTo(point->x, point->y);
}

void Frame::MoveTo(vec4* point)
{
    MoveTo(point->x, point->y);
}

void Frame::DrawTo(vec4 point)
{
    DrawTo(point.x, point.y);
}

void Frame::MoveTo(vec4 point)
{
    MoveTo(point.x, point.y);
}
