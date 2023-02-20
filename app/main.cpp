
#include "main.h"
#include "broker.h"
using namespace std;
int main()
{
	Broker* broker = nullptr;
	broker_initialize(&broker);

	broker_send(broker, "MyCppQueue", "{}");

	broker_destroy(broker);
	return 0;
}
