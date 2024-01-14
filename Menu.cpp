#include "Menu.hpp"

using namespace std;
using namespace SugarPP;


const string& Menu::Option::name() const
{
    return name_m;
}

Menu::Action Menu::Option::action() const
{
    return action_m;
}

void Menu::Option::run()
{
    action_m();
}

void Menu::Option::operator()()
{
    run();
}


size_t Menu::option_count() const
{
    return options_m.size();
}

    
Menu& Menu::add_option(const Option& option)
{
    options_m.push_back(option);
    return *this;
}

Menu& Menu::add_option(const string& name, Action action)
{
    return add_option(Option(name, action));
}

Menu& Menu::add_options(initializer_list<Option> options)
{
    for(const Option& option : options)
        options_m.push_back(option);
    
    return *this;
}


Menu& Menu::display()
{
    cout << title_m << endl << endl;

    for(auto [i, option] : Enumerate(options_m))
        cout << i << ". " << option.name() << endl;
    
    return *this;
}

Menu& Menu::launch()
{
    display();
    cout << endl;

    size_t option_number = input<size_t>("Option number: ");

    if(option_number < options_m.size())
        select(option_number);
    else
        cout << endl << "Error: Invalid option number." << endl;

    return *this;
}

Menu& Menu::select(size_t option_number)
{
    Action action = options_m[option_number].action();
    action();

    return *this;
}
