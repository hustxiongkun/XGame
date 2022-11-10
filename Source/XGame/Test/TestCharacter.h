#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "TestCharacter.generated.h"

UENUM(BlueprintType)
enum class EAbilityInputId : uint8
{
	None = 0 UMETA(Hidden),
	Jump,
	Sprint,
};

USTRUCT(BlueprintType)
struct FAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayName = "技能类"))
	TSubclassOf<UGameplayAbility> AbilityClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayName = "技能等级"))
	int32 Level = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayName = "对应ID"))
	TSet<EAbilityInputId> InputIds;
};

UCLASS()
class XGAME_API ATestCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATestCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComp = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayName = "技能信息", AllowPrivateAccess = "true"))
	TArray<FAbilityInfo> AbilityInfos;
};
