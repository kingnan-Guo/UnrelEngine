UHT 
会收集 头文件数据
当头文件发生变化，头文件会 重新生成 新的 函数数据

#include "MyPublicActor.generated.h"  // 存储反射信息 的数据

生成反射信息的数据 是同 UHT 和 UBT


反射数据是 ？







# 20 GameInstance 初始化
GameInstance 全局唯一单例，这个引擎初始化的时候 就已经是创建了，一直到引擎关闭
保存 全局 临时 数据， 持久化保存要用 SaveGame



# 21 Actor 添加组件初始化
Actor 是构成 世界的 所有元素，在这之上游戏的运行规则 和抽象实例

在蓝图中创建Actor 和




# 22 静态加载类和资源
静态加载资源  
```C

static ConstructorHelpers::FObjectFinder<UStaticMesh> TempStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));

```
静态加载资源类


# 26. AddActorLocalOffset 和 AddActorWorldOffset

AddActorLocalOffset 是相对于 Actor 的位置偏移,本地坐标偏移
AddActorWorldOffset 是相对于 世界坐标偏移


# 27. BeginOverlap 和 EndOverlap 事件 代理绑定
BeginOverlap

EndOverlap
 物体和另一个物体重叠之后 就产生这个响应 


# 28.虚幻C++Hit事件的代理绑定 
Hit 事件代理绑定，两个物体 表面接触 就会 产生 hit

# 29 碰撞设置



# 31.虚幻C++创建UserWidget并且绑定Button点击事件






# 33.虚幻C++单播代理
代理 监听可以分发数据
Source\projectC\Public\MyPublicDelegateActor.h
# 34.虚幻C++多播代理

Source\projectC\Public\MyPublicDelegateActor.h

# 35.虚幻C++动态多播代理
动态多播代理 区别在于 可以暴露给蓝图,在蓝图中进行 时间的绑定

# 36.虚幻C++子弹类型设置 
Source\projectC\Private\MyBulletActor.cpp
Content\NewBlueprint_bullet_Actor.uasset



# 37.虚幻C++创建Characte添加增强输入
















# 文档

https://dev.epicgames.com/documentation/zh-cn/unreal-engine/setting-up-visual-studio-code-for-unreal-engine

















```json
.vscode\c_cpp_properties.json

{
    "configurations": [
        {
            "name": "projectCEditor Editor Win64 Development (projectC)",
            "compilerPath": "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.43.34808\\bin\\Hostx64\\x64\\cl.exe",
            "cStandard": "c17",
            "cppStandard": "c++20",
            "intelliSenseMode": "msvc-x64",
            "compileCommands": [
                "D:\\work\\Unreal Projects\\projectC\\.vscode\\compileCommands_projectC.json"
            ],
			"includePath": [
				"${workspaceFolder}\\Intermediate\\**",
				"${workspaceFolder}\\Plugins\\**",
				"${workspaceFolder}\\Source\\**"
			],
			"defines": [ 
				"UNICODE", 
				"_UNICODE", 
				"__UNREAL__", 
				"UBT_COMPILED_PLATFORM=Windows", 
				"WITH_ENGINE=1", 
				"WITH_UNREAL_DEVELOPER_TOOLS=1", 
				"WITH_APPLICATION_CORE=1", 
				"WITH_COREUOBJECT=1" 
			] 
        },
        {
            "name": "Win32",
            "compilerPath": "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.43.34808\\bin\\Hostx64\\x64\\cl.exe",
            "cStandard": "c17",
            "cppStandard": "c++20",
            "intelliSenseMode": "msvc-x64",
            "compileCommands": [
                "D:\\work\\Unreal Projects\\projectC\\.vscode\\compileCommands_Default.json"
            ]
        }
    ],

    "version": 4
}

```