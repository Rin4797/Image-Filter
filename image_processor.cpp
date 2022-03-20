#include "BMP.h"
#include "filters/FilterFactory.h"

int main() {
    BMP bmp;
    bmp.Import("examples/example2.bmp");
    Image image = bmp.ImportedImage();
    FilterFactory F;
    std::cout << "SETINPUT" << std::endl;
//    image = F.sharpening.Apply(image);
    F.blur.SetSigma(10);
    image = F.blur.Apply(image);
    bmp.ImportImage(image);
    bmp.Export("examples/example3.bmp");
}
