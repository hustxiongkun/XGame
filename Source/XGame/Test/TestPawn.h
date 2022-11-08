#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Pawn.h"
#include "TestPawn.generated.h"

UCLASS()
class XGAME_API ATestPawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATestPawn();

	virtual void BeginPlay() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystemComp = nullptr;
	
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	void Test(const bool bShowLog);

	bool bShow = false;
};
