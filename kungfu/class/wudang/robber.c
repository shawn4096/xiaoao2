// Modify By River@SJ
//Modify By Renlai@xa

inherit FIGHTER;
//inherit F_UNIQUE;
#include <ansi.h>

int do_kill(object me);
int do_kick(string target);
/*
string *sword_skill = ({
"taiji-jian","xuantie-jianfa","fumo-jian","jinshe-jianfa","qingmang-jian","yuxiao-jian",
"yunu-jianfa","songshan-jian","murong-jianfa","huashan-jianfa", "duanjia-jianfa",
"huifeng-jian","liangyi-jian","quanzhen-jianfa" });

string *blade_skill = ({
"cibei-dao","fanliangyi-dao","liuhe-daofa","murong-daofa","qingmang-jian","wenjia-daofa",
"shandian-daofa","xiuluo-dao","xuanxu-daofa", "yanxing-daofa",});

string *staff_skill = ({ "wuchang-zhang","fengmo-zhang","tianshan-zhang","xinyuegong" });

string *club_skill = ({ "weituo-chu","zui-gun","weituo-gun","xinyuegong" });

string *whip_skill = ({ "piaomiao-bianfa","riyue-bian" });

string *dodge_skill = ({
"shuishangpiao","suibo-zhuliu","yanling-shenfa","yufeng-xiang","tianlong-xiang",
"yunu-shenfa","zhaixingshu","xiaoyaoyou","zhongyuefeng","huashan-shenfa","tiyunzong" });

string *weapon_list = ({ "chui","sword","blade","whip","gun","sword","gangzhang","blade" });
*/

string *first_title = ({"江南","江北","西南","中原","西北","河南","河北","东北"});
string *second_title = ({ "草寇","寨主","恶霸","山贼","土匪","飞贼", "盗贼"});

void create()
{
	string title;
	
	title = first_title[random(sizeof(first_title))];
	title += second_title[random(sizeof(second_title))];
/*	s_sword = sword_skill[random(sizeof(sword_skill))];
	s_blade = blade_skill[random(sizeof(blade_skill))];
	s_club  = club_skill[random(sizeof(club_skill))];
	s_whip  = whip_skill[random(sizeof(whip_skill))];
	s_staff = staff_skill[random(sizeof(staff_skill))];
	s_dodge = dodge_skill[random(sizeof(dodge_skill))];
	weapon = weapon_list[random(sizeof(weapon_list))];
*/
	set_name("无名氏",({"wuming shi"}));
		
	set("long","这家伙一付凶神恶煞的模样，时不时发出邪恶的阴笑。\n");
	set("title", HIW+title+NOR);
	set("age", 20 + random(50));
	
	set("combat_exp", 10000000);
	set("meitude", "peaceful");
	set("str", 30);
	set("dex", 30);
	set("int", 30);
	set("con", 30);
	set("max_qi", 40000);
	set("max_jing", 20000);
	set("max_neili", 10000);
	set("neili", 10000);
	set("no_heal",1);
	set("no_ansuan",1);
    	set("no_bark", 1);

/*	set_skill("huagu-mianzhang", 500);
	set_skill("strike", 500);
	set_skill("xinyuegong", 500);
	set_skill("taiji-shengong", 200);
	set_skill("sword", 500);
	set_skill("dodge", 500);
	set_skill("cuff", 500);
	set_skill("force", 500);
	set_skill("parry", 500);
	set_skill("blade", 500);
	set_skill("hammer", 500);
	set_skill("club", 500);
	set_skill("staff", 500);
	set_skill("whip", 500);
	set_skill("literate",500);
	set("env/no_protect", 1);
*/
/*	set_skill(s_sword, 500);
	set_skill(s_blade, 500);
	set_skill(s_club, 500);
	set_skill(s_whip, 500);
	set_skill(s_staff, 500);
	set_skill(s_dodge, 500);
	map_skill("force", "taiji-shengong");
	map_skill("sword", s_sword);
	map_skill("dodge", s_dodge);
	map_skill("parry", "taizuquan");
	map_skill("hammer", "xinyuegong");
	map_skill("blade", s_blade);
	map_skill("club", s_club);
	map_skill("whip", s_whip);
	map_skill("staff", s_staff);
	map_skill("strike", "huagu-mianzhang");
	prepare_skill("strike", "huagu-mianzhang");
	prepare_skill("cuff", "taizuquan");
*/
	setup();
/*	carry_object(BINGQI_D(weapon))->wield();*/
	carry_object(ARMOR_D("yexing-yi"))->wear();
	add_money("silver", random(10)+20);
	set("chat_chance", 5);
	set("chat_msg", ({
		(: random_move :)
	}) );
	if (clonep())
		call_out("dest", 950);
}
void init()
{
	object ob;
	::init();
	add_action("do_kick","kick");   
	if( interactive(ob = this_player())){
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}
}
////调用可能来自fighter的函数
int do_kill(object ob)
{
	object me = this_object();
	if(!ob) return 0;
	if (me->query_temp("kicked")) {  
		message_vision(HIR""+me->name()+"对$N说道：" + RANK_D->query_rude(ob) +"！穷追不舍，既然逃不掉，"+RANK_D->query_self_rude(me) +"跟你拼了！\n\n"NOR,ob);
		me->delete_temp("kicked");
	} else if (me->query_temp("fight_failed")) {
		message_vision(HIR""+me->name()+"对着$N说道：嘿嘿！有胆敢跟过来，"+RANK_D->query_self_rude(me) +"不客气了！\n\n"NOR,ob);
		me->delete_temp("fight_failed");
	} else 
		message_vision(HIR""+me->name()+"对着$N发出一阵阴笑，说道：既然被你这个" + RANK_D->query_rude(ob)+ "撞见了，那也就只能算你命短了！\n\n"NOR,ob);
	remove_call_out("checking");
	call_out("checking", 2, me, ob);
	//::do_kill(ob); //这里不再回血
	me->kill_ob(ob);
}

int checking(object me, object ob)
{
	int ret =  ::checking(me,ob);
	if(!ret) return 0;
	remove_call_out("checking");
	call_out("checking", 1, me, ob);
        if(!living(ob) && living(me) && me->query("jing")>0 && me->query("jingli")>0 && me->query("qi")>0  ){
		remove_call_out("checking");
		ob->set_temp("wd/wd_job_lost",1);
		ob->set("qi",100);																			//防止玩家意外死亡
		ob->set("jing",100);
		ob->set("jingli",100);
		tell_room(environment(me), "\n"+me->query("name")+"大喊一声：老子不奉陪了！转身几个起落就不见了。\n");
		destruct(me);
		 return 1;
	}
	if(!ob || environment(ob)!= environment(me)){
		remove_call_out("checking");
		 remove_call_out("do_lost");
		 call_out("do_lost",0);
		 return 1;
	}
}

void greeting(object ob)
{
	object me = this_object();

	if (!ob
	 || !present(ob)
	 || me->query_temp("target") != ob->query("id"))
		return;

	if (ob->query_temp("wd/wd_job")){
		if (environment(me)->query("no_fight") || environment(me)->query("sleep_room")) {
			me->delete_temp("fight_failed");
			me->delete_temp("kicked");
			if (random(2)==0) {
				message_vision(HIR""+me->name()+"看见$N走过来，神色有些异常，赶忙低下了头。\n"NOR,ob);
				tell_object(ob, HIR"你忍不住想狠狠踢(kick)这个家伙一脚。\n"NOR);
			} else {
				message_vision(HIR""+me->name()+"对着$N发出一阵阴笑，说道："+ RANK_D->query_rude(ob)+ "，这里地方太小，有种跟"+ RANK_D->query_self_rude(me) +"到外面比划比划！\n\n"NOR,ob);
				me->random_move();				
			}
			me->set_temp("fight_failed",1);
		} else {		
			ob->add_busy(1);
			me->start_busy(1);
			//remove_call_out("checking");
			//call_out("checking", 1, me, ob);
			remove_call_out("dest");
			call_out("dest", 900);
			remove_call_out("do_kill");
			call_out("do_kill", 0, ob);
		}
	}
}

int do_kick(string target)  
{
	object me = this_object();
	object ob = this_player();
	if (target && present(target, environment()) == me) {	
		if (!me->query_temp("fight_failed")) return 0;	
		message_vision(HIR"$N对着"+me->name()+"一脚踢过去："+ RANK_D->query_rude(me) +"，看你往哪里躲！"+me->name()+"见势不妙，奋力一挣，向外逃窜。\n\n"NOR,ob);
		me->random_move();
		me->delete_temp("fight_failed");
		me->set_temp("kicked",1);
		return 1;
	} else {
		return 0;
	}
}

void dest()
{
	//message_vision("$N好象突然想起什么事，急急忙忙的走开了。\n", this_object());
	command("emote 急急忙忙地离开了。");
	destruct(this_object());
}

void do_lost()
{
	object me,ob;
	me = this_object();
	ob = find_player(me->query_temp("target"));
	if(!ob) return;
	ob->set_temp("wd/wd_job_lost",1);
	ob->delete_temp("wd/ob");//这里删除npc对象 by renlai
	tell_room(environment(me), "\n"+me->query("name")+"大喊一声：老子不奉陪了！转身几个起落就不见了。\n");
	destruct(me);
}

/*
void unconcious()
{	
	object me,ob;

	me = this_object();	
	ob = find_player(me->query_temp("target"));
	if (!ob) {
		tell_room(environment(me), "\n"+me->query("name")+"大喊一声：吱！转身几个起落就不见了。\n");	
		destruct(me);
		return;
	}
	
	ob->delete_temp("wd/ob");//这里删除npc对象 by renlai
	ob->set_temp("wd/wd_jobok",1);
	//tell_room(environment(me), "\n"+me->query("name")+"大喊一声：不好！！转身几个起落就不见了。\n");	
	::die();
}

*/
void die()
{
	object me,ob;

	me = this_object();	
	
	me->interrupt_me();
	me->start_busy(-1);
    me->interrupt_me();
	
	tell_room(environment(me), "\n"+me->query("name")+"惨叫一声：啊......\n");	
	if (me->query_temp("target"))
	{	
	ob = find_player(me->query_temp("target"));
	if (!objectp(ob)) {
		tell_room(environment(me), "\n"+me->query("name")+"大喊一声：吱！转身几个起落就不见了。\n");	
		
		return;
	}	
	
	
	ob->delete_temp("wd/ob");//这里删除npc对象 by renlai
	ob->set_temp("wd/wd_jobok",1);	
	::die();
	}
	else
	{
		tell_room(environment(me), "\n"+me->query("name")+"大喊一声：吱吱！转身几个起落就不见了。\n");	
		destruct(me);
		return;		
	}
	destruct(me);
}
