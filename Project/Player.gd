extends Sprite2D

@export var speed = 200

@export var player : InworldPlayer

var screen_size : Vector2

# Called when the node enters the scene tree for the first time.
func _ready():
	screen_size = get_viewport_rect().size
	screen_size.x -= 64
	screen_size.y -= 64

# Called every frame. 'delta' is the elapsed time since the previous frame.
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
		
	position += velocity * delta
	position = position.clamp(Vector2.ZERO, screen_size)

func set_target(target : InworldCharacter):
	$Label.text = ""
	player.target_character = target

func send_text(text : String):
	$Label.text = text
	$Timer.start();
	

func _on_inworld_player_target_message_stt(stt : InworldMessageSpeechToText):
	$Label.text = stt.text
	if(stt.complete):
		$Timer.start()


func _on_timer_timeout():
	$Label.text = ""
