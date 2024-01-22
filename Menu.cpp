#include "Menu.hpp"
#include "IO.hpp"

using namespace std;
using namespace SugarPP;


const string& Menu::Option::name() const
{
    return name_m;
}

const Menu::Option::Action& Menu::Option::action() const
{
    return action_m;
}


Menu::Option::Result Menu::Option::run() const
{
    return action_m();
}

Menu::Option::Result Menu::Option::operator()() const
{
    return run();
}


size_t Menu::size() const
{
    return options_m.size();
}

size_t Menu::length() const
{
    return size();
}

const string& Menu::title() const
{
    return title_m;
}

void Menu::title(const std::string& new_title)
{
    title_m = new_title;
}

const string& Menu::back_button_title() const
{
    return back_button_title_m;
}

void Menu::back_button_title(const string& new_back_button_title)
{
    back_button_title_m = new_back_button_title;
}


void Menu::add_option(const string& name, Option::Action action)
{
    options_m.emplace_back(name, action);
}

void Menu::add_option(const Option& option)
{
    options_m.push_back(option);
}

void Menu::add_options(initializer_list<Option> options)
{
    for(const Option& option : options)
        options_m.push_back(option);
}


Menu::Option::Result Menu::select(size_t option_number)
{
    if(option_number == 0)
    {
        is_running_m = false;
        return Menu::Option::Result();
    }

    size_t index = option_number - 1;

    if(index < size())
    {
        cout << page_break;

        return options_m[index].run();
    }

    return "Error: Invalid option number.";
}

void Menu::launch(const string& prompt)
{
    is_running_m = true;

    while(is_running_m)
        display(prompt);
}

void Menu::launch()
{
    launch("Option Number: ");
}

void Menu::display(const string& prompt)
{
    cout << page_break;
    cout << title_m << newline;
    cout << newline;

    cout << indent << "0. " << back_button_title_m << newline;

    for(const auto& [i, option] : Enumerate(options_m, 1))
        cout << indent << i << ". " << option.name() << newline;
    
    cout << newline;

    size_t option_number = input<size_t>(prompt);
    Option::Result result = select(option_number);
    
    if(result.empty() == false)
    {
        cout << page_break;
        cout << result;
    }

    cout << newline;
}