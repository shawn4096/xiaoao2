// wudi.c 
// by fengyue

#include <ansi.h>
inherit F_CLEAN_UP;

string exert_name() {return HBRED+HIW"无敌大法"NOR;}

void remove_effect(object me, int amount);
void remove_effect2(object me, int amount);

int exert(object me)
{
        int i,j;
        string s;

        if((int)me->query_skill("dulong-dafa",1) < 350  )
                return notify_fail("你的毒龙大法功力不够，无法施用「无敌」大法。\n");
         if((int)me->query_skill("force",1) < 350  )
                return notify_fail("你的基本内功功力不够，无法施用「无敌」大法。\n");
		  if((int)me->query_skill("shenlong-yaoli",1) < 150  )
                return notify_fail("你的神龙药理功力不够，无法施用「无敌」大法。\n");
        if((int)me->query("max_neili") < 3500 )
                return notify_fail("你的最大内力不够，无法使用「无敌」大法。\n");
		if((int)me->query("neili") < 1000 )
                return notify_fail("你的当前内力不够，无法使用「无敌」大法。\n");
        if((int)me->query("eff_qi") < me->query("max_qi")/10 )
            return notify_fail("你现在受伤过重，不能使用「无敌」大法。\n");

        if( me->query_temp("sld/wudi") && environment(me)->query("no_death"))
               return notify_fail("没必要生死相搏吧。\n");

        if( (int)me->query_temp("sld/wudi2") )
                return notify_fail("你不要命了吗？你已经发挥最大潜力。\n");

        if((int)me->query("neili") < 1000  )

			return notify_fail("你的真气不够，无法使用「无敌」大法。\n");

        i = me->query_skill("dulong-dafa", 1);
      
 //判断无敌2    
	    if( me->query_temp("sld/wudi") 
			 && me->query("eff_qi") < me->query("max_qi")			 
			 && !me->query_temp("sld/wudi2") )
         {
			if( me->is_fighting() )
			{   
                s=RED"\n$N发疯般的叫道：“洪教主神通护佑，众弟子勇气百倍，以一当百，以百当万。\n"+
                "洪教主神目如电，烛照四方。我弟子杀敌护教，洪教主亲加提拔，升任圣职。\n"+ 
                "我教弟子护教而死，同升天堂！”，突然喷出一口鲜血，似乎已经忘记了伤痛！\n\n"NOR;

           
                if (!me->query("quest/sld/dldf/pass") && !random(3))
                {
					me->add("max_neili", -1); // 1点max neili作为代价得到高攻击力
                }
                          
                me->set("neili", me->query("max_neili")*2);
                me->set("jingli", me->query("eff_jingli")*2);
                me->set_temp("double_attack",1);
                me->add_temp("apply/attack", i/3);
                me->set_temp("sld/wudi2", i);
				me->reincarnate();

				//remove_call_out("remove_effect");
                //call_out("remove_effect",20, me);

                me->start_exert(1,"「无敌」");
                message_vision(s, me);
                return 1;
          }
		  else return notify_fail("你又没在战斗，用得着这么拼命么？\n");

        }
		//无敌1
		else if (!me->query_temp("sld/wudi"))
		{
			  me->set_temp("sld/wudi", i); 
			  me->add("neili", - 200);
                s=HIR"\n$N大声叫道：“洪教主神通广大，我教战无不胜，攻无不克，无坚不摧，无敌不破，\n"+
                "敌人望风披靡，逃之夭夭！”，双眼突然冒出一丝红光，似乎突然增加了功力！\n\n"NOR;
                 if (me->query("quest/sld/dldf/pass"))
                 {
					s+=HBRED+HIY"$N咬破自己的舌尖，鲜血飞溅，毒龙大法宛如一个气球，包裹在$N周围，毒龙大法的大威力至此方显。\n"NOR;
					me->add_temp("apply/damage",i/8);
					me->add_temp("apply/defense",i/6);					
					me->add_temp("apply/armor",i/6);
					me->set_temp("sld/wudi3",1);
                 }
				 //防止反复叠加
				if (j=me->add_temp("apply/attack"))
				{
					me->delete_temp("apply/attack");
                    me->delete_temp("apply/strength");		
				}
                 me->add_temp("apply/attack", i/3);
                 me->add_temp("apply/strength", i/15);				 
                                
				call_out("remove_effect",30, me);
                me->start_exert(1,"「无敌」");
                message_vision(s, me);
                return 1;			
		}               
       
		return notify_fail("你现在不需要使用「无敌」大法。\n");
}

void remove_effect(object me)
{
        int i,j;
        if(objectp(me) && me->query_temp("sld/wudi")) 
        {           
           i = me->query_temp("sld/wudi");
           me->add_temp("apply/strength", -i/15);
           me->add_temp("apply/attack", -i/3);		   
		   if (me->query("quest/sld/dldf/pass"))
           {
					me->add_temp("apply/damage",-i/8);
					me->add_temp("apply/defense",-i/6);					
					me->add_temp("apply/armor",-i/6);
            }
           me->delete_temp("sld/wudi");           
           message_vision(HIR"\n$N好象虚脱了一样，突然垮了下来！\n"NOR,me);
		   
		   if (me->query_temp("sld/wudi2"))
		   {
			    j = me->query_temp("sld/wudi2");                  
                me->add_temp("apply/attack", -j/3);
                me->delete_temp("double_attack");
				me->delete_temp("sld/wudi");
                me->delete_temp("sld/wudi2");
				me->delete_temp("sld/wudi3");
                message_vision(RED"紧接$N着心神一松，再也支持不住，神情顿时更显萎靡之态！\n"NOR,me);
		   }
		   
        }
}


int help(object me)
{
        write(WHT"\n毒龙大法之"+HIR"「无敌大法」"WHT"：\n\n"NOR);
        write(@HELP
	毒龙大法乃是神龙岛内功绝技，乃是开山祖师
	洪教主根据门派独特心法所创立。既有其蛇毒
	的特性，又有其强悍的一面。
	「无敌大法」绝技乃是利用深厚的内功心法和
	独特的神龙药理知识相结合，在短时间内大幅
	提升自己的功力，且越战越强。

	使用指令：yun wudi
		
要求：
	当前内力要求 1000 以上；
	最大内力要求 3500 以上；
	基本内功等级 350  以上；
	毒龙大法等级 350 以上；
	神龙药理等级 150 以上；
	激发内功为毒龙大法；
注意：
	1、若没有解开毒龙大法的谜题，会随机掉落
	使用者的最大内力。解开谜题后，毒龙大法将
	发生巨大的飞跃。
	2、有效的设置会有意想不到的效果，若身上
	带有宠物蛇，则可以通过不同的设定达到不同
	的效果，具体指令如下：
	set 驱蛇 <攻敌> 
	效果：宠物蛇会自动攻击敌人，伤气且中毒
	set 驱蛇 <护体>
	效果：宠物蛇会替自己抵挡部分进攻，甚至
	极其有可能替你抵挡致命一击。宠物蛇会因此
	死亡，需要重新培养。	
HELP
        );
        return 1;
}

