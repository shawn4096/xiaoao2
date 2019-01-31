// sanwu.c 三无三不手
// By River@SJ 02/16/2001

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>
string perform_name(){ return HIW"三无三不手"NOR; }
int perform3(object me,object target);
int perform2(object me,object target);

int perform(object me, object target)
{       
        string msg, dodge_skill;
        int i,damage, ap, dp,skill;
        object weapon;
        skill=me->query_skill("yinsuo-jinling",1)+me->query_per(1);
     //   if( !me->query("gmsanwu")) return notify_fail("你还不会「三无三不手」这项绝技。\n");
		if( !me->query("quest/gumu/sanwu/pass")) 
			return notify_fail("你还不会「三无三不手」这项绝技。\n");

        if( !target ) target = offensive_target(me);
 
         if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target))
                return notify_fail("「三无三不手」只能在战斗中使用。\n");
		
        if( !living(target))
                return notify_fail("对方已经晕过去了。\n");
                
        if( !objectp( weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "whip" )
                return notify_fail("你装备的武器不对，无法施展「三无三不手」。\n");

        if( (int)me->query_skill("yinsuo-jinling", 1) < 400 
         || (int)me->query_skill("meinu-quanfa", 1) < 400 
         || (int)me->query_dex() < 28)
                return notify_fail("你的美女拳法功夫还不够娴熟，不会使用「三无三不手」。\n");

        if(me->query_skill("yunu-xinjing", 1) < 400)
                return notify_fail("以你现在的内功修为还使不出「三无三不手」。\n");        
         
        if(me->query_skill_mapped("force") != "yunu-xinjing")
                return notify_fail("你所使用的内功不对。\n");

        if (me->query_skill_prepared("cuff") != "meinu-quanfa" 
         || me->query_skill_mapped("cuff") != "meinu-quanfa"
         || me->query_skill_mapped("whip") != "yinsuo-jinling" )
                return notify_fail("你现在无法使用「三无三不手」进行攻击。\n");

        if (me->query_skill_mapped("parry") != "yinsuo-jinling")
                return notify_fail("你所使用的招架不对。\n");
	//	if (me->query_temp("ysjl/sanwu"))
              //  return notify_fail("你正在使用三无三不手。\n");

        if((int)me->query("max_neili") < 6000 )
                return notify_fail("你的内力修为太弱，不能使用「三无三不手」！\n");

        if((int)me->query("neili") < 2500 )
                return notify_fail("你的真气不够！\n");
        if((int)me->query("jingli") < 1000 )
                return notify_fail("你的当前精力不够！\n");
       
		me->start_perform(4, "三无三不手");
		me->set_temp("ysjl/sanwu",3);
        //无孔不入
		msg = HIM"突然间只见鞭影幌动，身前身后都是"+weapon->query("name")+HIM"的影子。$N这一招「无孔不入」，乃是向$n周身\n"+
                 "百骸进攻，虽是一招，其实千头万绪，一招之中包含了数十招，竟是同时点$n全身各处大穴。\n"NOR;

        ap = (int)me->query("combat_exp") * me->query_per(1)/100000;
        dp = (int)target->query("combat_exp")* target->query_per(1)/100000;

        if( random(ap) > dp /2 ){
                damage = (int)me->query_skill("yinsuo-jinling", 1);
                damage *= me->query_per(1);
				damage /=2;
		//npc攻击玩家，弱化		
        if (!userp(me) && userp(target))
        {
			if( damage > 4000 ) damage = 4000;
		}
			 
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
                //中了无孔不入
				target->set_temp("sanwu/wukong", 1);
                me->add("neili", - 200);
               // msg += damage_msg(damage, "卷伤")+
               // "( $n"+eff_status_msg((int)target->query("qi")*100/(int)target->query("max_qi"))+" )\n"; 
             
				
				i = me->query_skill("yinsuo-jinling", 1) / 20;
                //第一招的额外奖励
				if (me->is_fighting()&&objectp(target))
             		call_out("perform_bonus", 0, me, target, i);
        }
        else {
                me->add("neili", -100);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
                               
        }        
        message_vision(msg, me, target);
		////if(userp(me) && me->query("env/damage"))
			tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ damage+ WHT"点攻击伤害。\n"NOR); 				
		//if(userp(target)&& target->query("env/damage")) 
			//tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ damage+ WHT"点伤害。\n"NOR);
 
		skill=skill+me->query_skill("jiuyin-zhengong",1)/4;
		
		me->add_temp("apply/attack",skill/3);
		me->add_temp("apply/damage",skill/6);
		COMBAT_D->do_attack(me, target, me->query_emp("weapon"), 3);
		if (me->query("quest/jiuyingm/pass")&&me->query_skill("jiuyin-zhengong"))
		{
			message_vision(HIB"$N手中长鞭挥动，九阴真气陡发，随即又是一招递出！\n"NOR,me,target);
			COMBAT_D->do_attack(me, target, me->query_emp("weapon"), 3);

		}
		me->add_temp("apply/attack",-skill/3);
		me->add_temp("apply/damage",-skill/6);
        //第二招
		if( me->query_skill("meinu-quanfa", 1) >= 140 
         && me->query_skill("yinsuo-jinling", 1) >= 140
		 && objectp(target)
         && me->query("neili") > 800 )
         perform2(me, target);
        return 1;
}

int perform2(object me, object target)
{
        int i,ap,dp;
        string msg,dodge_skill;
        int skill;
        skill=me->query_skill("yinsuo-jinling",1)+me->query_per(1);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target) ){
               tell_object(me, "你正要再发一招，却发现对手已经不用打了。\n");
               return 1;
        }

        ap = (int)me->query_dex(1)* me->query_per();
        dp = (int)target->query_dex(1)* target->query_per();             
        
		i = skill+me->query_skill("meinu-quanfa", 1);
		i +=me->query_skill("yunu-xinjing", 1)/5;
		
		if (me->query_skill("jiuyin-zhengong",1)>=200) 
			i=i+me->query_skill("jiuyin-zhengong",1);
		i=i/3;
		//无所不至
        msg = HIC"\n$N跟着一招「无所不至」，左手挥鞭，右手施展出美女拳法，鞭子尾直指$n的周身诸处偏门穴道。\n"NOR;
        
		if( random(ap) > dp/3 ){
                msg += HIR"$n躲闪不及，周身诸处的偏门穴道尽数被点中，全身竟然提不起一丝力气！\n"NOR;
                target->add_temp("apply/attack", -i/5);
                target->add_temp("apply/damage", -i/5);
                target->add_temp("apply/defense", -i/5);
                
				if( !random(3))
                   target->apply_condition("no_exert", 2);
                else  
                   target->apply_condition("no_perform", 2);
                
				target->set_temp("sanwu/wusuo", i/5);
                
				call_out("check_fight", 1, me, target, i/20);
                me->add("neili", -200);
        }
        else{
                me->add("neili", - 100);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_vision(msg, me, target);
		//2招
		COMBAT_D->do_attack(me, target, me->query_emp("weapon"), 3);

		if (me->query_skill("jiuyin-zhengong",1)>200 && objectp(target)) {
			message_vision(HIB"$N将古墓九阴真功的内劲附加在手腕，招式更见凌厉！\n"NOR,me,target);
			me->add_temp("apply/attack",skill/3);
			me->add_temp("apply/damage",skill/6);
			COMBAT_D->do_attack(me, target, me->query_emp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_emp("weapon"), 3);
			//COMBAT_D->do_attack(me, target, me->query_emp("weapon"), 3);
			me->add_temp("apply/attack",-skill/3);
			me->add_temp("apply/damage",-skill/6);
		}
        //第三招
		if( me->query_skill("meinu-quanfa", 1) >= 160
         && me->query_skill("yinsuo-jinling", 1) >=160
		 && objectp(target)
         && me->query("neili") > 800 )
         perform3(me, target);
        return 1;
}

int perform3(object me, object target)
{
        object weapon;
        int i;
		
        if(!target
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target) ){
               tell_object(me,"你正要再发一招，却发现对手已经不用打了。\n");
               return 0;
        }

        weapon = me->query_temp("weapon");

        i = me->query_skill("meinu-quanfa",1);
        i += me->query_skill("yinsuo-jinling", 1);
		i += me->query_skill("yunu-xinjing", 1)/5;
		if (me->query("quest/jiuyingm/pass"))
			i += me->query_skill("jiuyin-zhengong", 1)/2;
        i /= 3;
        
        if(!userp(me)) i = i / 4;


        message_vision(HIW"\n$N的第三手「无所不为」立即使出，这一招不再点穴，专打眼睛、咽喉、小腹、下阴等人身诸般\n"+
                          "柔软之处，是以叫作「无所不为」，阴狠毒辣。\n"NOR, me);
		//若对方被第二招打中则奖励
        if( target->query_temp("sanwu/wusuo")&&!me->query_temp("sanwu/buwei"))
		{
                
				me->add_temp("apply/attack", i);
                me->add_temp("apply/whip", i);
                me->add_temp("apply/damage", i);
                me->set_temp("sanwu/buwei", 1);
        }

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		//九阴功后增加威力
		if (me->query("quest/jiuyingm/pass") && me->query_temp("weapon"))
		{
			weapon = me->query_temp("weapon");
			me->add_temp("apply/attack",i/2);
			me->add_temp("apply/damage",i/4);
			message_vision(HBMAG"$N将九阴真经的功夫运用到银索金铃武技之中，鞭法灵动异常，顿时威力大增！\n"
			+HIY"$n一不小心为"+weapon->name()+HIY"所缠中。\n"NOR,me,target);
			target->add_busy(3);
			if (present(target,environment(me)) && me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            me->add_temp("apply/attack",-i/2);
			me->add_temp("apply/damage",-i/4);
		}
		if(objectp( weapon = me->query_temp("weapon"))) weapon->unequip(); 
		//兼容任何备的空手武技
        if (present(target,environment(me)) && me->is_fighting(target))
			COMBAT_D->do_attack(me, target, 0, 3);
        if (present(target,environment(me)) && me->is_fighting(target))
			COMBAT_D->do_attack(me, target, 0, 3);
		if (weapon) weapon->wield();
		//继续鞭法攻击
        if (present(target,environment(me)) && me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		
		//
        if( me->query_temp("sanwu/buwei")){
                me->add_temp("apply/attack", -i);
                me->add_temp("apply/whip", -i);
                me->add_temp("apply/damage", -i);
                me->delete_temp("sanwu/buwei");
        }
        me->add("neili", -200);
        me->add("jingli", -100);
        me->start_perform(4, "三无三不手");
        return 1;
}

void check_fight(object me,object target,int amount)
{        
        int j;
        if( !objectp(target) ) return;
        if( !me
         || !me->is_fighting(target)
         || amount < 1){
              j = target->query_temp("sanwu/wusuo");
              target->add_temp("apply/attack", j);
              target->add_temp("apply/damage", j);
              target->add_temp("apply/defense", j); 
              target->delete_temp("sanwu/wusuo");
              message_vision(HIW"\n$N为三无三不手所打中的穴道已解，精神不由为之一振。\n"NOR, target);
              return;
        }
        call_out("check_fight", 1, me, target, amount -1);
}

void perform_bonus(object me,object target,int amount)
{
        int j;
        object weapon;
        if (!me||!target) return;
		
		j = me->query_skill("yinsuo-jinling", 1);
        j += me->query_skill("yunu-xinjing", 1);
		j= j*me->query_per()/20;
        
		weapon = me->query_temp("weapon");

        if( me->is_fighting(target)
         && me->query_skill_mapped("whip") =="yinsuo-jinling"
         && me->query_skill_mapped("cuff") =="meinu-quanfa"
         && me->query_skill_prepared("cuff") == "meinu-quanfa"
         && environment(me) == environment(target)
         && amount > 0){
               

                switch(random(4)){
                        case 0:
                              message_vision(HIR"\n$N只觉得印堂和太阳穴处如针刺般绞痛,精神恍惚,似乎感觉精血在不断流失。\n"NOR,target);
                              target->receive_damage("jing", j,me);
                              target->receive_wound("jing", j/10,me); //edit by sohu..调整，因为伤害太大，导致死亡
                              break;
                        case 1:
                              message_vision(HIY"\n$n只觉得$N的鞭尾陡然变直戳中胸口檀中穴，丹田大量真气外泄，同时内劲无法控制。\n"NOR,me,target);
                              target->add("neili", -j*3);
                              if(target->query("neili") < 0) target->set("neili", 0);
							  target->apply_condition("no_exert",1);
                              target->add("jingli", -j);
                              break;                          
                        case 2:
                              message_vision(HIG"\n$N只觉得全身周遭穴道受阻，身形不由一滞，行动不便,当即无法出招。\n"NOR,target);
                              target->add_condition("no_perform",6);
                              target->add_busy(2+random(3));
                              break;
                        case 3:
                              message_vision(HIC"\n$n只觉得$N的鞭影如一团飞龙乱舞，将自己卷将起来，$N见$n受制，又挥出一片鞭影。\n"NOR,me,target);
                              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), me->query("gender")=="女性"?3:1);							  
                             if (me->query_temp("weapon")) 
							 {
							 weapon = me->query_temp("weapon"); 
							 weapon->unequip(); 
                              COMBAT_D->do_attack(me, target, 0, me->query("gender")=="女性"?3:1);
							  COMBAT_D->do_attack(me, target, 0, me->query("gender")=="女性"?3:1);
                              weapon->wield();
							 }
                              break;
                }
     //           me->start_perform(3, "三无三不手");
				if (me->is_fighting()&&objectp(target))
					call_out("perform_bonus", 3, me, target, amount - 3);
        }
        else {
                target->delete_temp("sanwu/wukong");
                return;
        }
}
int help(object me)
{
        write(WHT"\n银索金铃之"+HIR+"「三无三不手」："NOR"\n");
        write(@HELP
	银索金铃乃是古墓独门武技，源自小龙女
	大战金轮法王和武林诸位英雄豪杰时的武
	技。银索乃是采用天山天蚕丝打造，极为
	坚韧，且阴柔无比，前端为一金色的铃铛，
	有干扰对方施展正常武技的功能。
	三无三不手乃是古墓绝技之一，分为“无孔
	不入”、“无所不至”、“无所不为”三招。第
	一招无孔不入看似只是一招,实则千头万绪，
	一招之中包含了数十招,乃是向敌人周身百
	骸进攻，击点敌人全身各处大穴；第二招
	无所不至点的则是敌人周身诸处偏门穴道；
	第三招“无所不为”不再点穴,而是专打眼睛、
	咽喉、小腹、下阴等人身诸般柔软之处,招
	式最是阴险毒辣。
	
	perform whip.sanwu

要求：
	最大内力要求 6000 以上；      
	当前内力要求 2500 以上；
	当前精力要求 1000 以上；
	玉女心经等级 400  以上；
	美女拳法等级 400  以上，
	银索金铃等级 400  以上；
	基本鞭法等级 400  以上；
	激发拳法且备拳法为美女拳法；
	激发基本鞭法和招架为银索金铃；
	激发内功为玉女心经；
	手持鞭子类武器；                
                
HELP
        );
        return 1;
}