extends Control

@export var inworld_player : InworldPlayer

signal player_text(text : String)
signal character_text(text : String)
signal character_audio(audio : String)


func _on_text_input_entered(text : String):
	player_text.emit(text)
	inworld_player.target_character.send_text(text)


func _on_inworld_got_text(text : String):
	print("TEXT")
	character_text.emit(text)

func _on_inworld_got_audio(audioData : PackedByteArray):
	print("AUDIO")
	var audio_wav = AudioStreamWAV.new()

	audio_wav.data = audioData;
	audio_wav.format = AudioStreamWAV.FORMAT_16_BITS;
	audio_wav.mix_rate = 22000;
	
	$AudioStreamPlayer.stream = audio_wav;
	$AudioStreamPlayer.play();

