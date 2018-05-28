#include <array>
#include <vector>
#include <numeric>
#include <limits>
#include <exception>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "../utils/array_utils.hpp"

class UnmatchedLengthException : public std::runtime_error 
{
private:
    size_t dimensionArrayGivenSize;
    size_t dataArrayGivenSize;

public:
    UnmatchedLengthException() = delete;
    UnmatchedLengthException(size_t dimensionArraySize, size_t dataArraySize) 
        : runtime_error("Sizes of dimensional array and data array do not match"), dimensionArrayGivenSize{dimensionArraySize}, dataArrayGivenSize{dataArraySize} {};

    virtual const char* what() const throw()
    {
        std::stringstream message;
        message << runtime_error::what() << " " << dimensionArrayGivenSize << " and " << dataArrayGivenSize;

        return message.str().c_str();
    }
};

class OutOfBoundsException : public std::runtime_error 
{
public:
    OutOfBoundsException()
        : runtime_error("Searched Index in a dimension is higher than length in that dimension") {};

    virtual const char* what() const throw()
    {
        std::stringstream message;
        message << runtime_error::what();

        return message.str().c_str();
    }
};

class UncorrectMappingException : public std::runtime_error 
{
public:
    UncorrectMappingException() = delete;
    UncorrectMappingException(size_t id1, size_t id2) 
        : runtime_error("An object has been created with multiples references toward different objects of the same class.")
    {};

    virtual const char* what() const throw()
    {
        std::stringstream message;
        message << runtime_error::what();

        return message.str().c_str();
    }
};

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

        return imageData[offset];
    };

};