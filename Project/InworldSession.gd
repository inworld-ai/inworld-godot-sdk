extends InworldSession


func _ready() -> void:
	start_session()


func _on_got_connected(_node : Node) -> void:
	print("Connected!")
