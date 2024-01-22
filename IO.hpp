#ifndef SPLATSORTER_IO_HPP
#define SPLATSORTER_IO_HPP

#include <iostream>

#include "Common.hpp"

struct page_break_t
{
    constexpr page_break_t() {}
};

constexpr page_break_t page_break;

std::ostream& operator<<(std::ostream& os, const page_break_t& page_break_obj);


struct indent_t
{
    constexpr indent_t() {}
};

constexpr indent_t indent;

std::ostream& operator<<(std::ostream& os, const indent_t& indent_obj);


using newline_t = char;
constexpr newline_t newline = '\n';


#endif /* SPLATSORTER_IO_HPP */