#include <iostream>
#include <array>
#include <cctype>

#include "Common.hpp"
#include "IO.hpp"
#include "Menu.hpp"
#include "Roster.hpp"

using namespace std;
using namespace SugarPP;

void launch_main_menu();
void launch_lobby_menu();
void launch_delete_player_menu();
void register_player_from_user();
void overwrite_existing_player(const string& name, int wins, int losses);
void launch_edit_player_menu(const string& name);

bool boolean_prompt(const string& prompt);

static Roster g_lobby;

int main()
{
    cout << newline;

    launch_main_menu();

    cout << newline;
}

bool boolean_prompt(const string& prompt)
{
    cout << prompt;

    char answer = input<char>(" (Y/N): ");
    answer = toupper(answer);

    while(answer != 'Y' && answer != 'N')
    {
        answer = input<char>("Error: Please enter 'Y' (Yes) or 'N' (No): ");
        answer = toupper(answer);
    }

    return (answer == 'Y');
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
                if(g_lobby.empty())
                    return "The lobby is empty."s;
                
                sort(g_lobby.begin(), g_lobby.end());
                
                for(const Player& player : g_lobby)
                    cout << "[ " << player.rating() << " ] " << player.name() << newline;

                return Menu::Option::Result();
            }
        },
        {
            "Add Players", []()
            {
                int player_count = input<int>("Player Count: ");

                if(g_lobby.size() + player_count > 10)
                    return "Error: The lobby can only hold up to 10 players."s;
                
                for(int i : Range(0, player_count))
                    register_player_from_user();

                return Menu::Option::Result();
            }
        },
        {
            "Edit Player", []()
            {
                if(g_lobby.empty())
                    return "The lobby is empty."s;
                
                //

                return Menu::Option::Result();
            }
        },
        {
            "Remove Player", []()
            {
                //

                return Menu::Option::Result();
            }
        }
    });

    menu.launch();
}

void register_player_from_user()
{
    string name = input<string>("Player Name: ");
    int wins = input<int>("Wins: ");
    int losses = input<int>("Losses: ");

    cout << newline;

    if(g_lobby.contains(name))
        overwrite_existing_player(name, wins, losses);
    else
        g_lobby.add_player(name, wins, losses);
}

void overwrite_existing_player(const string& name, int wins, int losses)
{
    cout << "Player \"" << name << "\" already exists." << newline;

    if(boolean_prompt("Would you like to overwrite their data?"))
        g_lobby.add_player(name, wins, losses);
}

void launch_edit_player_menu(const string& name)
{
    Menu menu("Which player would you like to edit?");
    
    for(const Player& player : g_lobby)
        menu.add_option
        (
            player.name(), []()
            {
                //Stuff
                
                return Menu::Option::Result();
            }
        );
}