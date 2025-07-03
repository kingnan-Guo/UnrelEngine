# UnrelEngine
UnrelEngine5

























# 文档
https://dev.epicgames.com/documentation/zh-cn/unreal-engine/setting-up-visual-studio-code-for-unreal-engine

.vscode\c_cpp_properties.json

windows 10 
```json
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