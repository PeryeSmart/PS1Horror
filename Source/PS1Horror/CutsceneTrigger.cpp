// Fill out your copyright notice in the Description page of Project Settings.


#include "CutsceneTrigger.h"

// Sets default values
ACutsceneTrigger::ACutsceneTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CutsceneTriggerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	CutsceneTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Cutscene Trigger"));

	CutsceneTrigger->SetupAttachment(CutsceneTriggerRoot);
}
// Called when the game starts or when spawned
void ACutsceneTrigger::BeginPlay()
{
	Super::BeginPlay();
	CutsceneTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACutsceneTrigger::OnColliderOverlapBegin);
	if (CutsceneSequence) 
	{
		CutsceneSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();
		CutsceneSequenceActor->SetSequence(CutsceneSequence);
	}
}

// Called every frame
void ACutsceneTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACutsceneTrigger::OnColliderOverlapBegin(
	UPrimitiveComponent* Comp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherIndex,
	bool bFromSweep,
	const FHitResult & SweepResult) 
{
	AMainCharacter * Character = Cast<AMainCharacter>(OtherActor);

	if (Character && CutsceneSequence && ((PlayOnce && !CutscenePlayed) || !PlayOnce))
	{
		CutscenePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(),
			CutsceneSequence,
			FMovieSceneSequencePlaybackSettings(),
			CutsceneSequenceActor
		);
		
		AMainController * MainController = Cast<AMainController>(GetWorld()->GetFirstPlayerController());
		if (MainController) 
		{
			MainController->UpdatePlayerState(EPlayerState::InMenu);
			CutscenePlayer->Play();
			FTimerHandle handle;
			GetWorld()->GetTimerManager().SetTimer(
				handle, 
				[this]() {
					AMainController * MainController = Cast<AMainController>(GetWorld()->GetFirstPlayerController());
					MainController->UpdatePlayerState(EPlayerState::InGame);
					CutscenePlayed = true;
				}, 
				CutscenePlayer->GetFrameDuration() / CutscenePlayer->GetFrameRate().Numerator, false
			);
		}	
	}
}

