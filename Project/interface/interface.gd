extends Control

@export var inworld : InworldSession

signal player_text(text : String)
signal character_text(text : String)


func _ready() -> void:
	inworld.got_text.connect(_on_inworld_got_text)


func _on_text_input_entered(text : String):
	inworld.send_text(text)
	player_text.emit(text)


func _on_inworld_got_text(_node : Node, text : String):
	character_text.emit(text)
