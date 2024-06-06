#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Task1_TargetActor.h"
#include "Components/StaticMeshComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "ItteractInterface.h"
#include "Task1_Character.generated.h"
//====================================================================================================================================================================
UCLASS()
class TESTTASK_2024_API ATask1_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ATask1_Character();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
	UCameraComponent* Camera;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
	USpringArmComponent* CameraBoom;
	

//Stats
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	float ItteractionDistance = 500.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	ATask1_TargetActor* FocuseActor = nullptr;

//Enhanced input
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	UInputAction* ItteractAction;//E

//Other
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Controller")
	APlayerController* Test1_Character_Controller;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Objectives")
	TArray<TSubclassOf<ATask1_TargetActor>> Objectives;
//====================================================================================================================================================================
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Itteract();
	void FocusingItteractable();
};
