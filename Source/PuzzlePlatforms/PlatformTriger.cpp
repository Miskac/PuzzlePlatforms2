// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTriger.h"
#include "Components/BoxComponent.h"

#include "MovingPlatform.h"

// Sets default values
APlatformTriger::APlatformTriger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("TriggerVolume")));
	if(TriggerVolume == nullptr)
	{
		return;
	}
	
	RootComponent = TriggerVolume;

	
}

// Called when the game starts or when spawned
void APlatformTriger::BeginPlay()
{
	Super::BeginPlay();

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTriger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTriger::OnOverlapEnd);
}

// Called every frame
void APlatformTriger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTriger::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	for (AMovingPlatform* Platform : PlatformsToTrigger)
	{
		Platform->AddActiveTrigger();
	}
}

void APlatformTriger::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	for (AMovingPlatform* Platform : PlatformsToTrigger)
	{
		if (ensure(Platform!=nullptr)) 
		{
			Platform->RemoveActiveTrigger();
		}
	}
}

