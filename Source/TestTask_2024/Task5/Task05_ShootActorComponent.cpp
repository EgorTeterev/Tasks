#include "Task05_ShootActorComponent.h"

UTask05_ShootActorComponent::UTask05_ShootActorComponent()
{

	PrimaryComponentTick.bCanEverTick = true;


}


void UTask05_ShootActorComponent::StartFocuse()
{
	PredictProjectileMovement();
}

void UTask05_ShootActorComponent::EndFocuse()
{
	bIsFocusing = false;
	bIsPlatformSpawned = false;
}

void UTask05_ShootActorComponent::PredictProjectileMovement()
{
	if (!GetOwner()) return;
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	FRotator ControlRotation = Character->GetControlRotation();
	ProjectileSpawnLocation = Character->GetActorLocation() + ControlRotation.Vector() * 100.0f;
	ProjectileLaunchVelocity = ControlRotation.Vector() * 1000.0f;

	FPredictProjectilePathParams PredictParams;
	PredictParams.StartLocation = ProjectileSpawnLocation;
	PredictParams.LaunchVelocity = ProjectileLaunchVelocity;
	PredictParams.bTraceWithCollision = true; // Включает трассировку с учётом столкновений
	PredictParams.ProjectileRadius = 5.0f; // Радиус снаряда
	PredictParams.MaxSimTime = 3.0f; // Максимальное время симуляции
	PredictParams.SimFrequency = 15.0f; // Частота симуляции
	PredictParams.OverrideGravityZ = -980.f; // Гравитация

	FPredictProjectilePathResult PredictResult;
	bool bHit = UGameplayStatics::PredictProjectilePath(this, PredictParams, PredictResult);

	if (bHit)
	{
		int temp = 0;
		for (const FPredictProjectilePathPointData& PointData : PredictResult.PathData)
		{
			if (!(temp % 3)) {
				DrawDebugSphere(GetWorld(), PointData.Location, 15.0f, 12, FColor::Red, false, 0.1f);
			}
			temp++;
		}
			if (!bIsPlatformSpawned) {
				//Спавним платформу,если её ещё нет
				FActorSpawnParameters SpawnParams;
				FVector PlatformSpawnLocation = PredictResult.HitResult.Location;
				Platform = GetWorld()->SpawnActor<ATask05_HitPlace>(PlatformClass, PlatformSpawnLocation, FRotator::ZeroRotator, SpawnParams);
				Platform->SetActorEnableCollision(false);
				bIsPlatformSpawned = true;
			}
			else {
				Platform->SetActorLocation(PredictResult.HitResult.Location);
			}
	}
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

