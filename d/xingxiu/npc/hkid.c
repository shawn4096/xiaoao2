// npc: /d/xingxiu/herdsman.c
// Jay 3/18/96

inherit NPC;
string ask_dizi();
void create()
{
        set_name("牧童", ({ "mutong", "kid"}));
        set("gender", "男性");
        set("age", 8 + random(5));
        set("long", "一个牧童，赶着十几只羊。\n");
        set("attitude", "friendly");
        set("env/wimpy", 60);
        set("combat_exp", 200);

        set_skill("unarmed", 5);
        set_skill("dodge", 5);
        set_skill("parry", 5);
        set_skill("whip", 5);

        set_temp("apply/attack", 5);
        set_temp("apply/defense", 5);
        set("inquiry", ([

	    "竹笛": (: ask_dizi :),
	
	]));
        setup();
        set("chat_chance", 2);
        set("chat_msg", ({
              "牧童悲愤地嚷道：那帮星宿派弟子昨天拉走了我双亲。\n",
              "牧童对天发誓：我大了一定要报仇。\n",
        }));
        carry_object(BINGQI_D("bian"))->wield();
        carry_object(ARMOR_D("yangao"))->wear();
}

string ask_dizi()
{
	object me=this_player();
	command("say 就是普通的一只竹笛，我没事拿来吹奏而已。\n");
	command("say 你想要就送给你吧。\n");
	new("d/xingxiu/obj/zhudi")->move(me);
	return "牧童递给你一只竹笛。\n";
}


