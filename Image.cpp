//
// Created by floodd on 23/03/2022.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"



bool Image::load(string filename)
{
    std::ifstream ifs;
    ifs.open(filename, std::ios::binary);
    // need to spec. binary mode for Windows users

    try {
        if (ifs.fail()) {
            throw("Can't open input file");
        }
        std::string header;
        int w, h, b;
        ifs >> header;
        if (strcmp(header.c_str(), "P6") != 0) throw("Can't read input file");
        ifs >> w >> h >> b;
        this->w = w;
        this->h = h;
        this->pixels = new Rgb[w * h]; // this is throw an exception if bad_alloc
        ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data
        unsigned char pix[3]; // read each pixel one by one and convert bytes to floats
        for (int i = 0; i < w * h; ++i) {
            ifs.read(reinterpret_cast<char *>(pix), 3);
            this->pixels[i].r = pix[0];
            this->pixels[i].g = pix[1];
            this->pixels[i].b = pix[2];
        }
        ifs.close();
    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ifs.close();
        return false;
    }

    return true;
}
bool Image::loadRaw(string filename)
{
    std::ifstream ifs;
    ifs.open(filename, std::ios::binary);
    // need to spec. binary mode for Windows users

    try {
        if (ifs.fail()) {
            throw("Can't open input file");
        }
        std::string header;
        int w, h, b;
        ifs >> header;
        if (strcmp(header.c_str(), "P6") != 0) throw("Can't read input file");
        ifs >> w >> h >> b;
        this->w = w;
        this->h = h;
        this->pixels = new Rgb[w * h]; // this is throw an exception if bad_alloc
        ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data
        unsigned char pix[3]; // read each pixel one by one and convert bytes to floats
        for (int i = 0; i < w * h; ++i) {
            ifs.read(reinterpret_cast<char *>(pix), 3);
            this->pixels[i].r = pix[0];
            this->pixels[i].g = pix[1];
            this->pixels[i].b = pix[2];
        }
        ifs.close();
    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ifs.close();
        return false;
    }

    return true;
}

bool Image::savePPM(string filename)
{
    std::ofstream ofs;
    ofs.open(filename, std::ios::binary);
    // need to spec. binary mode for Windows users

    try {
        if (ofs.fail()) {
            throw("Can't open output file");
        }
        ofs << "P6\n" << w << " " << h << "\n255\n";
        unsigned char pix[3]; // convert floats to bytes
        for (int i = 0; i < w * h; ++i) {
            pix[0] = static_cast<unsigned char>(this->pixels[i].r);
            pix[1] = static_cast<unsigned char>(this->pixels[i].g);
            pix[2] = static_cast<unsigned char>(this->pixels[i].b);
            ofs.write(reinterpret_cast<char *>(pix), 3);
        }
        ofs.close();
    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ofs.close();
        return false;
    }

    return true;
}

void Image::filterRed()
{
    for (int i = 0; i < w * h; ++i) {
        pixels[i].b = 0;
        pixels[i].g = 0;
    }
}

void Image::filterGreen()
{
    for (int i = 0; i < w * h; ++i) {
        pixels[i].r = 0;
        pixels[i].b = 0;
    }
}

void Image::filterBlue()
{
    for (int i = 0; i < w * h; ++i) {
        pixels[i].r = 0;
        pixels[i].g = 0;
    }
}

void Image::greyScale()
{
    for (int i = 0; i < w * h; ++i) {
        pixels[i].r = (pixels[i].r + pixels[i].g + pixels[i].b) / 3;
        pixels[i].g = (pixels[i].r + pixels[i].g + pixels[i].b) / 3;
        pixels[i].b = (pixels[i].r + pixels[i].g + pixels[i].b) / 3;
    }
}

void Image::flipHorizontal()
{
    for (int i = 0; i < h; ++i) {
        for(int j = 0; j < w/2; ++j) {
            int temp = pixels[i * w + j].r;
            pixels[i * w + j].r = pixels[i * w + w - j - 1].r;
            pixels[i * w + w - j - 1].r = temp;
            temp = pixels[i * w + j].g;
            pixels[i * w + j].g = pixels[i * w + w - j - 1].g;
            pixels[i * w + w - j - 1].g = temp;
            temp = pixels[i * w + j].b;
            pixels[i * w + j].b = pixels[i * w + w - j - 1].b;
            pixels[i * w + w - j - 1].b = temp;
        }
    }
}

void Image::flipVertically()
{
    for(int j = 0; j < w; ++j) {
        for(int i = 0; i < h/2; ++i) {
            int temp = pixels[i * w + j].r;
            pixels[i * w + j].r = pixels[(h - i - 1) * w + j].r;
            pixels[(h - i - 1) * w + j].r = temp;
            temp = pixels[i * w + j].g;
            pixels[i * w + j].g = pixels[(h - i - 1) * w + j].g;
            pixels[(h - i - 1) * w + j].g = temp;
            temp = pixels[i * w + j].b;
            pixels[i * w + j].b = pixels[(h - i - 1) * w + j].b;
            pixels[(h - i - 1) * w + j].b = temp;
        }
    }
}

void Image::AdditionalFunction1() {
    for (int i = 0; i < w * h; ++i) {
        if (rand() % 100 < 10) {
            pixels[i].r = 0;
            pixels[i].g = 0;
            pixels[i].b = 0;
        } else if (rand() % 100 < 10) {
            pixels[i].r = 255;
            pixels[i].g = 255;
            pixels[i].b = 255;
        }
    }
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int r = 0, g = 0, b = 0;
            for (int k = -1; k <= 1; ++k) {
                for (int l = -1; l <= 1; ++l) {
                    if (i + k >= 0 && i + k < h && j + l >= 0 && j + l < w) {
                        r += pixels[(i + k) * w + (j + l)].r;
                        g += pixels[(i + k) * w + (j + l)].g;
                        b += pixels[(i + k) * w + (j + l)].b;
                    }
                }
            }
            pixels[i * w + j].r = r / 9;
            pixels[i * w + j].g = g / 9;
            pixels[i * w + j].b = b / 9;
        }
    }

}
void Image::AdditionalFunction2()
{
    Image temp(h, w);

    for(int r = 0; r < h; ++r) {
        for(int c = 0; c < w; ++c) {
            unsigned int dest = (c * h) + (h - r - 1);


            temp.pixels[dest] = pixels[(r * w) + c];

        }
    }
    *this = temp;
}
Image& Image::operator=(const Image &ref)
{
    if(this != &ref) {
        w = ref.w;
        h = ref.h;
        pixels = new Rgb[w * h];
        for(int i = 0; i < w * h; ++i) {
            pixels[i] = ref.pixels[i];
        }
    }
    return *this;
}

void Image::AdditionalFunction3(){}
//{
//    for (int i = 0; i < w * h; ++i)
//    {
//        if (rand() % 100 < 10)
//        {
//            pixels[i].r = 0;
//            pixels[i].g = 0;
//            pixels[i].b = 0;
//        }
//        else if (rand() % 100 < 10)
//        {
//            pixels[i].r = 255;
//            pixels[i].g = 255;
//            pixels[i].b = 255;
//        }
//    }
//    for(int i = 0; i < h; ++i)
//    {
//        for(int j = 0; j < w; ++j)
//        {
//            int r = 0, g = 0, b = 0;
//            for(int k = -1; k <= 1; ++k)
//            {
//                for(int l = -1; l <= 1; ++l)
//                {
//                    if(i + k >= 0 && i + k < h && j + l >= 0 && j + l < w)
//                    {
//                        r += pixels[(i + k) * w + (j + l)].r;
//                        g += pixels[(i + k) * w + (j + l)].g;
//                        b += pixels[(i + k) * w + (j + l)].b;
//                    }
//                }
//            }
//            pixels[i * w + j].r = r / 9;
//            pixels[i * w + j].g = g / 9;
//            pixels[i * w + j].b = b / 9;
//        }
//    }
//
//}

void Image::AdditionalFunction4()
{
    Image temp(h, w);

    for(int r = 0; r < h; ++r) {
        for(int c = 0; c < w; ++c) {
            unsigned int dest = (c*2 * h*2) + (h*2 - r*2 - 1*2);


            temp.pixels[dest] = pixels[(r*2 * w*2) + c*2];

        }
    }
    *this = temp;
}

void Image::gammaCorrection() {
    for (int i = 0; i < w * h; ++i) {
        pixels[i].r = pow(pixels[i].r / 255.0, 1.0) * 255;
        pixels[i].g = pow(pixels[i].g / 255.0, 1.0) * 255;
        pixels[i].b = pow(pixels[i].b / 255.0, 1.0) * 255;
    }
}

/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth()
{
    return w;
}

int Image::getHeight()
{
    return h;
}

Rgb* Image::getImage()
{
    return pixels;
}



int Image::pow(double d, float gamma) {
    return 0;
}



