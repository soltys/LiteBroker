#pragma once

#include <utility>

#include "SQLiteCpp/SQLiteCpp.h"

#ifdef _WIN32

#ifdef BROKER_EXPORT
#define BROKER_API extern "C" __declspec(dllexport)
#else
#define BROKER_API extern "C"  __declspec(dllimport)
#endif

#else
//NOT WINDOWS
#define BROKER_API 

#endif
class Broker
{
	SQLite::Database* db;

public:
	Broker(Broker& copy) = delete;
	Broker(Broker&& move) = delete;
	Broker& operator=(Broker other) = delete;
	Broker& operator=(Broker&& other) = delete;

	Broker(SQLite::Database* db) : db(db)
	{
	}

	SQLite::Database* get_db() const
	{
		return db;
	}

	~Broker()
	{
		delete db;
	}
};

typedef enum {
	OK,
	FAILED,
} BrokerResult;

class Task
{
public:
	Task(std::string id, std::string payload, const int status, const long long created,
	     std::string queue);

	std::string& get_id() { return id; }
	std::string& get_queue() { return queue; }
private:
	std::string id;
	std::string payload;
	int status;
	long long created;
	std::string queue;
};

class MessageCollection
{
public:
	MessageCollection(MessageCollection& copy) = delete;
	MessageCollection(MessageCollection&& move) = delete;
	MessageCollection& operator=(MessageCollection other) = delete;
	MessageCollection& operator=(MessageCollection&& other) = delete;
	
	MessageCollection(std::vector<Task> tasks) : tasks(new std::vector(std::move(tasks))) {}

	std::vector<Task>& get_tasks() const { return *tasks; }

	~MessageCollection()
	{
		tasks.reset();
	}
private:
	std::unique_ptr<std::vector<Task>> tasks;
	
};

BROKER_API BrokerResult broker_initialize(Broker** broker);
BROKER_API BrokerResult broker_send(const Broker* broker, const char* queue, const char* payload);
BROKER_API BrokerResult broker_receive(const Broker* broker, MessageCollection** collection);
BROKER_API BrokerResult broker_finalize(const MessageCollection* collection);
BROKER_API BrokerResult broker_set_status(const Broker* broker, const char* id, int status);
BROKER_API BrokerResult broker_destroy(const Broker* broker);
BROKER_API const char* broker_version();

