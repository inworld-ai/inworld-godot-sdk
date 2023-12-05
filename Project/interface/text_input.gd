extends Control

@export var line_edit : LineEdit

signal entered(text : String)
signal recording()
signal stop_recording()


func _on_send_button_pressed() -> void:
	entered.emit(line_edit.text)
	line_edit.clear()

func _on_record_button_down():
	recording.emit()

func _on_record_button_up():
	stop_recording.emit()
