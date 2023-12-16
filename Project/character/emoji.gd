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

func set_emotion(emotion : InworldCharacter.EmotionBehavior):
	match emotion:
		InworldCharacter.EmotionBehavior.AFFECTION:
			texture = affection_texture
		InworldCharacter.EmotionBehavior.ANGER:
			texture = anger_texture
		InworldCharacter.EmotionBehavior.BELLIGERENCE:
			texture = belligerence_texture
		InworldCharacter.EmotionBehavior.CONTEMPT:
			texture = contempt_texture
		InworldCharacter.EmotionBehavior.CRITICISM:
			texture = criticism_texture
		InworldCharacter.EmotionBehavior.DEFENSIVENESS:
			texture = defensiveness_texture
		InworldCharacter.EmotionBehavior.DISGUST:
			texture = disgust_texture
		InworldCharacter.EmotionBehavior.DOMINEERING:
			texture = domineering_texture
		InworldCharacter.EmotionBehavior.HUMOR:
			texture = humor_texture
		InworldCharacter.EmotionBehavior.INTEREST:
			texture = interest_texture
		InworldCharacter.EmotionBehavior.JOY:
			texture = joy_texture
		InworldCharacter.EmotionBehavior.NEUTRAL:
			texture = neutral_texture
		InworldCharacter.EmotionBehavior.SADNESS:
			texture = sadness_texture
		InworldCharacter.EmotionBehavior.STONEWALLING:
			texture = stonewall_texture
		InworldCharacter.EmotionBehavior.SURPRISE:
			texture = surprise_texture
		InworldCharacter.EmotionBehavior.TENSE:
			texture = tense_texture
		InworldCharacter.EmotionBehavior.TENSION:
			texture = tension_texture
		InworldCharacter.EmotionBehavior.VALIDATION:
			texture = validation_texture
		InworldCharacter.EmotionBehavior.WHINING:
			texture = whining_texture
	visible = true
	$Timer.start()

func _on_timer_timeout():
	visible = false
