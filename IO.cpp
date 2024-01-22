#include "IO.hpp"

using namespace std;
using namespace SugarPP;

ostream& operator<<(ostream& os, const page_break_t& page_break_obj)
{
    cout << "\n\n";

    for(int i : Range(0, 80))
        os << '=';
    
    os << "\n\n\n";

    return os;
}

ostream& operator<<(ostream& os, const indent_t& indent_obj)
{
    os << "    ";

    return os;
}