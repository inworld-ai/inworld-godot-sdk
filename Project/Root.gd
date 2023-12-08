extends Node

var mobs : Array
var current_mob : Node

# Called when the node enters the scene tree for the first time.
func _ready():
	mobs = [
		$Russ,
		$Carey,
		$Wilson,
		$Vik,
	]

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	var player_pos = $Player.position as Vector2
	var closest_mob = null
	var max_dist = 1000000000
	var dist
	for m in mobs:
		var m_pos = m.position
		dist = player_pos.distance_to(m.position)
		if dist < max_dist && dist < 150:
			closest_mob = m
			max_dist = dist
	
	if (current_mob != closest_mob and closest_mob != null):
		if(current_mob != null):
			current_mob.texture = current_mob.unselected_texture;
		current_mob = closest_mob
		current_mob.texture = current_mob.selected_texture;
		$Player.set_target(closest_mob.get_node("InworldCharacter"))
	
	if closest_mob == null:
		if(current_mob != null):
			current_mob.character.interrupt()
			current_mob.texture = current_mob.unselected_texture
		current_mob = null;
		$Player.set_target(null)
