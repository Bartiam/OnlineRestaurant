#include "restaurant.h"

int main()
{
	std::srand(std::time(NULL));
	Restaurant restaurant;

	std::thread order([&restaurant]() {restaurant.order(); });
	std::thread courier([&restaurant]() {restaurant.courier(); });

	order.detach();
	courier.join();

	return 0;
}