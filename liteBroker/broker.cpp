#define BROKER_EXPORT

#include "include/broker.h"
#include "schema.sql.hpp"
#include "create_task.sql.hpp"
#include <iostream>
#include "uuid_v4.h"

static long long get_timestamp_milliseconds();

BrokerResult broker_initialize(Broker** new_broker)
{
	std::cout << "broker_initialize()" << std::endl;
	std::cout << SQLite::getLibVersion() << std::endl;

	*new_broker = nullptr;
	try
	{
		auto *db = new SQLite::Database("broker.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
		*new_broker = new Broker(db);

		auto schema_resource = LOAD_RESOURCE(schema_sql);
		SQLite::Statement create_query(*db, schema_resource.toString());

		create_query.exec();
	}
	catch (SQLite::Exception e)
	{
		std::cout << e.getErrorCode() << std::endl;
		std::cout << e.getErrorStr() << std::endl;
		return BrokerResult::FAILED;		
	}

	std::cout << "/broker_initialize()" << std::endl;

	return BrokerResult::OK;
}

BrokerResult broker_send(const Broker* broker, const char* queue, const char* payload)
{
	auto db = broker->get_db();

	UUIDv4::UUIDGenerator<std::mt19937_64> uuid_generator;
	const auto uuid = uuid_generator.getUUID();

	SQLite::Transaction transaction(*db);
	const auto create_task_resource = LOAD_RESOURCE(create_task_sql);
	SQLite::Statement stmt(*db, create_task_resource.data());

	stmt.bind("$Id", uuid.str());
	stmt.bind("$Payload", payload);
	stmt.bind("$Created", get_timestamp_milliseconds());
	stmt.bind("$Queue", queue);

	stmt.exec();

	transaction.commit();
	return BrokerResult::OK;
}

long long get_timestamp_milliseconds() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

BrokerResult broker_destroy(const Broker* broker)
{
	std::cout << "broker_destroy()" << std::endl;
	delete broker;
	std::cout << "/broker_destroy()" << std::endl;
	return  BrokerResult::OK;
}
