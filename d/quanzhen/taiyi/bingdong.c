//Cracked by Kafei
// road: /d/zhongnan/bingdong.c
// by sdong 08/98

#include <ansi.h>
#include <room.h>
inherit ROOM;
private int blow_result(object victim);
int blow();
int do_dig();
void setup_ob(object me,object victim);

void create()
{
		  set("short",WHT"冰洞"NOR);

		  set("long",@LONG
这个大洞又高又宽，洞壁是天然花岗岩的，洞内寒气逼人，地上结着厚厚的坚冰。
你冷的都有些发抖。
LONG);

		  set("exits",([
				"east": __DIR__"xuanya4",
							 ])
			  );
	  set("cost",1);
	  setup();
}

void init()
{
	add_action("do_dig", "dig");
	remove_call_out("blow");
	call_out("blow",4 + random(3) );
}

int do_dig()
{
	remove_call_out("blow");
	call_out("blow",1 );
	return 1;
}

int blow()
{
	object *inv = all_inventory(find_object(__DIR__"bingdong"));
	object ob, me= this_player();
	int i;

	if( !this_player() || !environment(this_player()) )  return 1;
	if( base_name(environment(this_player())) != __DIR__"bingdong") return 1;

	message_vision( HIW"\n你觉得一阵冷气逼来，全身的血液都快冻僵了！\n"NOR, this_player() );

	for ( i=0 ; i < sizeof(inv); i++)
	{
		if ( (string)inv[i]->query("race") == "人类" )
		{
			blow_result(inv[i]);
		}
	}
	

	remove_call_out("blow");
	call_out( "blow",4 + random(3) );
	return 1;
}

private int blow_result(object victim)
{
	object ob2;

	if( random(60)==1 )
	{
		ob2=new(__DIR__"bigtiger");
		ob2->move(environment(victim));
		message_vision(HIR"突然从洞口中走进一只$N，它看到有人，怒吼一声，发疯似地向$n发起进攻！\n"NOR, ob2,victim);
		setup_ob(ob2,victim);
		ob2->kill_ob(victim);
		ob2->add_temp("offenders/"+victim->query("id"), 1);
		ob2->start_busy(1+random(3));
		victim->kill_ob(ob2);
	}

	if( random( victim->query_skill("force") ) > 45 && victim->query("neili") > 20 )
	{
		message_vision( HIC"\n$N赶紧运功抵御！\n"NOR, victim );
		victim->add_temp("xtg/yungong",1);
		if( victim->query_skill("force",1) < 350 )
			victim->improve_skill( "force",victim->query("con")+10 );
		victim->add("neili",-random(40));
		//引出程序调用,一天一次
		if (random(victim->query_temp("xtg/yungong"))>20
			&&victim->query_temp("quest/qz/xtg/wuqi/askhao")
			&&victim->query("quest/qz/xtg/wuqi/start")
			&&(time()-victim->query("quest/qz/xtg/wuqi/time"))>86400)
		{
			remove_call_out("xtg_effect");
			call_out("xtg_effect",1,victim);
			victim->delete_temp("qest/xtg/askkma");
		}
	}
	else
	{
		message_vision( HBWHT"\n$N被冻地打了个冷颤！\n"NOR, victim );
		victim->receive_wound("qi", random(300));
		victim->receive_damage("qi", random(500));
		if( victim->query_skill("force",1) < 300 )
			victim->improve_skill( "force",victim->query("con")*victim->query("int") );
	}


	return 1;
}

int xtg_effect(object me)
{
	int i,j,k;
    if (!me) return 0;
 
	i=random(me->query("kar"));
	if (me->query("marry"))
	{
		k=4;
	}else k=0;

	message_vision(HIC"剧烈的寒气慢慢侵入骨髓，辛苦修炼的先天功此时忽然化为一股暖融融的气流，遍布$N周身!\n"NOR,me);
	j = 20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	j=random(j);

    if (me->query("kar")>30) 
    {
	  log_file("quest/bug", sprintf("%s(%s) 参悟先天功五气朝元时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
    }
	if (i>27
		&& j<3
	   	&& random(me->query("con"))>(40+k)
		&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n一股暖流起于尾闾，顺督脉而上，到达百汇穴，盘旋良久。\n"
		 +"然后豁然而下，势如破竹，旋即复归于丹田，悠悠不绝。\n"+
			 " $N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIY"\n$N经过不断领悟，终于领悟了先天功五气朝元的奥秘，先天功豁然贯通！”\n"NOR,me); 
		 message_vision(HIG"\n恭喜！！，$N千辛万苦，终于得偿所愿，解开先天功五气朝元的终极谜题！”\n"NOR,me); 

         log_file("quest/xtgwqcy", sprintf("%s(%s) 成功！第%d次参悟，机缘巧合下，成功参悟先天功五气朝元的奥秘，当前随机幸运值：%d,当前随机值：%d,当前根骨值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/qz/xtg/wuqi/fail"),
		 i,
		 j,
		 me->query("con"),
         me->query("combat_exp")));

		 me->set("quest/qz/xtg/wuqi/time",time());
		 me->set("quest/qz/xtg/wuqi/pass",1);
		 me->delete_temp("quest/xtg");
		 me->delete_temp("xtg");
		 me->start_busy(1);
		 me->set("title",HIC"先天功"+HIR" 五气朝元"NOR);
		 me->add("mytitle",HIC"先天功"+HIR" 五气朝元"NOR);

		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N枯坐半晌，内功修炼仿佛遇到一层壁垒,无法突破。\n"NOR,me); 
		 message_vision(HIY"\n没能领悟透彻五气朝元的先天罡气！\n"NOR,me); 
		 me->apply_condition("snake_poison",1);
		 message_vision(HIY"\n参悟先天功五气朝元绝技解密失败！\n"NOR,me); 
         log_file("quest/xtgwqcy", sprintf("%s(%s) 失败！第%d次失败参悟先天功五气朝元绝技，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/qz/xtg/wuqi/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/qz/xtg/wuqi/fail",1);
		 me->set("quest/qz/xtg/wuqi/time",time());
		 me->delete_temp("quest/xtg");
		 me->delete_temp("xtg");

		 me->start_busy(1);
		 return 1;
   }

}

//复制数据
void setup_ob(object me,object victim)
{
	object *inv;
	mapping skill_status;
	string *sname;
	int i, max = 0, max1, j;


	if ( !me->query_temp("copied") ) {
		if ( mapp(skill_status = victim->query_skills()) ) {
		skill_status = victim->query_skills();
		sname = keys(skill_status);

		for(i=0; i<sizeof(skill_status); i++) {
			if ( skill_status[sname[i]] > max ) max = skill_status[sname[i]];
		}


		max1 = (int)max + random(max*3);

		if( victim->query("combat_exp",1) < 10000 ) max1 = max1/2;
		me->set_skill("dodge", max1);
		me->set_skill("parry", max1 );
		me->set_skill("force", max1);
		me->set_skill("strike", max1);
		me->set_skill("cuff", max1);
		me->set_skill("claw", max1);
		me->set_skill("force", max1);
		me->set_skill("yinyun-ziqi", max1);
		me->map_skill("force", "yinyun-ziqi");


		me->set("combat_exp", victim->query("combat_exp",1)+random(victim->query("combat_exp",1)/2));

		me->set("max_qi", victim->query("max_qi"));
		me->set("eff_qi", victim->query("max_qi"));
		me->set("max_jing", victim->query("max_jing"));
		me->set("eff_jing", victim->query("max_jing"));
		me->set("max_jingli", victim->query("max_jingli"));
		me->set("eff_jingli", victim->query("max_jingli"));

		me->set("qi", me->query("max_qi"));
		me->set("max_neili", victim->query("max_neili") );
		me->set("neili", victim->query("neili") );
		me->set("jing", me->query("max_jing"));
		me->set("jiali", victim->query("jiali")*3/4);
		if ( victim->query("max_jing") > 0 ) {
			me->set("max_jing", victim->query("max_jing"));
		}
		else me->set("max_jing", 500);
		me->set("jing", me->query("max_jing"));

		me->set("no_sing", 1);
		me->set_temp("copied", 1);
		me->set_temp("apply/attack", 80);
		me->set_temp("apply/damage", victim->query_temp("apply/damage") );
		}
	}
}
