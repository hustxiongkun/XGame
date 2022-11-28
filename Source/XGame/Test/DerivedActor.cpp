#include "DerivedActor.h"

ADerivedActor::ADerivedActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADerivedActor::TestBlueprintCallable()
{
	Super::TestBlueprintCallable();
	UE_LOG(LogTemp, Log, TEXT("[Test] ADrivedActor::TestBlueprintCallable"));
}
