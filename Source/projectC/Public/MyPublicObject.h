// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "MyPublicObject.generated.h"



USTRUCT(BlueprintType)// BlueprintType 可以在 蓝图中 的 结构体可以选择 此 MyStruct
struct FMyDateTableStruct: public FTableRowBase // 继承于 表格
{
	GENERATED_BODY()// 

		FMyDateTableStruct();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMyDateTableStruct")//  category 目录
		float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMyDateTableStruct")//  category 目录
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMyDateTableStruct")//  category 目录
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
