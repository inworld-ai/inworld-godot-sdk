extends InworldSession

func _ready():
	_on_connection_state_changed(get_connection_state())
	start()



func _on_connection_state_changed(connection_state : InworldSession.ConnectionState):
	match connection_state:
		InworldSession.ConnectionState.IDLE:
			print("Idle")
		InworldSession.ConnectionState.CONNECTING:
			print("Connecting")
		InworldSession.ConnectionState.CONNECTED:
			print("Connected")
		InworldSession.ConnectionState.FAILED:
			print("Failed")
		InworldSession.ConnectionState.DISCONNECTED:
			print("Disconnected")
		InworldSession.ConnectionState.RECONNECTING:
			print("Reconnecting")
