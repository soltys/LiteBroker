#pragma once

#include <utility>
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>

#ifdef _WIN32

#ifdef BROKER_EXPORT
#define BROKER_API extern "C" __declspec(dllexport)
#define BROKER_CLASS_EXPORT __declspec(dllexport)
#else
#define BROKER_API extern "C"  __declspec(dllimport)
#define BROKER_CLASS_EXPORT
#endif

#else
//NOT WINDOWS
#define BROKER_API extern "C" 
#define BROKER_CLASS_EXPORT

#endif
class BROKER_CLASS_EXPORT Broker
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

typedef enum  BROKER_CLASS_EXPORT  {
	OK,
	FAILED,
} BrokerResult;

class Task
{
public:
	Task(std::string id, std::string payload, const int status, std::string created,
	     std::string queue);

	const std::string& get_id() const { return id; }
	const std::string& get_queue() const { return queue; }
	const std::string& get_payload() const { return payload; }
	const int& get_status() const { return status; }
	const std::string& get_created() const { return created; }
private:
	std::string id;
	std::string payload;
	int status;
	std::string created;
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

// Create Broker object
BROKER_API BrokerResult broker_initialize(Broker** broker);
// Cleanup Broker object
BROKER_API BrokerResult broker_destroy(const Broker* broker);

//"Send" something to broker AKA create new row of data into DB
BROKER_API BrokerResult broker_send(const Broker* broker, const char* queue, const char* payload);

//Create object representing multiple rows
BROKER_API BrokerResult broker_receive(const Broker* broker, MessageCollection** collection);
//Get how many rows there is
BROKER_API size_t broker_task_count(const MessageCollection* collection);
//Get object representing single row details of on row
BROKER_API Task* broker_task_at(const MessageCollection* collection, int index);

//Group of methods getting single column - foreshadowing performance problem 
BROKER_API const char* broker_task_get_id(const Task* task);
BROKER_API const char* broker_task_get_payload(const Task* task);
BROKER_API const char* broker_task_get_queue(const Task* task);
BROKER_API const char* broker_task_get_created(const Task* task);
BROKER_API int broker_task_get_status(const Task* task);

//Clean-up object containing multiple rows
BROKER_API BrokerResult broker_finalize(const MessageCollection* collection);

BROKER_API BrokerResult broker_set_status(const Broker* broker, const char* id, int status);
BROKER_API const char* broker_version();

