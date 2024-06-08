#include "Task05_Projectile.h"



ATask05_Projectile::ATask05_Projectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile movement"));

}



void ATask05_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATask05_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

