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
        if (!imageOffset.hasSameId(imageRef.imageId)) throw UncorrectMappingException(); 
    };

    size_t getGlobalIndexFromPosition(const std::array<size_t, dimension> & positionArray)
    {
        if (!(positionArray < image.imageSizeArray)) throw OutOfBoundsException();

        auto offsetPositionArray = positionArray;

        std::transform(offsetPositionArray.begin(), offsetPositionArray.end(), imageOffset.getOffsetArray().begin(), offsetPositionArray.begin(), std::multiplies<size_t>());

        auto offset = std::accumulate(offsetPositionArray.begin(), offsetPositionArray.end(), 0, std::plus<size_t>());

        return offset;
    };

    std::array<size_t, dimension> getPositionFromGlobalIndex(size_t index)
    {
        std::array<size_t, dimension> positionArray{imageOffset.getOffsetArray().begin(), imageOffset.getOffsetArray().end()};

        auto positionIter{positionArray.rbegin()};
        auto offsetIter{imageOffset.getOffsetArray().rbegin()};
        for (;positionIter < positionArray.rend(); ++positionIter, ++offsetIter)
        {
            *positionIter = index / (*offsetIter);
            index -= (*positionIter) * (*offsetIter);
        }

        return positionArray;
    }

    Element & override ()(const std::array<size_t, dimension> & positionArray)
    {
        getGlobalIndexFromPosition(positionArray);

        return image.imageData[offset];
    };

    bool hasSameId(size_t id)
    {
        return id == image.imageId;
    }

};

#endif /* IMAGE_ELEMENT_GRID_HPP_INCLUDED */