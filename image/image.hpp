#include <array>
#include <vector>
#include <numeric>
#include <limits>
#include <exception>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "array_utils.hpp"

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

template <class Element, size_t dimension>
class Image
{
private:
    std::array<size_t, dimension> imageSizeArray;
    std::vector<Element> imageData;

    std::array<size_t, dimension> getOffsetArray() {
        auto offsetArray = imageSizeArray;
        
        std::rotate(offsetArray.begin(), offsetArray.begin()+1, offsetArray.end());
        *(offsetArray.begin()) = 1;

        for (auto directionalOffset{offsetArray.begin()+1}; directionalOffset<offsetArray.end(); ++directionalOffset)
        {
            *directionalOffset *= *(directionalOffset-1);
        }
        
        return offsetArray;
        
    };

public:
    Image() = delete;
    Image(const std::array<size_t, dimension> & sizeArray) : imageSizeArray{sizeArray}, imageData{} {
        auto totalSize = std::accumulate(imageSizeArray.begin(), imageSizeArray.end(), 1, std::multiplies<size_t>());

        imageData = std::vector<Element>(totalSize);
    };

    Image(const std::array<size_t, dimension> & sizeArray, Element initElement) : imageSizeArray{sizeArray}, imageData{} {
        auto totalSize = std::accumulate(imageSizeArray.begin(), imageSizeArray.end(), 1, std::multiplies<size_t>());

        imageData = std::vector<Element>(totalSize, initElement);
    };

    Image(const std::array<size_t, dimension> & sizeArray, const std::vector<Element> & data) : imageSizeArray{sizeArray}, imageData{data} {
        auto totalSize = std::accumulate(imageSizeArray.begin(), imageSizeArray.end(), 1, std::multiplies<size_t>());

        if (totalSize != imageData.size()) throw UnmatchedLengthException(totalSize, imageData.size());
    }; 

    Element getValue(const std::array<size_t, dimension> & positionArray) {

        if (!(positionArray < imageSizeArray)) throw new OutOfBoundsException();

        auto offsetPositionArray = positionArray;

        std::transform(offsetPositionArray.begin(), offsetPositionArray.end(), getOffsetArray().begin(), offsetPositionArray.begin(), std::multiplies<size_t>());

        auto offset = std::accumulate(offsetPositionArray.begin(), offsetPositionArray.end(), 0, std::plus<size_t>());

        return imageData[offset];
    }
};