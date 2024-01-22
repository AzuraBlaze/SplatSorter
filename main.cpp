#include <iostream>
#include <array>

#include "Common.hpp"
#include "Roster.hpp"
#include "Menu.hpp"
#include "IO.hpp"

using namespace std;
using namespace SugarPP;

int main()
{
    cout << newline;

    Menu home_menu("Home Options");
    home_menu.back_button_title("Exit");
    home_menu.add_options
    ({
        {
            "Lobby Options", []()
            {
                return Menu::Option::Result();
            }
        }
    });

    home_menu.launch();

    cout << newline;
}