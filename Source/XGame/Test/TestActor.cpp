// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	if (TestObject)
	{
		UE_LOG(LogTemp, Log, TEXT("[Test] TestObject is valid"));
		if (const FProperty* ObjProperty = TestObject->GetClass()->FindPropertyByName(FName("ObjectConfig")))
		{
			UE_LOG(LogTemp, Log, TEXT("[Test] ObjProperty is valid"));
			if (const FTestConfig* ObjConfig = ObjProperty->ContainerPtrToValuePtr<FTestConfig>(TestObject))
			{
				UE_LOG(LogTemp, Log, TEXT("[Test] ObjConfig is valid: Start = %f,  Location = %s"), ObjConfig->Start, *ObjConfig->Location.ToString());
			}
		}
		if (const FDoubleProperty* ObjFloat = CastField<FDoubleProperty>(TestObject->GetClass()->FindPropertyByName(FName("TestFloat"))))
		{
			UE_LOG(LogTemp, Log, TEXT("[Test] ObjFloat is valid: Float = %f"), ObjFloat->GetPropertyValue_InContainer(TestObject));

		}
	}
	if (TestClass)
	{
		UE_LOG(LogTemp, Log, TEXT("[Test] TestClass is valid"));
		if (const FProperty* ClassProperty = TestClass->FindPropertyByName(FName("ObjectConfig")))
		{
			UE_LOG(LogTemp, Log, TEXT("[Test] ClassProperty is valid"));
			if (const FTestConfig* ClassConfig = ClassProperty->ContainerPtrToValuePtr<FTestConfig>(TestClass->GetDefaultObject()))
			{
				UE_LOG(LogTemp, Log, TEXT("[Test] ClassConfig is valid: Start = %f,  Location = %s"), ClassConfig->Start, *ClassConfig->Location.ToString());
			}
		}
		if (FProperty* ClassFloat = TestClass->FindPropertyByName(FName("TestFloat")))
		{
			UE_LOG(LogTemp, Log, TEXT("[Test] ClassFloat is valid"));
			if (const double* FloatConfig = ClassFloat->ContainerPtrToValuePtr<double>(TestClass->GetDefaultObject()))
			{
				UE_LOG(LogTemp, Log, TEXT("[Test] FloatConfig is valid: Float = %f"), *FloatConfig);
			}
			if (const FDoubleProperty* FlotPtr = CastField<FDoubleProperty>(ClassFloat))
			{
				UE_LOG(LogTemp, Log, TEXT("[Test] FlotPtr is valid: Float = %f"), FlotPtr->GetPropertyValue_InContainer(TestClass->GetDefaultObject()));

			}

		}

	}
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

