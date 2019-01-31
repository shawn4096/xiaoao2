// jiabu.c
#include <ansi.h>
#include <wanted.h>
inherit NPC;
inherit F_MASTER;

string give_pass();

string *unknow = ({
	"你是何人？如何上得黑木崖？",
	"切口？这等机密尔等无权得知。",
	"不知。",
});

void create()
{
        set_name("贾布", ({ "jia bu", "jia", "bu"}));
	set("nickname", "黄面尊者");
        set("long",
"他那一张瘦脸蜡也似黄，两边太阳穴高高鼓起，便如藏了一杖核桃相似。\n");
        set("title",HIY"日月神教  "HIC"青龙堂长老"NOR);
        set("gender", "男性");
	set("age", 40);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 23);
	set("int", 23);
	set("con", 24);
	set("dex", 28);

        set("max_qi", 3600);
        set("max_jing", 3600);
        set("eff_jingli", 3600);
        set("jiali", 200);
        set("combat_exp", 1500000);

        set_skill("parry",400);
		set_skill("tianmo-jue",200);
        set_skill("dodge",400);
        set_skill("force",400);
        set_skill("strike",400);
        set_skill("cuff",400);
        set_skill("blade",400);
        set_skill("literate", 220);
        set_skill("huanmo-wubu",400);
        set_skill("tianmo-gong",400);
        set_skill("tianmo-zhang",400);
        set_skill("tianmo-dao",400);        

        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
        map_skill("parry", "tianmo-zhang");
        map_skill("strike", "tianmo-zhang");
        map_skill("blade", "tianmo-dao");        
        prepare_skill("strike", "tianmo-zhang");

	set("inquiry", ([
		"切口" : (: give_pass :)
	]));
	create_family("日月神教", 7, "长老");	
        setup();

	carry_object(MISC_D("cloth"))->wear();
}

string give_pass()
{
	object me = this_object();
	object ob;

	ob = environment(me);
	if (ob == load_object("/d/hmy/shimen.c"))
	if (!is_wanted(this_player()) && random(3) == 1)
			return "今日的切口是："+ob->query("pass");
	return unknow[random(sizeof(unknow))];
}

void attempt_apprentice(object ob)
{
     if(ob->query("shen") > 0){
        command("say 你不够心狠手辣，且心地不纯，我不收你！");
        return;
        }
	  if(ob->query_skill("tianmo-gong",1) < 300){
        command("say 你的天魔功不够，你还是上崖去找合适的师傅去吧！");
        return;
        }
     command("haha");
	 command("say 好吧，为了光大日月神教，我就收下你了。");
	 ob->set("class","riyue");
     command("recruit " + ob->query("id"));
}
