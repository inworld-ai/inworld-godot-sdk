# Inworld Godot SDK
Godot SDK for Inworld.ai. Create more realistic and believable worlds with characters powered by artificial intelligence. 

## Building the GDExtension
For official docs on GDExtensions please reference https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html

### Prerequisites
- Godot 4.2
- Scons

### Windows
#### Build debug
build-win.bat
```
scons platform=windows use_static_cpp=False
```
#### Build release
build-win-release.bat
```
scons platform=windows use_static_cpp=False target=template_release
```
#### Clean
clean-win.bat
```
scons --clean
```

### MacOS
#### Build debug
build-mac.sh
```
scons platform=macos
```
#### Build release
build-mac-release.sh
```
scons platform=macos target=template_release
```
#### Clean
clean-mac.sh
```
scons --clean
```

## Pre-built
Building the GDExtension is only required in order to contribute to, or modify, the Godot SDK for Inworld.ai.
To utilize the GDExtension without modification, simply download the release .zip from the latest release: https://github.com/inworld-ai/inworld-godot-sdk/releases/

### Installation
Extract the .zip file to your Godot project directory.

Edit the .GODOT file in this directory, and add or modify to include the following:
```
[native_extensions]

paths=["res://addons/inworld/inworld.gdextension"]
```

## Sample project
Included is a sample project to show a quick demo of inworld functionality and usage of the SDK within Godot.

For setup instructions please reference the included ReadMe.md file.