#include "gtest/gtest.h"
#include "generate_tests_elements.hpp"
#include <array>
#include "../image.hpp"
#include "../image_offset.hpp"

TEST(ImageOffsetShould, ReturnTheGoodOffsetArray)
{
    Image im{getWellSetImage()};
    ImageOffset imgOffset{im};

    std::array<size_t, 3> & offsetArrayRef = imgOffset.getOffsetArray();

    std::array<size_t, 3> testValuesOffset{1, 5, 25};

    for (auto index{0}; index < 3; ++index)
    {
        EXPECT_EQ(offsetArrayRef[index], testValuesOffset[index]);
    }
}
