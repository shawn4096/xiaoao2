// jianqin.c 一手执琴，一手执剑
// cre by sohu@xojh 2014
// 昆仑三圣 一手执琴，一手执剑，依靠强大内力，实施一心二用之术

#include <ansi.h>

#include <combat.h>

inherit F_SSERVER;

int exert(object me,object target)
{
	int i;
    string msg;
    object weapon,jwq;
	
	jwq=present("qin",me);
	
	i=me->query_skill("xuantian-wuji",1);

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("「琴剑双绝」只能对战斗中的对手使用。\n");

    if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
			return notify_fail("手中无剑,你怎么使得出「琴剑双绝」！\n");
   
    if(!jwq || !jwq->query("qinjian") )
			return notify_fail("你身上没有带琴，不能使用「琴剑双绝」！\n");
	if( me->query_temp("lyj/liangyi") )
			return notify_fail("你正在使用两仪决，不能使用「琴剑双绝」！\n");
	if( me->query_temp("xtwj/qinjian") )
			return notify_fail("你正在使用「琴剑双绝」！\n");
    if( (int)me->query_skill("liangyi-jian", 1) < 350 )
			return notify_fail("你的两仪剑法还未练成，不能使用！\n");
	if ( me->query_skill_mapped("sword")!="liangyi-jian")
            return notify_fail("你的剑法不是两仪剑，无法使用琴剑双绝。\n"); 
    if ((int)me->query_skill("xuantian-wuji", 1) < 350)
            return notify_fail("你的玄天无极功火侯太浅。\n"); 
	if( (int)me->query("max_neili", 1) < 5000 )
			return notify_fail("你现在最大内力不足，不能使用琴剑双绝！\n");
    if( (int)me->query("neili", 1) < 1000 )
			return notify_fail("你现在内力不足，不能使用琴剑双绝！\n");
	
	 if(!me->query("quest/kl/xtwj/qinjian/pass"))
			return notify_fail("你尚未解密琴剑双绝！\n");
		
		
				
    me->start_exert(1+random(3),"「琴剑双绝」");     	
    
    msg = HBGRN+HIY "\n$N剑交左手，剑势如风车般连环击出，挑、扎、刺，招式复杂多变，丝毫不带任何影响。\n"NOR;    	
	msg += BLU "\n随后，$N右手从容地从背囊中掏出一把"+jwq->query("name")+BLU"来，轻拢慢捻抹复挑，琴音铮铮作响！\n"NOR;    	

	message_vision(msg, me, target);	
	me->set_temp("xtwj/qinjian",1);
	call_out("remove_effect",1,me,i/5);
	return 1;
}

void remove_effect(object me, int count)
{
	
	int i;
	object jwq;
	if (!me) return;
	
	i=me->query_skill("xuantian-wuji",1);
	
	jwq=present("qin",me);
	
	if (objectp(me))
	{
        if  ( !me->is_fighting() || count < 0 )
		{	
        
			me->delete_temp("xtwj/qinjian");			
			if (i<450)
			{
				message_vision(WHT"\n$N的玄天无极功终究不纯，一不小心将琴弦按断数条。\n"NOR, me);
				jwq->add_temp("duan",1);
				//功力不纯，使用五次后琴断掉，450后正常
				if (jwq->query_temp("duan")>10)
				{
					message_vision(HIY"\n$N的玄天无极功终究不纯，最后一根琴弦被你按断，此琴彻底费去。\n"NOR, me);
					jwq->broken("按断的");
				}

			}
			else message_vision(CYN"\n$N的玄天无极功已然融会贯通，右手轻拢将琴放回囊中。\n"NOR, me);
			return;
		}
		call_out("remove_effect", 2, me, count -1);
        return;

	}
}

string exert_name() {return CYN"剑琴双绝"NOR;}

int help(object me)
{
        write(CYN"\n玄天无极功「剑琴双绝」："NOR"\n");
        write(@HELP
	何足道为当世之人成为“琴棋剑”三种绝技，号称昆仑三圣
	而据何足道自己所言，琴为第一，棋为次之，剑法为最末。
	后来何足道因代人传言，所以一路东进到嵩山少林寺，引
	一场惊世大战，在前进中，何足道在力斗少林俗家弟子时
	曾凭借深厚的内功，一手执剑，一手操琴，震惊当世。
	
	注意，此武技因为有一心二用之效果，所以不能和两仪剑
	法中两仪决共用。具体使用模式请玩家请自己摸索。
	
	指令：exert qinjian

要求:
	玄天无极功 350 级以上；
	最大内力 5000 点；
	当前内力 1000 点；
	两仪剑等级 350 级以上；
	激法内功为玄天无极功；
	激发剑法为两仪剑法；
	需要手执剑，身带琴
              
HELP
        );
        return 1;
}


/*
  if( random( attp ) > random( defp )/2 || target->is_busy()){
        
                message_vision( RED "$n躲闪不及，已经被飞散的碎片击中，全身血肉模糊！\n\n"NOR, me, target );
        
                damage = me->query_skill("liangyi-jian",1) + (int)me->query_skill("xuantian-wuji", 1)*2;
                damage = damage - random( target->query_skill("dodge")/3 );
                damage *= 2;
                if (damage>2500) damage = 2500;
                
                target->receive_wound("jing", random( damage/2 ));
                target->receive_damage("qi", 20 + random(damage));
                target->receive_wound("qi", 20 + damage);
                target->start_busy(3 + random(4));
                
                
                //追加攻击
                if( random( attp ) > random( defp ) || target->is_busy()) {
 
          message_vision( BBLU+HIW "$N将玄天无极发挥到及至，"HIG"五韵七弦"BBLU+HIW"剑真气激射而出，此时手中无剑亦有剑！\n\n"
         + NOR + RED"$n惨叫一声，身上已经被无形剑气穿透！\n"NOR, me, target );
 
                        damage *= 2;
                        target->receive_wound("jing", random( damage/2 ));
                        target->receive_damage("qi", 20 + random(damage));
                        target->receive_wound("qi", 20 + damage);
                        target->start_busy(2 + random(8));
                        }
            

        }


		
        msg = HIC "$N" HIC "手中长剑剑芒跃动，剑光暴长，剑尖颤动似乎分左右刺向$n"
              HIC "，\n$n" HIC "看到剑光偏左，疾侧身右转，但只这一刹，剑光刹时袭"
              "向右首！\n";
        if (random(me->query("combat_exp")) > (int)target->query("combat_exp") / 2 || !living(target))
        {
                me->start_busy(2);
                target->start_busy(random(3));
                damage = (int)me->query_skill("sword");
                damage = damage / 2 + random(damage / 2);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIC "$n" HIC "疾忙左转，却发现$N"
                                           HIC "的剑根本没有右偏，" + weapon->name() +
                                           HIC "登时把$n" HIC "的左胸留下一个血洞，"
                                           "血涌泉喷出！\n" NOR);
                me->add("neili", -180);
        } else
        {
                me->start_busy(2);
                msg += HIY "可是$p" HIY "轻轻一笑，侧身右转，果然$P"
                       HIY "的剑式突然左展，在$p" HIY "身前\n划过，"
                       "仅差半寸。却是一根毫毛都没伤到。\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
*/