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




protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
