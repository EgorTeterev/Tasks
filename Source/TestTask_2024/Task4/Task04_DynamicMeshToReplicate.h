#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Task04_DynamicMeshToReplicate.generated.h"

UCLASS()
class TESTTASK_2024_API ATask04_DynamicMeshToReplicate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATask04_DynamicMeshToReplicate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
