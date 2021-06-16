// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelLoadingWidget.generated.h"

/**
 * 
 */
UCLASS()
class PS1HORROR_API ULevelLoadingWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	ULevelLoadingWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry & MyGeometry, float InDeltaTime) override;
	void ShowWidget();
	void HideWidget();
};
