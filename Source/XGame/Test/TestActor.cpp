#include "TestActor.h"

#include "AIController.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameState.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerState.h"

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
	UE_LOG(LogTemp, Log, TEXT("[Test] UObject = %d, AActor = %d, UActorComponent = %d"), sizeof(UObject), sizeof(AActor), sizeof(UActorComponent));
	UE_LOG(LogTemp, Log, TEXT("[Test] AGameModeBase = %d, AGameMode = %d, AGameState = %d, APlayerState = %d"), sizeof(AGameModeBase), sizeof(AGameMode), sizeof(AGameState), sizeof(APlayerState));
	UE_LOG(LogTemp, Log, TEXT("[Test] APawn = %d, ACharacter = %d"), sizeof(APawn), sizeof(ACharacter));
	UE_LOG(LogTemp, Log, TEXT("[Test] AController = %d, APlayerController = %d, AAIController = %d"), sizeof(AController), sizeof(APlayerController), sizeof(AAIController));
	UE_LOG(LogTemp, Log, TEXT("[Test] APlayerCameraManager = %d, ACameraActor = %d, UCameraComponent = %d"), sizeof(APlayerCameraManager), sizeof(ACameraActor), sizeof(UCameraComponent));
	UE_LOG(LogTemp, Log, TEXT("[Test] AHUD = %d"), sizeof(AHUD));
	if(BlueprintClass)
	{
		FPackageId PackageId = FPackageId::FromName(FName(BlueprintClass->GetFullName()));
		UE_LOG(LogTemp, Log, TEXT("[Test] Blueprint Package = %s,  BlueprintClass = %s, PackageId = %llu, size = %d"), *GetPackage()->GetLoadedPath().GetPackageFName().ToString(), *BlueprintClass->GetFullName(), PackageId.Value(), sizeof(FPackageId));
		if(const UObject* OtherObj = NewObject<ATestActor>(this, BlueprintClass, TEXT("OterObj")))
		{
			PackageId = FPackageId::FromName(FName(OtherObj->GetFullName()));
			UE_LOG(LogTemp, Log, TEXT("[Test] Blueprint OtherObj = %s, PackageId = %llu"), *OtherObj->GetFullName(), PackageId.Value());
			if(const UClass* OtherClass = OtherObj->GetClass())
			{
				PackageId = FPackageId::FromName(FName(OtherClass->GetFullName()));
				UE_LOG(LogTemp, Log, TEXT("[Test] Blueprint OtherClass = %s, PackageId = %llu"), *OtherClass->GetFullName(), PackageId.Value());
			}
		}
	}
	if(const UClass* BlueprintPtrClass = BlueprintPtr.LoadSynchronous())
	{
		const FPackageId PackageId = FPackageId::FromName(FName(BlueprintPtrClass->GetFullName()));
		UE_LOG(LogTemp, Log, TEXT("[Test] Blueprint BlueprintPtrClass = %s, PackageId = %llu"), *BlueprintPtrClass->GetFullName(), PackageId.Value());
	}
}

void ATestActor::TestComponent()
{
	// 测试Actor的component
	for(const auto Component : GetComponents())
	{
		UE_LOG(LogTemp, Log, TEXT("[Test] ATestActor::BeginPlay: Owned Component = %s"), *Component->GetName());
	}
	for(const auto Component : GetInstanceComponents())
	{
		UE_LOG(LogTemp, Log, TEXT("[Test] ATestActor::BeginPlay: Instance Component = %s"), *Component->GetName());
	}
	for(const auto Component : BlueprintCreatedComponents)
	{
		UE_LOG(LogTemp, Log, TEXT("[Test] ATestActor::BeginPlay: Blueprint Component = %s"), *Component->GetName());
	}
}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	TestComponent();

	UE_LOG(LogTemp, Log, TEXT("[Test] GUID = %u"), GetUniqueID());

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
