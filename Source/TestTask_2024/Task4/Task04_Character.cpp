#include "Task04_Character.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "Engine/ActorChannel.h"
ATask04_Character::ATask04_Character()
{
	PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
	NetCullDistanceSquared = 99999;
	NetUpdateFrequency = 1.f;
}


void ATask04_Character::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority()) {
		Object = NewObject<UReplicatedObject>(this);
	}
}




bool ATask04_Character::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (Object) WroteSomething |= Channel->ReplicateSubobject(Object, *Bunch, *RepFlags);

	return WroteSomething;

}

void ATask04_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATask04_Character, Object);
}






























void ATask04_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("Random Int: %d"), Object->IntToReplicate);
}









void ATask04_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}