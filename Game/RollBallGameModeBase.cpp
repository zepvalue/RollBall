// Fill out your copyright notice in the Description page of Project Settings.


#include "RollBallGameModeBase.h"

#include "RollBallWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "RollBall/Items/RollBallItemBase.h"

void ARollBallGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ARollBallItemBase::StaticClass(), Items);
	ItemsInLevel = Items.Num();

	if(GameWidgetClass)
	{
		GameWidget = Cast<URollBallWidget>(CreateWidget(GetWorld(),GameWidgetClass));

		if(GameWidget)
		{
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}
}

void ARollBallGameModeBase::UpdateItemText()
{
	GameWidget->SetItemText(ItemsCollected,ItemsInLevel);
}

void ARollBallGameModeBase::ItemCollected()
{
	ItemsCollected++;
	UpdateItemText();
}
