#include "TestPawn.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

ATestPawn::ATestPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemCoomp"));
}

void ATestPawn::BeginPlay()
{
	Super::BeginPlay();
	if(AbilitySystemComp)
	{
		AbilitySystemComp->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(TEXT("State.Walk"))).AddWeakLambda(this, [](const FGameplayTag Tag, const int32 Count)
		{
			UE_LOG(LogTemp, Log, TEXT("[Test] ATestPawn::TagEvent Tag = %s, Count = %d"), *Tag.ToString(), Count);
		});
		FGameplayTagContainer Container;
		Container.AddTag(FGameplayTag::RequestGameplayTag(TEXT("State.Run")));
		Container.AddTag(FGameplayTag::RequestGameplayTag(TEXT("State.Jump")));
		AbilitySystemComp->AddGameplayEventTagContainerDelegate(Container, FGameplayEventTagMulticastDelegate::FDelegate::CreateWeakLambda(this, [](const FGameplayTag Tag, const FGameplayEventData* Data)
		{
			const FString DataTag = Data ? Data->EventTag.ToString() : TEXT("None");
			UE_LOG(LogTemp, Log, TEXT("[Test] ATestPawn::TagContainerDelegate Tag = %s, Data = %s"), *Tag.ToString(), *DataTag);
		}));
	}
}

UAbilitySystemComponent* ATestPawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void ATestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	FInputActionBinding AB("Test", IE_Pressed);
	AB.ActionDelegate = FInputActionHandlerSignature::CreateUObject(this, &ATestPawn::Test, true);
	PlayerInputComponent->AddActionBinding(AB);
	FInputActionBinding AB2("Test2", IE_Pressed);
	AB2.ActionDelegate = FInputActionHandlerSignature::CreateUObject(this, &ATestPawn::Test, false);
	PlayerInputComponent->AddActionBinding(AB2);
}

void ATestPawn::Test(const bool bShowLog)
{
	bShow = bShowLog;
	UE_LOG(LogTemp, Log, TEXT("[Test] ATestPawn::Test ShowLog = %s"), bShowLog ? TEXT("true"): TEXT("false"));
	if(AbilitySystemComp)
	{
		FGameplayTagContainer Container;
		AbilitySystemComp->GetOwnedGameplayTags(Container);
		if(Container.HasTag(FGameplayTag::RequestGameplayTag(TEXT("State.Jump"))))
		{
			UE_LOG(LogTemp, Log, TEXT("[Test] ATestPawn::Test Tag Jump"));
		}
		if(Container.HasTag(FGameplayTag::RequestGameplayTag(TEXT("State.Run"))))
		{
			UE_LOG(LogTemp, Log, TEXT("[Test] ATestPawn::Test Tag Run"));
		}
		const FGameplayTag WalkTag = FGameplayTag::RequestGameplayTag(TEXT("State.Walk"));
		const FGameplayTag SprintTag = FGameplayTag::RequestGameplayTag(TEXT("State.Sprint"));
		const FGameplayTag JumpTag = FGameplayTag::RequestGameplayTag(TEXT("State.Jump"));
		const FGameplayTag RunTag = FGameplayTag::RequestGameplayTag(TEXT("State.Run"));
		if(bShowLog)
		{
			AbilitySystemComp->UpdateTagMap(WalkTag, 1);
			AbilitySystemComp->UpdateTagMap(SprintTag, 1);
			AbilitySystemComp->UpdateTagMap(JumpTag, 1);
			AbilitySystemComp->UpdateTagMap(RunTag, 1);
		}
		else
		{
			FGameplayEventData EventData;
			EventData.Target = this;
			EventData.EventTag = JumpTag;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, WalkTag, EventData);
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, RunTag, EventData);
			AbilitySystemComp->UpdateTagMap(WalkTag, -1);
			AbilitySystemComp->UpdateTagMap(SprintTag, -1);
			AbilitySystemComp->UpdateTagMap(JumpTag, -1);
			AbilitySystemComp->UpdateTagMap(RunTag, -1);
		}
	}
}

