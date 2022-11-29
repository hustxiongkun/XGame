#pragma once

#include "CoreMinimal.h"
#include "TestActor.h"
#include "DerivedActor.generated.h"

UCLASS()
class XGAME_API ADerivedActor : public ATestActor
{
	GENERATED_BODY()

public:
	ADerivedActor();

	// ReSharper disable once CommentTypo
	// 子类不能使用UFUNCTION()进行标注 
	virtual void TestBlueprintCallable() override;
};
