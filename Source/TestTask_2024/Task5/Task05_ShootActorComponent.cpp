#include "Task05_ShootActorComponent.h"

UTask05_ShootActorComponent::UTask05_ShootActorComponent()
{

	PrimaryComponentTick.bCanEverTick = true;


}


void UTask05_ShootActorComponent::StartFocuse()
{
	PredictProjectileMovement();
}

void UTask05_ShootActorComponent::PredictProjectileMovement()
{
	if (!GetOwner()) return;
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	ControlRotation = Character->GetControlRotation();
	ProjectileSpawnLocation = Character->GetActorLocation() + ControlRotation.Vector() * 100.0f;
	ProjectileLaunchVelocity = ControlRotation.Vector() * 1000.0f;

	FPredictProjectilePathParams PredictParams;
	PredictParams.StartLocation = ProjectileSpawnLocation;
	PredictParams.LaunchVelocity = ProjectileLaunchVelocity;
	PredictParams.bTraceWithCollision = true;
	PredictParams.ProjectileRadius = 5.0f; 
	PredictParams.MaxSimTime = 3.0f; 
	PredictParams.SimFrequency = 30.0f; 
	PredictParams.OverrideGravityZ = -980.f; 

	FPredictProjectilePathResult PredictResult;
	bool bHit = UGameplayStatics::PredictProjectilePath(this, PredictParams, PredictResult);

	if (bHit)
	{
		int temp = 0;
		for (const FPredictProjectilePathPointData& PointData : PredictResult.PathData)
		{
			if (!(temp % 3)) {
				DrawDebugSphere(GetWorld(), PointData.Location, 15.0f, 12, FColor::Red, false, 0.04f);
			}
			temp++;
		}
			if (!bIsPlatformSpawned || !Platform) {
				FActorSpawnParameters SpawnParams;
				FVector PlatformSpawnLocation = PredictResult.HitResult.Location;
				Platform = GetWorld()->SpawnActor<ATask05_HitPlace>(PlatformClass, PlatformSpawnLocation, FRotator::ZeroRotator, SpawnParams);
				Platform->SetActorEnableCollision(false);
				bIsPlatformSpawned = true;
			}
			if(Platform){
				Platform->SetActorLocation(PredictResult.HitResult.Location);
			}
	}
}

void UTask05_ShootActorComponent::EndFocuse()
{
	MakeShot();
	Platform->SetActorEnableCollision(true);
	bIsFocusing = false;
	bIsPlatformSpawned = false;
}

void UTask05_ShootActorComponent::MakeShot()
{
	FActorSpawnParameters SpawnParams;
	Projectile = GetWorld()->SpawnActor<ATask05_Projectile>(ProjectileClass, ProjectileSpawnLocation, ControlRotation, SpawnParams);
	Projectile->ProjectileMovementComponent->InitialSpeed = 1000.0f;
}

// Called when the game starts
void UTask05_ShootActorComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTask05_ShootActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

