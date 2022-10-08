#pragma once

#include "CoreMinimal.h"
#include "TestActor.h"
#include "DrivedActor.generated.h"

UCLASS()
class XGAME_API ADrivedActor : public ATestActor
{
	GENERATED_BODY()

public:
	ADrivedActor();

	// 子类不能使用UFUNCTION()进行标注 
	virtual void TestBlueprintCallable() override;
};
