// chailang.c 豺狼
// by sohu@xojh
inherit NPC;

void create()
{
	set_name("髭狗", ({ "zi gou","zigou","gou" }) );
	set("long","一只饥饿的髭狗，浑身上下脏乎乎的，正用凶狠的眼光看着你。\n");
	set("race", "野兽");
	set("age", 5);

	set("eff_jing", 500);
	set("max_jing",500);
	set("max_qi", 1500);

	set("str", 40);
	set("dex", 40);
	set("con", 25);
	set("int", 20);
	set("unique", 2);

	set("limbs", ({ "头部", "身体", "前腿","后腿", "尾巴" }) );
	set("verbs", ({ "bite", "claw"}) );
        set("attitude","aggressive");
	set_temp("apply/attack", 50);
	set_temp("apply/damage", 10);
	//set_temp("apply/dodge", 50);
	//set_temp("apply/armor", 20);

	set("combat_exp", 260000);
     set("chat_chance", 1);
	set("chat_msg", ({
(: this_object(), "random_move" :),
"髭狗前腿扒在地上，喉咙里发出低沉的咆哮。\n",
"髭狗冲你裂了裂嘴，长长的牙齿在冷风中闪着寒光。\n",
}) );
        setup();
}
/*
void die()
{
	object ob;
	message_vision("$N嘴角流出了一缕鲜血，腿脚抽搐了几下，死了。\n", this_object());
	ob = new(ARMOR_D("baopi"));
	ob->move(environment(this_object()));
	destruct(this_object());
}
*/