#include "utility/Bitmap.h"

using namespace rotamina;

Bitmap::Bitmap() {
    this->data = nullptr;
    this->sizeX = 0;
    this->sizeY = 0;
}

Bitmap::~Bitmap() {
    if (data) {
        delete [] data;
    }
}

bool Bitmap::load(const char * filename) {
    
    FILE *fp;
    unsigned long size;           // size of the image in bytes.
    unsigned long i;              // standard counter.
    unsigned short int planes;    // number of planes in image (must be 1)
    unsigned short int bpp;       // number of bits per pixel (must be 24)

    // make sure the file is there.
    if ((fp = fopen (filename, "rb")) == 0) {
        printf ("File Not Found : %s\n", filename);
        return false;
    }

    // seek through the bmp header, up to the width/height:
    fseek (fp, 18, SEEK_CUR);

    // read the width
    if (fread (&sizeX, 4, 1, fp) != 1) {
        printf ("Error reading width from %s.\n", filename);
        fclose (fp);
        return false;
    }
    // printf ("Width of %s: %lu\n", filename, sizeX);

    // read the height
    if (fread (&sizeY, 4, 1, fp) != 1) {
        printf ("Error reading height from %s.\n", filename);
        fclose (fp);
        return false;
    }
    // printf ("Height of %s: %lu\n", filename, sizeY);

    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = sizeX * sizeY * 3;

    // read the planes
    if (fread (&planes, 2, 1, fp) != 1) {
        printf ("Error reading planes from %s.\n", filename);
        fclose (fp);
        return false;
    }

    if (planes != 1) {
        printf ("Planes from %s is not 1: %u\n", filename, planes);
        fclose (fp);
        return false;
    }

    // read the bpp
    if (fread (&bpp, 2, 1, fp) != 1) {
        printf ("Error reading bpp from %s.\n", filename);
        fclose (fp);
        return false;
    }

    if (bpp != 24) {
        printf ("Bpp from %s is not 24: %u\n", filename, bpp);
        fclose (fp);
        return false;
    }

    // seek past the rest of the bitmap header.
    fseek (fp, 24, SEEK_CUR);

    // read the data.
    data = new unsigned char[size];
    if (data == 0) {
        printf ("Error allocating memory for image data");
        fclose (fp);
        return false;
    }

    if (fread (data, size, 1, fp) != 1) {
        printf ("Error reading image data from %s.\n", filename);
        fclose (fp);
        return false;
    }
    
    for (int i = 0; i < size; i += 3) {
        std::swap(data[i], data[i + 2]);
    }

    fclose (fp);
    return true;
}

Eigen::Vector3f Bitmap::getColor(Eigen::Vector2f coord) {
    return getColor(coord[0], coord[1]);
}

Eigen::Vector3f Bitmap::getColor(float nx, float ny) {
    int x = nx * sizeX, y = ny * sizeY;
    int id = y * sizeX + x;
    return Eigen::Vector3f(nc(data[id * 3 + 2]), nc(data[id * 3 + 1]), nc(data[id * 3]));
}

float Bitmap::nc(char c) {
    return (float) c / 255.0f;
}
