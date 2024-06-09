#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "KismetMathLibrary.generated.h"
#include "ReplicatedObject.generated.h"


UCLASS(Blueprintable)
class TESTTASK_2024_API UReplicatedObject : public UObject
{
	GENERATED_BODY()
public:
	UReplicatedObject();
	UPROPERTY(Replicated,BlueprintReadWrite, EditAnywhere, Category = "Stats")
	int IntToReplicate;

	virtual bool IsSupportedForNetworking() const override { return true; };

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
