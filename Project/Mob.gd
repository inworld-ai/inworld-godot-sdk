extends Area2D

@export var inworld_session: InworldSession
@export var inworld_character: InworldCharacter
var mobs

func set_session(session: InworldSession, characterName: String):
	inworld_session = session
	$MobCharacter.session = session
	var brain_parts = []
	var workspace = session.scene.split("/")[1]
	var brain = "workspaces/" + workspace + "godot/characters/" + characterName
	$MobCharacter.brain = "/".join(brain_parts)
	inworld_character = $MobCharacter

	

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_mob_character_message_talk(talk):
	pass # Replace with function body.
