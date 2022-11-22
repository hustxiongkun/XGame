#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

#define TO_FLAG(Enum) (1 << static_cast<uint8>(Enum))

UENUM(BlueprintType, meta = (Bitflags))
enum class ETestType : uint8
{
	Rep,
	Rpc,
	EditConditon,
	Component,
	Size,
	PackageId,
	Property,
	Pointer,
};

USTRUCT(BlueprintType)
struct FTestConfig
{
	GENERATED_BODY()

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "Test", DisplayName = "开始")
	float Start = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Test", DisplayName = "位置")
	FVector Location = FVector::ZeroVector;
#endif
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

	UFUNCTION(BlueprintCallable)
	void TestComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "/Script/XGame.ETestType"))
	int32 TestType;

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

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "Config", meta = (TitleProperty = "{Start} and {Location}"))
	TArray<FTestConfig> ConfigMappings;
#endif
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess, DisplayName = "蓝图类"))
	TSubclassOf<ATestActor> BlueprintClass = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess, DisplayName = "蓝图类指针"))
	TSoftClassPtr<ATestActor> BlueprintPtr = nullptr;

	// 测试智能指针
	UPROPERTY()
	AActor* Test1;
	TWeakObjectPtr<AActor> Test2;
	UPROPERTY()
	AActor* Test3;
	// ReSharper disable once CppUE4ProbableMemoryIssuesWithUObject
	AActor* Test4;
	TObjectPtr<AActor> Test5;
	UPROPERTY()
	TObjectPtr<AActor> Test6;
};
