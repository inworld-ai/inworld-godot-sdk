extends CharacterBody2D

@export var session : InworldSession = null
@export var brain : String = ""

@export var unselected_texture : CompressedTexture2D = null
@export var selected_texture : CompressedTexture2D = null

var conversing_player : InworldPlayer = null

func _ready():
	$Sprite2D.texture = unselected_texture
	$InworldCharacter.brain = brain
	$InworldCharacter.session = session
	session.established.connect(_on_inworld_session_established)
	_on_inworld_session_established(session.get_established())

func _process(_delta : float):
	if conversing_player != null:
		if conversing_player.get_parent().position.x < position.x:
			$Sprite2D.scale.x = -1.0
		else:
			$Sprite2D.scale.x = 1.0

func _on_inworld_session_established(_established : bool):
	$Name.text = $InworldCharacter.given_name

func _on_inworld_character_message_talk(talk : InworldMessageTalk):
	$Speech.text = talk.text
	
	var audio_wav = AudioStreamWAV.new()
	audio_wav.data = talk.chunk;
	audio_wav.format = AudioStreamWAV.FORMAT_16_BITS;
	# Inworld sends audio data at 22.05k sample rate
	audio_wav.mix_rate = 22050;
		
	$AudioStreamPlayer2D.stream = audio_wav;
	$AudioStreamPlayer2D.play();


func _on_audio_stream_player_2d_finished():
	$Speech.text = ""
	$InworldCharacter.finish_current_message_talk()


func _on_inworld_character_interrupted():
	$Speech.text = ""
	$AudioStreamPlayer2D.stop()


func _on_inworld_character_message_emotion(emotion : InworldMessageEmotion):
	$Emoji.set_emotion(emotion.behavior)


func _on_inworld_character_conversing_start(player : InworldPlayer):
	conversing_player = player
	$Sprite2D.texture = selected_texture


func _on_inworld_character_conversing_stop(_player : InworldPlayer):
	conversing_player = null
	$Sprite2D.texture = unselected_texture
