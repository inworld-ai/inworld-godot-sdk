extends Area2D
@export var myName: String
@export var character: InworldCharacter
var mobs

var talking : bool = false;


signal character_text(text: String)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _on_mob_character_message_trigger(trigger):
	print(trigger.name)

func _on_mob_character_message_emotion(emotion):
	print(emotion.behavior + " " + emotion.strength)

func _on_mob_character_message_control(control):
	if(control.type == "InteractionEnd"):
		print("----------")
	
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


func _on_mob_character_talk_queue_next_ready(talk_queue):
	if(!talking):
		play_message_talk(talk_queue.pop_ready())

func _on_mob_character_message_talk(talk):
	print("HERE")


