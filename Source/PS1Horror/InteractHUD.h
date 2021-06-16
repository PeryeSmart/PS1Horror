// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InteractWidget.h"
#include "InteractHUD.generated.h"

/**
 * 
 */
UCLASS()
class PS1HORROR_API AInteractHUD : public AHUD
{
	GENERATED_BODY()
	
	public:
		AInteractHUD();
		virtual void BeginPlay() override;
		virtual void DrawHUD() override;
		virtual void ShowHUD() override;
		void MoveUp();
		void MoveDown();
		void Confirmed();
		void HideHUD();
		bool GetDialogChoice() { return InteractButtonWidget->GetDialogChoice(); };
		void AfterUpdate();
		void UpdateInteractDialog(FString InteractDialog);
		void UpdateInteractDialog(TArray<FString> InteractDialogLineArray);
		bool GetIsUpdating() { return IsUpdating; };
	
	private:
		TArray<FString> UpdateArray;
		int32 ArrayLineCounter = 0;
		bool IsUpdating = false;
		//UPROPERTY(EditDefaultsOnly, Category = "Widget Implementation")
			//TSubclassOf<UUserWidget> InteractWidgetClass;
		UPROPERTY(EditDefaultsOnly, Category = "Widget Implementation")
			TSubclassOf<UUserWidget> InteracButtontWidgetClass;
		UPROPERTY(EditDefaultsOnly, Category = "Widget Implementation")
			FName InteractWidgetName;
		UPROPERTY(EditDefaultsOnly, Category = "Widget Implementation")
			FName InteractButtonWidgetName;

	private:

		UInteractWidget* InteractButtonWidget;
};
