//jindao-heijian 阴阳倒乱刃法
//by fqyy 2003.5.9
/*
左刀横斫，
右剑斜刺。本来刀法以刚猛为主，剑招以轻灵为先，两般兵刃的性子截然相反，一人同使刀
剑，几是绝不可能之事，但公孙谷主双手兵刃越使越急，而刀法剑法却分得清清楚楚，刚柔
相济，阴阳相辅，当真是武林中罕见的绝技。

想到此处，猛地□左刀右攻，右剑左击，使出他平生绝学“阴阳
倒乱刃法”来。黑剑本来阴柔，此时突然硬砍猛斫，变成了阳刚的刀法，而笨重长大的锯齿
金刀却刺挑削洗，全走单剑的轻灵路子，刀成剑，剑变刀，当真是奇幻无方。
*/

//修订为nizhuan 

#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;
void remove_effect(object me, object weapon,object weapon2, int count);
int perform(object me, object target)
{
	int i,skill;
	object *inv;
	object weapon2;
        object weapon = me->query_temp("weapon");  

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("阴阳倒乱刃法只能对战斗中的对手使用。\n");
		if (!me->query_temp("jdhj/nizhuan"))
		{
			return notify_fail("金刀黑剑全凭一口气，你需运转金刀黑剑的逆转起手式。\n");
		}

        if( me->query_dex() < 60 )
                return notify_fail("你在身法上先天禀赋不足，不能使用阴阳倒乱刃法！\n");
        
        if( me->query_skill("dodge") < 450 )
                return notify_fail("阴阳倒乱刃法需要超绝的轻功配合，方能有效施展！\n");

        if( me->query_skill("sword") < 450 )
                return notify_fail("你剑法未到炉火纯青之境，还不会使用阴阳倒乱刃法！\n");
        if( me->query_skill("blade") < 450 )
                return notify_fail("你刀法未到炉火纯青之境，还不会使用阴阳倒乱刃法！\n");
        if( me->query_skill("jindao-heijian",1) < 450 )
                return notify_fail("你金刀黑剑未到炉火纯青之境，还不会使用剑圈封闭对方！\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("你的内力不够使用阴阳倒乱刃法！\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力不够使用阴阳倒乱刃法！\n");

        if (!weapon)
                return notify_fail("你手中无剑怎能使用阴阳倒乱刃法？！\n");
        if (me->query_temp("jdhj/luanren",1))
                return notify_fail("你正在使用阴阳倒乱刃法无法再阴阳倒乱刃法！\n");
    //    if (me->query_temp("jindao-heijian/nizhuan",1)&&me->query_skill("jindao-heijian",1)<300)
                //return notify_fail("你这点功夫就想使用阴阳倒乱刃法？！\n");
        if ( me->query_skill_mapped("sword") != "jindao-heijian"
          || me->query_skill_mapped("parry") != "jindao-heijian"
          || me->query_skill_mapped("blade") != "jindao-heijian"
          && userp(me))
             	return notify_fail("你必须先将黑剑金刀相互配合。\n");
       inv = all_inventory(me);
       for(i=0; i<sizeof(inv); i++) 
	   {
            if( inv[i]->query("equipped") || weapon == inv[i] ) continue;
			if (weapon->query("skill_type") == "blade")
			{
				   if( inv[i]->query("skill_type") == "sword" ) 
				   {
					   weapon2 = inv[i];
					   i = 3;
					   break;
					}
			}
			if (weapon->query("skill_type") == "sword") 
			{
				if( inv[i]->query("skill_type") == "blade" ) 
			    {
				   weapon2 = inv[i];
				   i = 2;
				   break;
			    }
		    }
       }
		if (!objectp(weapon2)) return notify_fail("你只有一种兵器就想阴阳倒乱刃法？\n");
	
		message_vision(YEL"\n$N左刀横斫，右剑斜刺。本来刀法以刚猛为主，剑招以轻灵为先，两般兵刃的性子截然相反，一人同使刀\n"+
					"剑，几是绝不可能之事，但$N双手兵刃越使越急，而刀法剑法却分得清清楚楚，刚柔相济，阴阳相辅，\n"+
					"当真是武林中罕见的绝技。\n\n" NOR, me);
		
        skill = me->query_skill("jindao-heijian", 1)/4*i;
        //skill = me->query_skill("jindao-heijian", 1)/4*i;
   
		me->add_temp("apply/attack", skill/5 );
        me->add_temp("apply/damage", skill/5 );
        
        me->set_temp("jdhj/luanren",skill);
		if (wizardp(me))
		{
			write("skill="+skill);
		}
        //if( me->is_fighting() && userp(me))
        //	me->start_busy(1);
       // me->start_perform(1,"阴阳倒乱刃法");
        me->add("neili", -800);
        me->add("jingli", -500);
		//call_out("remove_effect", 1, me, weapon,weapon2, skill/3);
		
		remove_effect(me,weapon,weapon2,skill/3);
		return 1;
}

void remove_effect(object me, object weapon,object weapon2, int count)
{
        int skill;
		if ( !me||!me->query_temp("jdhj/luanren") ) return;
        skill=me->query_temp("jdhj/luanren");
		
        if (count-- < 0
			||me->query_skill_mapped("sword")!="jindao-heijian"
			||me->query_skill_mapped("blade")!="jindao-heijian"
			||me->query_skill_mapped("parry")!="jindao-heijian"
			||!me->query_temp("weapon")
			||!objectp(weapon2)
			||weapon != me->query_temp("weapon")
			||!me->is_fighting())
		{
			me->add_temp("apply/attack", - skill/5);
          	me->add_temp("apply/damage", - skill/5);
          	me->delete_temp("jdhj/luanren");
			message_vision(YEL"\n$N心中有些顾虑，攻守难以兼顾，慢慢收回了攻势。\n\n" NOR, me);
			return;
        }
            call_out("remove_effect", 1, me, weapon,weapon2, count);
}
string perform_name(){ return YEL"阴阳倒乱刃法"NOR; }

int help(object me)
{
        write(HIC"\n金刀黑剑"+YEL"「阴阳倒乱刃法」"NOR"\n");
        write(@HELP
	金刀黑剑是情人谷公孙芷的家传武功，左手金刀右手黑剑
	金刀以劈砍切削之攻击，黑剑乃刺扎削之效果，金刀以刚
	性为主，黑剑以阴性为主，两者组合后会令人防不胜防。
	尤其是铁掌裘千尺嫁给公孙芷后，对这门武功去腐存精加
	以完善。更达到炉火纯青之境。但此门武技的缺点也是显
	然，正如裘千尺所言“难练易破”，存在致命缺点。
	铁掌弟子可以凭借身份解救裘千尺并获得裘千尺的指点，
	则此门功夫将更上层楼。
	黑剑本来阴柔，此时突然硬砍猛斫，变成了阳刚的刀法，
	而笨重长大的锯齿金刀却刺挑削洗，全走单剑的轻灵路子
	刀成剑，剑变刀，当真是奇幻无方。

	注意：set 金刀黑剑 倒乱刃 有机会打掉对方兵器。
	
	指令：perform sword(blade).nizhuan

要求：
	当前内力要求 1000 以上；
	当前精力要求 1000 以上；
	金刀黑剑等级 450 以上；
	基本轻功等级 450 以上；
	基本剑法等级 450 以上；
	基本刀法等级 450 以上；	
	后天身法等级 60 以上；	
	激发刀法为金刀黑剑。
	激发剑法为金刀黑剑。
	激发招架为金刀黑剑。
	激发内功不限；
	手持刀(剑)类武器并身上带对应配套武器。

HELP
        );
        return 1;
}
