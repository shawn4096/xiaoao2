
#include <ansi.h>
inherit FORCE;
#include "/kungfu/skill/force.h"
#include <combat_msg.h>

int valid_enable(string usage) {
   if ( this_player()->query("quest/雪山飞狐/武功/lengquanshengong_teach"))
             return usage == "force"; }
int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 20)
                return notify_fail("你的基本内功火候还不够。\n");
        return 1;
}

void skill_improved(object me)
{
        if (me->query_skill("lengquan-shengong", 1)>=220 && !me->query("quest/雪山飞狐/武功/lengquan"))
        {
                tell_object(me, HIW"\n忽然，你感觉体内寒气越聚越盛，全身似乎堕入冰窖，寒冷刺骨！\n"NOR);
                tell_object(me, HIW"\n过了一会，体内寒气逐渐聚在丹田处，全身精神为之一振，功力修为大大提升！\n"NOR);
                me->add("max_neili", me->query_skill("lengquan-shengong", 1)*2 + random(me->query_skill("lengquan-shengong", 1)*2));
                me->set("quest/雪山飞狐/武功/lengquan", 1);
        }
}
int practice_skill(object me)
{
        if((int)me->query_skill("lengquan-shengong", 1) >= 200)
        {
                if( (int)me->query("potential", 1) > 5
                 && (int)me->query("neili", 1) > 200)
                {
                        me->improve_skill("lengquan-shengong", (int)me->query_int()*2);
                        me->add("neili", -100); 
                        me->add("potential", -1*(1+random(3)));
                        return 1;
                }
                else
                        return notify_fail("你现在的修为不足以提高冷泉神功了。\n");
        }
        else
                return notify_fail("你现在的冷泉神功修为只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
       return __DIR__"lengquan-shengong/" + func;
}

mapping exercise_msg(object me)
{
  return ([
     "status_msg" : HIB + me->name()+"盘膝练功，脸上竟隐隐显出蓝光!" NOR,
    "start_my_msg" : HIW"你盘膝而坐，形神合一，暗运「"HIB"冷泉神功"HIW"」，将冷泉内劲游走全身经络。\n"NOR,
    "start_other_msg" : HIW + me->name()+"盘膝就座，开始运功打坐。\n"NOR,
    "halt_msg" : HIY"忽然$N双眼一睁，一声长啸，将运转全身的「"HIB"冷泉内劲"HIY"」散去，随即站了起来。\n"NOR,
    "end_my_msg" : HIB"你已将「冷泉内劲」游走全身经脉诸穴，只觉精神充沛，内劲充足无比！\n"NOR,
    "end_other_msg" : HIC"只见"+me->name()+"微微一笑，收起修炼打坐的姿势，缓缓站立起来，脸上竟透出隐隐蓝气\n"NOR,
    "heal_msg" : HIC"$N连催"+chinese_number(3+random(7))+"道冷泉内劲游走受损经络开始运功疗伤！\n"NOR,
    "heal_finish_msg" : HIC"就一眨眼功夫，$N双眼缓缓睁开，长长地吐出了一口浊气，哪里还有半点受伤的样子！\n"NOR,
    "heal_unfinish_msg" : HIM"$N突然「呼」的一声，吐出了一口气，看起来伤势并没有完全好转。\n"NOR,
    "heal_halt_msg" : HIB"$N心神一急，将游走全身的冷泉内劲立即散去，脸上蓝气大盛！\n"NOR,
    ]);
}


int ob_hit(object ob, object me, int damage)
{
	int skill = me->query_skill("force");
	int skill2= ob->query_skill("force");
	int neili = me->query_skill("neili");
	int neili2= ob->query_skill("neili");
        int i = 1;
	string msg;

   if(!me->query("quest/雪山飞狐/武功/lengquanshengong_teach"))     return 1;
//   if(me->query_temp("hjdf/fdj")) return 1;
   if ( random(skill) > (skill2*14/10/2-1) )
	{
            msg = HIB"$N"+HIB+"默运冷泉神功，化去了$n"HIB;
			if(neili > neili2*2)
			{
				msg += "大部分的攻击！\n"NOR;
                           i = -(damage/2 + random(damage/2));
			}
			else 
			{
				if(neili < neili2/4) 
				{
					msg += "很少的一点攻击！\n"NOR;
                                   i = -random(damage/5);
				}
				else 
				{
					msg += "一部分的攻击！\n"NOR;
                                   i = -(damage/4+random(damage/4));
				}
			}
		   message_vision(msg, me, ob);		
	}
   if (me->query_temp("lqsg/lq"))
   {
       message_vision(HIW"$N运起「"HIB"冷泉"HIW"」绝技发挥的淋漓尽致！$n的劲力又被$N周身的白雾化去，$N几乎没怎么收到这次攻击的影响！\n"NOR,me,ob);
       i = -damage;
   }
	return i;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor, string attack_skill)
{
	int skill,i;
	if(!me->query_temp("quest/雪山飞狐/武功/lengquan"))	return;
	
	if(random(me->query("combat_exp"))<victim->query("combat_exp")/2) return;
	
	if(me->query_temp("quest/雪山飞狐/武功/force_attack"))
	{
		me->delete_temp("quest/雪山飞狐/武功/force_attack");
		return;
    }
	me->set_temp("quest/雪山飞狐/武功/force_attack",1);
	
	if (random(me->query_dex()) > victim->query_dex()/2)
	{
		message_vision(WHT"$n被$N这一招砍伤，急忙运起内力，驱出寒气，不由一阵手忙脚乱！\n"NOR, me, victim);
	   // victim->start_lost(2+random(2));
		victim->add_temp("lost_attack",2+random(2));
		victim->add_busy(1);
		me->add("jingli",-50);
		me->add("neili",-100);
	 }
	 else if (random(me->query_con()) > victim->query_con()/2)
	 {
        message_vision(WHT"$n突然发现一缕寒气已经深入到五脏六腑，急忙运起内力，却为时已晚！\n"NOR,me,victim);	
        victim->add_condition("cold_poison", victim->query_condition("cold_poison")+random(2)+1);
	 }
     else if(userp(me))
	 {
		 	
	    skill = me->query_skill("force",1);

	    i = damage_bonus * (skill+1) / 1000;
	    i = i/2+ random(i);
	    if(me->query_temp("weapon"))
		    i = i*3;
	    if(me->query_temp("apply/damage")>=5000)
		 i = 5000+random(1000);
        message_vision(HBWHT"$n突然感觉真气隔阂，急忙运起内力驱寒，却只感觉胸口郁闷，哇的吐出一口鲜血！\n"NOR,me,victim);	
        if(victim->query("qi")<i) i=victim->query("qi");
		victim->receive_damage("qi",i/2,me);
		victim->recieve_wound("qi",i/2,me);

	 }
 
} 
