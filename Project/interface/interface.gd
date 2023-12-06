extends Control

@export var inworld_player : InworldPlayer
@export var inworld_character : InworldCharacter

signal player_text(text : String)
signal character_text(text : String)

var talking : bool = false;

func _on_text_input_entered(text : String):
	player_text.emit(text)
	inworld_player.target_character.send_text(text)


func _on_text_input_recording(recording : bool):
	inworld_player.talking = recording


func _on_inworld_character_message_emotion(emotion : InworldMessageEmotion):
	print(emotion.behavior + " " + emotion.strength)


func _on_inworld_character_message_trigger(trigger : InworldMessageTrigger):
	print(trigger.name)


func _on_inworld_character_message_control(control : InworldMessageControl):
	if(control.type == "InteractionEnd"):
		print("----------")


func _on_inworld_character_message_stt(stt : InworldMessageSpeechToText):
	print(stt.text)
	if(stt.complete):
		player_text.emit(stt.text)


func _on_inworld_character_talk_queue_next_ready(talk_queue : InworldTalkQueue):
	if(!talking):
		play_message_talk(talk_queue.pop_ready())
	

func _on_audio_stream_player_finished():
	talking = false;
	if(inworld_character.talk_queue.is_next_ready()):
		play_message_talk(inworld_character.talk_queue.pop_ready())

func play_message_talk(talk : InworldMessageTalk):
	if(!talk.text.is_empty()):
		character_text.emit(talk.text)
	if(!talk.chunk.is_empty()):
		talking = true;
		var audio_wav = AudioStreamWAV.new()
		audio_wav.data = talk.chunk;
		audio_wav.format = AudioStreamWAV.FORMAT_16_BITS;
		audio_wav.mix_rate = 16000;
		
		$AudioStreamPlayer.stream = audio_wav;
		$AudioStreamPlayer.play();
