#include "ReplicatedObject.h"
#include "Net/UnrealNetwork.h"

UReplicatedObject::UReplicatedObject()
{

}

void UReplicatedObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UReplicatedObject, IntToReplicate);
}
