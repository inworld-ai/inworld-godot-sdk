extends Control

@export var inworld_player : InworldPlayer

signal player_text(text : String)
signal character_text(text : String)

var effect : AudioEffectCapture
var recording

func _ready():
	var idx = AudioServer.get_bus_index("Listen")
	effect = AudioServer.get_bus_effect(idx, 0) as AudioEffectCapture

func _on_text_input_entered(text : String):
	player_text.emit(text)
	inworld_player.target_character.send_text(text)


func _on_inworld_got_text(text : String):
	character_text.emit(text)

func _process(delta):
	if $Listen.is_current():
		var num_frames = effect.get_buffer_length_frames()
		var buf = effect.get_buffer(effect.get_frames_available())
		inworld_player.target_character.send_audio(buf)
		
		#effect.clear_buffer()

func _on_text_input_recording():
	$Listen.make_current()
	inworld_player.target_character.start_audio_session()

func _on_text_input_stop_recording():
	$Listen.clear_current()
	inworld_player.target_character.stop_audio_session()
