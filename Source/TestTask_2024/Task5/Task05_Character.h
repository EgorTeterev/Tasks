#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Task05_ShootActorComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Task05_Character.generated.h"
//====================================================================================================================================================================

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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
	UTask05_ShootActorComponent* ShootComponent;


	//Enhanced input
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	UInputAction* ShootAction;//LMB

	//Other
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Controller")
	APlayerController* Test05_Character_Controller;

private:
	bool bIsFocusing;
	bool bIsPlatformSpawned;


protected:
	virtual void BeginPlay() override;
	void Look(const FInputActionValue& Value);

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
