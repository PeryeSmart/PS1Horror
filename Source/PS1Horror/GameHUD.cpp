// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

AGameHUD::AGameHUD()
{

}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();
	if (DialogWidgetClass && DialogChoicesWidgetClass && InventoryWidgetClass && LevelLoadingWidgetClass)
	{
		EnableInput(GetWorld()->GetFirstPlayerController());
		DialogWidget = CreateWidget<UDialogWidget>(GetWorld(), DialogWidgetClass, FName("Dialog"));
		DialogChoicesWidget = CreateWidget<UDialogChoicesWidget>(GetWorld(), DialogChoicesWidgetClass, FName("Dialog Choices"));
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass, FName("Inventory"));
		LevelLoadingWidget = CreateWidget<ULevelLoadingWidget>(GetWorld(), LevelLoadingWidgetClass, FName("Level Loading"));
		if (DialogWidget && DialogChoicesWidget && InventoryWidget && LevelLoadingWidget)
		{
			DialogWidget->AddToViewport();
			DialogWidget->HideWidget();
			DialogChoicesWidget->AddToViewport();
			DialogChoicesWidget->HideWidget();
			InventoryWidget->AddToViewport();
			InventoryWidget->HideWidget();
			LevelLoadingWidget->AddToViewport();
			LevelLoadingWidget->HideWidget();
			ActiveDialogWidget = Cast<IDialogInterface>(DialogWidget);
			ResetDialogHUD();
		}
	}
}

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();
}


void AGameHUD::ShowHUD()
{
	Super::ShowHUD();
}

void AGameHUD::MoveChoiceUp()
{
	ActiveDialogWidget->MoveUp();
}

void AGameHUD::MoveChoiceDown()
{
	ActiveDialogWidget->MoveDown();
}

void AGameHUD::FeedDialogChoicesHUD(FString _ChoiceDialog, FString _ConfirmationDialog, TArray<FString> _Choices)
{
	Choices = _Choices;
	ChoiceDialog = _ChoiceDialog;
	ConfirmationDialog = _ConfirmationDialog;
}

void AGameHUD::FeedDialogHUD(TArray<FString> _Dialog)
{
	Dialog = _Dialog;
	DialogLineCounter = 0;
	IsDialogUpdating = true;
	ActiveDialogWidget->ShowWidget();
}

void AGameHUD::FeedInventoryHUD(TArray<FItem*> _Inventory)
{
	if (InventoryWidget) 
	{
		InventoryWidget->SetUserFocus(GetWorld()->GetFirstPlayerController());
		InventoryWidget->LoadInventory(_Inventory);
		InventoryWidget->LoadItemList();
		InventoryWidget->ShowWidget();
	}
}

void AGameHUD::ShowLoadingScreen(bool ShowLoadingScreen)
{
	if (ShowLoadingScreen) 
	{
		LevelLoadingWidget->ShowWidget();
	}
	else 
	{
		LevelLoadingWidget->HideWidget();
	}
}

void AGameHUD::UpdateDialogWidget()
{
	if (DialogLineCounter < Dialog.Num()) 
	{
		ActiveDialogWidget->UpdateDialog(Dialog[DialogLineCounter]);
		DialogLineCounter++;
	}
	else 
	{
		ActiveDialogWidget->HideWidget();
		if (Choices.Num() > 0 && !IsInDialogChoice)
		{
			SwapDialogWidget();
			ActiveDialogWidget->UpdateDialog(ChoiceDialog, Choices);
			ActiveDialogWidget->ShowWidget();
			IsInDialogChoice = true;
		}
		else 
		{
			if (IsInDialogChoice) 
			{
				SelectedChoice = ActiveDialogWidget->GetLatestChoice();
				ResetDialogHUD();
				SwapDialogWidget();
			}
			ResetDialogHUD();
		}
	}	
}

void AGameHUD::Confirmed()
{
	if (IsDialogUpdating)
	{
		UpdateDialogWidget();
	}
	else 
	{
		DialogConfirmation();
	}
}

void AGameHUD::DialogConfirmation()
{
	if (IsDialogConfirming)
	{
		ResetDialogHUD();
	}
	if (!ConfirmationDialog.IsEmpty() && !IsDialogConfirming)
	{
		ActiveDialogWidget->UpdateDialog(ConfirmationDialog);
		ActiveDialogWidget->ShowWidget();
		IsDialogConfirming = true;
	}
}

void AGameHUD::SwapDialogWidget() 
{
	if (Cast<UDialogWidget>(ActiveDialogWidget)) 
	{
		ActiveDialogWidget = Cast<IDialogInterface>(DialogChoicesWidget);
	}
	else if (Cast<UDialogChoicesWidget>(ActiveDialogWidget))
	{
		ActiveDialogWidget = Cast<IDialogInterface>(DialogWidget);
	}
}

void AGameHUD::ResetDialogHUD() 
{
	ActiveDialogWidget->ClearWidget();
	if (IsDialogConfirming) 
	{
		ConfirmationDialog = FString();
		IsDialogConfirming = false;
	}
	Dialog = TArray<FString>();
	Choices = TArray<FString>();
	ChoiceDialog = FString();
	IsDialogUpdating = false;
	IsInDialogChoice = false;
	DialogLineCounter = 0;
	ActiveDialogWidget->HideWidget();
}

void AGameHUD::ResetInventoryHUD() 
{
	InventoryWidget->HideWidget();
	InventoryWidget->ClearItemList();
}
