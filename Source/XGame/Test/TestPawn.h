#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TestPawn.generated.h"

UCLASS()
class XGAME_API ATestPawn : public APawn
{
	GENERATED_BODY()

public:
	ATestPawn();

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	void Test(const bool bShowLog);

	bool bShow = false;
};
