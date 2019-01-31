// miaoke.c妙可 
// by sohu
// 制药id
#include <ansi.h>

inherit NPC;
//inherit F_MASTER;
int ask_jingjie();
int ask_miji();
int ask_lianwan();
int ask_fail();
int ask_fangqi();

void create()
{
        set_name("妙可", ({ "miao ke", "miaoke" ,"ke"}));
        set("long",@LONG
他是宝象法师座下的嫡传弟子之一，在几个弟子中功力深厚，为宝象
安排在野外炼制各种药材，打猎弟子往往将获得猎物交由他来处理，然后
制成血刀门绝密药丸。身材甚胖，状如球，满脸堆满了笑容，一副人畜无
害的样子。
LONG
        );
        set("title", "血刀门第六代弟子" NOR);
        set("gender", "男性");
		set("class", "huanxi");
        set("age", 35);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 13200);
        set("eff_jing", 3500);
		set("max_jing",3500);
		set("eff_jingli", 3500);
        set("neili", 13500);
        set("max_neili", 13500);
        set("jiali", 150);
        set("combat_exp", 4700000);
        set("score", 5000);
		set("unique", 1);

        set_skill("huanxi-chan", 150);
        set_skill("literate", 100);
        set_skill("force", 350);
        set_skill("xuedao-jing", 400);
        set_skill("dodge", 350);
        set_skill("xueying-dunxing", 350);
        set_skill("xuedao-daofa", 400);
        set_skill("parry", 350);
        set_skill("strike", 350);
        set_skill("blade", 400);
       // set_skill("hand", 350 );
        set_skill("jingang-liantishu", 400 );

        map_skill("force", "xuedao-jing");
        map_skill("dodge", "xueying-dunxing");
        map_skill("strike", "hongsha-zhang");
        map_skill("parry", "xuedao-daofa");
        map_skill("blade", "xuedao-daofa");

        prepare_skill("strike","hongsha-zhang");

        create_family("血刀门",6, "弟子");
		set("chat_chance_combat", 65);
		set("chat_msg_combat", ({
			(: perform_action, "blade.chuanxin" :),
			(: perform_action, "blade.liuxing" :),
			(: perform_action, "blade.bafang" :),
			(: perform_action, "blade.chilian" :),
			(: exert_function, "yuxue" :),			
			(: perform_action, "dodge.xueying" :),
		}));
		set("inquiry",([
		"血刀警戒"	: (: ask_jingjie :),
		"炼丸"	: (: ask_lianwan :),
		"秘籍"	: (: ask_miji :),
		"放弃警戒"	: (: ask_fail :),
		"放弃炼丸"	: (: ask_fangqi :),

		]));


        setup();
        carry_object("/d/xueshan/npc/obj/gongde-jiasha")->wear();
        carry_object(BINGQI_D("xinyuedao"))->wield();        

        add_money("silver",20+random(10));
}

int ask_jingjie()
{
	object me;
	me=this_player();
	if (me->query("family/family_name")!="血刀门")
	{
		return notify_fail("你不是我血刀门弟子，来此作甚？\n");
	}
	if (me->query("combat_exp")>2000000)
	{
		return notify_fail("你的武功已经足够纵横江湖了，把这些工作机会都让给你的师弟师妹们吧？\n");
	}

	command("say 既然你已经成了我血刀派弟子，当为血刀门有所担当！\n");
	command("say 我血刀门之所以早期成长较快，主要的原因是我派有一门独到的秘方！\n");
	command("say 可以通过血鼎来提炼血肉中的精华，练成“五肉”、“五血”丸子，加快武功修炼！\n");
	command("say 所以那些所为的正派人士一直把我们当做歪门邪道，时常来此干扰门中弟子修炼！\n");

	command("say 这乃是我派不传之秘，你既然已经成为门中弟子，当先为门派做些贡献！\n");
	command("say 在此处好好警戒外敌入侵，不可轻易离开，看护好这个血鼎！\n");
	command("say 输入指令(jingjie 铜鼎)，就可以开始，如果要离开需输入(leave)\n");
	me->set_temp("xdjj/askmiaoke",1);
	return 1;
		
}

int ask_miji()
{
	object me,ob;
	me=this_player();
	if (me->query("family/family_name")!="血刀门")
	{
		return notify_fail("你不是我血刀门弟子，来此作甚？\n");
	}
	if (!me->query("quest/xd/dichuan"))
	{
		return notify_fail("你不是我血刀门嫡传弟子，来此作甚？\n");
	}
	command("say 既然你已经成了我血刀门嫡传弟子，我就给你这本《时轮经》！\n");
	command("say 这本书你要好好研读，不可辜负了我的一番期望！\n");
	ob=new("d/xuedao/obj/huanxi_book2");
	ob->move(me);
	command("pat "+me->query("id"));
	command("say 血刀门当大兴！\n");
	return 1;
		
}

int ask_lianwan()
{
	object me;
	me=this_player();
	
	if (me->query("family/family_name")!="血刀门")
	{
		command("say 你不是我血刀门弟子，来此作甚？\n");
		return 1;
	}
	if (me->query("job_time/血刀打猎")<200)
	{
		command("say 你打猎次数不够200次，根本就搞不懂炼丸？\n");
		return 1;
	}
	if (me->query_skill("medicine",1)<100)
	{
		command("say 你的医学技能不足100次，别瞎折腾了？\n\n");
		return 1;
	}


	if (me->query_temp("xd/lianwan/askke"))
	{
		command("say 我已经跟你说了啊？\n");
		return 1;
	}
	if (me->query_temp("lianwan_tick"))
	{
		command("say 你正在炼丸子中？\n");
		return 1;
	}
	command("say 好，我这里正好有你前期积累的一些血肉，你就开始炼丸子吧！\n");
	command("say 千万要注意火候和技巧！\n");

	command("say 打猎数越多，越容易成功！\n");
	message_vision(HIY"$N从一旁的木架上取下鹿肉、猪肉、樟子肉、鹰肉、兔子肉和一些新鲜血液，递给了$n。\n"NOR,this_object(),me);
	command("say 炼出来的丸子你可以自己服用，对你身体有大益！\n");
	command("say "+me->query("name")+"你也可以送给门中年岁比较大的长老，他们毕竟气血不足，很是需要！\n");
	command("say "+me->query("name")+"你千万要注意火候！\n");
	me->set_temp("xd/lianwan/askke",1);
	return 1;
		
}
//警戒失败job

int ask_fail()
{
	object me,ob;
	me=this_player();
	if (me->query_temp("xdjj/askmiaoke"))
	{
		command("say 既然你完不成血刀警戒任务就暂时下去歇息去了,哼！\n");
		me->delete_temp("xdjj/askmiaoke");

	} else command("say 你什么都没做，瞎放弃什么？\n");

	me->delete_temp("xdjj");
	me->apply_condtion("job_busy",35);
	command("say "+me->query("name")+"放弃了从妙可这儿接到的血刀警戒任务。\n");
	return 1;
}

int ask_fangqi()
{
	object me,ob;
	me=this_player();
	if (me->query_temp("xd/lianwan/askke"))
	{
		command("say 既然你完不成炼丸任务就暂时下去歇息去了,哼！\n");
		me->delete_temp("xdjj/askmiaoke");
		

	} else command("say 你什么都没做，瞎放弃什么？\n");


	me->delete_temp("xd");
	me->apply_condtion("job_busy",35);
	environment(this_object())->delete("lianwan");
	command("say "+me->query("name")+"放弃了从我这儿接到的炼丸任务。\n");
	return 1;
}