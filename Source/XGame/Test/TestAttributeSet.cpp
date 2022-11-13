#include "TestAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

bool UTestAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	UE_LOG(LogTemp, Log, TEXT("[UTestAttributeSet] PreGameplayEffectExecute: %s = %f"), *Data.EvaluatedData.Attribute.GetName(), Data.EvaluatedData.Attribute.GetNumericValue(this));
	return Super::PreGameplayEffectExecute(Data);
}

void UTestAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	UE_LOG(LogTemp, Log, TEXT("[UTestAttributeSet] PreAttributeBaseChange: %s = %f, NewValue = %f"), *Attribute.GetName(), Attribute.GetNumericValue(this), NewValue);
	Super::PreAttributeBaseChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		// BaseValue
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
}

void UTestAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	UE_LOG(LogTemp, Log, TEXT("[UTestAttributeSet] PreAttributeChange: %s = %f, NewValue = %f"), *Attribute.GetName(), Attribute.GetNumericValue(this), NewValue);
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		// CurrentValue
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
}

void UTestAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	UE_LOG(LogTemp, Log, TEXT("[UTestAttributeSet] PostAttributeChange: %s = %f, OldValue = %f, NewValue = %f"), *Attribute.GetName(), Attribute.GetNumericValue(this), OldValue, NewValue);
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	if (Attribute == GetMaxHealthAttribute())
	{
		// BaseValue, CurrentValue
		SetHealth(GetHealth() + NewValue - OldValue);
	}
}

void UTestAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const
{
	UE_LOG(LogTemp, Log, TEXT("[UTestAttributeSet] PostAttributeBaseChange: %s = %f, OldValue = %f, NewValue = %f"), *Attribute.GetName(), Attribute.GetNumericValue(this), OldValue, NewValue);
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
}

void UTestAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	UE_LOG(LogTemp, Log, TEXT("[UTestAttributeSet] PostGameplayEffectExecute: %s = %f"), *Data.EvaluatedData.Attribute.GetName(), Data.EvaluatedData.Attribute.GetNumericValue(this));
	Super::PostGameplayEffectExecute(Data);
}

void UTestAttributeSet::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UTestAttributeSet, Health);
	DOREPLIFETIME(UTestAttributeSet, MaxHealth);
}