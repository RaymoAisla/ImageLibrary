#ifndef IMAGE_ELEMENT_GRID_HPP_INCLUDED
#define IMAGE_ELEMENT_GRID_HPP_INCLUDED

#include <array>
#include <numeric>
#include <algorithm>
#include "../utils/array_utils.hpp"
#include "image_exceptions.hpp"
#include "image.hpp"
#include "image_offset.hpp"

template <class Element, size_t dimension>
class ImageElementGrid {

private:
    Image<Element, dimension> & image;
    const ImageOffset<Element, dimension> & imageOffset;

public:
    ImageElementGrid() = delete;
    ImageElementGrid(Image<Element, dimension> & imageRef) : image{imageRef}, imageOffset{ImageOffset(imageRef)}
    {};
    ImageElementGrid(Image<Element, dimension> & imageRef, const ImageOffset<Element, dimension> & imageOffsetRef) : image{imageRef}, imageOffset{imageOffsetRef}
    {
        if (imageOffset != ImageOffset(imageRef)) throw UncorrectMappingException(); 
    };

    Element & override ()(const std::array<size_t, dimension> & positionArray)
    {
        if (!(positionArray < image.imageSizeArray)) throw OutOfBoundsException();

        auto offsetPositionArray = positionArray;

        std::transform(offsetPositionArray.begin(), offsetPositionArray.end(), imageOffset.getOffsetArray().begin(), offsetPositionArray.begin(), std::multiplies<size_t>());

        auto offset = std::accumulate(offsetPositionArray.begin(), offsetPositionArray.end(), 0, std::plus<size_t>());

        return image.imageData[offset];
    };

};

#endif /* IMAGE_ELEMENT_GRID_HPP_INCLUDED */