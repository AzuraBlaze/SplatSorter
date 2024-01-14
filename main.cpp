#include <iostream>

#include "Common.hpp"
#include "Menu.hpp"

using namespace std;
using namespace SugarPP;

static bool is_running = true; 

int main()
{
    cout << endl;

    Menu menu("What would you like to do?");
    menu.add_options
    ({
        {
            "Exit", []()
            {
                is_running = false;
            }
        },
        {
            "Add player", []()
            {
                //
            }
        },
        {
            "Edit player", []()
            {
                //
            }
        },
        {
            "Delete player", []()
            {
                //
            }
        }
    });

    while(is_running)
    {
        cout << endl;

        menu.launch();

        cout << endl;
    }

    cout << endl;
}