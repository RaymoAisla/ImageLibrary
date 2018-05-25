#include <array>

template<class Element, size_t dimension>
bool operator > (const std::array<Element, dimension> & firstArray, const std::array<Element, dimension> & secondArray)
{
    auto firstIter{firstArray.begin()};
    auto secondIter{secondArray.begin()};

    bool comparisonResult{true};

    while (comparisonResult && firstIter < firstArray.end())
    {
        if (*firstIter <= *secondIter) comparisonResult = false;
        ++firstIter;
        ++secondIter;
    }

    return comparisonResult;
}

template<class Element, size_t dimension>
bool operator >= (const std::array<Element, dimension> & firstArray, const std::array<Element, dimension> & secondArray)
{
    auto firstIter{firstArray.begin()};
    auto secondIter{secondArray.begin()};

    bool comparisonResult{true};

    while (comparisonResult && firstIter < firstArray.end())
    {
        if (*firstIter < *secondIter) comparisonResult = false;
        ++firstIter;
        ++secondIter;
    }

    return comparisonResult;
}

template<class Element, size_t dimension>
bool operator < (const std::array<Element, dimension> & firstArray, const std::array<Element, dimension> & secondArray)
{
    auto firstIter{firstArray.begin()};
    auto secondIter{secondArray.begin()};

    bool comparisonResult{true};

    while (comparisonResult && firstIter < firstArray.end())
    {
        if (*firstIter >= *secondIter) comparisonResult = false;
        ++firstIter;
        ++secondIter;
    }

    return comparisonResult;
}

template<class Element, size_t dimension>
bool operator <= (const std::array<Element, dimension> & firstArray, const std::array<Element, dimension> & secondArray)
{
    auto firstIter{firstArray.begin()};
    auto secondIter{secondArray.begin()};

    bool comparisonResult{true};

    while (comparisonResult && firstIter < firstArray.end())
    {
        if (*firstIter > *secondIter) comparisonResult = false;
        ++firstIter;
        ++secondIter;
    }

    return comparisonResult;
}