extends Control

@export var player : Node
@export var inworld_player : InworldPlayer
@export var inworld_character : InworldCharacter

signal player_text(text : String)
signal character_text(text : String)

var talking : bool = false;

func _on_text_input_entered(text : String):
	if inworld_player.target_character != null:
		player_text.emit(text)
		player.send_text(text)
		inworld_player.target_character.send_text(text)

func _on_text_input_recording(recording : bool):
	inworld_player.talking = recording
	if(recording and inworld_player.target_character != null):
		inworld_player.target_character.interrupt()
