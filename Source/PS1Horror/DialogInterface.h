// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DialogInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDialogInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PS1HORROR_API IDialogInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void UpdateDialog(FString DialogText) = 0;
	virtual void UpdateDialog(FString DialogText, TArray<FString> Choice);
	virtual void HideWidget() = 0;
	virtual void ShowWidget() = 0;
	virtual void ClearWidget() = 0;
	virtual void MoveUp();
	virtual void MoveDown();
	virtual bool GetLatestChoice();
};
