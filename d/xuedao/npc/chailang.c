// chailang.c ����
// by sohu@xojh
inherit NPC;

void create()
{
	set_name("����", ({ "chai lang","chailang","lang" }) );
	set("long","һֻ�����Ĳ��ǣ���������ѩ��ëƤ������Щ�ƻ��ƣ�ɢ���������Ĺ���\n");
	set("race", "Ұ��");
	set("age", 5);

	set("eff_jing", 500);
	set("max_jing",500);
	set("max_qi", 1500);

	set("str", 40);
	set("dex", 40);
	set("con", 25);
	set("int", 20);
	set("unique", 2);

	set("limbs", ({ "ͷ��", "����", "ǰ��","����", "β��" }) );
	set("verbs", ({ "bite", "claw"}) );
        set("attitude","aggressive");
	set_temp("apply/attack", 10);
	set_temp("apply/damage", 10);
	//set_temp("apply/dodge", 50);
	//set_temp("apply/armor", 20);

	set("combat_exp", 260000);
     set("chat_chance", 1);
	set("chat_msg", ({
(: this_object(), "random_move" :),
"����ǰ�Ȱ��ڵ��ϣ������﷢���ͳ���������\n",
"���ǳ����������죬��������������������ź��⡣\n",
}) );
        setup();
}
/*
void die()
{
	object ob;
	message_vision("$N���������һ����Ѫ���Ƚų鴤�˼��£����ˡ�\n", this_object());
	ob = new(ARMOR_D("baopi"));
	ob->move(environment(this_object()));
	destruct(this_object());
}
*/