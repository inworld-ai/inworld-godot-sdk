extends Node

var mobs
var characters = [
	"godot",
	"carey",
	"wilson",
	"vik"
]
var current_name: String

# Called when the node enters the scene tree for the first time.
func _ready():
	$Player.start($PlayerStartPosition.position)
	mobs = [$Godot, $Carey, $Wilson, $Vik]
	for i in range(len(mobs)):
		mobs[i].set_session($InworldSession, characters[i])
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	var player_pos = $Player.position as Vector2
	var closest_mob = null
	var max_dist = 1000000000
	var dist
	for m in mobs:
		var m_pos = m.position
		dist = player_pos.distance_to(m.position)
		if dist < max_dist:
			closest_mob = m
			max_dist = dist
	if max_dist < 150 and (current_name != closest_mob.myName or current_name == null):
		print("Setting partner to: " + closest_mob.myName)
		current_name = closest_mob.myName
		$Player.set_conversation_partner(closest_mob.inworld_character)
	else:
		$Player.clear_conversation_partner()
		
