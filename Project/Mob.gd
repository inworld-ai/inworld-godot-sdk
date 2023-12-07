extends Area2D

@export var inworld_session: InworldSession
@export var inworld_character: InworldCharacter
@export var myName: String
var mobs

var talking : bool = false;


signal character_text(text: String)

func set_session(session: InworldSession, characterName: String):
	inworld_session = session
	$MobCharacter.session = session
	myName = characterName
	var brain_parts = []
	var workspace = session.scene.split("/")[1]
	var brain = "workspaces/" + workspace + "godot/characters/" + characterName
	$MobCharacter.brain = "/".join(brain_parts)
	inworld_character = $MobCharacter

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

func _on_character_text(text):
	print("HERE")
	$TextOutput.add_text(myName, text)
