// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/ActorComponent.h"
#include "Collectible.h"
#include "FireArm.h"
#include "DataRepository.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "MainCharacter.generated.h"

UCLASS()
class PS1HORROR_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	AMainCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
		UCameraComponent * FPSCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interaction Collision")
		UBoxComponent* InteractCollider;

private:

	UPROPERTY(EditAnywhere, Category = "Character Speed")
		float WalkSpeed;

	UPROPERTY(EditAnywhere, Category = "Character Speed")
		float RunSpeed;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		class USkeletalMeshComponent* CharacterMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		class USkeletalMeshComponent* WeaponMeshComp;

	IInteractInterface* InteractableObject;
	TArray<FString> Inventory;
	AActor* LatestCameraReference;
	FWeapon* EquippedWeapon;

	bool IsInteracting;
	bool IsRunning = false;
	bool IsMovingBackward = false;
	bool IsInFightingStance = false;
	bool IsWeaponEquipped = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		bool GetIsRunning() { return IsRunning; };

	UFUNCTION(BlueprintCallable)
		bool GetIsMovingBackward() { return IsMovingBackward; };

	UFUNCTION(BlueprintCallable)
		bool GetIsInFigthingStance() { return IsInFightingStance; };

private:
	friend class AMainController;

	void MoveForward(float Axis);
	void TurnLeft(float Axis);
	void BeforeInteract(FString& InteractableID);
	void Interact();
	void Walk();
	void Crouch();
	void EquipWeapon(FWeapon* WeaponToEquip);
	TArray<FString>GetInventory() { return Inventory; };

	UFUNCTION()
	void OnInteractOverlapBegin(
		UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult & SweepResult);

	UFUNCTION()
	void OnInteractOverlapEnd(
		UPrimitiveComponent* HitComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);

	void FocusCameraOnInteractable();
	void AddToInventory(ACollectible* Collectible, FString ItemID);
	void EnterFightingStance();
	void LeaveFightingStance();
	void Attack();
};
