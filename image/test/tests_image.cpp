#include "gtest/gtest.h"
#include "generate_tests_elements.hpp"
#include <array>
#include <vector>
#include "../image.hpp"

TEST(ImageInitShould, ThrowIfUnaccordedSizeAreGiven)
{
    std::array<size_t, 3> dim {2, 2, 2};
	
	std::vector<int> vec = std::vector<int>(10, 0);

    EXPECT_THROW(Image(dim, vec), UnmatchedLengthException);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}