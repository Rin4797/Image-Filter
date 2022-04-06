#include "gtest/gtest.h"

#include <iostream>
#include <fstream>
#include <string>

#include "BMP.h"
#include "Image.h"
#include "Exception.h"
#include "filters/FilterFactory.h"
#include "Parser.h"

TEST(image_processor, simple) {
    EXPECT_EQ(2 * 3, 6);
}

TEST(BMP, ReadAndWrite) {
    std::ofstream output1("examples/test/input_correct.bmp", std::ios::out | std::ios::binary);
    output1.write("BM", 2);
    output1.write("F\0\0\0", 4);
    output1.write("\0\0\0\0", 4);
    output1.write("6\0\0\0", 4);
    output1.write("(\0\0\0", 4);

    output1.write("\x2\0\0\0", 4);
    output1.write("\x2\0\0\0", 4);

    output1.write("\x1\0", 2);
    output1.write("\x18\0", 2);
    output1.write("\0\0\0\0", 4);
    output1.write("\x10\0\0\0", 4);
    output1.write("\x13\v\0\0", 4);
    output1.write("\x13\v\0\0", 4);
    output1.write("\0\0\0\0", 4);
    output1.write("\0\0\0\0", 4);

    output1.write("\0\0?", 3);
    output1.write("???", 3);

    output1.write("\0\0", 2);

    output1.write("?\0\0", 3);
    output1.write("\0?\0", 3);

    output1.write("\0\0", 2);

    output1.close();

    std::ofstream output2("examples/test/input_incorrect_type.bmp", std::ios::out | std::ios::binary);
    output2.write("BB", 2);
    output2.write("F\0\0\0", 4);
    output2.write("\0\0\0\0", 4);
    output2.write("6\0\0\0", 4);
    output2.write("(\0\0\0", 4);

    output2.write("\x2\0\0\0", 4);
    output2.write("\x2\0\0\0", 4);

    output2.write("\x1\0", 2);
    output2.write("\x18\0", 2);
    output2.write("\0\0\0\0", 4);
    output2.write("\x10\0\0\0", 4);
    output2.write("\x13\v\0\0", 4);
    output2.write("\x13\v\0\0", 4);
    output2.write("\0\0\0\0", 4);
    output2.write("\0\0\0\0", 4);

    output2.write("\0\0?", 3);
    output2.write("???", 3);

    output2.write("\0\0", 2);

    output2.write("?\0\0", 3);
    output2.write("\0?\0", 3);

    output2.write("\0\0", 2);

    output2.close();

    std::ofstream output3("examples/test/input_incorrect_rawsize.bmp", std::ios::out | std::ios::binary);
    output3.write("BM", 2);
    output3.write("F\0\0\0", 4);
    output3.write("\0\0\0\0", 4);
    output3.write("6\0\0\0", 4);
    output3.write("(\0\0\0", 4);

    output3.write("\x2\0\0\0", 4);
    output3.write("\x2\0\0\0", 4);

    output3.write("\x1\0", 2);
    output3.write("\x18\1", 2);
    output3.write("\0\0\0\0", 4);
    output3.write("\x10\0\0\0", 4);
    output3.write("\x13\v\0\0", 4);
    output3.write("\x13\v\0\0", 4);
    output3.write("\0\0\0\0", 4);
    output3.write("\0\0\0\0", 4);

    output3.write("\0\0?", 3);
    output3.write("???", 3);

    output3.write("\0\0", 2);

    output3.write("?\0\0", 3);
    output3.write("\0?\0", 3);

    output3.write("\0\0", 2);

    output3.close();

    BMP bmp;

    Image image = bmp.Import("examples/test/input_correct.bmp");
    bmp.Export("examples/test/output.bmp", image);

    std::ifstream id1("examples/test/output.bmp");
    std::string outfile((std::istreambuf_iterator<char>(id1)), std::istreambuf_iterator<char>());

    std::ifstream id2("examples/test/input_correct.bmp");
    std::string infile((std::istreambuf_iterator<char>(id2)), std::istreambuf_iterator<char>());

    EXPECT_EQ(infile, outfile);

    try {
        bmp.Import("examples/test/input_incorrect.bmp");
    } catch (InvalidBMP err) {
        EXPECT_STREQ(err.what(), "Cannot be opened for reading");
    } catch (...) {
        FAIL();
    }

    try {
        bmp.Import("examples/test/input_incorrect_type.bmp");
    } catch (InvalidBMP err) {
        EXPECT_STREQ(err.what(), "Wrong type");
    } catch (...) {
        FAIL();
    }

    try {
        bmp.Import("examples/test/input_incorrect_rawsize.bmp");
    } catch (InvalidBMP err) {
        EXPECT_STREQ(err.what(), "Wrong amount of bits");
    } catch (...) {
        FAIL();
    }
}

TEST(Filter, Filters) {
    FilterFactory F;

    Image image(5, 5);

    image.SetColor(0, 0, Color(0, 0, 0));
    image.SetColor(1, 0, Color(0, 0, 255));
    image.SetColor(2, 0, Color(0, 255, 255));
    image.SetColor(3, 0, Color(0, 0, 255));
    image.SetColor(4, 0, Color(0, 0, 0));

    image.SetColor(0, 1, Color(128, 0, 0));
    image.SetColor(1, 1, Color(128, 0, 255));
    image.SetColor(2, 1, Color(128, 255, 255));
    image.SetColor(3, 1, Color(128, 0, 255));
    image.SetColor(4, 1, Color(128, 0, 0));

    image.SetColor(0, 2, Color(255, 0, 0));
    image.SetColor(1, 2, Color(255, 0, 255));
    image.SetColor(2, 2, Color(255, 255, 255));
    image.SetColor(3, 2, Color(255, 0, 255));
    image.SetColor(4, 2, Color(255, 0, 0));

    image.SetColor(0, 3, Color(128, 0, 0));
    image.SetColor(1, 3, Color(128, 0, 255));
    image.SetColor(2, 3, Color(128, 255, 255));
    image.SetColor(3, 3, Color(128, 0, 255));
    image.SetColor(4, 3, Color(128, 0, 0));

    image.SetColor(0, 4, Color(0, 0, 0));
    image.SetColor(1, 4, Color(0, 0, 255));
    image.SetColor(2, 4, Color(0, 255, 255));
    image.SetColor(3, 4, Color(0, 0, 255));
    image.SetColor(4, 4, Color(0, 0, 0));

    Image image_crop(3, 3);

    image_crop.SetColor(0, 0, Color(255, 0, 0));
    image_crop.SetColor(1, 0, Color(255, 0, 255));
    image_crop.SetColor(2, 0, Color(255, 255, 255));

    image_crop.SetColor(0, 1, Color(128, 0, 0));
    image_crop.SetColor(1, 1, Color(128, 0, 255));
    image_crop.SetColor(2, 1, Color(128, 255, 255));

    image_crop.SetColor(0, 2, Color(0, 0, 0));
    image_crop.SetColor(1, 2, Color(0, 0, 255));
    image_crop.SetColor(2, 2, Color(0, 255, 255));

    Image image_gs(5, 5);

    image_gs.SetColor(0, 0, Color(0, 0, 0));
    image_gs.SetColor(1, 0, Color(29, 29, 29));
    image_gs.SetColor(2, 0, Color(178, 178, 178));
    image_gs.SetColor(3, 0, Color(29, 29, 29));
    image_gs.SetColor(4, 0, Color(0, 0, 0));

    image_gs.SetColor(0, 1, Color(38, 38, 38));
    image_gs.SetColor(1, 1, Color(67, 67, 67));
    image_gs.SetColor(2, 1, Color(217, 217, 217));
    image_gs.SetColor(3, 1, Color(67, 67, 67));
    image_gs.SetColor(4, 1, Color(38, 38, 38));

    image_gs.SetColor(0, 2, Color(76, 76, 76));
    image_gs.SetColor(1, 2, Color(105, 105, 105));
    image_gs.SetColor(2, 2, Color(255, 255, 255));
    image_gs.SetColor(3, 2, Color(105, 105, 105));
    image_gs.SetColor(4, 2, Color(76, 76, 76));

    image_gs.SetColor(0, 3, Color(38, 38, 38));
    image_gs.SetColor(1, 3, Color(67, 67, 67));
    image_gs.SetColor(2, 3, Color(217, 217, 217));
    image_gs.SetColor(3, 3, Color(67, 67, 67));
    image_gs.SetColor(4, 3, Color(38, 38, 38));

    image_gs.SetColor(0, 4, Color(0, 0, 0));
    image_gs.SetColor(1, 4, Color(29, 29, 29));
    image_gs.SetColor(2, 4, Color(178, 178, 178));
    image_gs.SetColor(3, 4, Color(29, 29, 29));
    image_gs.SetColor(4, 4, Color(0, 0, 0));

    Image image_blur(5, 5);

    image_blur.SetColor(0, 0, Color(64, 19, 109));
    image_blur.SetColor(1, 0, Color(64, 65, 188));
    image_blur.SetColor(2, 0, Color(64, 102, 227));
    image_blur.SetColor(3, 0, Color(64, 65, 188));
    image_blur.SetColor(4, 0, Color(64, 19, 109));

    image_blur.SetColor(0, 1, Color(127, 19, 108));
    image_blur.SetColor(1, 1, Color(127, 64, 188));
    image_blur.SetColor(2, 1, Color(126, 102, 227));
    image_blur.SetColor(3, 1, Color(127, 64, 188));
    image_blur.SetColor(4, 1, Color(127, 19, 108));

    image_blur.SetColor(0, 2, Color(165, 18, 108));
    image_blur.SetColor(1, 2, Color(165, 64, 188));
    image_blur.SetColor(2, 2, Color(164, 102, 226));
    image_blur.SetColor(3, 2, Color(165, 64, 188));
    image_blur.SetColor(4, 2, Color(165, 18, 108));

    image_blur.SetColor(0, 3, Color(127, 19, 109));
    image_blur.SetColor(1, 3, Color(127, 65, 188));
    image_blur.SetColor(2, 3, Color(126, 102, 227));
    image_blur.SetColor(3, 3, Color(127, 65, 188));
    image_blur.SetColor(4, 3, Color(127, 19, 109));

    image_blur.SetColor(0, 4, Color(64, 19, 109));
    image_blur.SetColor(1, 4, Color(64, 65, 188));
    image_blur.SetColor(2, 4, Color(64, 102, 227));
    image_blur.SetColor(3, 4, Color(64, 65, 188));
    image_blur.SetColor(4, 4, Color(64, 19, 109));

    Image image_sharp(5, 5);

    image_sharp.SetColor(0, 0, Color(0, 0, 0));
    image_sharp.SetColor(1, 0, Color(0, 0, 255));
    image_sharp.SetColor(2, 0, Color(0, 255, 255));
    image_sharp.SetColor(3, 0, Color(0, 0, 255));
    image_sharp.SetColor(4, 0, Color(0, 0, 0));

    image_sharp.SetColor(0, 1, Color(129, 0, 0));
    image_sharp.SetColor(1, 1, Color(129, 0, 255));
    image_sharp.SetColor(2, 1, Color(129, 255, 255));
    image_sharp.SetColor(3, 1, Color(129, 0, 255));
    image_sharp.SetColor(4, 1, Color(129, 0, 0));

    image_sharp.SetColor(0, 2, Color(255, 0, 0));
    image_sharp.SetColor(1, 2, Color(255, 0, 255));
    image_sharp.SetColor(2, 2, Color(255, 255, 255));
    image_sharp.SetColor(3, 2, Color(255, 0, 255));
    image_sharp.SetColor(4, 2, Color(255, 0, 0));

    image_sharp.SetColor(0, 3, Color(129, 0, 0));
    image_sharp.SetColor(1, 3, Color(129, 0, 255));
    image_sharp.SetColor(2, 3, Color(129, 255, 255));
    image_sharp.SetColor(3, 3, Color(129, 0, 255));
    image_sharp.SetColor(4, 3, Color(129, 0, 0));

    image_sharp.SetColor(0, 4, Color(0, 0, 0));
    image_sharp.SetColor(1, 4, Color(0, 0, 255));
    image_sharp.SetColor(2, 4, Color(0, 255, 255));
    image_sharp.SetColor(3, 4, Color(0, 0, 255));
    image_sharp.SetColor(4, 4, Color(0, 0, 0));

    F.crop.SetParameters(3, 3);
    EXPECT_EQ(F.crop.Apply(image), image_crop);
    EXPECT_EQ(F.grayscale.Apply(image), image_gs);
    F.blur.SetSigma(1);
    EXPECT_EQ(F.blur.Apply(image), image_blur);
    EXPECT_EQ(F.sharpening.Apply(image), image_sharp);
}

TEST(Image, simple) {
    Image image(2, 3);
    EXPECT_EQ(image.GetWidth(), 2);
    EXPECT_EQ(image.GetHeight(), 3);
    image.Resize(5, 9);
    EXPECT_EQ(image.GetWidth(), 5);
    EXPECT_EQ(image.GetHeight(), 9);
    EXPECT_EQ(image.GetColorValue(10, 10), Color(0, 0, 0));
    try {
        image.GetColor(10, 10);
    } catch (std::out_of_range err) {
        EXPECT_STREQ(err.what(), "Wrong coordinates");
    } catch (...) {
        FAIL();
    }
}