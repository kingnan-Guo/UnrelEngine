// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProductObject.generated.h"

/**
 * 当前这个是 父类 所以准备写成 抽象接口 
 * 
 * UCLASS() 改成 UCLASS(Abstract) 抽象类
 */
UCLASS(Abstract)// 抽象类
class PROJECTC_API UProductObject : public UObject
{
	GENERATED_BODY()
	

public:
	// virtual void Product();
	virtual void ShowInfo(){
		UE_LOG(LogTemp, Warning, TEXT("ProductObject ShowInfo"));
	};




};
