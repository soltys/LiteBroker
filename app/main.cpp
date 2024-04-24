
#include "main.h"
#include <litebroker.h>

int main()
{
	std::cout << "Broker Version: " << broker_version() << std::endl;
	Broker* broker = nullptr;
	broker_initialize(&broker);

	broker_send(broker, "MyCppQueue", "{}");

	MessageCollection* collection = nullptr;
	broker_receive(broker, &collection);

	auto tasks = collection->get_tasks();

	// ranges::for_each(tasks, [&broker](Task& t)
	// {
	// 	if (t.get_queue() == std::string("SetStatus1"))
	// 	{
	// 		broker_set_status(broker, t.get_id().data(), 1);
	// 	}
	// 	else if (t.get_queue() == std::string("SetStatus2"))
	// 	{
	// 		broker_set_status(broker, t.get_id().data(), 2);
	// 	}
	// 	else
	// 	{
	// 		broker_set_status(broker, t.get_id().data(), -1);
	// 	}
	// });

	broker_finalize(collection);

	broker_destroy(broker);
	return 0;
}
