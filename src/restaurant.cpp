#include "restaurant.h"
//Конструктор класса по умолчанию, который устанавливает доступные блюда для готовки;
Restaurant::Restaurant()
{
	dishes.push_back("Pizza");
	dishes.push_back("Soup");
	dishes.push_back("Steak");
	dishes.push_back("Salad");
	dishes.push_back("Sushi");
}
// Метод waiter() имитирует работу официанта;
void Restaurant::waiter(const int& ordered)
{
	std::cout << "The waiter handed over the order. " << std::endl;
	orders.push_back(ordered); // Добавляет индекс блюда для готовки;
	std::thread kith([&]() {kitchen(); }); // Поток вызывающий метод kitchen;
	kith.detach();
}
// Метод order() имитирует работу онлайн заказа;
void Restaurant::order()
{
	while (count < 10)
	{
		std::this_thread::sleep_for(std::chrono::seconds(rand() % 6 + 5)); // Останавливает поток на время в заданном диапазоне(5-10), для имитации заказа пользователем;
		int ordered = rand() % 5; // Имитирование выбора блюда пользователем;
		std::cout << "An order was made. " << dishes[ordered] << std::endl;
		waiter(ordered); // Вызов метода waiter() и передача данных для добавления заказанного блюда в список;
	}
}
// метод courier() имитирует работу курьера;
void Restaurant::courier()
{
	while (count < 10)
	{
		std::this_thread::sleep_for(std::chrono::seconds(30)); // Останавливает поток на 30с для имитации работы курьера;
		std::cout << "The courier took the ready meals: " << std::endl;

		for (int i = 0; i < readyMeals.size(); ++i) // Цикл выводящий блюда, который забрал курьер из кухни;
			std::cout << readyMeals[i] << "\t";
		std::cout << std::endl;

		++count;
		readyMeals.clear();
	}
}
// Метод kitchen() имитирует готовку;
void Restaurant::kitchen()
{
	std::mutex mtx;

	mtx.lock(); // Блокировка потока, если кухня ещё не закончила с прошлым заказом;
	std::cout << "Preparing a dish: " << dishes[orders[0]] << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(rand() % 11 + 5)); // Останавливает поток на время в заданном диапазоне(5-10), для имитации работы повора;

	std::cout << dishes[orders[0]] << " is ready. " << std::endl;
	readyMeals.push_back(dishes[orders[0]]);
	orders.erase(orders.begin());
	mtx.unlock(); // Разблокирование потока, для начала работы над следующим заказом;
}
