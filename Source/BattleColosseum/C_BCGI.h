// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "C_BCGI.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API UC_BCGI : public UGameInstance
{
	GENERATED_BODY()
	
public:		// ����

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString SAVEGAME;

public:		// �Լ�
	UC_BCGI();
};
