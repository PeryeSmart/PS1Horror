// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemCommandObject.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemCommandSignature, UItemCommandObject*, CommandObject);

UCLASS(Blueprintable)
class PS1HORROR_API UItemCommandObject : public UObject
{
	GENERATED_BODY()
public:
		UItemCommandObject();
		void SetCommandName(FString _CommandName);

		UFUNCTION(BlueprintCallable)
			FString GetCommandName() { return CommandName; };

		FItemCommandSignature GetCommandDelegate() { return CommandDelegate; };
private:
	FString CommandName;

public:
	FItemCommandSignature CommandDelegate;

};
