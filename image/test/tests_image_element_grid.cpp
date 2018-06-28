#include "gtest/gtest.h"
#include "generate_tests_elements.hpp"
#include "../image.hpp"
#include "../image_element_grid.hpp"

TEST(ImageElementGridShould, ReturnTheGoodValue)
{
    Image im{getWellSetImage()};
    ImageElementGrid imageElementGrid{im};

    EXPECT_EQ(55, imageElementGrid({0,1,2}));
    EXPECT_EQ(7, imageElementGrid({2,1,0}));
    EXPECT_EQ(0, imageElementGrid({0,0,0}));
    EXPECT_EQ(124, imageElementGrid({4,4,4}));

    EXPECT_THROW(imageElementGrid({5,0,0}), OutOfBoundsException);
    EXPECT_THROW(imageElementGrid({5,5,5}), OutOfBoundsException);
}
