#include "TestCharacter.h"

#include "AbilitySystemComponent.h"
#include "TestAttributeSet.h"


ATestCharacter::ATestCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	TestAttributes = CreateDefaultSubobject<UTestAttributeSet>(TEXT("Attributes"));
}

void ATestCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if(AbilitySystemComp && HasAuthority())
	{
		AbilitySystemComp->InitAbilityActorInfo(this, this);
		for(const auto& [AbilityClass, Level, InputIds]: AbilityInfos)
		{
			for(const auto& InputId : InputIds)
			{
				// 创建枚举对应的输入ID到技能的映射 ->(技能映射)
				AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityClass, Level, static_cast<int32>(InputId), this));
			}
		}
	}
}

void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 添加Action映射 ->(按键映射)
	//UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(FName("Jump"), EKeys::SpaceBar));

	if(AbilitySystemComp)
	{
		AbilitySystemComp->InitAbilityActorInfo(this, this);
		// 绑定输入到枚举(EAbilityInputId)的映射 ->(枚举映射)
		AbilitySystemComp->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbilityInputBinds(
			FString() ,FString(), FTopLevelAssetPath(TEXT("/Script/XGame"), TEXT("EAbilityInputId"))));
	}

	if(PlayerInputComponent)
	{
		PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ATestCharacter::TestBindAction);
	}
}

UAbilitySystemComponent* ATestCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void ATestCharacter::TestBindAction()
{
	++BindCount;
	TestArray.SetNum(6);
	if(BindCount == 1)
	{
		TestArray[3] = 7;
	}
	UE_LOG(LogTemp, Log, TEXT("[ATestCharacter] Test : Bind action %d success; Array num = %d, %d"), BindCount, TestArray.Num(), TestArray[3]);
}
