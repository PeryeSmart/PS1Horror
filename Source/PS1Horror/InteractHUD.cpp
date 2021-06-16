// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractHUD.h"

AInteractHUD::AInteractHUD()
{

}

void AInteractHUD::BeginPlay() 
{
	Super::BeginPlay();
	if (InteracButtontWidgetClass)
	{
		EnableInput(GetWorld()->GetFirstPlayerController());
		InteractButtonWidget = CreateWidget<UInteractWidget>(GetWorld(), InteracButtontWidgetClass, InteractButtonWidgetName);
		/** Make sure widget was created */
		if (InteractButtonWidget)
		{
			/** Add it to the viewport */

			InteractButtonWidget->AddToViewport();

			InteractButtonWidget->HideWidget();
		}
	}
}

void AInteractHUD::DrawHUD()
{
	Super::DrawHUD();
}


void AInteractHUD::ShowHUD()
{
	Super::ShowHUD();
}

void AInteractHUD::MoveUp()
{
	InteractButtonWidget->MoveUp();
}

void AInteractHUD::MoveDown()
{
	InteractButtonWidget->MoveDown();
}

void AInteractHUD::Confirmed()
{
	if (IsUpdating) 
	{
		UpdateInteractDialog(UpdateArray);
	}
	else 
	{
		InteractButtonWidget->Confirmed();
	}
}
void AInteractHUD::UpdateInteractDialog(FString InteractDialog)
{
	if (InteractButtonWidget)
	{
		InteractButtonWidget->UpdateInteractDialog(InteractDialog);
		UE_LOG(LogTemp, Error, TEXT("UPDATING TEXT"));
	}
}
void AInteractHUD::UpdateInteractDialog(TArray<FString> InteractDialogLineArray)
{
	if (InteractButtonWidget)
	{
		if (UpdateArray != InteractDialogLineArray) 
		{
			UpdateArray = InteractDialogLineArray;
		}
		if(ArrayLineCounter != InteractDialogLineArray.Num())
		{
			if (!IsUpdating) 
			{
				IsUpdating = true;			
			}
			if (InteractDialogLineArray[ArrayLineCounter].Contains(FString(" * "))) 
			{
				InteractButtonWidget->ShowWidget();
				InteractButtonWidget->SetKeyboardFocus();
				InteractButtonWidget->UpdateInteractDialog(InteractDialogLineArray[ArrayLineCounter]);
			}
			else
			{
				InteractButtonWidget->UpdateInteractDialog(InteractDialogLineArray[ArrayLineCounter]);
				InteractButtonWidget->ShowWidget();
			}

			UE_LOG(LogTemp, Error, TEXT("UPDATING TEXT"));
			ArrayLineCounter++;
		}
		else 
		{
			AfterUpdate();
		}
	}
}

void AInteractHUD::AfterUpdate()
{
	ArrayLineCounter = 0;
	IsUpdating = false;			
	InteractButtonWidget->HideWidget();
}

void AInteractHUD::HideHUD() 
{
	if (InteractButtonWidget)
	{
		InteractButtonWidget->HideWidget();
	}
}