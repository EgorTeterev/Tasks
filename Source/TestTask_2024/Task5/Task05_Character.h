#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Task05_Character.generated.h"

UCLASS()
class TESTTASK_2024_API ATask05_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ATask05_Character();
	//Components
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
	UCameraComponent* Camera;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
	USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	float MaxDistanceToShoot = 6000.0f;



	//Enhanced input
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	UInputAction* ShootAction;//LMB

	//Other
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Controller")
	APlayerController* Test05_Character_Controller;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
	TSubclassOf<AActor> Projectile;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Platform")
	TSubclassOf<AActor> Platform;

	UPROPERTY(EditAnywhere, Category = "Platform")
	FVector LocationToSpawnPlatform;
	
	AActor* SpawnedPlatform = nullptr;
private:
	bool bIsFocusing;
	bool bIsPlatformSpawned;
	FVector SpawnLocation;
	FVector LaunchVelocity;
protected:
	virtual void BeginPlay() override;
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void StartFocuse();
	void EndFocuse();
	UFUNCTION(BlueprintCallable)
	void MakeShot(FVector ShootVector, FVector ShootVelocity);
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
