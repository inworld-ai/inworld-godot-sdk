extends Control

signal player_text(text : String)

func _on_text_input_entered(text : String):
	player_text.emit(text)
