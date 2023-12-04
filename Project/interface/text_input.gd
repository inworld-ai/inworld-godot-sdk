extends Control

@export var line_edit : LineEdit

signal entered(text : String)
signal recording()
signal stop_recording()


func _on_send_button_pressed() -> void:
	entered.emit(line_edit.text)
	line_edit.clear()


func _on_record_button_pressed():
	if $HBoxContainer/Record.disabled == true:
		stop_recording.emit()
		$HBoxContainer/Record.disabled = false
	else:
		recording.emit()
		$HBoxContainer/Record.disabled = true
