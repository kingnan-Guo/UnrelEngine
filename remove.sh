# # 1. 关闭所有UE和VS实例
# # 2. 删除项目目录中的：
# rm -rf Binaries/
# rm -rf Intermediate/
# rm -rf Saved/
# rm -rf .vs/

# # 3. 删除引擎缓存（Windows路径）：
# del /s /q "%LOCALAPPDATA%\UnrealEngine\DerivedDataCache\*.*"

# # 4. 重新生成项目文件：
# #    - 右键点击 .uproject 文件
# #    - 选择 "Generate Visual Studio Project Files"

# # 5. 在VS中重新编译：
# #    - 打开 .sln 文件
# #    - 选择 "Development Editor" 配置
# #    - 编译解决方案 (F7)


rm -r -fo Binaries, Intermediate, Saved, .vs, *.sln, *.vcxproj*, *.opendb

# 删除引擎全局缓存：
rm -r -fo "$env:LOCALAPPDATA\UnrealEngine\DerivedDataCache\*"
rm -r -fo "$env:LOCALAPPDATA\UnrealBuildTool\*"