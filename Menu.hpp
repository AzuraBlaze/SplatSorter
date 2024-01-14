#ifndef SPLATSORTER_MENU_HPP
#define SPLATSORTER_MENU_HPP

#include <vector>
#include <functional>
#include <initializer_list>
#include <string>

#include "Common.hpp"

class Menu
{
    public:

    using Action = std::function<void()>;

    class Option
    {
        const std::string name_m;
        Action action_m;

        public:

        Option() = delete;

        Option(const std::string& name, Action action)
        : name_m(name), action_m(action) {}

        const std::string& name() const;
        Action action() const;

        void run();
        void operator()();
    };

    private:

    const std::string title_m;
    std::vector<Option> options_m;

    public:

    Menu(const std::string& title)
    : title_m(title) {}


    std::size_t option_count() const;

    Menu& add_option(const Option& option);
    Menu& add_option(const std::string& name, Action action);
    Menu& add_options(std::initializer_list<Option> options);

    Menu& display();
    Menu& launch();
    Menu& select(std::size_t option_number);
};

#endif /* SPLATSORTER_MENU_HPP */