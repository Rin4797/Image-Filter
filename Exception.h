#pragma once

#include <exception>
#include <stdexcept>

class InvalidFilterArgument : public std::logic_error {
public:
    InvalidFilterArgument();
    InvalidFilterArgument(const char* msg);
};

class InvalidFilter : public std::logic_error {
public:
    InvalidFilter();
    InvalidFilter(const char* msg);
};

class InvalidBMP : public std::runtime_error {
public:
    InvalidBMP();
    InvalidBMP(const char* msg);
};
