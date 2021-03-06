#ifndef IMAGE_GLOBAL_PROPERTIES_HPP_INCLUDED
#define IMAGE_GLOBAL_PROPERTIES_HPP_INCLUDED

#include <functional>
#include <optional>
#include <array>
#include <map>
#include <algorithm>
#include "../utils/array_utils.hpp"
#include "image.hpp"
#include "image_offset.hpp"
#include "image_exceptions.hpp"

template <class Element, size_t dimension>
class ImageGlobalProperties
{
    private:
    const Image<Element, dimension> & image;
    std::optional<std::vector<Element>::iterator> max;
    std::optional<std::vector<Element>::iterator> min;
    std::optional<std::reference_wrapper<ImageElementGrid>> imageElementGrid;
    std::optional<std::map<Element, size_t>> histogramMap;

    public:
    ImageGlobalProperties() = delete;
    ImageGlobalProperties(const Image<Element, dimension>  & imageRef) : image{imageRef}, max{std::nullopt}, min{std::nullopt}, imageElementGrid{std::nullopt}, histogramMap{std::nullopt} {};
    ImageGlobalProperties(const Image<Element, dimension>  & imageRef, ImageElementGrid & imageElementGridRef) 
        : image{imageRef}, max{std::nullopt}, min{std::nullopt}, imageElementGrid{imageElementGridRef}, histogramMap{std::nullopt}
    {
        if (!imageElementGrid.hasSameId(image.imageId)) throw UncorrectMappingException(); 
    };

    Element maxValue()
    {
        if (!max.has_value()) 
        {
            max = std::max_element(image.imageData.begin(), image.imageData.end());
        }
        return **max;
    };

    Element minValue()
    {
        if (!min.has_value()) 
        {
            min = std::min_element(image.imageData.begin(), image.imageData.end());
        }
        return **min;
    };

    std::array<size_t, dimension> indexOfMaxValue()
    {
        maxValue();
        size_t index{std::distance(image.imageData.begin(), *max)};

        return imageElementGrid.getPositionFromGlobalIndex(index);
    };

    std::array<size_t, dimension> indexOfMinValue()
    {
        minValue();
        size_t index{std::distance(image.imageData.begin(), *min)};

        return imageElementGrid.getPositionFromGlobalIndex(index);
    };

    std::map<Element, size_t> & histogram()
    {
        if (!histogramMap.has_value())
        {
            for (Element element : image.imageData)
            {
                ++(*histogramMap)[element];
            }
        }
        return histogramMap;
    }
    
};

#endif /* IMAGE_GLOBAL_PROPERTIES_HPP_INCLUDED */