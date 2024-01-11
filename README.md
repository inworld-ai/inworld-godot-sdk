# Inworld Godot SDK
Godot SDK for Inworld.ai. Create more realistic and believable worlds with characters powered by artificial intelligence. 

>  **Support Note**: The Godot SDK is built and maintained by the developer community. 
> Inworld will maintain the basic functionality of initially released features of this SDK, while continuous development
> and new features will be driven by our community. 
> If you're keen on contributing to the Godot SDK, we welcome your involvement! 


## Getting Started

Official documentation on GDExtensions can be found [**here**](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html).

### Self-built
The SDK contains several scripts for building the SDK with scons. They are also provided below for reference:

#### Windows
##### Build debug
build-win.bat
```
scons platform=windows use_static_cpp=False
```
##### Build release
build-win-release.bat
```
scons platform=windows use_static_cpp=False target=template_release
```
##### Clean
clean-win.bat
```
scons --clean
```

#### Mac
##### Build debug
build-mac.sh
```
scons platform=macos
```
##### Build release
build-mac-release.sh
```
scons platform=macos target=template_release
```
##### Clean
clean-mac.sh
```
scons --clean
```

### Pre-built
Building the GDExtension is only required in order to contribute to, or modify, the Godot SDK for Inworld.ai.
To utilize the GDExtension without modification, simply download the release .zip from the latest release: https://github.com/inworld-ai/inworld-godot-sdk/releases/

#### Installation
Extract the .zip file to your Godot project directory.

Edit the .godot file in this directory, and add or modify to include the following:
```
[native_extensions]

paths=["res://addons/inworld/inworld.gdextension"]
```

### Sample project
Included is a sample project to show a quick demo of inworld functionality and usage of the SDK within Godot.

For setup instructions please reference the included ReadMe.md file.

## Nodes
Inworld is utilized in Godot via custom Node types.

Simply add Inworld nodes to a scene, configure their properties, and utilize their functionalities from gdscript.

## Session
The InworldSession Node is responsible for starting and stopping sessions with Inworld.

### Configuration

#### Player (Optional)
If the player property is set before start() is called, the session will register the player properties with the session. This will enable characters from this session to reference the player by their given name.

#### Project Name (Optional)
A unique identifier for your project. Though not required, this will help the inworld support team to identify your sessions.

#### Workspace Name
The name of your [Inworld Studio](https://studio.inworld.ai/) workspace.
> :warning: **Note**: Do not prepend 'workspaces/'. For example if the URL of your Inworld studio workspace is **workspaces/my-godot-workspace-name**, simply enter **my-godot-workspace-name** in this field.

#### Scene Type
The type of scene for the session to use.

Scene: A normal inworld scene. You can configure these scenes from the 'Scenes' tab in your inworld studio workspace.

Single-Character: An automatically generated scene that contains a single character. No scene from the inworld studio workspace is required.

#### Scene Name
The name of a scene in your [Inworld Studio](https://studio.inworld.ai/) workspace.

For scene type, use the name of the desired scene from the 'Scenes' tab in your inworld studio workspace.
> :warning: **Note**: Do not prepend 'scenes/'. For example if the URL of your Inworld studio scene is **workspaces/my-godot-workspace-name/scenes/my-godot-scene**, simply enter **my-godot-scene** in this field.

For single-character type, use the name of the desired character from the 'Characters' tab in your Inworld Studio workspace.
> :warning: **Note**: Do not prepend 'characters/'. For example if the URL of your inworld studio character is **workspaces/my-godot-workspace-name/characters/my-godot-character**, simply enter **my-godot-character** in this field.

#### Auth
The Base64 Authorization Key generated from [Inworld Studio](https://studio.inworld.ai/).

You can generate a key from the 'Integrations' tab in your inworld studio workspace. Under the 'API Keys' section, click '+Generate new key', then click 'Copy Base64'.

### Session Usage

#### Managing Sessions

```func start() -> void``` Start the inworld session.

```func stop() -> void``` Stop the inworld session.

#### Connection State

```
enum ConnectionState {
	IDLE = 0,
	CONNECTING = 1,
	CONNECTED = 2,
	FAILED = 3,
	PAUSED = 4,
	DISCONNECTED = 5,
	RECONNECTING = 6,
};
```

```func get_connection_state() -> ConnectionState``` Get the current connection state.

```signal: connection_state_changed(ConnectionState)``` Emitted when the connection state changes.

```func get_connected() -> bool``` Get if the current connection state is CONNECTED.

```signal: connected(bool)``` Emitted when the connection state changes between CONNECTED and anything other than CONNECTED.

```func get_established() -> bool``` Get if the session has established session info.

```signal: established(bool)``` Emitted when the session establishes or is torn down.

## Character
The InworldCharacter Node is responsible for representing an Inworld character within a session.

### Configuration

#### Brain
The brain of your Inworld character from your [Inworld Studio](https://studio.inworld.ai/) workspace.
> :warning: **Note**: Do not prepend 'characters/'. If the URL of your Inworld Studio character is **workspaces/my-godot-workspace-name/characters/my-godot-character**, simply enter **my-godot-character** in this field.

> :warning: **Note**: Although it is common for the character name and brain to be the same value, the brain name is **not** the name of your character.

#### Given Name (Read-Only)
The brain of your Inworld character from your [Inworld Studio](https://studio.inworld.ai/) workspace.
> :warning: **Note**: This value is read-only, and will be populated when the associated session for the character is established.

#### Session
The session for the character to receive data from.

### Character Usage

#### Text

```func send_text(String text)``` Sends a text message of 'text' to the character.

#### Trigger
```func send_trigger(String name, Dictionary params)``` Sends a trigger of 'name' with parameters 'params' to the character.

#### Audio
```func start_audio_session()``` Starts an audio session with the character.
> :warning: **Note**: Audio session management is automatically handled by the SDK. Only call this if you know what you are doing!

```func stop_audio_session()``` Stops an audio session with the character.
> :warning: **Note**: Audio session management is automatically handled by the SDK. Only call this if you know what you are doing!

```func send_audio(PackedByteArray data)``` Sends PCM 'data' to the character.
> :warning: **Note**: Sending audio data is automatically handled by the SDK. Only call this if you know what you are doing!

### Interrupt
```func interrupt()``` Interrupts the character, will signal 'interrupt' and remove any remaining unprocessed MessageTalk.

```signal interrupt()``` Emitted when the character has been interrupted.

> :warning: **Note**: Characters will be interrupted automatically when send text, sent a trigger, or STT is recognized.

### Character Messages
As data is received from the inworld session, messages will be created and emitted from the character.

#### Message Talk
```signal: message_talk(MessageTalk)``` Emitted when the character has a MessageTalk to process.
> :warning: **Note**: Only one MessageTalk can be processed at a time per character. Call ```func finish_current_message_talk()``` to release the message.

##### Data
```String text``` Text representation of the talk.

```PackedByteArray chunk``` Raw PCM data representation of the talk.

```TypedArray<Viseme> visemes``` Lipsync visemes that represent the raw PCM data.

###### Viseme
```StringName code``` Code of the viseme.

```float time_stamp``` Timestamp of the PCM data that the viseme represents.

#### Message Speech To Text
```signal: message_stt(MessageSpeechToText)``` Emitted when the character has a MessageSpeechToText to process.
> :warning: **Note**: As audio data is received, the player speech will continue to update until a final representation has been determined. It is expected to receieve many partial STT messages before completion.

##### Data
```String text``` Text representation of the players speech.

```bool complete``` If the text representation has been finalized.

#### Message Emotion
```signal: message_emotion(MessageEmotion)``` Emitted when the character has a MessageEmotion to process.

```
enum EmotionBehavior {
	AFFECTION = 0,
	ANGER = 1,
	BELLIGERENCE = 2,
	CONTEMPT = 3,
	CRITICISM = 4,
	DEFENSIVENESS = 5,
	DISGUST = 6,
	DOMINEERING = 7,
	HUMOR = 8,
	INTEREST = 9,
	JOY = 10,
	NEUTRAL = 11,
	SADNESS = 12,
	STONEWALLING = 13,
	SURPRISE = 14,
	TENSE = 15,
	TENSION = 16,
	VALIDATION = 17,
	WHINING = 18,
};
```

```
enum EmotionStrength {
	WEAK = 0,
	NORMAL = 1,
	STRONG = 2,
};
```

##### Data
```EmotionBehavior behavior``` Type of emotion that the character is feeling.

```EmotionStrength strength``` The strength of the type of emotion that the charcter is feeling.

#### Message Trigger
```signal: message_trigger(MessageTrigger)``` Emitted when the character has a MessageTrigger to process.

##### Data
```String name``` Name of the trigger.

```Dictionary params``` Parameters of the trigger.

## Player
The InworldPlayer Node is responsible for allowing the player to interface with inworld characters.

### Configuration

#### Given Name
The name of the player. If an Inworld session is configured with this player before it is started, characters in the session will refer to the player by this name.

#### Target Character
The Inworld character that the player has targeted. If the player is talking, audio data will be routed to this character.

#### Talking
If the microphone audio should be forwarded to the target character if available.

#### Conversing
```signal conversing_start(InworldCharacter)``` Emitted when the player has selected the character as a target.

```signal conversing_stop(InworldCharacter)``` Emitted when the player has deselected the character as a target.
