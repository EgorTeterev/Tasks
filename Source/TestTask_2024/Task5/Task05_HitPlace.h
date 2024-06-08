#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Task05_HitPlace.generated.h"

UCLASS()
class TESTTASK_2024_API ATask05_HitPlace : public AActor
{
	GENERATED_BODY()
public:	
	ATask05_HitPlace();








protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
};
