extends Sprite2D

@export var affection_texture : CompressedTexture2D
@export var anger_texture : CompressedTexture2D
@export var belligerence_texture : CompressedTexture2D
@export var contempt_texture : CompressedTexture2D
@export var criticism_texture : CompressedTexture2D
@export var defensiveness_texture : CompressedTexture2D
@export var disgust_texture : CompressedTexture2D
@export var domineering_texture : CompressedTexture2D
@export var humor_texture : CompressedTexture2D
@export var interest_texture : CompressedTexture2D
@export var joy_texture : CompressedTexture2D
@export var neutral_texture : CompressedTexture2D
@export var sadness_texture : CompressedTexture2D
@export var stonewall_texture : CompressedTexture2D
@export var surprise_texture : CompressedTexture2D
@export var tense_texture : CompressedTexture2D
@export var tension_texture : CompressedTexture2D
@export var validation_texture : CompressedTexture2D
@export var whining_texture : CompressedTexture2D

func _ready():
	visible = false

func set_emotion(emotion : String):
	match emotion:
		"Affection":
			texture = affection_texture
		"Anger":
			texture = anger_texture
		"Belligerence":
			texture = belligerence_texture
		"Contempt":
			texture = contempt_texture
		"Criticism":
			texture = criticism_texture
		"Defensiveness":
			texture = defensiveness_texture
		"Disgust":
			texture = disgust_texture
		"Domineering":
			texture = domineering_texture
		"Humor":
			texture = humor_texture
		"Interest":
			texture = interest_texture
		"Joy":
			texture = joy_texture
		"Neutral":
			texture = neutral_texture
		"Sadness":
			texture = sadness_texture
		"Stonewalling":
			texture = stonewall_texture
		"Surprise":
			texture = surprise_texture
		"Tense":
			texture = tense_texture
		"Tension":
			texture = tension_texture
		"Validation":
			texture = validation_texture
		"Whining":
			texture = whining_texture
	visible = true
	$Timer.start()


func _on_timer_timeout():
	visible = false
