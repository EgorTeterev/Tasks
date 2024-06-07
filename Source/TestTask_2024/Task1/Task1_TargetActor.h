#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItteractInterface.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Task1_TargetActor.generated.h"

//====================================================================================================================================================================
UCLASS()
class TESTTASK_2024_API ATask1_TargetActor : public AActor,public IItteractInterface
{
	GENERATED_BODY()
	
public:	
	ATask1_TargetActor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	float DistanceToCharacter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	bool bIsInViewPort;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	FVector2D VectorToShowWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	FVector2D ScreenPosition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")

	FVector2D ClampedPosition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	int32 ViewPortSizeX;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	int32 ViewPortSizeY;
//target location is static,so we can check it one,on BeginPlay()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	FVector TargetLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character")
	ACharacter* Character;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character location")
	FVector CharacterLocation;
	void Itteract();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void UpdateDistance();
	void IsInViewPort();
};
