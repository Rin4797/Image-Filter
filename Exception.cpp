#include "Exception.h"

InvalidFilterArgument::InvalidFilterArgument(): std::logic_error("")
{}

InvalidFilterArgument::InvalidFilterArgument(const char* msg): std::logic_error(msg)
{}

InvalidFilter::InvalidFilter(): std::logic_error("")
{}

InvalidFilter::InvalidFilter(const char* msg): std::logic_error(msg)
{}

InvalidBMP::InvalidBMP(): std::runtime_error("")
{}

InvalidBMP::InvalidBMP(const char* msg): std::runtime_error(msg)
{}
