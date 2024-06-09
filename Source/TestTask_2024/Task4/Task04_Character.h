#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ReplicatedObject.h"

#include "Task04_Character.generated.h"

UCLASS()
class TESTTASK_2024_API ATask04_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ATask04_Character();


	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Object")
	UReplicatedObject* Object;


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
};
