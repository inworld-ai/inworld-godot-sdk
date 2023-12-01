extends InworldSession

func _ready():
	_on_connection_state_changed(get_connection_state())
	start()



func _on_connection_state_changed(connection_state : ConnectionState):
	print(connection_state)
