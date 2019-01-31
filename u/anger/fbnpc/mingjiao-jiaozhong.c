// Modify By LOOKLOVE@SJ 2000/1/8


inherit FIGHTER;

inherit F_UNIQUE;
inherit F_SAVE;


#include <ansi.h>
#include <canpian.h>

int check2(object ob, object me);
void create()
{
	set_name("明教教众", ({"mingjiao jiaozhong", "jiao zhong","jiaozhong"}));
	set("title", "五行旗副旗主");
	set("init",0);

	set("gender", "男性");
	set("age", 20 + random(60));
	set("long", "这是五行旗下的副旗主。\n" );
	if( random(20) < 1 )
		set("double_attack",1);

	set("attitude", "peaceful");
	set("str", 30 + random(21));
    set("int", 30 + random(21));
	set("con", 30 + random(21));
	set("dex", 30 + random(21));

	set("qi", 10000);
	set("shen", 1000);
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
	object fbroom;
	int hard,level;

	::init();
	ob = this_object();
	fbroom=environment(ob);
	
	
	if(fbroom->query("leader"))  me = fbroom->query("leader");			
	

	if( query("init") == 0
	 && me->query_temp("gmd_job")
	 && userp(me) ) {
	 	
	 	set("init", 1);
	 	
		if( me->query_temp("gmd_job/lvl")){
			lvl = me->query_temp("gmd_job/lvl");
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
		
		lvl += me->query_temp("gmd_job/finish")*5;
		
		setparty(me->query_temp("gmd_job/finish"),lvl,lvl*lvl*lvl/10*6/5 );

		set("ciwei_level",me->query_temp("gmd_job/finish"));
				
		set_name("明教教众", ({"mingjiao jiaozhong", "jiao zhong","jiaozhong"}));
	    set("title", "五行旗副旗主");
		
		set("max_neili",query_skill("force")*8 + query("combat_exp")/1000);
		set("max_jingli",query_skill("force")*8);
		set("eff_jingli",query_skill("force")*8);
		
		set("shen", -1);

		copy_state();
		setup();
		reincarnate();	

        
								
		cloth = new(ARMOR_D("cloth"));
		cloth->set("name",HIW"火焰滚边白袍"NOR);
		cloth->move(ob);
		cloth->wear();		
		add_temp("apply/defense", 200);
	    add_temp("apply/armor", 200);
		add_temp("apply/attack",200);
        add_temp("apply/damage",200);
	   
		
       if (me->query_temp("gmd_job/finish"))
		   level=me->query_temp("gmd_job/finish");
	   else level=33;
	   
		set("double_attack",1);
		
		if(level<=10) 
		{
			hard =level*30;
		}	
		if(level>10) 
		{
			hard =level*level*3.5;
		}		
		if(level>20) 
		{
			hard=level*level*4;
		}
		
		if(level>30) 
		{
			hard=level*level*4;
		}
			    
             add_temp("apply/armor", hard);
			 add_temp("apply/defense", hard);
             add_temp("apply/attack",hard);
             add_temp("apply/damage", hard);			 
			 
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


void die()
{
	object me,ob;
	object fbroom;
	int level=1;
	int vip;

	ob = this_object();	
	
	
	fbroom=environment(ob);
	
	if(fbroom->query("leader"))
	{
		    me = fbroom->query("leader");		
            me->delete_temp("gmd_up");
			
			if (me->query("buyvip")) vip =5;
	        if (me->query("y-card-vip")) vip =10;
	        if (me->query("m-card-vip")) vip =20;
			
		 if (check2(ob,me))
		 {
			tell_room(fbroom, "明教教众仰天惨笑，突然间扑倒在地，一动也不动了。\n");
			
			//这里掉落残片
			 //外层判断富源和人品
			 //函数内判断vip,和人品
			if ((random(me->query("kar"))>20) && random(me->query_temp("gmd_job/finish"))>10 && random(vip)==1)
			{
			   if (dropcanpian(me,me->query_temp("gmd_job/finish")))
			    {
				    tell_object(me, HIY"你似乎看到从对方身上掉下一卷纸,眼看便要被风吹跑，你眼疾手快一把就抄了起来！\n"NOR);
			    }
			}
			
			::die();			
		 }
		 return;	 
	}
	::die();
}


int check2(object ob, object me)
{
	object *team;
    object fbroom;
	 int index;  
	
	team=me->query_team();	
	fbroom=environment(ob);
	
	if (!team) {
	    if( !me 
	 || !living(me)       
	 || !me->query_temp("gmd_job")	 
	 || environment(me)!=environment(ob)){
		tell_room(fbroom, "明教教众道：'就这点伎俩，也敢来攻打光明顶。'，说完转身离开。\n");
		
		fbroom->set("over",1);
		me->delete_temp("gmd_job");
		me->set_temp("gmdfail",1);
		me->apply_condition("job_busy",10+random(20));
		me->apply_condition("gmd_job",3); //這裏不能消除，否則無法退出副本
		//CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")围攻光明顶失败！\n"NOR);
		destruct(ob);
		return 0;
	}
	}
	else
	{
		
		if (me->query_temp("gmd_job/team") !=me->query_team())	
	    {
		    write(HIY "你组队出现问题，任务失败。\n" NOR);
		    me->set_temp("gmdfail",1);
			destruct(ob);
		    return 0;		
	    }		
		
		for(index=0;index<sizeof(team);index++){
			if (objectp(team[index]))
			{
			 if (!living(team[index]) || (environment(team[index])!=environment(ob)))
			 {
				 tell_room(fbroom, "明教教众道：'就这点伎俩，也敢来攻打光明顶。'，说完转身离开。\n");
				 team[0]->delete_temp("gmd_job");
				 team[0]->set_temp("gmdfail",1);
				 me->delete_temp("gmd_job");
				 me->set_temp("gmdfail",1);
				 team[index]->apply_condition("job_busy",10+random(20));
				 me->apply_condition("gmd_job",3);
				// CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")一行围攻光明顶失败！\n"NOR);	                
		          destruct(ob);
		          return 0;						 
			 }
			}
			else				
				{
					 tell_room(fbroom, "明教教众道：'就这点伎俩，也敢来攻打光明顶。'，说完转身离开。\n");
					 me->delete_temp("gmd_job");
				     me->set_temp("gmdfail",1);					 
					 me->apply_condition("job_busy",10+random(20));
					 me->apply_condition("gmd_job",3);	
                    // CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")一行围攻光明顶失败！\n"NOR);					 
		             destruct(ob);
					 return 0;
				}
			 }
		
	}
return 1;	
}



void check(object ob, object me)
{
   object *team;
   object fbroom;
   int index;   
	if( !ob ) return;
	team=me->query_team();
	//team=me->query_temp("gmd_job/team");
	
	checking(ob,me);
	
	command("lineup with menggu wushi 1");
	command("lineup with menggu wushi 2");
	command("lineup with menggu wushi 3");
	command("lineup with menggu wushi 4");
	command("lineup with menggu wushi 5");
	command("lineup form wuxing-zhen");
	command("lineup with menggu wushi 1");
	command("lineup with menggu wushi 2");
	command("lineup with menggu wushi 3");
	command("lineup with menggu wushi 4");
	command("lineup with menggu wushi 5");
		//|| me->query("qi")<1000			
	
	if (!team) {
	if( !me 
	 || !living(me)       
	 || !me->query_temp("gmd_job")	 
	 || environment(me)!=environment(ob)){
		tell_room(environment(ob), "明教教众道：'就这点伎俩，也敢来攻打光明顶。'，说完转身离开。\n");
		fbroom=environment(ob);
		fbroom->set("over",1);
		me->delete_temp("gmd_job");
		me->set_temp("gmdfail",1);
		me->apply_condition("job_busy",10+random(20));
		me->apply_condition("gmd_job",3); //這裏不能消除，否則無法退出副本
		//CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")围攻光明顶失败！\n"NOR);
		destruct(ob);
		return;
	}
	}
	else
	{
		for(index=0;index<sizeof(team);index++){
			if (objectp(team[index]))
			{
			 if (!living(team[index]) || (environment(team[index])!=environment(ob)))
			 {
				  tell_room(environment(ob), "明教教众道：'就这点伎俩，也敢来攻打光明顶。'，说完转身离开。\n");
				 team[0]->delete_temp("gmd_job");
				 team[0]->set_temp("gmdfail",1);
				 me->delete_temp("gmd_job");
				 me->set_temp("gmdfail",1);
				 team[index]->apply_condition("job_busy",10+random(20));
				 me->apply_condition("gmd_job",3);
                // CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")一行围攻光明顶失败！\n"NOR);	        
		          destruct(ob);
		          return;						 
			 }
			}
			else				
				{
					 tell_room(environment(ob), "明教教众道：'就这点伎俩，也敢来攻打光明顶。'，说完转身离开。\n");
					 me->delete_temp("gmd_job");
				     me->set_temp("gmdfail",1);					 
					 me->apply_condition("job_busy",10+random(20));
					 me->apply_condition("gmd_job",3);
					// CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")一行围攻光明顶失败！\n"NOR);	        
		             destruct(ob);
				}
			 }
		
	}
	
	call_out("check",1,ob,me);
}
