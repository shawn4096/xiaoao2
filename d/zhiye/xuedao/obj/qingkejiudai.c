// jiudai.c  �ƴ�
// Lklv modify 2001.9.28

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name("�����ƴ�", ({"qingke jiudai", "jiudai", "qingke", "dai"}));
	set_weight(700);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ������װ�����ƵĴ�ƴ������װ�ðˡ������ľơ�\n");
		set("unit", "��");
		set("value", 20);
		set("max_liquid", 25);
	}

	// because a container can contain different liquid
	// we set it to contain wine at the beginning
	set("liquid", ([
		"type": "alcohol",
		"name": "������",
		"remaining": 25,
		"drunk_supply": 25,
	]));
}