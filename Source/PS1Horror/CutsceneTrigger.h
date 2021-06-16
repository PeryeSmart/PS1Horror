// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainController.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/LevelSequence/Public/LevelSequence.h"
#include "Runtime/LevelSequence/Public/LevelSequencePlayer.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "CutsceneTrigger.generated.h"

UCLASS()
class PS1HORROR_API ACutsceneTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACutsceneTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
		void OnColliderOverlapBegin(
			UPrimitiveComponent* Comp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherIndex,
			bool bFromSweep,
			const FHitResult & SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	bool CutscenePlayed = false;
	ALevelSequenceActor* CutsceneSequenceActor;
	ULevelSequencePlayer* CutscenePlayer;

	UPROPERTY(VisibleAnywhere, Category = "Root")
		USceneComponent* CutsceneTriggerRoot;
	UPROPERTY(VisibleAnywhere, Category = "Cutscene Trigger")
		UBoxComponent* CutsceneTrigger;
	UPROPERTY(EditAnywhere, Category = "Cutscene")
		ULevelSequence* CutsceneSequence;
	UPROPERTY(EditAnywhere, Category = "Cutscene")
		bool PlayOnce;
};
