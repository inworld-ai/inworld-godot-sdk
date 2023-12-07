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
	mobs = [
		$Godot,
		$Carey,
		$Wilson,
		$Vik,
	]
	$Player.start($PlayerStartPosition.position)
	pass

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
		$Player/InworldPlayer.target_character = $Vik/InworldCharacter
	#else:
		#$Player.clear_conversation_partner()

func _on_inworld_player_target_message_talk(talk: InworldMessageTalk):
	$Interface.set_text($Player/InworldPlayer.target_character.brain, talk.text)
	if(!talk.chunk.is_empty()):
		var audio_wav = AudioStreamWAV.new()
		talk.chunk.decode_u16(0)
		audio_wav.data = talk.chunk;
		audio_wav.format = AudioStreamWAV.FORMAT_16_BITS;
		audio_wav.mix_rate = 16000;
		
		$Interface/AudioStreamPlayer.stream = audio_wav;
		$Interface/AudioStreamPlayer.play();

func _on_audio_stream_player_finished():
	$Player/InworldPlayer.target_character.finish_current_message_talk()


func _on_inworld_player_target_message_stt(stt):
	if (stt.complete):
		$Interface.set_text("Character", stt.text)
