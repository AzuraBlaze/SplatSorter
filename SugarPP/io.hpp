/*****************************************************************//**
 * \file   IO.hpp
 * \brief  Convenient functions for using std::cin/cout
 *
 * \author Peter
 * \date   September 2020
 *********************************************************************/

// #pragma once

#ifndef SUGARPP_IO_HPP
#define SUGARPP_IO_HPP

#ifndef SugarPPNamespace
#define SugarPPNamespace
#endif /* SugarPPNamespace */

#include <iostream>
#include <string>
#include <tuple>
#include <fstream>
#include <mutex>
#include <vector>
#include <typeinfo>     //for typeid().name

#if __cplusplus >= 201703L
#include <string_view>
#include <filesystem>
#endif

#ifdef SugarPPNamespace
namespace SugarPP
{
#endif
    /**
     * @brief Restore the error state of the stream and "eat" the rest invalid input left in the stream
     * @param is The stream object to restore
     */
    inline void restore(std::istream& is)
    {
        is.clear();
        while (is.get() != '\n')
            ;
    }

    /**
     * @brief Get the correct type of value from `stdin`
     * @tparam T The expected return type
     * @param prompt A short prompt message printed on `stdout`, which will appear before user input
     * @param retry The flag for whether to retry the whole process when an input exception occurs, whether it's the type mismatch or invalid input
     * @return If retry flag is set to false and an exception does occurs, the function clears any invalid states, and return a default-constructed object of the expected type. Otherwise return the correct input.
     */
    template <typename T>
    [[nodiscard]] T input(const char* prompt = nullptr, bool retry = true)
    {
        using TargetType = std::remove_cv_t<T>;
        TargetType i{};
        if (!retry)
        {
            if (prompt)
                std::cout << prompt;
            if (!std::cin)
                restore(std::cin);
            std::cin >> i;
        }
        else
        {
            do
            {
                if (!std::cin)
                    restore(std::cin);
                if (prompt)
                    std::cout << prompt;
                if constexpr (std::is_integral_v<T>)
                {
                    //handles negative number and convert to its absolute value when expected an unsigned
                    if (std::cin.peek() == '-')
                    {
                        std::make_signed_t<TargetType> i_abs;
                        std::cin >> i_abs;
                        if (!std::cin)
                            continue;
                        restore(std::cin);
                        return abs(i_abs);
                    }
                }
                std::cin >> i;
            } while (!std::cin);
        }
        restore(std::cin);
        return i;
    }

    /**
     * @brief Specialization for `std::string`, which uses `std::getline` internally.
     * @note When the string is empty it will be counted as failure and will trigger a retry if it is enabled
     * @see input
     */
    template <>
    [[nodiscard]] inline std::string input(const char* prompt, bool retry)
    {
        std::string s;
        if (!retry)
        {
            if (prompt)
                std::cout << prompt;
            if (!std::cin)
                restore(std::cin);
            std::getline(std::cin, s);
        }
        else
        {
            do {
                if (!std::cin)
                    restore(std::cin);
                if (prompt)
                    std::cout << prompt;
                std::getline(std::cin, s);
            } while (s.empty());
        }
        return s;
    }

    /**
     * @brief Overload for `std::string` as prompt message
     * @see input
     */
    template<typename T>
    T input(std::string const& prompt, bool retry = true)
    {
        return input<T>(prompt.c_str(), retry);
    }

    /**
     * @brief Overload for `std::string` as prompt message and specialized for `std::string` as return type.
     * @see input
     */
    template<>
    [[nodiscard]] inline std::string input(std::string const& prompt, bool retry)
    {
        return input<std::string>(prompt.c_str(), retry);
    }


#if __cplusplus >= 201703L
    /**
     * @brief Overload for `std::string_view` as prompt message, if C++17 is available
     * @see input
     */
    template<typename T>
    T input(std::string_view prompt, bool retry = true)
    {
        return input<T>(prompt.data(), retry);
    }
    /**
     * @brief Overload for `std::string_view` as prompt message and specialized for `std::string` as return type, if C++17 is available
     */
    template<>
    inline std::string input(std::string_view prompt, bool retry)
    {
        return input<std::string>(prompt.data(), retry);
    }
#endif

    namespace detail
    {

        template<typename T>
        struct is_tuple_impl : std::false_type {};

        template<typename... Ts>
        struct is_tuple_impl<std::tuple<Ts...>> : std::true_type {};

        template<typename T>
        struct is_tuple : is_tuple_impl<std::decay_t<T>> {};

        template<typename T, typename = void>
        struct iterable_impl :std::false_type {};

        template<typename T>
        struct iterable_impl<T, decltype(std::begin(std::declval<T>()), void())> :std::true_type {};  //still works even when T is const

        template<typename T>
        struct iterable :iterable_impl
        <
            std::conditional_t
            <
                std::is_array_v<std::remove_reference_t<T>>,
                T,
                std::decay_t<T>
            >
        > {};


        template<typename T, std::ostream& os = std::cout, typename = void>
        struct printable :std::false_type {};

        template<typename T, std::ostream& os>
        struct printable<T, os, decltype(os << std::declval<T>(), void())> :std::true_type {};

        template<char delim = ' ', std::ostream& os = std::cout, typename T>
        void print_impl(T&& arg)
        {
            /*If it's bool, print as "True" / "False" */
            if constexpr (std::is_same_v<std::decay_t<T>, bool>)
                os << (arg ? "True" : "False");
            /*Not bool, but printable, can be const char[], */
            else if constexpr (printable<T>::value && (std::is_same_v<std::decay_t<T>, char*> || std::is_same_v<std::decay_t<T>, const char*> || !std::is_array_v<std::remove_reference_t<T>>))
                os << arg;
            else if constexpr (is_tuple<T>::value)
            {
                os << '(';
                std::apply([](auto&&... args)
                    {
                        ((os << args << delim), ...);
                    }, arg);
                os << '\b' << ')';
            }
            else if constexpr (iterable<T>::value && printable<decltype(*std::begin(std::declval<T>()))>::value)
            {
                os << '[';
                bool printed = false;
                for (auto& element : arg)
                {
                    os << element << delim;
                    printed = true;
                }
                if (printed)
                    os << '\b' << ']';
                else
                    os << ']';
            }
            else if constexpr (iterable<typename std::remove_reference_t<T>::value_type>::value)
            {
                os << '[';
                for (auto& element : arg)
                    print_impl(element);
                os << ']';
            }
            else
                os << '<' << typeid(T).name() << '>';
        }
    }

    /**
     * @brief Print any number of arguments to `stdout`, separated by `delim`
     * @tparam delim The separator between each thing to print, default to a space
     */
    template <char delim = ' ', std::ostream& os = std::cout, typename... Args>
    void print(Args &&... args)
    {
        ((detail::print_impl<delim, os>(args), os << delim), ...);
        os << '\n';
    }

    /**
     * @brief Print any number of arguments to `stdout`, separated by a line, same as `print<'\n'>`
     * @see print
     */
    template <std::ostream& os = std::cout, typename... Args>
    void printLn(Args &&... args)
    {
        ((detail::print_impl<' ', os>(args), os << '\n'), ...);
    }

    /*Thread-safe IO*/

    /**
     * @brief The thread-safe IO class. Every functions inside the class are static, which acts like a namespace but holding a mutex to regulate all the calls to print.
     */
    template<std::ostream& os = std::cout>
    struct ThreadSafe
    {
        static inline std::mutex m;

        /**
         * @brief Thread-safe version of print, blocks until the printing is finished.
         * @see ::print
         */
        template<char delim = ' ', typename...Args>
        static void print(Args&& ...args)
        {
            std::lock_guard lock{ m };
#ifdef SugarPPNamespace
            SugarPP::print<delim, os>(std::forward<Args>(args)...);
            //This is unnecessary on MSVC/Clang-cl, but GCC/Clang will reject the code for simply using ::
#else
            ::print<delim, os>(std::forward<Args>(args)...);    
#endif
        }

        /**
         * @brief Non-blocking version of print, which returns immediately if another thread is printing.
         */
        template<char delim = ' ', typename...Args>
        static void tryPrint(Args&& ...args)
        {
            std::unique_lock const lock{ m, std::try_to_lock_t{} };
            if (lock)
#ifdef SugarPPNamespace
                SugarPP::print<delim, os>(std::forward<Args>(args)...);
#else
                ::print<delim, os>(std::forward<Args>(args)...);
#endif
                
        }

        /**
         * @brief Thread-safe version of printLn, blocks until the printing is finished.
         */
        template<typename... Args>
        static void printLn(Args&&... args)
        {
            std::lock_guard lock{ m };
#ifdef SugarPPNamespace
            SugarPP::printLn<os>(std::forward<Args>(args)...);
#else
            ::printLn<os>(std::forward<Args>(args)...);
#endif
            
        }

        /**
         * @brief Non-blocking version of printLn, which returns immediately if another thread is printing.
         */
        template<typename... Args>
        static void tryPrintLn(Args&&... args)
        {
            std::unique_lock const lock{ m, std::try_to_lock_t{} };
            if (lock)
#ifdef SugarPPNamespace
                SugarPP::printLn<os>(std::forward<Args>(args)...);
#else
                ::printLn<os>(std::forward<Args>(args)...);
#endif
                
        }
    };

    struct FileIOError:std::runtime_error
    {
        FileIOError(const char* const fileName):std::runtime_error(std::string{fileName}+" causes a file IO error"){}
    };

    template<typename Char = char>
    class FileIterator
    {
        std::ifstream fs;
    public:
        using value_type = std::basic_string<Char>;
        using difference_type = std::ptrdiff_t;
        using pointer = std::basic_string<Char>*;
        using reference = std::basic_string<Char>&;
        using iterator_category = std::forward_iterator_tag;

        FileIterator(Char const* fileName);
        FileIterator(std::basic_string<Char> const& fileName);

#if __cplusplus >= 201703L
        FileIterator(std::basic_string_view<Char> const fileName);
        FileIterator(std::filesystem::directory_entry const& file);
#endif
        value_type operator*() const
        {

        }
        FileIterator& operator++()
        {

        }

    };

    /**
     * @brief Read a whole file into a long string
     * @param fname The input file name
     * @tparam Char The type of char of the returned string, can be either char or wchar_t
     * @tparam EnableException To throw an IO exception or not during the operation
     * @return A std::basic_string<Char> which contains the original content of the file
     * @details Will construct a std::filesystem::path object to detect whether the file exist or not in C++17
     */
    template<bool EnableException = false, typename Char = char>
    auto file_to_string(const char* fname)
    {
#if __cplusplus >= 201703L
        if constexpr (EnableException)
        {
            if (std::filesystem::directory_entry{ fname }.exists())
            {
                std::basic_ifstream<Char> fs{ fname };
                if (fs.is_open())
                    return std::basic_string<Char>(std::istreambuf_iterator<Char>{fs}, std::istreambuf_iterator<Char>{});
            }
            else
                throw FileIOError{ fname };
        }
        else
        {
            std::basic_ifstream<Char> fs{ fname };
            return std::basic_string<Char>(std::istreambuf_iterator<Char>{fs}, std::istreambuf_iterator<Char>{});
        }
#else
        std::basic_ifstream<Char> fs{ fname };
        if constexpr (EnableException)
        {
            if (!fs.is_open())
                throw FileIOError{ fname };
        }
        return std::basic_string<Char>(std::istreambuf_iterator<Char>{fs}, std::istreambuf_iterator<Char>{});
#endif
    }

    /**
     * @brief Read a whole file into a std::vector<Char>
     * @param fname The input file name
     * @tparam Char The type of char of the returned vector, can be either char or wchar_t
     * @tparam EnableException To throw an IO exception or not during the operation
     * @return A std::vector<Char> which contains the original content of the file
     * @details Will construct a std::filesystem::path object to detect whether the file exist or not in C++17
     */
    template<bool EnableException=false, typename Char=char>
    auto file_to_vec(const char* fname)
    {
#if __cplusplus >= 201703L
        if constexpr (EnableException)
        {
            if (std::filesystem::directory_entry{ fname }.exists())
            {
                std::basic_ifstream<Char> fs{ fname };
                if (fs.is_open())
                    return std::vector<Char>(std::istreambuf_iterator<Char>{fs}, std::istreambuf_iterator<Char>{});
            }
            else
                throw FileIOError{ fname };
        }
        else
        {
            std::basic_ifstream<Char> fs{ fname };
            return std::vector<Char>(std::istreambuf_iterator<Char>{fs}, std::istreambuf_iterator<Char>{});
        }
#else
        std::basic_ifstream<Char> fs{ fname };
        if constexpr (EnableException)
        {
            if (!fs.is_open())
                throw FileIOError{ fname };
        }
        return std::vector<Char>(std::istreambuf_iterator<Char>{fs}, std::istreambuf_iterator<Char>{});
#endif
    }

#ifdef SugarPPNamespace
}
#endif

#endif /* SUGARPP_IO_HPP */