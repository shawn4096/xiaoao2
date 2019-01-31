// jiudai.c  酒袋
// Lklv modify 2001.9.28

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name("青稞酒袋", ({"qingke jiudai", "jiudai", "qingke", "dai"}));
	set_weight(700);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一个用来装青稞酒的大酒袋，大概装得八、九升的酒。\n");
		set("unit", "个");
		set("value", 20);
		set("max_liquid", 25);
	}

	// because a container can contain different liquid
	// we set it to contain wine at the beginning
	set("liquid", ([
		"type": "alcohol",
		"name": "青稞酒",
		"remaining": 25,
		"drunk_supply": 25,
	]));
}