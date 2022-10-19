#include "TestPawn.h"

ATestPawn::ATestPawn()
{
	PrimaryActorTick.bCanEverTick = true;
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
}

