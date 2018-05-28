#include "gtest/gtest.h"
#include <array>
#include <vector>
#include "../image.hpp"

Image getWellSetImage()
{
    std::array<size_t, 3> dim {5, 5, 5};
	
	std::vector<int> vec = std::vector<int>(125, 0);
	
	for (int i=0;i<125;++i)
	{
		vec[i] = i;
	}
	
	return Image<int, 3>{dim, vec};
}

TEST(ImageInitShould, ThrowIfUnaccordedSizeAreGiven)
{
    std::array<size_t, 3> dim {2, 2, 2};
	
	std::vector<int> vec = std::vector<int>(10, 0);

    EXPECT_THROW(Image(dim, vec), UnmatchedLengthException);
}

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

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}