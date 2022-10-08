#include "DrivedActor.h"

ADrivedActor::ADrivedActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADrivedActor::TestBlueprintCallable()
{
	Super::TestBlueprintCallable();
	UE_LOG(LogTemp, Log, TEXT("[Test] ADrivedActor::TestBlueprintCallable"));
}
