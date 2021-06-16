// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogWidget.h"

UDialogWidget::UDialogWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{


}

void UDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDialogWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime) 
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UDialogWidget::UpdateDialog(FString _DialogText)
{
	DialogText = _DialogText;
	DialogTextBlock->SetText(FText::FromString(DialogText));
	
}

void UDialogWidget::ShowWidget()
{
	this->SetVisibility(ESlateVisibility::Visible);
}

void UDialogWidget::HideWidget()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UDialogWidget::ClearWidget() 
{
	DialogTextBlock->SetText(FText::FromString(FString("")));
}