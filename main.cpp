#include <iostream>
#include "Player.hpp"
#include "SugarPP/io.hpp"

int main()
{
    int num = SugarPP::input<int>("Enter a number: ");
    SugarPP::print("You entered:", num);
}