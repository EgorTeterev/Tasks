#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ReplicatedObject.generated.h"


UCLASS()
class TESTTASK_2024_API UReplicatedObject : public UObject
{
	GENERATED_BODY()
public:
	UReplicatedObject();
	UPROPERTY(Replicated,BlueprintReadWrite, EditAnywhere, Category = "Stats")
	int IntToReplicate;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
