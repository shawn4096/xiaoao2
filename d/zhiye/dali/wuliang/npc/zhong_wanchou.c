// NPC :zhong_wanchou.c 钟万仇 
// By River 98/12
#include <ansi.h>

inherit NPC;
string ask_duan();
string ask_eren();
string ask_manying();

void create()
{
        set_name("钟万仇", ({ "zhong wanchou", "zhong", "wanchou"}));
        set("title",HIC"万劫谷谷主"NOR);
        set("nickname",HIR"马王神"NOR);
        set("gender", "男性" );
        set("age", 42);
        set("str", 30);
        set("con", 23);
        set("dex", 22);
        set("int", 10);
        set("per", 5);
   		set("attitude", "heroism");

        set("max_qi", 28000);
        set("max_jing", 5000);
        set("eff_jingli", 5000);
        set("neili", 20000);
		set("qi", 18000);	
        set("max_neili", 20000);
        set("jiali", 140);
        set("unique", 1);
        
        set("long","只见他好长一张马脸，眼睛生得甚高，一个园园的大鼻子却和嘴巴挤在一块。\n");
        set("combat_exp", 6400000);
        set("shen", -1000); 

        set_skill("parry", 400);
        set_skill("dodge", 400);
        set_skill("force", 400);
        set_skill("strike", 400);
        set_skill("yijin-jing", 400);        
        set_skill("shaolin-shenfa", 400);
        set_skill("zhongjia-zhang", 400);
        map_skill("dodge", "shaolin-shenfa");
        map_skill("parry", "zhongjia-zhang");
        map_skill("strike", "zhongjia-zhang");
        map_skill("force", "yijin-jing");
        prepare_skill("strike","zhongjia-zhang");

        set("inquiry", ([            
            "段正淳" : (: ask_duan :),
			 "四大恶人" : (: ask_eren :),
			"恶贯满盈" : (: ask_manying :),
        ]));

        setup();
        carry_object("/clone/armor/cloth")->wear();
}
string ask_duan()
{
	command("say 他妈的这个孙子就是个小白脸！\n ");
	return "别跟我提这个小白脸，谁提我跟谁急！";

}
string ask_eren()
{
	command("say 四大恶人名冠江湖，威震天南！\n");
	command("say 老四为穷凶极恶--云中鹤！\n");
	command("say 老三为南海鳄神--岳某人！\n");
	command("say 老二为无恶不作--叶二娘！\n");
	command("say 老大是恶贯满盈--段延庆！\n");
	this_player()->set_temp("yanqing/askeren",1);
	return "谁招惹四大恶人，谁将永不安生！\n";
}
string ask_manying()
{
	object me=this_player();
	if (me->query("shen")>-200000)
	{
		command("say 你一个道貌岸然的正派人士来此作甚(小于200k负神)？\n");
		return "哼！小白脸，一看就不是好东西！\n";
	}
	if (!me->query_temp("yanqing/askeren"))
	{
		command("say 段延庆乃是四大恶人之首！\n");
		return "哼！小白脸，一看就不是好东西！";
	}
	command("say 这段延庆乃是大理一皇子，但现在下落不明！\n");
	command("say 最近为我的事一直在奔波，据说段在拈花寺一代出没！\n");
	command("say 你若想去找他，最好去那边看看！\n");
	command("say 不过，我看他最近脾气不是太好，你要小心！\n");
	
	this_player()->set_temp("yanqing/askzhong",1);
	return "四大恶人，谁招惹谁死！\n";
}