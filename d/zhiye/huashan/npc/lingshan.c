// NPC: /d/huashan/npc/lingshan.c
// Date: Look 99/03/25
// Lklv Modify at 2001.10.18
// 重要NPC.无法杀死 by spiderii@ty
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_me();
string ask_sword();
void create()
{
	set_name("岳灵珊", ({ "yue lingshan", "yue", "lingshan" }));
	set("long",
"华山掌门岳不群和夫人宁中则的爱女，容颜俏丽，天真无邪，自小娇惯，\n"
"华山门下人人叫她作“小师妹”。\n");
	set("nickname", "小师妹");
	set("rank_info/respect", "小师妹");
	set("gender", "女性");
	set("age", 19);
	set("attitude", "friendly");
	set_max_encumbrance(1000000);
	set("shen_type", 1);
	set("str", 22);
	set("int", 25);
	set("con", 23);
	set("dex", 28);
	set("per", 30);
	set("unique", 1);
	set("no_get", 1);
	set("job_npc", 1);

	set("max_qi",6700);
	set("max_jing",4600);
	set("neili",6000);
	set("max_neili",6000);
	set("eff_jingli", 4600);
	set("jiali", 150);
	set("combat_exp", 3020000);
	set("score", 5000);

	set_skill("sword",  280);
	set_skill("dodge",  280);
	set_skill("force",  280);
	set_skill("parry",  280);
	set_skill("literate",280);
	set_skill("chongling-jian", 280);
	set_skill("huashan-jianfa", 280);
	set_skill("huashan-shenfa", 280);
	set_skill("huashan-qigong",280);
	set_skill("poyu-quan",280);
	set_skill("cuff",280);

	map_skill("force", "huashan-qigong");
	map_skill("cuff", "poyu-quan");
	map_skill("parry", "huashan-jianfa");
	map_skill("sword", "huashan-jianfa");
	map_skill("dodge", "huashen-shenfa");

	prepare_skill("cuff", "poyu-quan");
	create_family("华山派", 14, "弟子");
	
	set("inquiry", ([
		"力不从心" : (: ask_me :),
		"碧水剑" : (: ask_sword :),
	]));

	setup();
	carry_object(BINGQI_D("sword/sword"))->wield();
	carry_object(ARMOR_D("armor/cloth"))->wear();
}

void heart_beat()
{
	::heart_beat();

	clear_conditions_by_type("poison");
	if( !is_fighting() && living(this_object()))
		reincarnate();
}
string ask_sword()
{
	object sword,me;
	
	me =this_player();
	sword =present("bishui jian", me);
		
	if (!sword )
		return "好好练功去吧，没事不要骚扰小师妹！\n";
	if (me->query_temp("quest/huashan/zixia/zixia2"))
	{
       me->set_temp("quest/huashan/bishuijian",1);
	   return "岳灵珊神色抑郁，说道,'自从上次被大师兄扔掉山涧，就再也没有见到它了'！";
	};
	return "岳灵珊不懂你的意思。该干啥干啥去吧。\n";

}
 
int accept_object(object who, object obj)
{
	int times;
	object ling,me,sword;
	ling =present("ling pai", who);
	me = this_player();
    
	sword = present("bishui jian", who);

	if (me->query_temp("quest/huashan/bishuijian")&& obj->query("id")=="bishui jian")
	{
		me->set_temp("quest/huashan/zixia3",1);
		write(HIY"岳灵珊高兴滴蹦了起来，似乎对你的好感大增。\n"NOR);
		write(HIC"$N把碧水剑送给了小师妹，百无聊赖之际，伤痛发作，决定还是先回到休息室疗养一番。\n"NOR);
		obj->move(this_object());
		destruct(obj);
		me->delete_temp("quest/huashan/bishuijian");		
		return 1;
	}
//标记给了碧水剑

	if (! obj->query_temp("mmr") 
	 && !obj->is_corpse()
	 && obj->query("id") != "shouji") {
		command("say 这东西我要来没用。");
		return 0;
	}
	if (!ling )
		return notify_fail("你的令牌呢？\n");
	if (!who->query_temp("hs/jobji"))
		return notify_fail("你还没有领任务，怎么就来祭坛了？\n");
	if ((int)ling->query_temp("mmr", 1) != who->query("id"))
		return notify_fail("这好象不是你领的令牌吧？\n");
	if ((int)ling->query_temp("done", 1) > 1 )
		return notify_fail("完成这么多次任务了，你赶紧回去复命吧。\n");
	if (!who->query_temp("hs/have"))
		return notify_fail("你还没有去找恶贼，怎么就来祭坛了？\n");
	if (obj->query_temp("mmr")) {
		if ( obj->query_temp("mmr", 1) != who->query("id") )
                	return notify_fail("这人好象并未在华山为非做歹啊？\n");
	}
	if (obj->query_temp("faint_by") != who && obj->query("kill_by") != who )
		return notify_fail("这人好象不是你杀的吧？\n");

	if ( obj->query("victim_user") )
		return notify_fail("想用玩家蒙混过关？没那么容易！\n");

	times = ling->query_temp("done", 1);
	write("岳灵珊在你的令牌上写下了一个 "+CHINESE_D->chinese_number(times+1)+" 字。\n", who);

	if (!obj->is_corpse() && obj->query("id") != "shouji" ){
		command("say " + "好吧，请把恶贼放于祭台，上天会惩罚他的，侠义之士的在天之灵会安息了。\n");
		who->set_temp("jitan", 1);
	}
	else {
		command("say " + "我华山派不喜滥杀，" + RANK_D->query_respect(who) + "下次不可如此好勇斗狠了。\n");
		ling->add_temp("done", 1);
	}
	if( (int)ling->query_temp("done", 1) == 1 )
		command("say " + "等一会仪式结束，你就可以去师傅那里复命了。\n");
	//me->set_max_encumbrance(10000000);
	who->start_busy(random(3));
	who->delete_temp("hs/have");
	call_out("destroying", 1, obj);
	return 1;
}

void destroying(object obj,object me)
{
	if (!obj) return;
	destruct(obj);
	return;
}

string ask_me()
{
	object ling,me;
	
	me =this_player();
	ling =present("ling pai", me);
		
	if (!ling )
		return "你的令牌呢？\n";
	if (!me->query_temp("hs/jobji"))
		return "你还没有领任务，怎么就来祭坛了？\n";
	if ((int)ling->query_temp("mmr", 1) != me->query("id"))
		return "这好象不是你领的令牌吧？\n";
	if ((int)ling->query_temp("done", 1) > 1 )
		return "完成这么多次任务了，你赶紧回去复命吧。\n";
	if (!ling->query_temp("done", 1))
		return "你什么也没干啊？\n";
	if (me->query_temp("hs/have"))
		return "你还没有去找恶贼，怎么就来祭坛了？\n";
	if (me->query_temp("hs/robot"))
		return "你还不回去复命？\n";
	//杀完一个
	me->set_temp("hs/robot",1);
	return "既然如此，你这就回去复命吧！";
}
void die()
{
	object ob;
	if (!query_temp("living"))
	{
		ob = new("/d/huashan/npc/lingshan");
		ob->move("/d/huashan/jitan");
	}
	::die();
}

void attempt_apprentice(object ob)
{
        mapping fam;
		if ( ob->query("fengset")) {
		command("say 你不是已经拜了剑宗的前辈为师了么？");
		return;
		}
		        if(ob->query("quest/huashan")=="剑宗"){
                command("heng");
                command("say 哼哼！剑宗弟子早已离开华山，不再是华山派弟子，你又来这里，难道是想争夺这掌门之位？");
                return;
        }
        if( (string)ob->query("gender") != "女性" ) {
                command ("say 对不起，我只收女弟子。");
                return;
        }
		
        if ((int)ob->query("shen") < 10000) {
		command("say 我华山派乃是堂堂名门正派，对弟子要求极严，没有正神10k别来找我。");
		command("say 在德行方面，" + RANK_D->query_respect(ob) + "是否还做得不够？");
		return;
        }
		command("xixi");
        command("say 咦，不错的小女孩嘛，我就收下你了。");
        command("recruit " + ob->query("id"));
	    ob->set("title","华山派气宗亲传弟子");
        ob->set("quest/huashan","气宗");
        return;
}
