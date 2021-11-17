// Fill out your copyright notice in the Description page of Project Settings.


#include "RollBallItemBase.h"

#include "RollBall/Game/RollBallGameModeBase.h"

// Sets default values
ARollBallItemBase::ARollBallItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	RootComponent = Mesh;

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ARollBallItemBase::OverlapBegin);

}

// Called when the game starts or when spawned
void ARollBallItemBase::BeginPlay()
{
	Super::BeginPlay();
	 
} 

void ARollBallItemBase::Collected_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("COLLECTED"));
	ARollBallGameModeBase* GameMode = Cast<ARollBallGameModeBase>(GetWorld()->GetAuthGameMode());
	if(GameMode) GameMode->ItemCollected();
}

void ARollBallItemBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("OVERLAP"));
	Collected();
}


