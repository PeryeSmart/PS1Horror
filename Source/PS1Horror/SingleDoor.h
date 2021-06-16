// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "InteractInterface.h"
#include "Engine/Level.h"
#include "MainController.h"
#include "SingleDoor.generated.h"

UCLASS()
class PS1HORROR_API ASingleDoor : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASingleDoor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Door Implementation of pure virtual method of InteractInterface
	virtual void Interact() override;
	virtual bool GetIsFocusEnable() override;
	virtual FString GetInteractableName() override { return FString(); };
	virtual FText GetInteractableDialog() override { return FText(); };
	virtual FString GetInteractableID() override { return InteractableID; };
	bool GetIsDoorOpen();
	bool GetIsDoorLocked();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OpenDoor();
	void UnlockDoor();
	void CloseDoor();
	void SetDoorLocked(bool _IsDoorLocked);
	void SetDoorOpen(bool _IsDoorOpen);

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* DoorRootComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* DoorCollider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Parts")
		UStaticMeshComponent* Door;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Parts")
		UStaticMeshComponent* DoorFrame;
private:
	bool IsOpenning;
	UPROPERTY(EditAnywhere, Category = "Item Description")
		FString InteractableID;
	UPROPERTY(EditAnywhere, Category = "Item Description")
		bool IsFocusEnable;
	UPROPERTY(EditAnywhere, Category = "Door Behaviour")
		AActor* KeyItem;
	UPROPERTY(EditAnywhere, Category = "Door Behaviour")
		bool LoadLevelOnOpen;
	UPROPERTY(EditAnywhere, Category = "Door Behaviour")
		FName LevelToLoad;
	UPROPERTY(EditAnywhere, Category = "Door Behaviour")
		bool IsDoorOpen;
	UPROPERTY(EditAnywhere, Category = "Door Behaviour")
		bool IsDoorLocked;
	UPROPERTY(EditAnywhere, Category = "Door Behaviour")
		float DoorOpeningAngle;
	UPROPERTY(EditAnywhere, Category = "Door Animation")
		ULevelSequence* DoorInCutsceneSequence;
	UPROPERTY(EditAnywhere, Category = "Door Animation")
		ULevelSequence* DoorOutCutsceneSequence;
};
