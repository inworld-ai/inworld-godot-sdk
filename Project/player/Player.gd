extends CharacterBody2D

@export var given_name : String = "Player"
@export var talking : bool = false

@export var speed : float = 256.0


func _ready():
	$InworldPlayer.given_name = given_name
	$InworldPlayer.talking = talking

func _physics_process(_delta):
	velocity = Vector2.ZERO
	if Input.is_action_pressed("move_right"):
		velocity.x += 1
	if Input.is_action_pressed("move_left"):
		velocity.x -= 1
	if Input.is_action_pressed("move_down"):
		velocity.y += 1
	if Input.is_action_pressed("move_up"):
		velocity.y -= 1

	if(velocity.x < 0):
		$AnimatedSprite2D.scale.x = -1.0
	elif (velocity.x > 0):
		$AnimatedSprite2D.scale.x = 1.0
		
	if velocity.length() > 0:
		velocity = velocity.normalized() * speed
		$AnimatedSprite2D.animation = "walk"
		$AnimatedSprite2D.play()
	else:
		$AnimatedSprite2D.animation = "default"
		$AnimatedSprite2D.stop()

	move_and_slide()

func send_text(text : String):
	if $InworldPlayer.target_character != null:
		$InworldPlayer.target_character.send_text(text)
	$Speech.text = text
	$Timer.start();

func _on_timer_timeout():
	$Speech.text = ""

func _on_inworld_session_established(_established : bool):
	$Name.text = $InworldPlayer.given_name

func _on_inworld_player_conversing_start(character : InworldCharacter):
	character.message_stt.connect(_on_inworld_player_target_message_stt)

func _on_inworld_player_conversing_stop(character : InworldCharacter):
	character.message_stt.disconnect(_on_inworld_player_target_message_stt)

func _on_inworld_player_target_message_stt(stt : InworldMessageSpeechToText):
	$Speech.text = stt.text
	if(stt.complete):
		$Timer.start()
