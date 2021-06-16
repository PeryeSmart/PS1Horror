// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "UMG/Public/Components/Button.h" 
#include "UMG/Public/Components/Image.h" 
#include "InteractWidget.generated.h"

/**
 * 
 */
UCLASS()
class PS1HORROR_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInteractWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry & MyGeometry, float InDeltaTime) override;
	void UpdateInteractDialog(FString _InteractDialog);
	void ShowWidget();
	void HideWidget();
	void Confirmed();
	void MoveUp();
	void MoveDown();
	void SetIsVisible(bool _IsVisible);
	bool GetIsVisible() { return IsWidgetVisible; };
	bool GetDialogChoice() { return DialogChoice; };
private:
	UFUNCTION()
		void YesClicked();
	UFUNCTION()
		void NoClicked();
private:
	TArray<UButton*> BtnArray;
	bool DialogChoice;
	UPROPERTY(EditAnywhere, Category = "Interact Message")
		bool IsWidgetVisible;
	UPROPERTY(EditAnywhere, Category = "Interact Message")
		FString InteractDialog;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* InteractTextBlock;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UButton* BtnYes;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UButton* BtnNo;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UImage* Gameview;
	UPROPERTY(EditAnywhere, Category = "Texture")
		UTexture2D* rt;
};