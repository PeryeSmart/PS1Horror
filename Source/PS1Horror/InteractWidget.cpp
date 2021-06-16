// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWidget.h"

UInteractWidget::UInteractWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	
}

void UInteractWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	for (UButton* Btn : BtnArray) 
	{
		if (Btn->HasKeyboardFocus()) 
		{
			Btn->SetColorAndOpacity(FLinearColor::Blue);
		}
		else 
		{
			Btn->SetColorAndOpacity(FLinearColor::White);
		}
	}
}

void UInteractWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BtnYes->OnClicked.AddDynamic(this, &UInteractWidget::YesClicked);
	BtnNo->OnClicked.AddDynamic(this, &UInteractWidget::NoClicked);
	BtnArray.Add(BtnYes);
	BtnArray.Add(BtnNo);
	bIsFocusable = true;
}

void UInteractWidget::YesClicked() 
{

}

void UInteractWidget::NoClicked()
{

}

void UInteractWidget::MoveUp() 
{
	UE_LOG(LogTemp ,Error ,TEXT("Focus set on yes"));
	BtnYes->SetKeyboardFocus();
}

void UInteractWidget::MoveDown()
{
	UE_LOG(LogTemp, Error, TEXT("Focus set on no"));
	BtnNo->SetKeyboardFocus();
}

void UInteractWidget::Confirmed()
{
	if (BtnYes->HasKeyboardFocus()) 
	{
		DialogChoice = true;
		UE_LOG(LogTemp, Error, TEXT("Dialog True"));
	}
	else 
	{
		DialogChoice = false;
		UE_LOG(LogTemp, Error, TEXT("Dialog False"));
	}
}

void UInteractWidget::UpdateInteractDialog(FString _InteractDialog)
{
	InteractDialog = _InteractDialog;
	InteractTextBlock->SetText(FText::FromString(InteractDialog));
}

void UInteractWidget::ShowWidget()
{
	this->SetVisibility(ESlateVisibility::Visible);
	SetIsVisible(true);
}

void UInteractWidget::HideWidget()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	SetIsVisible(false);
}

void UInteractWidget::SetIsVisible(bool _IsVisible)
{
	IsWidgetVisible = _IsVisible;
}

