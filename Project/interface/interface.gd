extends Control

@export var inworld_character : InworldCharacter

signal player_text(text : String)
signal character_text(text : String)


func _on_text_input_entered(text : String):
	player_text.emit(text)
	inworld_character.send_text(text)


func _on_inworld_got_text(text : String):
	character_text.emit(text)
