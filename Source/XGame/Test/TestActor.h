// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", DisplayName = "配置")
	UObject* TestObject = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", DisplayName = "配置类")
	TSubclassOf<UObject> TestClass = nullptr;
};
