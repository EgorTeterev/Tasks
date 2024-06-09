#include "ReplicatedObject.h"
#include "Net/UnrealNetwork.h"

UReplicatedObject::UReplicatedObject()
{
	IntToReplicate = FMath::RandRange(0, 100);
}

void UReplicatedObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UReplicatedObject, IntToReplicate);
}
