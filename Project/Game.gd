extends Node

@export var max_converse_distance : float = 128.0

@onready var characters : Array[CharacterBody2D] = [
		$Wizard,
		$Rogue,
		$Viking,
		$Knight,
	]
var current_character : CharacterBody2D = null

func _ready():
	$InworldSession.player = $Player/InworldPlayer
	$InworldSession.start()

func _process(_delta):
	var player_pos = $Player.position as Vector2
	var closest_character : CharacterBody2D = null
	var closest_character_distance : float = INF
	for character in characters:
		var character_distance : float = player_pos.distance_to(character.position)
		if character_distance < closest_character_distance && character_distance < max_converse_distance:
			closest_character = character
			closest_character_distance = character_distance
	
	if current_character == closest_character:
		return

	if current_character != null:
		current_character.get_node("InworldCharacter").interrupt()

	current_character = closest_character

	if current_character == null:
		$Player/InworldPlayer.target_character = null
	else:
		$Player/InworldPlayer.target_character = current_character.get_node("InworldCharacter")


func _on_inworld_session_connection_state_changed(connection_state):
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

func _on_interface_player_text(text : String):
	$Player.send_text(text)
