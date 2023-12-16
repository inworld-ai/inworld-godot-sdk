extends Control

signal entered(text : String)

func _on_send_button_pressed() -> void:
	entered.emit($HBoxContainer/LineEdit.text)
	$HBoxContainer/LineEdit.clear()
