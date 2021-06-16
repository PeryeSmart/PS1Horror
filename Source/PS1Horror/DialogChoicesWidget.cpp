// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogChoicesWidget.h"

UDialogChoicesWidget::UDialogChoicesWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{


}

void UDialogChoicesWidget::NativeConstruct()
{
	Super::NativeConstruct();
	bIsFocusable = true;
}

void UDialogChoicesWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (YesButton->HasKeyboardFocus())
	{
		YesButton->SetBackgroundColor(FLinearColor(FVector4(0.052409f, 0.208036f, 0.838542f, 0.600f)));
		NoButton->SetBackgroundColor(FLinearColor(FVector4(1.f, 1.f, 1.f, 0.f)));
	}
	else
	{
		//YesButton->SetColorAndOpacity(FLinearColor::White);
		//NoButton->SetColorAndOpacity(FLinearColor::Blue);
		YesButton->SetBackgroundColor(FLinearColor(FVector4(1.f, 1.f, 1.f, 0.f)));
		NoButton->SetBackgroundColor(FLinearColor(FVector4(0.052409f, 0.208036f, 0.838542f, 0.600f)));
	}
}

void UDialogChoicesWidget::UpdateDialog(FString _DialogText, TArray<FString> _Choices)
{
	DialogText = _DialogText;
	DialogTextBlock->SetText(FText::FromString(DialogText));
	YesButtonTxt->SetText(FText::FromString(_Choices[0])); 
	NoButtonTxt->SetText(FText::FromString(_Choices[1]));
	MoveUp();
}

void UDialogChoicesWidget::MoveUp()
{
	UE_LOG(LogTemp, Error, TEXT("Focus set on yes"));
	YesButton->SetKeyboardFocus();
	LatestChoice = true;
}

void UDialogChoicesWidget::MoveDown()
{
	UE_LOG(LogTemp, Error, TEXT("Focus set on no"));
	NoButton->SetKeyboardFocus();
	LatestChoice = false;
}

void UDialogChoicesWidget::UpdateDialog(FString _DialogText)
{

}

void UDialogChoicesWidget::ShowWidget()
{
	this->SetVisibility(ESlateVisibility::Visible);
}

void UDialogChoicesWidget::HideWidget()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UDialogChoicesWidget::ClearWidget()
{
	DialogTextBlock->SetText(FText::FromString(FString("")));
	YesButtonTxt->SetText(FText::FromString(FString("")));
	NoButtonTxt->SetText(FText::FromString(FString("")));
}