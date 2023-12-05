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

func _process(delta):
	if $Listen.is_current():
		
		var total = effect.get_buffer_length_frames()
		var left = effect.get_frames_available()
		#print(total, " ", left, " ", total - left)
	
		if effect.can_get_buffer(total - left):
			var buf = effect.get_buffer(total - left);
			print(buf.size())
			effect.clear_buffer()
			inworld_player.target_character.send_audio(buf)

func _on_text_input_recording():
	if $Listen.is_current() == false:
		print("Starting audio session")
		$MicListener.autoplay = true
		$Listen.make_current()
		inworld_player.target_character.start_audio_session()

func _on_text_input_stop_recording():
	$Listen.clear_current()
	inworld_player.target_character.stop_audio_session()

func _on_inworld_character_message_talk(talk : InworldMessageTalk):
	if(!talk.text.is_empty()):
		character_text.emit(talk.text)
		
	if(!talk.chunk.is_empty()):
		var audio_wav = AudioStreamWAV.new()

		audio_wav.data = talk.chunk;
		audio_wav.format = AudioStreamWAV.FORMAT_16_BITS;
		audio_wav.mix_rate = 22000;
		
		$AudioStreamPlayer.stream = audio_wav;
		$AudioStreamPlayer.play();


func _on_inworld_character_message_emotion(emotion : InworldMessageEmotion):
	print(emotion.behavior + " " + emotion.strength)


func _on_inworld_character_message_trigger(trigger : InworldMessageTrigger):
	print(trigger.name)


func _on_inworld_character_message_control(control : InworldMessageControl):
	if(control.type == "InteractionEnd"):
		print("----------")
