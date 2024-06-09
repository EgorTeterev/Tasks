#include "Task05_ShootActorComponent.h"
//====================================================================================================================================================================
UTask05_ShootActorComponent::UTask05_ShootActorComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
}
//====================================================================================================================================================================
void UTask05_ShootActorComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTask05_ShootActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
//====================================================================================================================================================================
void UTask05_ShootActorComponent::PredictProjectileMovement()
{
	//get owner
	if (!GetOwner()) return;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	//get info to start projectile prediction from owner location
	ControlRotation = Character->GetControlRotation();
	ProjectileSpawnLocation = Character->GetActorLocation() + ControlRotation.Vector() * 100.0f;
	ProjectileLaunchVelocity = ControlRotation.Vector() * 1000.0f;
	//prediction params
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
	//if predict result hits smth, we place hit platform(if its not spawned) and update its position,and draw projectile path by debug speheres;
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
				//TODO: bug,if character uses StartFocuse, focusing the projectile - weird problem about collision
				Platform = GetWorld()->SpawnActor<ATask05_HitPlace>(PlatformClass, PlatformSpawnLocation, FRotator::ZeroRotator, SpawnParams);
				Platform->SetActorEnableCollision(false);
				
				bIsPlatformSpawned = true;
			}
			if(Platform){
				Platform->SetActorLocation(PredictResult.HitResult.Location);
			}
	}
}
//====================================================================================================================================================================
void UTask05_ShootActorComponent::StartFocuse()
{
	PredictProjectileMovement();
}

void UTask05_ShootActorComponent::EndFocuse()
{
	MakeShot();
	if (Platform) {
		Platform->SetActorEnableCollision(true);
	}
	
	bIsFocusing = false;
	bIsPlatformSpawned = false;
}

void UTask05_ShootActorComponent::MakeShot()
{
	FActorSpawnParameters SpawnParams;
	Projectile = GetWorld()->SpawnActor<ATask05_Projectile>(ProjectileClass, ProjectileSpawnLocation, ControlRotation, SpawnParams);
	Projectile->ProjectileMovementComponent->InitialSpeed = 1000.0f;//maybe should take + character current velocity?
}
//====================================================================================================================================================================
