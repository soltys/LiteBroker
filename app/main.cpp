﻿
#include "main.h"
#include "broker.h"

using namespace std;
int main()
{
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
