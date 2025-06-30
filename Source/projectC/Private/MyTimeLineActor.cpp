// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTimeLineActor.h"

// Sets default values
AMyTimeLineActor::AMyTimeLineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	myTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("UTimelineComponent"));

	// 创建默认对象
	myScene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	myStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	myBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> TempStaticMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Architecture/Wall_400x400.Wall_400x400'"));
	if (TempStaticMeshAsset.Succeeded()) {
	    // 设置模型
		myStaticMesh->SetStaticMesh(TempStaticMeshAsset.Object);

	}

	RootComponent = myScene;// 设置根组件
	myStaticMesh->SetupAttachment(myScene);// 设置子组件
	myBox->SetupAttachment(myScene);// 设置子组件

	// 设置碰撞体
	myBox->SetBoxExtent(FVector(600, 200, 400));

	// 设置相对位置
	myStaticMesh->SetRelativeLocation(FVector(0, 0, 0));




}

// Called when the game starts or when spawned
void AMyTimeLineActor::BeginPlay()
{
	Super::BeginPlay();


	TimelineDelegate.BindUFunction(this, FName("TimelineStart"));// 绑定函数
	TimelineEventFinishedDelegate.BindUFunction(this, FName("TimelineEnd"));

	// 设置 浮点曲线
	myTimeline->AddInterpFloat(myCurve, TimelineDelegate);
	// myTimeline->SetLooping(false);
	// myTimeline->PlayFromStart();// 播放时间线
	// myTimeline->Play();
	myTimeline->SetTimelineFinishedFunc(TimelineEventFinishedDelegate);// 时间线结束的回调函数




    // 绑定碰撞事件
	myBox->OnComponentBeginOverlap.AddDynamic(this, &AMyTimeLineActor::BeginOverLapFunction);
	myBox->OnComponentEndOverlap.AddDynamic(this, &AMyTimeLineActor::EndOverLapFunction);


}

// Called every frame
void AMyTimeLineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AMyTimeLineActor::TimelineStart(float Value){
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("TimelineStart: %f"), Value));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("TimelineStart"));
	// 在Z 轴 上的旋转
	// float YawRotation = FMath::Lerp(0, 90, Value);// 插值
	// myStaticMesh->SetRelativeRotation(FRotator(0, YawRotation, 0));
}


void AMyTimeLineActor::TimelineEnd(float Value){
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("TimelineStart"));
}



void AMyTimeLineActor::BeginOverLapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("AMyTimeLineActor BeginOverLapFunction"));


	AMyPublicCharacter* myTempCharacter = Cast<AMyPublicCharacter>(OtherActor);// 获取角色; OtherActor 是 碰撞的物体
	// 这里是如何 获取角色，如何判定 是 碰撞到了
	if (myTempCharacter) {// 
	    myTimeline->PlayFromStart();// 播放时间线
	}
	


}
void AMyTimeLineActor::EndOverLapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("AMyTimeLineActor EndOverLapFunction"));
	AMyPublicCharacter* myTempCharacter = Cast<AMyPublicCharacter>(OtherActor);// 获取角色; OtherActor 是 碰撞的物体
	if (myTempCharacter) {// 
	    myTimeline->ReverseFromEnd();// 播放时间线
	}
}

