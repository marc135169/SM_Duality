// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Enemies.h"

// Sets default values
ACPP_Enemies::ACPP_Enemies()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_Enemies::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Enemies::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_Enemies::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

