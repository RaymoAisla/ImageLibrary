#ifndef GENERATE_TESTS_ELEMENTS_HPP_INCLUDED
#define GENERATE_TESTS_ELEMENTS_HPP_INCLUDED

#include <array>
#include <vector>
#include "../image.hpp"

Image<int, 3> getWellSetImage()
{
    std::array<size_t, 3> dim {5, 5, 5};
	
	std::vector<int> vec = std::vector<int>(125, 0);
	
	for (int i=0;i<125;++i)
	{
		vec[i] = i;
	}
	
	return Image<int, 3>{dim, vec};
}

#endif /* GENERATE_TESTS_ELEMENTS_HPP_INCLUDED */