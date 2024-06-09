#include "DynamicReplicatedActor.h"

ADynamicReplicatedActor::ADynamicReplicatedActor()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

void ADynamicReplicatedActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADynamicReplicatedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

