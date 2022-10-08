#include "TestActor.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATestActor::TestMulticast_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("[Test] TestMulticast"));
}

void ATestActor::TestBlueprintCallable()
{
	UE_LOG(LogTemp, Log, TEXT("[Test] ATestActor::TestBlueprintCallable"));
}

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
				UE_LOG(LogTemp, Log, TEXT("[Test] ObjConfig is valid: Start = %f,  Location = %s"), ObjConfig->Start,
				       *ObjConfig->Location.ToString());
			}
		}
		if (const FDoubleProperty* ObjFloat = CastField<FDoubleProperty>(
			TestObject->GetClass()->FindPropertyByName(FName("TestFloat"))))
		{
			UE_LOG(LogTemp, Log, TEXT("[Test] ObjFloat is valid: Float = %f"),
			       ObjFloat->GetPropertyValue_InContainer(TestObject));
		}
	}
	if (TestClass)
	{
		UE_LOG(LogTemp, Log, TEXT("[Test] TestClass is valid"));
		if (const FProperty* ClassProperty = TestClass->FindPropertyByName(FName("ObjectConfig")))
		{
			UE_LOG(LogTemp, Log, TEXT("[Test] ClassProperty is valid"));
			if (const FTestConfig* ClassConfig = ClassProperty->ContainerPtrToValuePtr<FTestConfig>(
				TestClass->GetDefaultObject()))
			{
				UE_LOG(LogTemp, Log, TEXT("[Test] ClassConfig is valid: Start = %f,  Location = %s"),
				       ClassConfig->Start, *ClassConfig->Location.ToString());
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
				UE_LOG(LogTemp, Log, TEXT("[Test] FlotPtr is valid: Float = %f"),
				       FlotPtr->GetPropertyValue_InContainer(TestClass->GetDefaultObject()));
			}
		}
	}
}
