extends Control

@export var line_edit : LineEdit

signal entered(text : String)


func _on_send_button_pressed() -> void:
	entered.emit(line_edit.text)
	line_edit.clear()
