#ifndef IMAGE_GLOBAL_PROPERTIES_HPP_INCLUDED
#define IMAGE_GLOBAL_PROPERTIES_HPP_INCLUDED

#include <functional>
#include <optional>
#include <array>
#include "../utils/array_utils.hpp"
#include "image.hpp"
#include "image_offset.hpp"
#include "image_exceptions.hpp"

typedef bool isDefined;

template <class Element, size_t dimension>
class ImageGlobalProperties
{
    private:
    const Image<Element, dimension> & image;
    std::optional<Element> max;
    std::optional<Element> min;
    std::optional<std::reference_wrapper<ImageOffset>> imageOffset;

    public:
    ImageGlobalProperties() = delete;
    ImageGlobalProperties(const Image<Element, dimension>  & imageRef) : image{imageRef}, max{std::nullopt}, min{std::nullopt}, imageOffset{std::nullopt} {};
    ImageGlobalProperties(const Image<Element, dimension>  & imageRef, ImageOffset & imageOffsetRef) 
        : image{imageRef}, max{std::nullopt}, min{std::nullopt}, imageOffset{imageOffsetRef} 
    {
        if (imageOffset != ImageOffset(imageRef)) throw UncorrectMappingException(); 
    };

    Element maxValue()
    {
        if (!max.has_value()) 
        {
            max = *std::max_element(image.imageData.begin(), image.imageData.end());
        }
        return *max;
    };

    Element minValue()
    {
        if (!min.has_value()) 
        {
            min = *std::min_element(image.imageData.begin(), image.imageData.end());
        }
        return *min;
    };

    std::array<size_t, dimension> indexOfMaxValue()
    {
        if (!imageOffset.has_value()) 
        {
            imageOffset = ImageOffset(image);
        }

        size_t index{std::distance(image.imageData.begin(), std::max_element(image.imageData.begin(), image.imageData.end()))};

        std::array<size_t, dimension> positionArray{imageOffset.getOffsetArray().begin(), imageOffset.getOffsetArray().end()};

        auto positionIter{positionArray.rbegin()};
        auto offsetIter{imageOffset.getOffsetArray().rbegin()};
        for (;positionIter < positionArray.rend(); ++positionIter, ++offsetIter)
        {
            *positionIter = index / (*offsetIter);
            index -= (*positionIter) * (*offsetIter);
        }

        return positionArray;
    };
};

#endif /* IMAGE_GLOBAL_PROPERTIES_HPP_INCLUDED */