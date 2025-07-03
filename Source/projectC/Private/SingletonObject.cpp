// Fill out your copyright notice in the Description page of Project Settings.


#include "SingletonObject.h"



USingletonObject* USingletonObject::SingletonObjectInstance = nullptr;// 初始化为空指针
USingletonObject* USingletonObject::GetSingletonObjectInstance(){
    if(SingletonObjectInstance == nullptr){
        SingletonObjectInstance = NewObject<USingletonObject>();
    }
    return SingletonObjectInstance;
}








void USingletonObject::SetValue(int32 value){
    Value = value;
};

int32 USingletonObject::GetValue(){
    return Value;
}