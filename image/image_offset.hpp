#ifndef IMAGE_OFFSET_HPP_INCLUDED
#define IMAGE_OFFSET_HPP_INCLUDED

#include <array>
#include <algorithm>
#include "../utils/array_utils.hpp"
#include "image_exceptions.hpp"
#include "image.hpp"

template <class Element, size_t dimension>
class ImageOffset {

private:
    const Image<Element, dimension> & image;
    std::array<size_t, dimension> offsetArray;

public:
    ImageOffset() = delete;
    ImageOffset(const Image<Element, dimension> & imageRef) : image{imageRef}, offsetArray{} {
        offsetArray = image.imageSizeArray;
        
        std::rotate(offsetArray.begin(), offsetArray.begin()+1, offsetArray.end());
        *(offsetArray.begin()) = 1;

        for (auto directionalOffset{offsetArray.begin()+1}; directionalOffset<offsetArray.end(); ++directionalOffset)
        {
            *directionalOffset *= *(directionalOffset-1);
        }
    };

    const std::array<size_t, dimension> & getOffsetArray() {
        return offsetArray;
    };

    bool hasSameId(size_t id)
    {
        return id == image.imageId;
    }

    friend bool operator ==(const ImageOffset & imgOffset1, const ImageOffset & imgOffset2);
    friend bool operator !=(const ImageOffset & imgOffset1, const ImageOffset & imgOffset2);

};

bool operator ==(const ImageOffset & imgOffset1, const ImageOffset & imgOffset2)
{
    return (imgOffset1.offsetArray == imgOffset2.offsetArray && imgOffset1.image.imageId == imgOffset2.image.imageId);
}

bool operator !=(const ImageOffset & imgOffset1, const ImageOffset & imgOffset2)
{
    return !(imgOffset1 == imgOffset2);
}

#endif /* IMAGE_OFFSET_HPP_INCLUDED */