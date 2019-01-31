///kungfu/skill/quanzhen-jianfa/qixing.c 七星绝命剑
// Modified by sohu@xojh
#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;
string perform_name(){ return HIR"七星绝命剑"NOR; }

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lv, i, atk, hit,def;
        string htz_msg;
        object weapon = me->query_temp("weapon");
        int damage, p;     
		def=1;
        if( !target ) return notify_fail("你要对谁使用「七星绝命剑」绝技。。\n");
			
		//target = offensive_target(me);

        if( !objectp(target)
         || !target->is_character()
		 || !living(target)
         || !me->is_fighting(target) )
                return notify_fail("你只能对战斗中的对手使用「七星绝命剑」绝技。。\n");
        //不解密施展不出，有效屏蔽掉外传招式
		if(!me->query("quest/qz/qzjf/qixing/pass"))
                return notify_fail("你虽然听说过七星绝命剑，但是一直没有领悟其中诀窍，还不会运用！\n");

        if( (int)me->query_skill("quanzhen-jianfa", 1) < 500 )
                return notify_fail("你的全真剑法不够熟练，使不出「七星绝命剑」绝技。\n");

        if ( !weapon
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "quanzhen-jianfa")
               return notify_fail("你现在无法使用七星绝命剑。\n");
        if(me->query_skill_mapped("parry") != "quanzhen-jianfa" && me->query_skill_mapped("parry") != "kongming-quan")
                return notify_fail("你的招架功夫不对，无法使用七星绝命剑！\n");

        if((int)me->query_skill("sword", 1) < 500 )
               return notify_fail("你的基本功还不够娴熟，使不出「七星绝命剑」绝技。\n");
        if((int)me->query_str(1) < 60)
               return notify_fail("「七星绝命剑」需要高的臂力，你还使不出「七星绝命剑」绝技。\n");
        if((int)me->query_dex(1) < 60)
               return notify_fail("「七星绝命剑」需要高的身法，你还使不出「七星绝命剑」绝技。\n");

        if((int)me->query_skill("force", 1) < 500)
               return notify_fail("你的内功修为不够，无法使用「七星绝命剑」绝技。\n");  
        if((int)me->query_skill("xiantian-gong", 1) < 500)
               return notify_fail("你的先天功修为不够，无法使用「七星绝命剑」绝技。\n");  

        if((int)me->query_temp("qzjf/qixing"))
               return notify_fail("你正在使用「七星绝命剑」绝技。\n"); 

        if((int)me->query("max_neili") < 5500)
               return notify_fail("你的内力不够，无法使用「七星绝命剑」绝技。\n");
        if((int)me->query("neili") < 1500)
               return notify_fail("你的内力不够，无法使用「七星绝命剑」绝技。\n");
        if((int)me->query("max_jingli")< 3000)
               return notify_fail("你的精力不够，无法使用「七星绝命剑」绝技。\n");


        
        me->set_temp("qzjf/qixing",1);     
        lv = me->query_skill("quanzhen-jianfa",1);
		atk= me->query_skill("quanzhen-jianfa",1)+me->query_skill("xiantian-gong",1)/2;

        //if(!userp(target)) atk = atk*3/2; //玩家攻击npc，效果增加

        hit = (lv/75); //560后大飞
        if(hit >7) hit = 7;
        if(hit <2) hit = 2;       

        
        message_vision(HBMAG"\n$N一声长啸，一抖手中剑，剑幕中飞出"+chinese_number(hit)+"朵寒星，既如狂风暴雨又如流星般向$n罩了过去。\n"NOR,me,target);
        me->add_temp("apply/attack", atk/2);
		me->add_temp("apply/damage", atk/4);
       	
		htz_msg = HIC"\n$N将自己所参悟的天罡北斗阵的奥秘和剑法结合起来，默运先天功，但见天空\n";
        if(hit >= 1)htz_msg += "「"HIR"天璇星"HIC"」";
        if(hit >= 2)htz_msg += "、「"HIG"天枢星"HIC"」";
        if(hit >= 3)htz_msg += "、「"HIY"天玑星"HIC"」";
        if(hit >= 4)htz_msg += "、「"HIB"天权星"HIC"」";
        if(hit >= 5)htz_msg += "、「"HIM"玉衡星"HIC"」";
        if(hit >= 6)htz_msg += "、「"HIC"开阳星"HIC"」";
        if(hit >= 7)htz_msg += "、「"HIW"摇光星"HIC"」";

        htz_msg += "星光下泄，"+chinese_number(hit)+"星陆续微微一闪，\n"NOR+HIY"这七星绝命剑竟似乎能引动北斗星力，当真威力无比！\n"NOR;

        message_vision(htz_msg, me, target);
        me->set_temp("htz_times",hit);
        me->set_temp("htz_effect",1);
        me->add_temp("htz/lianhuan", 3);
        me->set_temp("action_flag", member_array("sword", keys(me->query_skill_map())));

//七星绝命剑飞跃        
        if( objectp(target)&&me->query("str")>=45 
			&&me->query("quanzhen/force")=="pass")
		{
		         me->set_temp("htzup",1);
	           	 target->set_temp("must_be_hit",1);
		         target->add_temp("apply/defense",-2000);
				 target->add_temp("apply/armor",-lv/2);
				 target->add_temp("apply/parry",-lv/2);

				 def=3; //攻击伤害会飞跃
				 call_out("target_remove",lv/50,target,lv);
	             message_vision(HBBLU"\n只见$N将先天真气引动周天星斗光华，举手投足之间竟有丝缕星光飞烁，威力更是大增！\n"NOR, me, target);
		}
		me->add_temp("apply/attack",lv/6);
		me->add_temp("apply/armor",lv/6);
		me->add_temp("apply/sword",lv/6);
        for( i=0; i < hit; i++ )
        {
              me->add_temp("htz/lianhuan", 1);            
			  if (!(objectp(target) && me->is_fighting(target)))
			  {
				 message_vision(HBRED"\n$N忽然收招敛式，凝神定睛观瞧。\n"NOR, me, target);
				 break;
				  
			  }
			     COMBAT_D->do_attack(me, target, weapon, 3);
              continue;
        }
		me->add_temp("apply/attack",-lv/6);
		me->add_temp("apply/armor",-lv/6);
		me->add_temp("apply/sword",-lv/6);

        //取消连击
		me->delete_temp("htz/lianhuan");
        
		if(me->query_temp("htzup")) {
	     if(objectp(target)&& me->is_fighting(target)) {
           message_vision(HBRED"\n只见$N将顿悟「天运无穷，三光迭耀，而极星不移」之奥妙，当下抢占北极星位，剑尖闪烁，刺向$n的前胸。\n"NOR, me, target);
           target->add_busy(2);  
           if( random(me->query("str",1)) > target->query("str",1)/2 
              || random(me->query("combat_exp",1)/10000) > target->query("combat_exp",1)/20000 
              || random(me->query("neili",1)/100 )> target->query("neili",1) /200)
{

              message_vision(HBMAG"那晶莹飞舞的星光忽的一下炸裂开来，竟然全是精纯的先天真气凝聚而成，剑光凛冽，无坚不摧！\n$n猝不及防，当下被穿胸而过，眼看是活不成了！\n"NOR, me, target);
              target->receive_damage("qi",2000+random(5000),me);
			  target->receive_wound("qi",2000+random(2000),me);
			  me->add_temp("apply/damage",atk/4);

              COMBAT_D->do_attack(me, target, weapon, 3);//取消call die,增加一项攻击
              me->add_temp("apply/damage",-atk/4);
           }
            else  message_vision(HBMAG"那晶莹飞舞的星光忽的一下炸裂开来，竟然全是精纯的先天真气凝聚而成，凛冽如剑，无坚不摧！\n"
			                   +GRN+"$n知这星光怪异，心中早有准备，抽身急退，堪堪躲过，却已是狼狈不堪。\n"NOR, me, target);
             target->receive_damage("jingli", atk,me);
		     target->delete_temp("must_be_hit");
		     target->add_temp("apply/defense",2000);  
	          	                      
		    } 			 
		}
        message_vision(HIC"\n这"+chinese_number(hit)+"招七星绝命剑，暗含周天星斗运转轨迹，变化无穷，鬼神难测！\n"NOR, me);
		     
        me->add("neili", -hit*20+20);
        me->add("jing", -hit*5);
        me->start_perform(6,"「七星绝命剑」");
		me->start_busy(1+random(2));
        me->delete_temp("htz/lianhuan");
        me->delete_temp("htz_times");
        me->delete_temp("qzjf/qixing");
        me->delete_temp("htzup");
        
        me->add_temp("apply/attack",   - atk/2);
		me->add_temp("apply/damage", -atk /4);
        return 1;
}

int target_remove(object target,int lv)
{
	if (!target) return 0;
	
	target->delete_temp("must_be_hit");
	target->add_temp("apply/defense",2000);
	target->add_temp("apply/armor",lv/2);
	target->add_temp("apply/parry",lv/2);
	return 1;
}
int help(object me)
{
        write(HIR"\n全真剑法之「七星绝命剑」："NOR"\n");
        write(@HELP
	全真剑法为全真教王重阳独创，乃是从道藏和北斗七星运转的规律中
	所悟而来，乃是天罡北斗阵的精华。，其中七星绝命剑的招式更是暗
	合天道运行规则，乃全真教核心招式，该招式凌厉无比，犹如星斗变
	换，日月暗淡。全真弟子需在先天功和全真剑法达到350级后，请教丘
	处机，经由指点去相应地点解密而得。

	指令：perform sword.qixing

要求：  
	有效身法和臂力要求至少60；
	当前内力需求 1500 以上；
	最大内力需求 5500 以上；
	最大精力需求 3000 以上；
	全真剑法等级 500 以上；
	先天功法等级 500 以上；
	基本剑法等级 500 以上；
	激发剑法为全真剑法；
	激发招架为全真剑法或空明拳；
	激发内功为先天功。
	先天臂力>=45后有额外攻击加成，550后威力彻底大飞。
                
HELP
        );
        return 1;
}


