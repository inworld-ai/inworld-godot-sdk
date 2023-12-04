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

func _on_inworld_got_audio(audioDataBase64 : String):
	print("AUDIO")
	#var audio_wav = AudioStreamWAV.new()
	##var audioData = Marshalls.base64_to_raw(audioDataBase64);
	#var crypto = Crypto.new()
	#var audioData = crypto.decode_base64_to_array(audioDataBase64);
	#audio_wav.data = audioData
	#audio_wav.format = AudioStreamWAV.FORMAT_16_BITS;
	#
	#$AudioStreamPlayer.stream = audio_wav;
	#$AudioStreamPlayer.play();
