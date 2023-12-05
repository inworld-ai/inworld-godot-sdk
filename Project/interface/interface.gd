extends Control

@export var inworld_player : InworldPlayer

signal player_text(text : String)
signal character_text(text : String)


func _on_text_input_entered(text : String):
	player_text.emit(text)
	inworld_player.target_character.send_text(text)


func _on_inworld_character_message_talk(talk : InworldMessageTalk):
	if(!talk.text.is_empty()):
		character_text.emit(talk.text)


func _on_inworld_character_message_emotion(emotion : InworldMessageEmotion):
	print(emotion.behavior + " " + emotion.strength)



func _on_inworld_character_message_trigger(trigger : InworldMessageTrigger):
	print(trigger.name)


func _on_inworld_character_message_control(control : InworldMessageControl):
	if(control.type == "InteractionEnd"):
		print("----------")
