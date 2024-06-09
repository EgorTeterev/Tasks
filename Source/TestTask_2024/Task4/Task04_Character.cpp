#include "Task04_Character.h"
#include "Net/UnrealNetwork.h"

ATask04_Character::ATask04_Character()
{
	PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
}


void ATask04_Character::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority()) {
		Object = NewObject<UReplicatedObject>(this);
		if (Object)
		{
			Object->IntToReplicate = 50;
		}
	}
}


void ATask04_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ATask04_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ATask04_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATask04_Character, Object);
}