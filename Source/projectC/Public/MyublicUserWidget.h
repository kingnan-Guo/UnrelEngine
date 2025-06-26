// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h" // 按钮 组件
#include "MyublicUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API UMyublicUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* myButtonStart;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* myButtonQuit;

		virtual bool Initialize() override; // 初始化 返回临时布尔值


		UFUNCTION()
		void myButtonStartClicked(); // 按钮点击事件
		UFUNCTION()
		void myButtonQuitClicked(); // 按钮点击事件



		// 创建进度条
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyProgressBar")
			float myProgressBarValue = 100.0f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyProgressBar")
			float myProgressBarMaxValue = 100.0f;
		UFUNCTION()
			void UpdateProgressBarValue(); // 按钮点击事件

};
