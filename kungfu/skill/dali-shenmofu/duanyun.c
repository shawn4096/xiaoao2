//裁天断云  
//duanyun.c 选自大力神魔范松绝技
//cre by sohu@xojh 

#include <ansi.h>
#include <combat.h>
inherit F_DBASE;
inherit F_SSERVER;
string *bodys=({"胸口","上臂","小腿","后背","腰部","软肋","臀部"});
int perform(object me, object target)
{
        object weapon;
        int damage, axe, i,ap,pp,j;

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
		||!living(target)
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("「裁天断云」只能对战斗中的对手使用。\n");

        if( !objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "axe" )
                return notify_fail("你手中无斧，怎能运用「裁天断云」？！\n");


       // if( me->query_temp("sl_chaodu") )
              // return notify_fail("「裁天断云」是少林密技，太过刚猛有违天和，不可多用！\n");

        

        if(me->query_temp("dlf/duanyun"))
               return notify_fail("你正在使用大力神魔斧的「裁天断云」，全身内力已经灌注到手中兵器中，无暇他顾了。\n");

        if((int)me->query_skill("dali-shenmofu", 1) < 300 )
               return notify_fail("你「大力神魔斧」修为还不够，还未能领悟「裁天断云」！\n");

        if((int)me->query("str")<15)
               return notify_fail("你的先天膂力不够，无法用出「裁天断云」\n");

        if((int)me->query_con(1)<10)
               return notify_fail("你的根骨不够，无法承受「裁天断云」的劲力迸发。\n");

      

        if((int)me->query_skill("axe",1) < 300)
               return notify_fail("「裁天断云」是以斧头劲力发出，无坚不摧，你的基本斧法修为尚浅吧?\n");

        if (me->query_skill_mapped("force") != "tianmo-gong" )
          if(me->query_skill_mapped("force") != "xixing-dafa")
                return notify_fail("你所使用的特殊内功不对。\n"); 

        if(me->query_skill("xixing-dafa", 1)<350)
          if(me->query_skill("tianmo-gong", 1) < 350)
                return notify_fail("以你现在的内功修为还使不出「裁天断云」。\n");  

        if (me->query_skill_mapped("axe") != "dali-shenmofu"
         || me->query_skill_mapped("parry") != "dali-shenmofu")
                return notify_fail("你现在无法使用「裁天断云」进行攻击。\n");

        if( me->query("max_neili") < 5000 )
                return notify_fail("你的内力修为不足，劲力不足以施展「裁天断云」！\n");

        if( me->query("neili") <= 2000 )
                return notify_fail("你的内力不够，劲力不足以施展「裁天断云」！\n");

        if( me->query("jingli") <= 1500 )
                return notify_fail("你的精力有限，不足以施展「裁天断云」！\n");

        message_vision(HIR"\n$N大喝一声，宛如晴天霹雳，身形顿时暴涨，如同神魔再世一般，抡起"+weapon->name()+HIR"向四周疯狂地砍去，\n"+
			"$N浑身劲气弥漫"+weapon->name()+HIR"带起一片斧影劈向$n的周身!\n" NOR, me,target);       

        damage = (int)me->query_skill("axe",1) + (int)me->query_skill("tianmo-jue",1);
        axe = me->query_skill("axe",1);        
		i = 10+random(me->query_skill("tianmo-jue",1)/20);
        damage = damage*i;
        
		if(userp(target))
                damage = damage *2/3;
        else
                damage = damage *3/2;
        if (wizardp(me))
                write(sprintf("damage = %d\n",damage));
        ap = COMBAT_D->skill_power(me,"axe",SKILL_USAGE_ATTACK);
        pp = COMBAT_D->skill_power(target,"parry",SKILL_USAGE_DEFENSE);
        
		if(target->is_busy())
                pp /= 2;
        //吸星大法加成
		j=1;
		if (me->query_skill_mapped("force")=="xixing-dafa" && me->query("xixing",1)==1)
		{
			j=2;
		}
		if(me->query_skill("xixing-dafa",1)>550 && me->query("xixing",1)>1){
                damage *=2;
                ap *= 2;
                pp /= 2;
				j=3;
        }
		
        me->set_temp("dlf/duanyun",1);
        if(random(ap+pp)>pp)
        {
                me->add("neili", -1000);
                me->add("jingli", -800);
                if (damage>10000) damage=damage+(damage-10000)/100;
                
				target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/3,me);
                message_vision(HIY"\n$n一时为$N霸道刚猛的声势所摄,眼见$N招式迅疾无比，一时间招架不及，被"+weapon->name()+HIY"劈中"NOR+HIR+bodys[random(sizeof(bodys))]+HIY"，顿时鲜血飞溅！\n" NOR, me,target);
                if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR); 
                if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR); ;
               // COMBAT_D->report_status(target);
                target->start_busy(j+random(2));
				target->apply_condition("no_exert",1+random(1));
                
       }
       else {
                message_vision(HIC"\n$n眼见$N来势凶狠，运起浑身功力，一个锦鲤翻身，向旁滑出数丈，躲过了这致命一击！\n" NOR, me,target);
				target->start_busy(1+random(1));
                me->add("neili", -1500);
                me->add("jingli", -800);
                
       }
       // if (objectp(target)&&me->is_fighting(target))
        //{
		//	message_vision(YEL"\n$N随即跟上，将手中"+weapon->query("name")+YEL"飞掷而出！\n" NOR, me,target);
        //}
        if(!userp(me)) axe = axe / 2;
        
		me->add_temp("apply/attack", axe/4);
        me->add_temp("apply/damage", axe/5);

        if(me->is_fighting(target)){
              message_vision(HIG"\n$N断喝一声，“裁天式！”，招式威猛无铸，宛如要将天空一斧头劈开似得，"+weapon->query("name")+HIG"飞掷而出！\n" NOR, me,target);
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			 // COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

		}
        if(me->is_fighting(target)){
			  message_vision(HIR"\n$N向前一纵，伸手接住"+weapon->query("name")+HIR"又吼道，“断云式！”，劲气透过"+weapon->query("name")+HIR"连攻数招！\n" NOR, me,target);
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		      if(me->is_fighting(target))
			     COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			  if(me->is_fighting(target))
			     COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		}
        me->add_temp("apply/attack", -axe/4);
        me->add_temp("apply/damage", -axe/5);
        me->delete_temp("dlf/duanyun");
		me->start_perform(4+random(2),"「裁天断云」");

       return 1;
}


string perform_name(){ return HIW"裁天断云"NOR; }
int help(object me)
{
        write(HIW"\n大力神魔斧之「裁天断云」："NOR"\n\n");
		write(
@HELP裁天断云:
	大力神魔范松手中的大力神魔斧乃当世绝技，可惜随
	十大长老围华山后，范长老的失踪而遗失，据说有人
	曾在华山后山山洞中发现范长老的绝技。、
	「裁天断云」的特殊攻击，将手中兵器击出飞向对手。
	乃是「大力神魔斧」的范松终极招式。
	要求：
		需要大力神魔斧500级
		特殊内功要求  500级
		先天臂力不小于35；
		后天根骨不小于20；
HELP
        );
        return 1;
}

