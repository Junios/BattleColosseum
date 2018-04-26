// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Components/InputComponent.h"
#include "Classes/GameFramework/CharacterMovementComponent.h"
#include "ConstructorHelpers.h"
#include "C_Warrior.generated.h"


UCLASS()
class BATTLECOLOSSEUM_API AC_Warrior : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Warrior();

protected:
	// ������Ʈ
	class USpringArmComponent* springArm;
	class UCameraComponent* cam;

	// ������
	bool IsSprinting;									// �ٱ� �Ҹ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SprintRate;									// �ٱ� ����
	float Ori_Speed;									// ���� �ӵ�
	float Sprint_Speed;									// ���� �ӵ�
	bool RightView;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SexMan;										// ����(�⺻�� : ����)
	class USkeletalMesh* ManMesh;
	class USkeletalMesh* WomanMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// �Լ���
		// �Է� ���� �ൿ �Լ�
	void MoveForward(float Value);						// ������ ����
	void MoveRight(float Value);						// ������ ����
	void ActiveSprint();								// �ٱ� Ȱ��ȭ
	void DeActiveSprint();								// �ٱ� ��Ȱ��ȭ
	void SwitchView();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
