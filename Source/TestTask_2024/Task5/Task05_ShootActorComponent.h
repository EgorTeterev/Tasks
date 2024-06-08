#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Task05_HitPlace.h"
#include "Task05_Projectile.h"
#include "Task05_ShootActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTTASK_2024_API UTask05_ShootActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTask05_ShootActorComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	float ProjectileSpeed = 1000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Platform class to spawn")
	TSubclassOf<ATask05_HitPlace> PlatformClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile class to spawn")
	TSubclassOf<ATask05_Projectile> ProjectileClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
	ATask05_Projectile* Projectile;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Platform")
	ATask05_HitPlace* Platform;


	FVector ProjectileSpawnLocation;
	FVector ProjectileLaunchVelocity;
	FRotator ControlRotation;
	void StartFocuse();
	void EndFocuse();
private:
	bool bIsFocusing = false;
	bool bIsPlatformSpawned = false;
	void PredictProjectileMovement();
	void MakeShot();
protected:
	virtual void BeginPlay() override;	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

};
