#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

USTRUCT(BlueprintType)
struct FTestConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test", DisplayName = "开始")
	float Start = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test", DisplayName = "位置")
	FVector Location = FVector::ZeroVector;
};

UENUM(BlueprintType)
enum class EMode: uint8
{
	Mode2D,
	Mode3D
};

UCLASS()
class XGAME_API ATestActor : public AActor
{
	GENERATED_BODY()

public:
	/**
	 * @brief 构造函数
	 */
	ATestActor();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category = "Test")
	void TestMulticast();

	UFUNCTION(BlueprintCallable)
	virtual void TestBlueprintCallable();

	UPROPERTY(EditAnywhere, Category = "TestEditCondition", meta=(InlineEditConditionToggle))
	bool TestBool;
	UPROPERTY(EditAnywhere, Category = "TestEditCondition", meta=(EditCondition = "TestBool"))
	int32 TestInt;
	UPROPERTY(EditAnywhere, Category = "TestEditCondition", meta=(EditCondition = "TestBool"))
	float TestFloat;
	UPROPERTY(EditAnywhere, Category = "TestEditCondition", meta=(EditCondition = "TestBool", HideEditConditionToggle))
	FVector TestVector;
	UPROPERTY(EditAnywhere, Category = "TestEditCondition2", meta=(InlineCategoryProperty))
	EMode Mode;
	UPROPERTY(EditAnywhere, Category = "TestEditCondition2", meta=(EditCondition = "Mode == EMode::Mode2D", EditConditionHides))
	FVector2D TestVector2D;
	UPROPERTY(EditAnywhere, Category = "TestEditCondition2", meta=(EditCondition = "Mode == EMode::Mode3D", EditConditionHides))
	FVector TestVector3D;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess, DisplayName = "配置"))
	UObject* TestObject = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess, DisplayName = "配置类"))
	TSubclassOf<UObject> TestClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess, DisplayName = "测试"))
	AActor* TestActor = nullptr;
	UPROPERTY(EditAnywhere, Category = "Config", meta = (TitleProperty = "{Start} and {Location}"))
	TArray<FTestConfig> ConfigMappings;
};
