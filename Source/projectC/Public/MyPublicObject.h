// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "MyPublicObject.generated.h"



USTRUCT(BlueprintType)// BlueprintType ������ ��ͼ�� �� �ṹ�����ѡ�� �� MyStruct
struct FMyDateTableStruct: public FTableRowBase // �̳��� ���
{
	GENERATED_BODY()// 

		FMyDateTableStruct();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMyDateTableStruct")//  category Ŀ¼
		float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMyDateTableStruct")//  category Ŀ¼
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMyDateTableStruct")//  category Ŀ¼
		int32  Level;
};
/**
 * 
 */
UCLASS()
class PROJECTC_API UMyPublicObject : public UObject
{
	GENERATED_BODY()

public:
	FMyDateTableStruct MyDateTableStruct;
	
};
