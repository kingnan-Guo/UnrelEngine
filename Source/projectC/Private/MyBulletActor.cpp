// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBulletActor.h"

// Sets default values
AMyBulletActor::AMyBulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the mesh component
	myBulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("myBulletMeshComponent"));
	myBulletSphere = CreateDefaultSubobject<USphereComponent>(TEXT("myBulletSphereComponent"));
	myBulletMove = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("myBulletMoveComponent"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> myMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	myBulletMesh->SetStaticMesh(myMeshAsset.Object);// 设置静态网格组件的静态网格
	myBulletMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));// 设置相对缩放

	// 根组件
	RootComponent = myBulletMesh;
	myBulletSphere->SetupAttachment(myBulletMesh);// 将球体组件附加到静态网格组件上
	myBulletSphere->SetSphereRadius(10.f);// 设置球体半径
	myBulletMove->SetUpdatedComponent(myBulletMesh);// 将移动组件附加到静态网格组件上; SetUpdatedComponent 是 设置移动组件的更新组件


	// 设置移动组件的移动速度
	myBulletMove->InitialSpeed = 1000.f;
	myBulletMove->MaxSpeed = 2000.f;
	myBulletMove->ProjectileGravityScale = 0.f;// 设置重力影响
	myBulletMove->bRotationFollowsVelocity = true;// 设置旋转跟随速度
	myBulletMove->bIsHomingProjectile = true;// 设置是否为追踪弹 ,跟随组件设为真
}

// Called when the game starts or when spawned
void AMyBulletActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

