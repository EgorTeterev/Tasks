#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Task04_Character.generated.h"

UCLASS()
class TESTTASK_2024_API ATask04_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ATask04_Character();
//	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
