#define BROKER_EXPORT

#include "include/broker.h"

#include "schema.sql.hpp"
#include "create_task.sql.hpp"
#include "receive_tasks.sql.hpp"
#include "task_set_status.sql.hpp"

#include <iostream>
#include "uuid_v4.h"

static long long get_timestamp_milliseconds();

Task::Task(std::string id, std::string payload, const int status, const long long created, std::string queue) : id(std::move(id)),
payload(std::move(payload)),
status(status),
created(created),
queue(std::move(queue))
{
}

BrokerResult broker_initialize(Broker** new_broker)
{
	*new_broker = nullptr;
	try
	{
		auto* db = new SQLite::Database("broker.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
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

	return BrokerResult::OK;
}

BrokerResult broker_send(const Broker* broker, const char* queue, const char* payload)
{
	auto db = broker->get_db();

	UUIDv4::UUIDGenerator<std::mt19937_64> uuid_generator;
	const auto uuid = uuid_generator.getUUID();

	const auto create_task_resource = LOAD_RESOURCE(create_task_sql);
	SQLite::Statement stmt(*db, create_task_resource.data());

	stmt.bind("$Id", uuid.str());
	stmt.bind("$Payload", payload);
	stmt.bind("$Created", get_timestamp_milliseconds());
	stmt.bind("$Queue", queue);

	stmt.exec();

	return BrokerResult::OK;
}

long long get_timestamp_milliseconds() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

BrokerResult broker_receive(const Broker* broker, MessageCollection** collection)
{
	auto db = broker->get_db();

	const auto receive_tasks_resource = LOAD_RESOURCE(receive_tasks_sql);
	try
	{
		SQLite::Statement stmt(*db, receive_tasks_resource.data());
		std::vector<Task> tasks;
		while (stmt.executeStep())
		{
			Task task(
				stmt.getColumn("Id"),
				stmt.getColumn("Payload"),
				stmt.getColumn("Status"),
				stmt.getColumn("Created"),
				stmt.getColumn("Queue"));
			tasks.push_back(task);
		}
		*collection = new MessageCollection(std::move(tasks));
	}
	catch (SQLite::Exception e)
	{
		std::cout << "exception: " << e.what() << std::endl;
		return BrokerResult::FAILED;
	}

	return BrokerResult::OK;
}


BrokerResult broker_finalize(const MessageCollection* collection)
{
	delete collection;

	return BrokerResult::OK;
}


BrokerResult broker_set_status(const Broker* broker, const char* id, int status)
{
	auto db = broker->get_db();

	const auto task_set_status_resource = LOAD_RESOURCE(task_set_status_sql);
	try
	{
		SQLite::Statement stmt(*db, task_set_status_resource.data());
		stmt.bind("$Id", id);
		stmt.bind("$Status", status);
		stmt.exec();
	}
	catch (SQLite::Exception e)
	{
		std::cout << "exception: " << e.what() << std::endl;
		return BrokerResult::FAILED;
	}

	return BrokerResult::OK;
}


BrokerResult broker_destroy(const Broker* broker)
{
	delete broker;
	return  BrokerResult::OK;
}

size_t broker_task_count(const MessageCollection* collection)
{
	return collection->get_tasks().size();
}

Task* broker_task_at(const MessageCollection* collection, const int index)
{
	return &collection->get_tasks().at(index);
}

const char* broker_task_get_id(const Task* task)
{
	return task->get_id().c_str();
}

const char* broker_task_get_payload(const Task* task)
{
	return task->get_payload().c_str();
}

const char* broker_task_get_queue(const Task* task)
{
	return task->get_queue().c_str();
}


const char* broker_version()
{
	return "0.0.7.0";
}