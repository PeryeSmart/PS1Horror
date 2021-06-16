// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelLoadingWidget.h"

ULevelLoadingWidget::ULevelLoadingWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void ULevelLoadingWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void ULevelLoadingWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void ULevelLoadingWidget::ShowWidget()
{
	this->SetVisibility(ESlateVisibility::Visible);
}

void ULevelLoadingWidget::HideWidget()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}