//By sohu@xojh 疯魔杖

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name(){ return HIR"疯魔诀"NOR; }

int perform(object me,object target)
{
    object weapon;
    int i;
    
    if( !target ) target = offensive_target(me);
     
    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("疯魔诀只能对战斗中的对手使用。\n");

   // if(me->query_skill_mapped("force") != "huntian-qigong")
               // return notify_fail("你的内功不是混天气功，无法使用疯魔诀！\n");
    if( (int)me->query_skill("force", 1) < 350 )
                return notify_fail("你的基本内功还未练成，不能使用疯魔诀！\n");
    if( (int)me->query_skill("fengmo-zhang", 1) < 350 ) 
                return notify_fail("你的疯魔杖法还未练成，不能使用疯魔诀！\n");
    if((int)me->query_skill("staff", 1) < 350 )
                return notify_fail("你的基本杖法不够娴熟，不能在使用疯魔诀。\n");
    if((int)me->query_dex(1) < 40 )
                return notify_fail("你的身法还不够灵巧，不能使用疯魔诀。\n");
    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "staff"
        || me->query_skill_mapped("staff") != "fengmo-zhang"
        || me->query_skill_mapped("parry") != "fengmo-zhang")
                return notify_fail("你现在不激发疯魔杖法，使得了疯魔诀么？\n");
                
    if((int)me->query("max_neili") < 4500 )
                return notify_fail("你的内力修为不够，不能使用疯魔诀！\n");
    

    message_vision(HIR"\n$N状若疯狂，怒发冲冠，大喝一声，浑然不顾，将手中的"+weapon->query("name")+RED"抡圆了，瞬间向$n挥出一百零八招！\n"NOR,me,target);

       
    i = me->query_skill("fengmo-zhang",1);
	if (me->query_skill("huntian-qigong",1)>350)
		    i += (int)me->query_skill("huntian-qigong",1)/5;
        
		me->add("neili", -300);
        me->add_temp("apply/attack",  i/3);
        me->add_temp("apply/damage",  i/4);
        
        me->set_temp("fmz/fengmo",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),(i<350)?1:3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),(i<250)?1:3);
		
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
	       
		if (me->is_fighting(target)
		&& me->query_skill_prepared("hand")=="suohou-shou"
		&& me->query_skill("suohou-shou",1)>300)
		{
		 weapon->unequip(); 
	     me->add_temp("apply/hand", i/3);
		 message_vision(HIR"$N将手中的"+weapon->query("name")+HIR"拎在手中，暗运真气，陡然施展出马副帮主绝技锁喉手!\n"NOR,me,target);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1); 
		 target->add_busy(1);
		 me->add_temp("apply/hand", -i/3);
         weapon->wield();
		}
        me->add_temp("apply/attack",  -i/3);
        me->add_temp("apply/damage",  -i/4);
        me->delete_temp("fmz/fengmo");
    
    me->start_busy(1);
    target->start_busy(1);
	me->start_perform(3+random(2),"「疯魔诀」");
    return 1;
}

int help(object me)
{
   write(WHT"\n疯魔杖法之"HIR"「疯魔诀」："NOR"\n");
   write(@HELP
	疯魔杖法乃是丐帮扬州分舵主马俱为的成名武技，该杖法原本源自少林。
	后来在江湖中流传，经历代高手去芙存精，使得疯魔杖法不断精炼，招式
	越加犀利。疯魔诀乃是凭借一口真气，奋不顾自己的安危，全力抢攻，瞬
	间施展出一百零八招攻击，令对方目不暇接，难以应付。
	注意：若激发并备 hand 锁喉手,300级后会能再出一招。男性有优势,350
	   级后若激发混天气功并运使混天功则本招飞跃。
	
   指令：perform staff.fengmo

要求：  
	最大内力 4500 以上；
	当前内力 2000 以上；
	疯魔杖法等级 350 以上；
	基本内功等级 350 以上；
	后天身法 40 以上；
	激发招架为疯魔杖法,
	装备杖法

HELP
   );
   return 1;
}
