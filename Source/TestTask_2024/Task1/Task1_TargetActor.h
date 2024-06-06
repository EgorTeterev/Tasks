#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItteractInterface.h"
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
	virtual void Itteract_Implementation() override;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
};
