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

UCLASS()
class XGAME_API ATestActor : public AActor
{
	GENERATED_BODY()

public:
	/**
	 * @brief 构造函数
	 */
	ATestActor();

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
