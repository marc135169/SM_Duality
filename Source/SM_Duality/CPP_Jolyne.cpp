///ça marche le pull/push Auto et là ?

///ICIIIII!!!!!!
#include "CPP_Jolyne.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputLibrary.h"
#include "../../../../../../../Unreal5.2/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"

// Sets default values
ACPP_Jolyne::ACPP_Jolyne()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	cameraComponent = CreateDefaultSubobject<UCameraComponent>("camera");
	//spawnComponent = CreateDefaultSubobject<>("Spawn"); peut être un spawn de notre pet si il meurt
	springArmComponent->SetupAttachment(RootComponent);
	cameraComponent->SetupAttachment(springArmComponent);

}

void ACPP_Jolyne::BeginPlay()
{
	Super::BeginPlay();
	InitInput();
	onDeath.AddDynamic(this, &ACPP_Jolyne::SetIsDead);
}

void ACPP_Jolyne::DebugText(FString _text)
{
	UE_LOG(LogTemp, Error, TEXT("%s"), *_text);
}

void ACPP_Jolyne::SetIsDead(bool _value)
{
	isDead = _value;
}

#pragma region overlap et perte de vie TODO
void ACPP_Jolyne::ManageOverlap(AActor* _overlapped, AActor* _overlap)
{
	if (isDead)return;
	UE_LOG(LogTemp, Warning, TEXT("%s|%s"), *_overlap->GetName(), *_overlapped->GetName());
	if (!_overlapped || !_overlap)return;
	//ACPP_Projectile* _projectile = Cast<ACPP_Projectile>(_overlap);
	/*if (!_projectile)return;
	TakeHunterDamage(_projectile->GetDamage());*///TakeHunterDamage(damage)
	if (health <= 0)
		onDeath.Broadcast(true);
}
void ACPP_Jolyne::TakeHunterDamage(const float& _value)
{
	health -= _value;
	health = health < 0 ? 0 : health; // if(health < 0) health = 0 else health = health;
}
#pragma endregion

void ACPP_Jolyne::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma region Input(ZQSD, AE, MOUSE) 
// rajouter clic gauche(forcer un deplacement), clic droit(bouclier), espace(saut), ctrl(soin pet)
void ACPP_Jolyne::InitInput()
{
	ULocalPlayer* _localPlayer = GetWorld()->GetFirstPlayerController()->GetLocalPlayer();
	if (!_localPlayer)return;
	UEnhancedInputLocalPlayerSubsystem* _inputSystem = _localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!_inputSystem)return;
	_inputSystem->AddMappingContext(mappingContext, 0);
}
void ACPP_Jolyne::MoveForward(const FInputActionValue& _value)
{
	if (isDead)return;
	DebugText("Fwd");
	const FVector _fwd = GetActorForwardVector();
	const float _delta = GetWorld()->DeltaTimeSeconds;
	const float _movementValue = _value.Get<float>() * _delta * moveSpeed;
	forwardAxisAnime = _movementValue;
	AddMovementInput(_fwd, _movementValue);
}// Z,S.
void ACPP_Jolyne::MoveRight(const FInputActionValue& _value)
{
	if (isDead)return;
	DebugText("Rgt");
	const FVector _rgt = GetActorRightVector();
	const float _delta = GetWorld()->DeltaTimeSeconds;
	const float _movementValue = _value.Get<float>() * _delta * moveSpeed;
	rightAxisAnime = _movementValue;
	AddMovementInput(_rgt, _movementValue);
}// D,Q.
void ACPP_Jolyne::Rotate(const FInputActionValue& _value)
{
	if (isDead)return;
	DebugText("Rotate");
	const float _delta = GetWorld()->DeltaTimeSeconds;
	const float _rotationValue = _value.Get<float>() * _delta * rotationSpeed;
	AddControllerYawInput(_rotationValue);
}// MouseX , E,A .
void ACPP_Jolyne::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* _inputCompo = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!_inputCompo)
	{
		DebugText("Failed to Cast Input Component");
		return;
	}
	_inputCompo->BindAction(inputToMoveFwd, ETriggerEvent::Triggered, this, &ACPP_Jolyne::MoveForward);
	_inputCompo->BindAction(inputToMoveFwd, ETriggerEvent::Completed, this, &ACPP_Jolyne::MoveForward);
	_inputCompo->BindAction(inputToMoveRgt, ETriggerEvent::Triggered, this, &ACPP_Jolyne::MoveRight);
	_inputCompo->BindAction(inputToMoveRgt, ETriggerEvent::Completed, this, &ACPP_Jolyne::MoveRight);
	_inputCompo->BindAction(inputToRotate, ETriggerEvent::Triggered, this, &ACPP_Jolyne::Rotate);
	_inputCompo->BindAction(inputToRotate, ETriggerEvent::Completed, this, &ACPP_Jolyne::Rotate);
		
	//le mettre a completed permet de renvoyer 0 si on appuie plus Pour ANIMATION!
}
#pragma endregion






