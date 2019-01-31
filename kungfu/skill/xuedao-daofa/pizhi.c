// pizhi.c  血刀经 [批纸削腐]
// changed by sohu@xojh 2016/7

#include <ansi.h>
#include <skill.h>
#include <combat.h>
#include <weapon.h>
inherit F_SSERVER;
#include <combat_msg.h>
 
string perform_name(){ return HIW"批纸"HIB"削腐"HIC"诀"NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg, weaname;
        int lvl,damage,i,skill;
		lvl=me->query_skill("xuedao-daofa",1);
        if( !me->is_fighting() )
                return notify_fail("「批纸削腐诀」只能在战斗中使用。\n");

        if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n");

        if((int)me->query_dex() < 28)
                return notify_fail("你的身法不够, 目前还不能使用这项绝技! \n");

        if((int)me->query_skill("blade") < 500)
                return notify_fail("你的基本刀法修为不够, 不能使用「批纸削腐诀」！\n");
 
        if((int)me->query_skill("xuedao-daofa",1) < 500)
                return notify_fail("你的血刀刀法修为不够， 目前不能使用「批纸削腐诀」! \n");
        
		if(!me->query("quest/xuedao/xddf/pizhi"))
                return notify_fail("你尚未领会贯通这门绝技， 目前不能使用「批纸削腐诀」! \n");

        if((int)me->query_skill("xuedao-jing",1) < 500)
                return notify_fail("你的血刀经修为不够， 目前不能使用「批纸削腐诀」! \n");

        if( me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("你必须使用血刀刀法，才能使用「批纸削腐诀」的绝技！\n");
		if ( me->query_skill_mapped("parry") != "xuedao-daofa" && me->query_skill_mapped("parry") != "jingang-liantishu")
             	return notify_fail("你的招架不对，必须激发刀法为血刀刀法或金刚炼体术。\n");

        if( me->query_skill_mapped("force") != "xuedao-jing" &&me->query_skill_mapped("force") != "shenzhao-jing")
                return notify_fail("你现在所使用的内功同「血刀经」向抵触，不能使出「批纸削腐诀」的绝技！\n");

        if( (int)me->query("max_neili") < 15000 )
                return notify_fail("你的最大内力修为不够！\n");
        if((int)me->query("neili")<1600)
                return notify_fail("你的真气不够！\n"); 
        if((int)me->query("jingli")<1200)
                return notify_fail("你的精力不够！\n"); 

        target = me->select_opponent();

      //  if( !userp(me) && userp(target) )
               // return notify_fail("「批纸削腐诀」只能由玩家使用！\n");

        lvl = (int)me->query_skill("xuedao-jing",1);
        weapon = me->query_temp("weapon");
        weaname = weapon->query("name");
        msg = HIW "\n$N狂啸声中，运起「"HIC"批纸"HIB"削腐"HIW"诀」秘诀，刹时身法如电，"NOR+weapon->query("name")+HIW"一分为六，如一道血影般的劈将出去！\n"NOR;
        message_vision(msg, me);

     
//批纸诀  
        message_vision(CYN"$N腰劲运肩，肩通于臂，手腕轻灵，苦练数年的「批纸诀」功夫顿显，刀法精奇，柔性十足！\n"
						+"$N出手快极,$n只觉刀光划成的圆圈又已指向身前，光圈越划越大，刹那间呼啸而过，胆战心惊！\n"
						+"刀光初时还只绕着$n前胸转圈，数招一过，已连$n小腹也包在刀圈之中，再使数招，刀圈扩及$n的头颈\n"
						+HIR"$n只觉自颈至腹，所有要害已尽在他刀光笼罩之下，不禁心神大孩！\n"NOR,me,target);
		
		if(random(me->query_skill("xuedao-daofa",1))>target->query_skill("parry",1)/2
		   ||random(me->query_dex())>target->query_dex()/2)
		{
			message_vision(HBYEL"\n$n为这片诡异的血光所迷惑，似乎闻到一股莫名的甜香，开始手忙脚乱起来。\n",me,target);

			damage = me->query_skill("xuedao-daofa",1);
			damage += me->query_skill("blade",1);
			damage +=me->query_skill("xuedao-jing",1);
			damage =damage*3 + random(damage);
			target->start_busy(lvl/200);
			target->add_temp("lost_attack", lvl/200);
			target->apply_condition("no_perform", 1);
			target->apply_condition("no_exert", 1);
			target->add("neili",-(500+random(150)));
			target->receive_damage("qi", damage,me);
			target->receive_wound("qi", damage/3,me);
		  	msg = damage_msg(damage, "砍伤");
			msg = replace_string(msg, "$w", weapon->name());
			msg = replace_string(msg, "$l", "小腹");
			message_vision(msg, me, target);
			COMBAT_D->report_status(target, random(2));
			me->add("neili",-300);
			me->add("jingli",-100);	
		}
		//必中，血刀大招，不附加
	
		target->set_temp("must_be_hit",1);
		
		message_vision(HIC"\n$N一刀既出，后续招式连环如影，全凭本能的下意识反应,瞧人如纸片，一刀一片，一刀一片“刷刷刷”地挥出。\n"NOR,me);

		if (present(target,environment(me)) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if (present(target,environment(me)) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if (present(target,environment(me)) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		target->delete_temp("must_be_hit");

		me->delete_temp("xddf/shendao");
        

		me->add("neili", -200-random(300));
        if(me->query("neili")<0) me->set("neili",0);
        me->add("jingli", -80);
       	
		me->start_busy(random(2)+ 2);        
		me->start_perform(5,"批纸削腐诀");
		if (objectp(me)&&objectp(target)&&me->is_fighting())
			call_out("xddf_xiaofu",1,me,target);
        return 1;
}
//削腐诀

int xddf_xiaofu(object me,object target)
{
		int skill,lvl;
		object weapon;

        if (!me||!target) return;
        lvl=me->query_skill("xuedao-jing",1);
		weapon=me->query_temp("weapon");

		message_vision(HBWHT+HIB"$N血刀经功力逆转，顿时臂无劲，腕无力，施展出“无劲胜有劲”，“无力即有力”的「削腐诀」深层次功夫！\n"
						+"「"HIR"削腐诀"HIB"」这门功夫原本是用一块豆腐放在木板之上，一刀刀削薄，要将两寸厚的一块豆腐削成二十块，每一片\n"
						+"都完整不破,此时功夫便算初步小成！但$n数年如一日沉浸在这招中，此时施展威力自不可同日而语。\n"NOR,me,target);
//550级后大飞
 	   if(lvl>550)
		{           
            me->add_temp("apply/attack", lvl/10);
            me->add_temp("apply/damage", lvl/10);
			message_vision(HIB"$N刀法已然大乘，血刀刀法威力此时方得彰显，血光弥漫，刀气纵横！\n"NOR,me);
        } 
//浴血诀后有加成

		if(me->query_temp("xdj/yuxue")) 
		{
                skill = me->query_skill("xuedao-jing",1)/10;
                me->add_temp("apply/damage", skill);
				me->set_temp("xddf/pzyxadd",skill);
                message_vision(RED"$N更把血刀经怪异内劲附于兵刃之上，"NOR+weapon->query("name")+RED"通体流淌着异样的红色光芒！\n"NOR, me,target);
        }

        me->add_temp("apply/blade", lvl/5);
        me->add_temp("apply/parry", lvl/5);
        me->add_temp("apply/dodge", lvl/5);
		me->set_temp("xddf/xiaofu",lvl);

				
		if (present(target,environment(me)) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if (present(target,environment(me)) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if(lvl >250)
                if (present(target,environment(me)) && me->is_fighting(target))
                    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if(lvl >350)
                if (present(target,environment(me)) && me->is_fighting(target))
                    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if(lvl >450)
                if (present(target,environment(me)) && me->is_fighting(target))
                    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if(lvl >550)
                if (present(target,environment(me)) && me->is_fighting(target))
                    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			
		me->add_temp("apply/blade",- lvl/5);
        me->add_temp("apply/parry",- lvl/5);
        me->add_temp("apply/dodge",- lvl/5);
        //消除550影响
        if(lvl>550)
		{
            me->add("neili", -300-random(200));
            me->add_temp("apply/attack", -lvl/10);
            me->add_temp("apply/damage", -lvl/10);
        }
		//消除浴血加成影响
        if(me->query_temp("xddf/pzyxadd"))
		{
            me->add_temp("apply/damage", -skill);
			me->delete_temp("xddf/pzyxadd");
        }
		me->add("neili", -500-random(300));
        if(me->query("neili")<0) me->set("neili",0);
        me->add("jingli", -380);

		me->start_busy(random(2)+ 2);        
		me->start_perform(6,"「批纸削腐诀」");
		message_vision(HIW"$N收刀入鞘，歪身斜站，喋喋淫笑不已，甚是得意！\n"NOR,me);     
	    return;

}
int help(object me)

{
        write(RED"\n血刀刀法之「"HIW"批纸"HIB"削腐"RED"诀」："NOR"\n\n");
        write(@HELP
	血刀经乃是从密宗一分支中演化出来的怪异刀法武技
	创始人为血刀门的血刀老祖，「血刀门」的镇派绝学，
	分为内功跟刀法两部分，全都记录在《血刀经》上，
	「血刀刀法」怪异至极，每招都是在决不可能的方位
	劈砍，令对手防不胜防，以其怪异和血腥名震江湖。
	「批纸削腐诀」是用平时所辛苦修炼的批纸削腐基本
	功夫融入到实战中，批纸诀讲求打压虚弱对手，削腐
	诀则是趁对方不备，瞬间连出数刀，功力越强，刀法
	越是凶狠，550级后削腐诀飞跃。

指令：perform blade.pizhi

要求：
	当前内力 1600 以上；
	最大内力 15000 以上；
	当前精力 1200 以上；
	血刀经等级 500 以上；
	血刀大法等级 500 以上；
	基本刀法等级 500 以上；
	激发刀法为血刀刀法；
	激发招架为血刀刀法或金刚护体术；
	激发内功为血刀经。
	手持刀类武器
HELP
        );
        return 1;
}