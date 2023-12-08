extends AnimatedSprite2D

@export var speed = 200
@export var player : InworldPlayer

var screen_size : Vector2

func _ready():
	screen_size = get_viewport_rect().size
	screen_size.x -= 64
	screen_size.y -= 64
	screen_size.y -= 56

func _process(delta):
	var velocity = Vector2.ZERO # The player's movement vector.
	if Input.is_action_pressed("move_right"):
		velocity.x += 1
	if Input.is_action_pressed("move_left"):
		velocity.x -= 1
	if Input.is_action_pressed("move_down"):
		velocity.y += 1
	if Input.is_action_pressed("move_up"):
		velocity.y -= 1

	if velocity.length() > 0:
		velocity = velocity.normalized() * speed
		animation = "walk"
		play()
	else:
		animation = "default"
		stop()

	position += velocity * delta
	position = position.clamp(Vector2.ZERO, screen_size)

func set_target(target : InworldCharacter):
	$Speech.text = ""
	player.target_character = target

func send_text(text : String):
	$Speech.text = text
	$Timer.start();

func _on_inworld_player_target_message_stt(stt : InworldMessageSpeechToText):
	$Speech.text = stt.text
	if(stt.complete):
		$Timer.start()

func _on_timer_timeout():
	$Speech.text = ""


func _on_inworld_session_established(established):
	$Name.text = player.name
