#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Task1_TargetActor.generated.h"

//====================================================================================================================================================================
UCLASS()
class TESTTASK_2024_API ATask1_TargetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATask1_TargetActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
