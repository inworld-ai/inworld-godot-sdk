extends Sprite2D

@export var character: InworldCharacter

@export var unselected_texture : CompressedTexture2D
@export var selected_texture : CompressedTexture2D


func _on_inworld_character_message_talk(talk : InworldMessageTalk):
	$Label.text = talk.text
	
	var audio_wav = AudioStreamWAV.new()
	audio_wav.data = talk.chunk;
	audio_wav.format = AudioStreamWAV.FORMAT_16_BITS;
	audio_wav.mix_rate = 22000;
		
	$AudioStreamPlayer2D.stream = audio_wav;
	$AudioStreamPlayer2D.play();


func _on_audio_stream_player_2d_finished():
	$Label.text = ""
	character.finish_current_message_talk()


func _on_inworld_character_interrupted():
	$Label.text = ""
	$AudioStreamPlayer2D.stop()
