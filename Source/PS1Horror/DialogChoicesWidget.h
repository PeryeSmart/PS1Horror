// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h" 
#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "DialogInterface.h"
#include "DialogChoicesWidget.generated.h"

/**
 * 
 */
UCLASS()
class PS1HORROR_API UDialogChoicesWidget : public UUserWidget, public IDialogInterface
{
	GENERATED_BODY()
	public:
		UDialogChoicesWidget(const FObjectInitializer& ObjectInitializer);
		virtual void NativeConstruct() override;
		virtual void NativeTick(const FGeometry & MyGeometry, float InDeltaTime) override;
		virtual void UpdateDialog(FString _DialogText, TArray<FString> _Choices) override;
		virtual void UpdateDialog(FString _DialogText) override;
		virtual void ShowWidget() override;
		virtual void HideWidget() override;
		virtual void MoveUp() override;
		virtual void MoveDown() override;
		virtual bool GetLatestChoice() override { return LatestChoice; };
		virtual void ClearWidget() override;

	private:
		bool LatestChoice;
		UPROPERTY(VisibleAnywhere, Category = "Dialog")
			FString DialogText;
		UPROPERTY(EditAnywhere, meta = (BindWidget))
			URichTextBlock* DialogTextBlock;
		UPROPERTY(EditAnywhere, meta = (BindWidget))
			UTextBlock* YesButtonTxt;
		UPROPERTY(EditAnywhere, meta = (BindWidget))
			UTextBlock* NoButtonTxt;
		UPROPERTY(EditAnywhere, meta = (BindWidget))
			UButton* YesButton;
		UPROPERTY(EditAnywhere, meta = (BindWidget))
			UButton* NoButton;
};
