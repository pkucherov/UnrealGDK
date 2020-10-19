// Copyright (c) Improbable Worlds Ltd, All Rights Reserved

#pragma once

#include "SpatialView/ConnectionHandler/AbstractConnectionHandler.h"
#include "SpatialView/OpList/OpList.h"

namespace SpatialGDK
{
class SpatialOSConnectionHandler : public AbstractConnectionHandler
{
public:
	explicit SpatialOSConnectionHandler(Worker_Connection* Connection);

	virtual void Advance() override;
	virtual uint32 GetOpListCount() override;
	virtual OpList GetNextOpList() override;
	virtual void SendMessages(TUniquePtr<MessagesToSend> Messages) override;
	virtual const FString& GetWorkerId() const override;
	virtual const TArray<FString>& GetWorkerAttributes() const override;
	virtual Worker_EntityId GetWorkerSystemEntityId() const override;

private:
	struct ConnectionDeleter
	{
		void operator()(Worker_Connection* Connection) const noexcept;
	};

	TUniquePtr<Worker_Connection, ConnectionDeleter> Connection;
	TMap<int64, int64> InternalToUserRequestId;
	FString WorkerId;
	TArray<FString> WorkerAttributes;
	Worker_EntityId WorkerSystemEntityId;
};

} // namespace SpatialGDK
