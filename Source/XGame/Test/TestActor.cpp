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
	if(TestType & TO_FLAG(ETestType::Size))
	{
		UE_LOG(LogTemp, Log, TEXT("[Test] ATestActor::TestBlueprintCallable"));
		UE_LOG(LogTemp, Log, TEXT("[Test] UObject = %d, AActor = %d, UActorComponent = %d"), sizeof(UObject), sizeof(AActor), sizeof(UActorComponent));
		UE_LOG(LogTemp, Log, TEXT("[Test] AGameModeBase = %d, AGameMode = %d, AGameState = %d, APlayerState = %d"), sizeof(AGameModeBase), sizeof(AGameMode), sizeof(AGameState), sizeof(APlayerState));
		UE_LOG(LogTemp, Log, TEXT("[Test] APawn = %d, ACharacter = %d"), sizeof(APawn), sizeof(ACharacter));
		UE_LOG(LogTemp, Log, TEXT("[Test] AController = %d, APlayerController = %d, AAIController = %d"), sizeof(AController), sizeof(APlayerController), sizeof(AAIController));
		UE_LOG(LogTemp, Log, TEXT("[Test] APlayerCameraManager = %d, ACameraActor = %d, UCameraComponent = %d"), sizeof(APlayerCameraManager), sizeof(ACameraActor), sizeof(UCameraComponent));
		UE_LOG(LogTemp, Log, TEXT("[Test] AHUD = %d"), sizeof(AHUD));
	}

	if(TestType & TO_FLAG(ETestType::PackageId))
	{
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
}

void ATestActor::TestComponent()
{
	if(TestType & TO_FLAG(ETestType::Component))
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
}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	TestComponent();

	UE_LOG(LogTemp, Log, TEXT("[Test] GUID = %u"), GetUniqueID());

	if(TestType & TO_FLAG(ETestType::Property))
	{
		if (TestObject)
		{
			UE_LOG(LogTemp, Log, TEXT("[Test] TestObject is valid"));
			if (const FProperty* ObjProperty = TestObject->GetClass()->FindPropertyByName(FName("ObjectConfig")))
			{
				UE_LOG(LogTemp, Log, TEXT("[Test] ObjProperty is valid"));
#if WITH_EDITORONLY_DATA
				if (const FTestConfig* ObjConfig = ObjProperty->ContainerPtrToValuePtr<FTestConfig>(TestObject))
				{
					UE_LOG(LogTemp, Log, TEXT("[Test] ObjConfig is valid: Start = %f,  Location = %s"), ObjConfig->Start,
						   *ObjConfig->Location.ToString());
				}
#endif
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
#if WITH_EDITORONLY_DATA
				if (const FTestConfig* ClassConfig = ClassProperty->ContainerPtrToValuePtr<FTestConfig>(
					TestClass->GetDefaultObject()))
				{
					UE_LOG(LogTemp, Log, TEXT("[Test] ClassConfig is valid: Start = %f,  Location = %s"),
						   ClassConfig->Start, *ClassConfig->Location.ToString());
				}
#endif
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
	
	if(TestType & TO_FLAG(ETestType::Pointer))
	{
		// 测试智能指针
		if(UWorld* World = GetWorld(); IsValid(World))
		{
			Test1 = World->SpawnActor<AActor>();
			Test2 = World->SpawnActor<AActor>();
			Test3 = World->SpawnActor<AActor>();
			Test4 = World->SpawnActor<AActor>();
			Test5 = World->SpawnActor<AActor>();
			Test6 = World->SpawnActor<AActor>();

			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, [this]()
			{
				Test1->Destroy();
				Test2->Destroy();
				Test3->Destroy();
				Test3 = nullptr;
				Test4->Destroy();
				Test5->Destroy();
				Test6->Destroy();
			}, 5.0f, false);

			FTimerHandle TimerHandle2;
			GetWorldTimerManager().SetTimer(TimerHandle2, [this]()
			{
				if(Test1)
				{
					UE_LOG(LogTemp, Log, TEXT("[Test] Test1 指针存在"));
					if(Test1->IsPendingKillPending() || Test1->IsUnreachable())
					{
						UE_LOG(LogTemp, Log, TEXT("[Test] Test1 指针存在但已被销毁或无法访问"));
					}
					if(IsValid(Test1))
					{
						UE_LOG(LogTemp, Log, TEXT("[Test] Test1 IsValid"));
					}
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("[Test] Test1 指针不存在"));
				}
			
				if(Test2.IsValid())
				{
					UE_LOG(LogTemp, Log, TEXT("[Test] Test2 指针存在"));
					if(Test2->IsPendingKillPending() || Test2->IsUnreachable())
					{
						UE_LOG(LogTemp, Log, TEXT("[Test] Test2 指针存在但已被销毁或无法访问"));
					}
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("[Test] Test2 指针不存在"));
				}
			
				if(Test3)
				{
					UE_LOG(LogTemp, Log, TEXT("[Test] Test3 指针存在"));
					if(Test3->IsPendingKillPending() || Test3->IsUnreachable())
					{
						UE_LOG(LogTemp, Log, TEXT("[Test] Test3 指针存在但已被销毁或无法访问"));
					}
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("[Test] Test3 指针不存在"));
				}
			
				if(Test4)
				{
					UE_LOG(LogTemp, Log, TEXT("[Test] Test4 指针存在"));
					if(Test4->IsPendingKillPending() || Test4->IsUnreachable())
					{
						UE_LOG(LogTemp, Log, TEXT("[Test] Test4 指针存在但已被销毁或无法访问"));
					}
					if(IsValid(Test4))
					{
						UE_LOG(LogTemp, Log, TEXT("[Test] Test4 IsValid"));
					}
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("[Test] Test4 指针不存在"));
				}
			
				if(Test5.Get())
				{
					UE_LOG(LogTemp, Log, TEXT("[Test] Test5 指针存在"));
					if(Test5->IsPendingKillPending() || Test5->IsUnreachable())
					{
						UE_LOG(LogTemp, Log, TEXT("[Test] Test5 指针存在但已被销毁或无法访问"));
					}
					if(IsValid(Test5))
					{
						UE_LOG(LogTemp, Log, TEXT("[Test] Test5 IsValid"));
					}
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("[Test] Test5 指针不存在"));
				}
			
				if(Test6)
				{
					UE_LOG(LogTemp, Log, TEXT("[Test] Test6 指针存在"));
					if(Test6->IsPendingKillPending() || Test6->IsUnreachable())
					{
						UE_LOG(LogTemp, Log, TEXT("[Test] Test6 指针存在但已被销毁或无法访问"));
					}
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("[Test] Test6 指针不存在"));
				}
			}, 2.0f, true, 10.0f);
		}
	}
}
