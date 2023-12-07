extends Control

@export var inworld_player : InworldPlayer
@export var inworld_character : InworldCharacter

signal player_text(text : String)
signal character_text(text : String)

var talking : bool = false;

func _on_text_input_entered(text : String):
	player_text.emit(text)
	inworld_player.target_character.send_text(text)

func _on_inworld_character_message_stt(stt : InworldMessageSpeechToText):
	print(stt.text)
	if(stt.complete):
		player_text.emit(stt.text)
