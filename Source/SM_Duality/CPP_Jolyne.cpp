// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Jolyne.h"

// Sets default values
ACPP_Jolyne::ACPP_Jolyne()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_Jolyne::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Jolyne::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_Jolyne::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

