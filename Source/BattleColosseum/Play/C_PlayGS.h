// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "C_PlayGS.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API AC_PlayGS : public AGameStateBase
{
	GENERATED_BODY()

public: // ����
	float ms;
	int sec;
	int min;
	int hour;

	bool start;

public: // �Լ�
	AC_PlayGS();

	virtual void Tick(float DeltaSeconds) override;

};
