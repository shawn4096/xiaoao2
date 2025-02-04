// 施琅
// 1/28/2002	by augx@sj
//update by jpei 2010 加了海战的奖励


inherit NPC;
#include "ansi.h"
#define	SEAWAR_D	__DIR__"seaward"

string ask_seawar();
int ask_xuexi(object who);

void create()
{
	set_name("施琅", ({ "shi lang", "shi" }));
	set("title", "钦命靖海将军");
	set("shen_type", 1);

	set("gender", "男性");
	set("age", 35);
	set("long", "此人就是钦命靖海将军，一身武将打扮威风凛凛。\n他正准备率领大清船队攻打神龙岛。");

	set_skill("sword", 120);
	set_skill("cuff", 120);
	set_skill("dodge", 120);
	set_skill("taizu-quan", 120);
	set_skill("xiaoyaoyou", 120);
	set_skill("force", 120);
	set_skill("huntian-qigong", 120);
	set_skill("parry", 120);
	set_skill("literate", 100);
	
	map_skill("cuff", "taizu-quan");
	map_skill("parry", "taizu-quan");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("force", "huntian-qigong");
	prepare_skill("cuff", "taizu-quan");

	set_temp("apply/damage", 50);

	set("combat_exp", 300000);
	set("attitude", "friendly");
	
	set("no_ansuan",1);
	set("no_bark",1);
	set("no_quest",1);
	set("no_get", 1);
	set("job_npc", 1);

	set("inquiry", ([
		"攻打神龙岛" :	(: ask_seawar() :),
		"job" :		(: ask_seawar() :),
		"参战" :	(: ask_seawar() :),
		"神龙岛" :	"我们正要攻打神龙岛，你如果愿意参战就快来从军吧！",
		"谋划":		(: ask_xuexi :),
		"作战指示":	(: ask_xuexi :),
	]) );
	
	set("chat_chance", 2);
	set("chat_msg", ({
		CYN"施琅说道：神龙岛兵强马壮，不好对付啊。\n"NOR,
		CYN"施琅说道：据说神龙岛从罗刹人那里买了几艘炮船，不知是真是假。\n"NOR,
		CYN"施琅说道：有皇上的龙威护佑，此战必胜！\n"NOR,
	}) );
	
	setup();
	carry_object(ARMOR_D("armor"))->wear();
	carry_object(BINGQI_D("sword"))->wield();
}

void kill_ob(object ob)
{
	object me = this_object();
	command("say 本将出征在即，没功夫陪你玩。");
	me->remove_enemy(ob);
	ob->remove_killer(me);
	return;
}

int accept_fight(object ob)
{
	command("say 本将出征在即，没功夫陪你玩。");
	return 0;
}

string ask_seawar()
{
	object * team;
	object me;
	int i;
	
	me = this_player();
	team = me->query_team();

	if(wizardp(me) && me->query("env/test"))
		return SEAWAR_D->play(me,me,1);
	
	if( sizeof(team) != 2 )
		return "出海参战，你的队伍必须要有两个人。";
	for (i=0;i<sizeof(team);i++) {
		if ( !team[i] || !userp(team[i]) || !present(team[i],environment(me)) )
			return "你要和谁一起出战？";
		if( team[i]->query_condition("job_busy") || team[i]->query("job_name")=="大清国海战" || team[i]->query_condition("killer") )
			return "你们的队伍太忙碌了，休息一会儿再参战吧。";
		if( team[i]->query("combat_exp")<100000 )
			return "你们的队伍的经验太少了，还是先去锻炼一下儿再来参战吧。";
		if( team[i]->query("shen")<30000 )
			return "你们似乎不是很有正气，我可不放心让你们参战。";
		if( team[i]->query_temp("quest/busy")) //added by tangfeng 与quest冲突
			return "你们有人在解密之中，你们还是先处理好你其他事情再说吧。";
	}

	return SEAWAR_D->play(team[0],team[1],1);
}

int ask_xuexi(object who)
{
	object me = this_player();
	object obj;
	int i, g,s,times;
	i = random(2);
	g = me->query_skill("gunnery",1);
	s = me->query_skill("sailing",1);
	times = (int)me->query("job_time/大清国海战",1);

	if ( times < 100 || times < (int)me->query("hz_times") + 50  ){
		command("say 纸上谈兵是没有用的，你多参加几次海战再来找我吧！\n");
		return 1;
	}
	if ( g > 500 && s > 500 ){
		command("say 将军本领已然不在老夫之下，一切尽依将军意思行事便是。\n");
		command("flatter " + me->query("id"));
		return 1;
	}

	if( times >= (int)me->query("hz_times") + 50 ) 
	{
		command("praise " + me->query("id"));
		message_vision("say 本将近日刚想到一些行军布阵之法，你拿去仔细参详一下，以便作战之用。\n",me);

		me->set("hz_times",times);

		switch(i) {
			case 0:         
				obj = new ("/d/sld/seawar/gunnery-book");
				obj->set("max_skill", g+ 10);
			break;    
			case 1:         
				obj = new ("/d/sld/seawar/sailing-book");
				obj->set("max_skill", s+ 10);
			break;
			break;  
			default:return 1;
		}
		if( me->query_skill("sailing") > 500 ) { 
			obj = new ("/d/sld/seawar/gunnery-book");
			obj->set("max_skill", g + 10);
		}
		if( me->query_skill("gunnery") > 500 ) { 
			obj = new ("/d/sld/seawar/sailing-book");
			obj->set("max_skill", s + 10);
		}
		obj->move(me);

		message_vision(HIC"施琅拿出一本厚厚的作战笔记交给了$N。\n"NOR, me);  
		return 1;
	}

	command("say 本将出征在即，你且过两日再来。\n");
	return 1;
}



