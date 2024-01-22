#ifndef SPLATSORTER_MENU_HPP
#define SPLATSORTER_MENU_HPP

#include <string>
#include <functional>
#include <vector>

#include "Common.hpp"

class Menu
{
public:

    class Option
    {
    public:
        using Result = std::string;
        using Action = std::function<Result()>;
    
    private:
        const std::string name_m;
        Action action_m;

    public:

        Option(const std::string& name, const Action& action)
        : name_m(name), action_m(action) {}

        const std::string& name() const;
        const Action& action() const;

        Result run() const;
        Result operator()() const;
    };

private:

    std::string title_m;
    std::string back_button_title_m;
    std::vector<Option> options_m;
    bool is_running_m = false;

public:

    Menu(const std::string& title, const std::string back_button_title = "Back")
    : title_m(title), back_button_title_m(back_button_title) {}

    std::size_t size() const;
    std::size_t length() const;

    const std::string& title() const;
    void title(const std::string& new_title);

    const std::string& back_button_title() const;
    void back_button_title(const std::string& new_back_button_title);

    void add_option(const std::string& name, Option::Action action);
    void add_option(const Option& option);
    void add_options(std::initializer_list<Option> options);

    Option::Result select(std::size_t option_number);
    void launch();
    void launch(const std::string& prompt);

private:

    void display(const std::string& prompt);
};

#endif /* SPLATSORTER_MENU_HPP */