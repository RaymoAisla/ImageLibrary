#ifndef IMAGE_HPP_INCLUDED
#define IMAGE_HPP_INCLUDED

#include <array>
#include <vector>
#include <numeric>
#include "../utils/array_utils.hpp"
#include "image_exceptions.hpp"

template <class Element, size_t dimension>
struct Image
{
    static size_t imageIdCounter{0};

    size_t imageId;

    const std::array<size_t, dimension> imageSizeArray;
    std::vector<Element> imageData;

    Image() = delete;
    Image(const std::array<size_t, dimension> & sizeArray) : imageSizeArray{sizeArray}, imageData{}, imageId{imageIdCounter} {
        auto totalSize = std::accumulate(imageSizeArray.begin(), imageSizeArray.end(), 1, std::multiplies<size_t>());

        imageData = std::vector<Element>(totalSize);

        ++imageIdCounter;
    };

    Image(const std::array<size_t, dimension> & sizeArray, Element initElement) : imageSizeArray{sizeArray}, imageData{}, imageId{imageIdCounter} {
        auto totalSize = std::accumulate(imageSizeArray.begin(), imageSizeArray.end(), 1, std::multiplies<size_t>());

        imageData = std::vector<Element>(totalSize, initElement);

        ++imageIdCounter;
    };

    Image(const std::array<size_t, dimension> & sizeArray, const std::vector<Element> & data) : imageSizeArray{sizeArray}, imageData{data}, imageId{imageIdCounter} {
        auto totalSize = std::accumulate(imageSizeArray.begin(), imageSizeArray.end(), 1, std::multiplies<size_t>());

        if (totalSize != imageData.size()) throw UnmatchedLengthException(totalSize, imageData.size());

        ++imageIdCounter;
    }; 
};

template <class Element, size_t dimension>
size_t Image<Element, dimension>::imageIdCounter = 0;

#endif /* IMAGE_HPP_INCLUDED */