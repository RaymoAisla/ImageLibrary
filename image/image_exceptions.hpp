#ifndef IMAGE_ELEMENT_GRID_HPP_INCLUDED
#define IMAGE_ELEMENT_GRID_HPP_INCLUDED

#include <exception>

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

#endif /* IMAGE_ELEMENT_GRID_HPP_INCLUDED */