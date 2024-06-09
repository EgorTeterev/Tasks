#include "Task04_Character.h"
#include "Net/UnrealNetwork.h"
// Sets default values
ATask04_Character::ATask04_Character()
{
	PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

}


// Called when the game starts or when spawned
void ATask04_Character::BeginPlay()
{
	Super::BeginPlay();

}


void ATask04_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}





void ATask04_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

