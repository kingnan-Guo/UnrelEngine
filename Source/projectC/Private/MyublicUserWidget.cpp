// Fill out your copyright notice in the Description page of Project Settings.


#include "MyublicUserWidget.h"

bool UMyublicUserWidget::Initialize(){
    if(!Super::Initialize()){// 是否继承父类的初始化
        return false;
    }

    myButtonStart->OnClicked.AddDynamic(this, &UMyublicUserWidget::myButtonStartClicked);
    myButtonQuit->OnClicked.AddDynamic(this, &UMyublicUserWidget::myButtonQuitClicked);
    return true;
}



void UMyublicUserWidget::myButtonStartClicked(){
    UE_LOG(LogTemp, Warning, TEXT("Start Button Clicked"));

}


void UMyublicUserWidget::myButtonQuitClicked(){
    UE_LOG(LogTemp, Warning, TEXT("Quit Button Clicked"));
}