#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Task05_Projectile.generated.h"

UCLASS()
class TESTTASK_2024_API ATask05_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ATask05_Projectile();
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
