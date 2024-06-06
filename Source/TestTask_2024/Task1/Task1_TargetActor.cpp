#include "Task1_TargetActor.h"
//====================================================================================================================================================================
ATask1_TargetActor::ATask1_TargetActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATask1_TargetActor::Itteract_Implementation()
{
	Execute_Itteract(this);
}
//====================================================================================================================================================================
void ATask1_TargetActor::BeginPlay()
{
	Super::BeginPlay();
	
}
//====================================================================================================================================================================
void ATask1_TargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

