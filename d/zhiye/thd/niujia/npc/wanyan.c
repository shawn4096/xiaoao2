// wanyanhonglie.c

inherit NPC;
#include <ansi.h>
string ask_name();
string ask_help();
#define QUESTDIR1 "quest/射雕英雄传/风雪惊变/"

void create()
{
       // set_name("完颜洪烈", ({"wanyan honglie", "honglie", "wanyan"}));
        set_name("中年男子", ({"zhongnan nanzi", "nanzi", "man"}));
		set("gender", "男性");
       // set("title", HIY"大金国赵王爷"NOR);
        set("age", 31);
        set("class", "officer");
	      set("long","[1;31m他看起来受了很重的伤，看上去快要不行了。[0m\n");
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 26);
        set("per", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 26);

        set("qi", 20000);
        set("max_qi", 20000);
        set("jing", 3200);
        set("max_jing", 3200);
        set("neili", 8300);
        set("max_neili", 8300);
        set("jiali", 10);
		
        set("combat_exp", 2500000);
        set("score", 10000);
		set("inquiry", ([
			"name" : (:ask_name:),
			"救你" : (:ask_help:),
			]));

        set_skill("force", 250);
        set_skill("dodge", 240);
        set_skill("parry", 240);
        set_skill("cuff",240);
		set_skill("caoshang-fei",250);
		set_skill("taizu-quan",250);

        set_skill("baduan-jin",250);
		map_skill("force","baduan-jin");
       	map_skill("dodge","caoshang-fei");
       	map_skill("cuff","taizu-quan");
       	map_skill("parry","taizu-quan");

		setup();
        carry_object("/clone/armor/jinduan")->wear();
        carry_object("d/mr/obj/guanxue")->wear();

}

string ask_name()
{
	object me=this_player();
	if (!me->query("quest/射雕英雄传/风雪惊变/notongyin"))
	{
		return "我不相信你，你是谁？有什么企图？\n";
	}
	command("say 既然这位英雄如此侠肝义胆，我就暂且相信你！\n");
	command("say 我是大金国王爷完颜洪烈，请壮士救我，必不负你！\n");
	set_name("完颜洪烈", ({"wanyan honglie", "honglie", "wanyan"}));
	set("title", HIY"大金国赵王爷"NOR);
	me->set_temp("quest/射雕英雄传/风雪惊变/askwanyanname",1);
	return "英雄若能一路护送我回京，本王定当重谢！\n";
}
string ask_help()
{
	object me=this_player();
	if (!me->query("quest/射雕英雄传/风雪惊变/notongyin"))
	{
		return "居心叵测，难得信任！？\n";
	}

	if (!me->query_temp("quest/射雕英雄传/风雪惊变/askwanyanname"))
	{
		return "你一看就是素养及其低下，一点礼貌都没有！\n";
	}
	message_vision(HIY"$N付下身子，悄声说道，“他们在前院喝酒，我来救你，你要配合我”!\n"NOR,me);
	command("say 壮士救我，本王必不负你！\n");
	apply_condition("liuxue",1000);
	apply_condition("neishang",1000);
	me->set_temp("quest/射雕英雄传/风雪惊变/answerhelpwanyan",1);

	return "英雄既然答应救我，本王定当重谢！\n";
}