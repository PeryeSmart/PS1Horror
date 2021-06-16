// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/RichTextBlock.h"
#include "DialogInterface.h"
#include "DialogWidget.generated.h"

/**
 * 
 */
UCLASS()
class PS1HORROR_API UDialogWidget : public UUserWidget, public IDialogInterface
{
	GENERATED_BODY()
	public:
		UDialogWidget(const FObjectInitializer& ObjectInitializer);
		virtual void NativeConstruct() override;
		virtual void NativeTick(const FGeometry & MyGeometry, float InDeltaTime) override;
		virtual void UpdateDialog(FString _DialogText) override;
		virtual void ShowWidget() override;
		virtual void HideWidget() override;
		virtual void ClearWidget() override;

	private:
		UPROPERTY(VisibleAnywhere, Category = "Dialog")
			FString DialogText;
		UPROPERTY(EditAnywhere, meta = (BindWidget))
			URichTextBlock* DialogTextBlock;
};
