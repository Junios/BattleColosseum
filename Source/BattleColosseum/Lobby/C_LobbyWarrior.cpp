// Fill out your copyright notice in the Description page of Project Settings.

#include "C_LobbyWarrior.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"
#include "UnrealNetwork.h"
#include "Components/InputComponent.h"

AC_LobbyWarrior::AC_LobbyWarrior() {
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CharacterMovement = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("CharacterMovement"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_ManBody(TEXT("SkeletalMesh'/Game/Meshes/Characters/Male/ColoM.ColoM'"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_WomanBody(TEXT("SkeletalMesh'/Game/Meshes/Characters/Female/ColoW.ColoW'"));

	if (SM_ManBody.Succeeded()) {
		SM_Man = SM_ManBody.Object;
	}
	if (SM_WomanBody.Succeeded()) {
		SM_Woman = SM_WomanBody.Object;
	}

	RootComponent = Capsule;
	SkeletalMesh->SetupAttachment(Capsule);
	SpringArm->AttachToComponent((USceneComponent*)Capsule, FAttachmentTransformRules::KeepRelativeTransform);
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	SkeletalMesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	bReplicates = true;

	// ���� �ʱ�ȭ
	IsSprinting = false;
	SprintRate = 100.f;
	RightView = false;

	this->bUseControllerRotationPitch = false;				// �÷��̾ ���Ʒ��� ���ư��� �ʵ���
	SpringArm->bUsePawnControlRotation = true;				// ��Ʈ�ѷ��� ȸ������ ����ϵ���
	SpringArm->bInheritPitch = true;						// ī�޶� ���Ʒ��� ���ư�����
	SpringArm->SocketOffset = FVector(0.f, 50.f, 70.f);		// ������ ������� ����
	SpringArm->TargetArmLength = 150.f;						// ī�޶� �Ÿ� ������ ����
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 9.0f;
	SpringArm->CameraRotationLagSpeed = 9.0f;

	Capsule->SetNotifyRigidBodyCollision(true);  // hit �̺�Ʈ Ȱ��ȭ(�����̸�)
}

void AC_LobbyWarrior::BeginPlay()
{
	Super::BeginPlay();

	Ori_Speed = 400.f;
	Sprint_Speed = Ori_Speed * SprintRate;
	if (IsMan) {
		SkeletalMesh->SetSkeletalMesh(SM_Man);
	}
	else {
		SkeletalMesh->SetSkeletalMesh(SM_Woman);
	}
}

void AC_LobbyWarrior::MoveForward(float Value)
{
	if (Value != 0.f) {
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AC_LobbyWarrior::MoveRight(float Value)
{
	if (Value != 0.f) {
		AddMovementInput(GetActorRightVector(), Value);
	}
}

bool AC_LobbyWarrior::ActiveSprint_Validate() {
	return true;
}

void AC_LobbyWarrior::ActiveSprint()
{
	if (!IsSprinting)
		IsSprinting = true;
}

bool AC_LobbyWarrior::DeActiveSprint_Validate() {
	return true;
}

void AC_LobbyWarrior::DeActiveSprint()
{
	if (IsSprinting)
		IsSprinting = false;
}

void AC_LobbyWarrior::SwitchView()
{
	if (RightView) {
		RightView = false;
		SpringArm->SocketOffset = FVector(0.f, -50.f, 70.f);
	}
	else {
		RightView = true;
		SpringArm->SocketOffset = FVector(0.f, 50.f, 70.f);
	}
}

void AC_LobbyWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsSprinting) {
		// ĳ���� �����Ʈ ������Ʈ�� Max Speed ���� Sprint_Speed�� �ٲ�
		CharacterMovement->MaxWalkSpeed = Sprint_Speed;
	}
	else {
		// ĳ���� �����Ʈ ������Ʈ�� Max Speed ���� Ori_Speed�� �ٲ�
		CharacterMovement->MaxWalkSpeed = Ori_Speed;
	}
}

void AC_LobbyWarrior::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("K_MoveForward", this, &AC_LobbyWarrior::MoveForward);
	PlayerInputComponent->BindAxis("K_MoveRight", this, &AC_LobbyWarrior::MoveRight);
	PlayerInputComponent->BindAxis("K_LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("K_Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("K_Jump", IE_Pressed, this, &AC_LobbyWarrior::Jumpp);

	PlayerInputComponent->BindAction("K_Sprint", IE_Pressed, this, &AC_LobbyWarrior::ActiveSprint);
	PlayerInputComponent->BindAction("K_Sprint", IE_Released, this, &AC_LobbyWarrior::DeActiveSprint);

	PlayerInputComponent->BindAction("K_SwitchView", IE_Pressed, this, &AC_LobbyWarrior::SwitchView);
}

void AC_LobbyWarrior::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(AC_LobbyWarrior, IsSprinting);
}

void AC_LobbyWarrior::Jumpp() {
	CharacterMovement->DoJump(false);
}
