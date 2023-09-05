#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <thread>
#include <mutex>



class Restaurant
{
private:
	std::vector<int> orders;
	std::vector<std::string> dishes;
	std::vector<std::string> readyMeals;
	int count = 0;
	void waiter(const int& ordered);
	void kitchen();
public:
	void order();
	void courier();
	Restaurant();
};