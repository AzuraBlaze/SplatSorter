#include <iostream>
#include <array>

#include "Common.hpp"
#include "Roster.hpp"
#include "Menu.hpp"
#include "IO.hpp"

using namespace std;
using namespace SugarPP;

void launch_main_menu();
void launch_lobby_menu();


int main()
{
    cout << newline;

    launch_main_menu();

    cout << newline;
}


void launch_main_menu()
{
    Menu menu("Main Options");
    menu.back_button_title("Exit");
    menu.add_options
    ({
        {
            "Lobby Options", []()
            {
                launch_lobby_menu();

                return Menu::Option::Result();
            }
        }
    });

    menu.launch();
}

void launch_lobby_menu()
{
    Menu menu("Lobby Options");
    menu.add_options
    ({
        {
            "View Players", []()
            {
                return Menu::Option::Result();
            }
        },
        {
            "Add Players", []()
            {
                return Menu::Option::Result();
            }
        },
        {
            "Edit Player", []()
            {
                return Menu::Option::Result();
            }
        },
        {
            "Delete Player", []()
            {
                return Menu::Option::Result();
            }
        }
    });

    menu.launch();
}