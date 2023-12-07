extends Control

@export var scroll : ScrollContainer
@export var container : Container

func _ready() -> void:
	scroll.get_v_scroll_bar().changed.connect(handle_scrollbar_changed)


func handle_scrollbar_changed() -> void:
	scroll.scroll_vertical = int(scroll.get_v_scroll_bar().max_value)


func add_text(who : String, text : String) -> void:
	var to_add = Label.new()
	to_add.text = who + " : " + text
	container.add_child(to_add)


#func _on_interface_character_text(text : String) -> void:
	#add_text("Character", text)
#
#
#func _on_interface_player_text(text : String) -> void:
	#add_text("Player", text)

	
