#include <iostream>
#include "Player.hpp"
#include "SugarPP/all.hpp"

#include <vector>

using namespace std;
using namespace SugarPP;

int main()
{
    cout << endl;

    int num = input<int>("Enter a number: ");
    print("You entered:", num, '\n');

    vector<int> nums;

    for(int n : Range(1, num + 1))
        nums.push_back(n);

    for(auto [i, value] : Enumerate(nums))
        cout << '[' << to_string(i) << "] => " << value << endl;

    cout << endl;
}