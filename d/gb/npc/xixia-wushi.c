// Modify By LOOKLOVE@SJ 2000/1/8

#include <ansi.h>

inherit FIGHTER;

inherit F_UNIQUE;
inherit F_SAVE;

/*
string *skill = ({
	"longzhua-gong", "yizhi-chan", "jingang-quan",
	"qianye-shou",  "sanhua-zhang","xianglong-zhang",
	"yiyang-zhi", "tanzhi-shentong", "poyu-quan",
	"anran-zhang","luoying-zhang","hanbing-mianzhang",
	"nianhua-zhi", "qishang-quan","yiyang-zhi",
});

string *force = ({
	"yijin-jing",  "yijin-jing", "yijin-jing",
	"yijin-jing",  "yijin-jing","huntian-qigong",
	"qiantian-yiyang", "bihai-chaosheng","zixia-gong",
	"yunu-xinjing","bihai-chaosheng","shenghuo-shengong",
	"yijin-jing","jiuyang-shengong","qiantian-yiyang",
});

string *perform = ({
	"canyun",  "wofo", "fumo",
	"qianshou", "sanhua","paiyun",
	"sandie",  "shentong", "leidong",
	"xiaohun","pikong","xixue",
	"fuxue","qishang","sandie",
});

string *base = ({
	"claw",  "finger", "cuff",
	"hand",  "strike","strike",
	"finger",  "finger", "cuff",
	"strike","strike","strike",
	"finger","cuff","finger",
});

*/
void create()
{
	set_name("西夏武士", ({"xixia wushi", "wu shi", "wushi", "shi"}));
	set("title", "一品堂");
	set("init",0);

	set("gender", "男性");
	set("age", 20 + random(60));
	set("long", "这是西夏一品堂从江湖上重金招聘的一名武林高手。\n" );
	if( random(20) < 1 )
		set("double_attack",1);

	set("attitude", "peaceful");
	set("str", 30 + random(20));
    set("int", 30 + random(20));
	set("con", 30 + random(20));
	set("dex", 30 + random(20));

	set("qi", 10000);
	set("max_qi", 10000);
	set("jing", 10000);
	set("max_jing", 10000);
	//set("neili", 12000);
	//set("max_neili", 912000);
	//set("jiali", 10000);
	set("eff_jingli", 10000);
	set("combat_exp", 2000000);
	set("score", 20000);
	set("jiali",10);
	set("no_get",1);
	set("no_quest", 1);
	set_skill("wuxing-zhen",200);
	
        setup();
}

void init()
{
	object me,ob,cloth;
	int lvl;
	//string s_skill,s_force,s_perform,s_base;
	int index;
	object *lineup;
	object *team;
	int hard,level;

	::init();
	
	
	//find_player(query("targat"));
	if(query("targat")) me=query("targat"); 
		else 
		{
			me = this_player();
		
			if (me->query_team()) 
	         {
		        team=me->query_team();	
	            me=team[0];
		     }
		}
			 
		
	
	ob = this_object();

	if( query("init") == 0
	 && me->query_temp("smy_job")
	 && userp(me) ) {
	 	
	 	set("init", 1);
	 	
		if( me->query_temp("smy_job/lvl")){
			lvl = me->query_temp("smy_job/lvl");
		}
				
		else {
			if(!me->query_team()){
				lvl = me->query("max_pot");
			}
			else {
				team = me->query_team();
				lvl = 0;
				for(index=0;index<sizeof(team);index++){
					if( team[index]->query("max_pot") > lvl )
						lvl = team[index]->query("max_pot");//取最大值
				}
			}
			lvl = lvl - 105 + random(5);
		}
		
		lvl += me->query_temp("smy_job/finish")*5;
		
		setparty(me->query_temp("smy_job/finish"),lvl,lvl*lvl*lvl/10*6/5 );

		set("ciwei_level",me->query_temp("smy_job/finish"));
				
		set_name("西夏武士", ({"xixia wushi","wu shi", "wushi", "shi"}));
		set("title", "一品堂");		
		/*				
		index = random( sizeof( skill ) );

		s_skill = skill[ index ];
		s_force = force[ index ];
		s_perform = perform[ index ];
		s_base = base[ index ];

		set("gender", "男性");
		set("age", 20 + random(60));

		set("combat_exp", lvl*lvl*lvl/10*6/5);
		set("meitude", "peaceful");
		set("str", 20 + random(5));
		set("int", 15 + random(5));
		set("con", 20 + random(5));
		set("dex", 20 + random(5));
		set("shen", 0);

		set("max_qi", 4500+lvl*lvl*lvl/20000*(1 + sizeof(lineup)));
		set("max_neili", 3000+lvl*lvl*lvl/15000*(1+sizeof(lineup)));
		set("max_jing", 3000);
		set("eff_jingli", 4000);
		set("neili",query("max_neili")*3/2);
		set("qi",query("max_qi"));
		set("jiali",lvl/ 5);

		set_skill(s_skill, lvl );
		set_skill(s_force, lvl );
		set_skill(s_base, lvl);
		set_skill("dodge", lvl);
		set_skill("force", lvl);
		set_skill("parry", lvl);
		set_skill("tiyunzong", lvl);
		set_skill("qimen-bagua", 200);
		set_skill("literate", 200);
		set_skill("poison", 200);
		map_skill("force", s_force);
		map_skill("dodge", "tiyunzong");
		map_skill("parry", s_skill);
		map_skill(s_base, s_skill);
		prepare_skill(s_base, s_skill);

		set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: perform_action, s_base + "." + s_perform :)
		}) );
		
		*/
		
		set("max_neili",query_skill("force")*8 + query("combat_exp")/1000);
		set("max_jingli",query_skill("force")*8);
		set("eff_jingli",query_skill("force")*8);

		copy_state();
		setup();
		reincarnate();
		
		
								
		cloth = new(ARMOR_D("cloth"));
		cloth->set("name",HIC"西夏长袍"NOR);
		cloth->move(ob);
		cloth->wear();
		add_money("silver", 20+random(30));
		add_temp("apply/defense", 200);
	    add_temp("apply/armor", 200);
	   if (me->query_temp("smy_job/finish"))
		   level=me->query_temp("smy_job/finish");
	   else level=80;
        		
		set("double_attack",1);
		
		if(level<=10) 
		{
			hard =level*70;
		}	
		if(level>10) 
		{
			hard =level*81;
		}		
		if(level>=20) 
		{
			hard=level*90;
		}
		
		if(level>=30) 
		{
			hard=level*93;
		}
		
		if(level>=40) 
		{
			hard=level*94;
		}
		if(level>50) 
		{
			hard=level*100;		 
		}
		
		     add_temp("apply/damage", hard);
             add_temp("apply/armor", hard);
			 add_temp("apply/defense", hard);
             add_temp("apply/attack",hard);	
		     set("neili",query("max_neili")* 2);
		
		call_out("check",1,ob,me);
		if(!me->query_team()) {
			ob->kill_ob(me);
		}
		else {
			team = me->query_team();
				for(index=0;index<sizeof(team);index++){
					if( present(team[index]->query("id"),environment(me) ))
						ob->kill_ob(team[index]);
				}
		}
	}
}

void check(object ob, object me)
{
   object *team;
   object fbroom;
   int index;   
	if( !ob ) return;
	team=me->query_team();
	
	checking(ob,me);
	
	command("lineup with xixia wushi 1");
	command("lineup with xixia wushi 2");
	command("lineup with xixia wushi 3");
	command("lineup with xixia wushi 4");
	command("lineup with xixia wushi 5");
	command("lineup form wuxing-zhen");
	command("lineup with xixia wushi 1");
	command("lineup with xixia wushi 2");
	command("lineup with xixia wushi 3");
	command("lineup with xixia wushi 4");
	command("lineup with xixia wushi 5");
		//|| me->query("qi")<1000			
	
	if (!team) {
	if( !me 
	 || !living(me)       
	 || !me->query_temp("smy_job")	 
	 || environment(me)!=environment(ob)){
		tell_room(environment(ob), "西夏武士道：'蛮子已有准备，快撤。'，说完转身逃去了\n");
		fbroom=environment(ob);
		fbroom->set("over",1);
		me->delete_temp("smy_job");
		me->set_temp("smyfail",1);
		me->apply_condition("job_busy",10+random(20));
		//me->apply_condition("smy_job",0); //這裏不能消除，否則無法退出副本
		destruct(ob);
		return;
	}
	}
	else
	{
		for(index=0;index<sizeof(team);index++){
			 if (!living(team[index]) || (environment(team[index])!=environment(ob)))
			 {
				 team[0]->delete_temp("smy_job");
				 team[0]->set_temp("smyfail",1);
				 me->delete_temp("smy_job");
				 me->set_temp("smyfail",1);
				 team[index]->apply_condition("job_busy",10+random(20));
                 tell_room(environment(ob), "西夏武士道：'蛮子已有准备，快撤。'，说完转身逃去了\n");
		          destruct(ob);
		          return;						 
			 }
			 }
		
	}
	
	call_out("check",1,ob,me);
}
