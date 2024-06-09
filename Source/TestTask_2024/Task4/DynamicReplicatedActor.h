#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicReplicatedActor.generated.h"

UCLASS()
class TESTTASK_2024_API ADynamicReplicatedActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADynamicReplicatedActor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
