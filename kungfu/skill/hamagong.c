// hamagong.c 蛤蟆功
// reModified by fengyue


inherit FORCE;

int get_bouns(int damage,int t,int level,int flag);
int valid_enable(string usage) { return usage == "force"; }

#include "/kungfu/skill/force.h"
#include <ansi.h>


int valid_learn(object me)
{
	if( me->query_skill("hamagong", 1) < 100 )
		return notify_fail("蛤蟆功不是随便什么地方都可以练习的。\n");
	return 1;
}


int practice_skill(object me)
{
	if((int)me->query_skill("hamagong", 1) >= 100 ){
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200){
			me->improve_skill("hamagong", (int)me->query_int());
			me->add("neili", -150);
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("你现在的修为不足以提高蛤蟆功了。\n");
	}
	else return notify_fail("蛤蟆功不可随便练习。\n");
}


string exert_function_file(string func)
{
	return __DIR__"hamagong/" + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIW + me->name()+"半蹲在地上，身冒白气" NOR,
		"heal_msg" : HIW"$N全身放松，半蹲在地上开始运功疗伤。。\n"NOR,
		"heal_finish_msg" : HIW"$N“哇！”的大叫一声，全身的白气渐渐消散。\n"NOR,
		"heal_unfinish_msg" : "$N“哇！”的大叫一声，站了起来，但脸色苍白，看来还有伤在身。\n",
		"heal_halt_msg" : "$N身冒白气，“哇！”的大叫一声，站起身来。\n",
	]);
}


string* msgs =
({
        HBRED"$N突然身形一让，微微侧头，一口唾沫吐出，去势猛烈！\n"NOR,
        HBWHT"$N斗然张口急咬，看来似乎滑稽，但因张口快捷，教人难以躲闪！\n"NOR,
        HBMAG"$N又是一口唾沫急吐，竟将痰涎唾沫也当作了攻敌利器，夹在拳招之中使用！\n"NOR, 
        HBWHT"$N蛤蟆功逆转运用，上者下之，左者右之，一掌拍回！\n"NOR,
        HBCYN"$N逆运经脉，更是厉害，一见对方招来，便口吐白沫，举头猛撞！\n"NOR, 

});

int ob_hit(object ob, object me, int damage)
{
    int t;
    t = random(10);        
	if(!environment(me)) return 0;
	if( me->query("env/蛤蟆功")=="逆转" && t> 6)		
		{
			message_vision(msgs[random(sizeof(msgs))]+"$n猛然间被$N吓了一大跳，这招不由得慢了几分！\n"NOR,me,ob);
			return -get_bouns(damage,t,me->query_skill("hamagong",1),1);
		}
	
    if( (me->query("qi")-damage) >= 3000 ) return 0;
	
    if ( t >= 5 && me->query("env/蛤蟆功")=="逆转" )
      {       
	       message_vision(HIY"$N"HIY"$N眼见情形危机，伸手在自己脸上猛抓一把，又反足在自己屁股上狠踢一脚，出招完全不按常理，却躲过了这致命的一击！\n" NOR, me);
	       return -damage;
      }
}

int hit_ob(object me,object victim,int damage)
{
	if(!me) return 0;
	if(!environment(me)) return 0;
	
	if (me->query_temp("hmg/powerup")
		&&random(10)>5
		&&me->query("env/蛤蟆功散毒"))
	{
		//message_vision(msgs[random(sizeof(msgs))]+"\n$N蛤蟆功劲气凌厉，体内蓄积已久的毒素向外溢出。\n"NOR,me);
	//	write("1111111111");
		message_vision(HIB"$N蛤蟆功劲气凌厉，体内蓄积已久的毒素向外溢出。\n"NOR,me);
		if (!random(2)
		&&me->query("baituo/poison/gsdu")	
		&&!me->query_condition("snake_poison"))
		{
			victim->apply_condition("snake_poison",2);
		}else if (!me->query_condition("hama_poison")
				  && random(10)>6
				  && me->query("baituo/poison/chanchu"))
		{
			victim->apply_condition("hama_poison",2);

		}
	}

	if( me->query("env/蛤蟆功")=="逆转" &&me->query_temp("hmg_nizhuan"))
	{
		int t;
        t = random(10);
		
        if( t > 6 )
		{
            message_vision(msgs[random(sizeof(msgs))],me);
			
           // message_vision(msgs[random(sizeof(msgs))]+"$N经脉逆运，神智不清，出手却是越发凌厉。\n"NOR,me);
			return get_bouns(damage,t,me->query_skill("hamagong",1),1);
		}
        if (t>7)
        {
            message_vision(HBRED"$N经脉逆运，神智不清，出手却是越发凌厉。\n"NOR,me);
            return get_bouns(damage,t,me->query_skill("hamagong",1),2);
        }
		if (me->query_temp("hmg_nizhuan") && me->query("oyf/hamagong",1)==3 && random(10)>6)
	    {
		  if (me->is_busy()){		
			message_vision(HIR "\n$N已然将九阴真经逆练成功，全身经脉逆转，杂乱无序，全身功力流转，和寻常武学的经脉大为不同。\n"
				  +"在逆转功力运行下，一路充穴破关，将封住的穴位重新打通,$N又恢复了行动。\n" NOR, me,victim);
            me->start_busy(-1);
		  }
		  if( me->query_condition("no_exert") ){
               message_vision(HIY"$N默运蛤蟆功真气，经脉逆转之下，压下了翻腾不已的气血！\n"NOR,me);
               me->clear_condition("no_exert");
           }
	    }
	}
	return 0;
}

int get_bouns(int damage,int t,int level,int flag)
{
	int dm;
	dm= (damage*flag*(t+level/20))/(t+level/20+10);
	if(flag && level>350) dm += dm/2;
	if(flag && level>450) dm += dm/2;
	return dm;
}
