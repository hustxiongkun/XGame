#include "TestCharacter.h"

#include "AbilitySystemComponent.h"


ATestCharacter::ATestCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
}

void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(AbilitySystemComp)
	{
		for(const auto& [AbilityClass, Level, InputIds]: AbilityInfos)
		{
			for(const auto& InputId : InputIds)
			{
				// 创建枚举对应的输入ID到技能的映射
				AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityClass, Level, static_cast<int32>(InputId), this));
			}
		}
	}
}

void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(AbilitySystemComp)
	{
		// 绑定输入到枚举(EAbilityInputId)的映射
		AbilitySystemComp->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbilityInputBinds(
			FString() ,FString(), FString("EAbilityInputId")));
	}
}

UAbilitySystemComponent* ATestCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

