//bao.c

inherit NPC;
#include <ansi.h>
string ask_likai();
string ask_jiya();

#define QUESTDIR "quest/射雕英雄传/"
#define QUESTDIR1 "quest/射雕英雄传/风雪惊变/"

void create()
{
	set_name("包惜弱", ({ "bao xiruo", "bao", "xiruo" }) );
	set("gender", "女性" );
	set("age", 25);
	set("long",
"她身材极好，虽然脸有点黑，但是还是看出无限的妩媚动人。\n");
	set("str", 10);
	set("dex", 10);
	set("con", 5);
	set("int", 5);
	set("per", 30);
	set("shen_type", 1);
	set_skill("unarmed", 5);
    
	set("combat_exp", 15000);
	set("max_qi", 100);
	set("max_jing", 100);
	set("max_neili", 0);
	set("eff_jingli",200);
	set("qi",100);
	set("jing",100);
	set("jingli",200);
	set("neili", 0);

  set("inquiry", ([
    "郭啸天" : "他是我夫君义兄。",
    "杨康" : "这是一个道人给我未出世的儿女取的名字。",
    "郭靖" : "这是我夫君义兄郭啸天的骨肉。",
    "方才离开做什么去了" : (:ask_likai:),
	"杀鸡杀鸭" : (:ask_jiya:),
	]));

    setup();
	carry_object("/clone/armor/cloth.c")->wear();
	carry_object(ARMOR_D("shoes"))->wear();
} 


string ask_likai()
{
	object me;
	me=this_player();

	message_vision(HIC"$N走上前去，凑近包惜弱身前悄声个问道，“方才你离开会去做什么？”\n	"NOR,me);
	if (me->query(QUESTDIR1+"yestongyin")||me->query(QUESTDIR+"yestongyin"))
	{
		command("shake ");
		command("say 我正在准备好酒，还请到前院好好喝酒\n");
		return "赶紧回去痛饮！\n";
	}
	if (me->query(QUESTDIR1+"notongyin"))
	{
		command("blush ");
		command("say 我，我，我........。\n");
		me->set_temp(QUESTDIR1+"askbao",1);
		return ".........";

	}
	
	return "唉，一看就是喝酒喝多了！\n";
}

string ask_jiya()
{
	object me;
	me=this_player();
	
	if (me->query(QUESTDIR1+"yestongyin")||!me->query_temp(QUESTDIR1+"askbao"))
	{
		command("say 你一个大男人天天到女人面前嘀咕什么？\n ");
		command("say 一看就不是好东西！\n");
		command("pei ");
		return "呸呸！";
	}	
	message_vision(HIC"$N小声对包惜弱恶狠狠地说道，“你要是不说我就把你所养的小鸡小鸭全部杀掉？”\n	"NOR,me);

	
		command("fear ");
		command("sigh ");
		command("say 我方才去拿鸡蛋，但发现后面茅草屋中很是异常，我很是害怕!\n");
		command("say 又不敢说，怕影响了你们喝酒，所以我.....!\n");
		me->set_temp(QUESTDIR1+"weihebao",1);

	return "动不动就杀人，这很不好!\n";

}