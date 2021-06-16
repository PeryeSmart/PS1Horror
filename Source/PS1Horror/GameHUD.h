// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DialogWidget.h"
#include "DialogChoicesWidget.h"
#include "InventoryWidget.h"
#include "DialogInterface.h"
#include "LevelLoadingWidget.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class PS1HORROR_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	public:
		AGameHUD();
		virtual void BeginPlay() override;
		virtual void DrawHUD() override;
		virtual void ShowHUD() override;

	private:

		friend class AMainController;

		bool GetDialogUpdating() { return IsDialogUpdating; };
		bool GetIsInDialogChoice() { return IsInDialogChoice; };
		bool GetSelectedChoice() { return SelectedChoice; };
		void SwapDialogWidget();
		void UpdateDialogWidget();
		void FeedDialogHUD(TArray<FString> _Dialog);
		void FeedDialogChoicesHUD(FString _ChoiceDialog, FString _ConfirmationDialog, TArray<FString> _Choices);
		void FeedInventoryHUD(TArray<FItem*> _Inventory);
		void Confirmed();
		void MoveChoiceUp();
		void MoveChoiceDown();
		void ResetDialogHUD();
		void ResetInventoryHUD();
		void DialogConfirmation();
		void ShowLoadingScreen(bool ShowLoadingScreen);

	private:

		TArray<FString> Dialog;
		TArray<FString> Choices;
		FString ChoiceDialog;
		FString ConfirmationDialog;
		int32 DialogLineCounter;
		bool IsDialogUpdating = false;
		bool IsInDialogChoice = false;
		bool IsDialogConfirming = false;
		bool SelectedChoice;
		UPROPERTY(EditAnywhere, Category = "Dialog Widgets")
			TSubclassOf<UUserWidget> DialogWidgetClass;
		UPROPERTY(EditAnywhere, Category = "Dialog Widgets")
			TSubclassOf<UUserWidget> DialogChoicesWidgetClass;
		UPROPERTY(EditAnywhere, Category = "Inventory Widget")
			TSubclassOf<UUserWidget> InventoryWidgetClass;
		UPROPERTY(EditAnywhere, Category = "Level Loading Widget")
			TSubclassOf<UUserWidget> LevelLoadingWidgetClass;
		UDialogWidget* DialogWidget;
		UDialogChoicesWidget* DialogChoicesWidget;
		UInventoryWidget* InventoryWidget;
		ULevelLoadingWidget* LevelLoadingWidget;
		IDialogInterface* ActiveDialogWidget;
};
