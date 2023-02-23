CREATE TABLE IF NOT EXISTS "Task" (
	"Id" TEXT NOT NULL,
	"Payload" TEXT CHECK(json_valid(Payload) = 1),
	"Status" INTEGER NOT NULL DEFAULT 0 CHECK(Status < 5),
	"Created" TEXT,
	"Queue"	TEXT,
	PRIMARY KEY("Id")
) WITHOUT ROWID;
CREATE INDEX "Ix_Task_Name" ON "Task" (
	"Queue"
);
CREATE INDEX "Ix_Task_Status" ON "Task" (
	"Status"
);