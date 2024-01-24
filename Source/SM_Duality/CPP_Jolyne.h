

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
//#include "InputMappingContext.h"
#include <GameFramework/SpringArmComponent.h>
#include "GameFramework/Character.h"
#include "../../../../../../../Unreal5.2/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputDeveloperSettings.h"
#include "../../../../../../../Unreal5.2/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputLibrary.h"
#include "CPP_Jolyne.generated.h"

UCLASS()
class SM_DUALITY_API ACPP_Jolyne : public ACharacter
{
	GENERATED_BODY()

#pragma region Event
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, bool, _value); // dans animation ui besoin du bool, pour faire la fonction qui active l'event
	UPROPERTY()
	FOnDeath onDeath;
#pragma endregion

#pragma region Component
	/*UPROPERTY(EditAnywhere, Category = "PlayerCharracter|Component")
	TObjectPtr<> spawnComponent = nullptr;*/
	UPROPERTY(EditAnywhere, Category = "PlayerCharracter|Component")
	TObjectPtr<USpringArmComponent> springArmComponent = nullptr;
	UPROPERTY(EditAnywhere, Category = "PlayerCharracter|Component")
	TObjectPtr<UCameraComponent> cameraComponent = nullptr;
#pragma endregion

#pragma region Input
	UPROPERTY(EditAnywhere, Category = "PlayerCharracter|InputMovement")
	TObjectPtr<UInputMappingContext> mappingContext = nullptr;
	UPROPERTY(EditAnywhere, Category = "PlayerCharracter|InputMovement")
	TObjectPtr<UInputAction> inputToMoveRgt = nullptr;
	UPROPERTY(EditAnywhere, Category = "PlayerCharracter|InputMovement")
	TObjectPtr<UInputAction> inputToMoveFwd = nullptr;
	UPROPERTY(EditAnywhere, Category = "PlayerCharracter|InputMovement")
	TObjectPtr<UInputAction> inputToRotate = nullptr;
	UPROPERTY(EditAnywhere, Category = "PlayerCharracter|InputMovement")
	float moveSpeed = 200;
#pragma endregion

#pragma region AnimationUI
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharracter|Animation") //Pour animation de mort et UI
	float health = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharracter|Animation")
	bool isDead = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharracter|Animation")
	float rightAxisAnime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharracter|Animation")
	float forwardAxisAnime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharracter|Animation")
	float rotationSpeed = 80;
#pragma endregion


public:
	
	ACPP_Jolyne();

protected:
	
	virtual void BeginPlay() override;
	void InitInput();
	void MoveForward(const FInputActionValue& _value);
	void MoveRight(const FInputActionValue& _value);
	void Rotate(const FInputActionValue& _value);
	UFUNCTION(BlueprintCallable)
	void DebugText(FString _text);
	UFUNCTION()
	void SetIsDead(bool _value);
	UFUNCTION()
	void ManageOverlap(AActor* _overlapped, AActor* _overlap);
	void TakeHunterDamage(const float& _value);
public:	
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
