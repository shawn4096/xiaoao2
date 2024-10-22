// cangsong.c 苍松迎客 Created by LSXK@hsbbs 2007/7/25
// 在《笑傲江湖》里，此招为令狐冲绝技，因此设定Quest,需要向令狐冲请教后，增加威力。
// 降低解quest前的命中率，解完quest后，才恢复教好的命中。  By lsxk@hsbbs 2007/7/31
/* 他侧头再看第二组图形时，见使剑的所使是本门一招‘苍松迎
   客’，登时精神一振，这一招他当年足足花了一个月时光才练
   得纯熟，已成为他临敌时的绝招之一。
*/

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
string perform_name() {return HIG"苍松迎客"NOR;}
int perform(object me, object target)
{
        object weapon;
        int damage,p,i;
        string msg,dodge_skill;
        if ( me->query("quest/hsjf/cangsong")=="pass")
        {
			i=3;
        }
		else i=1;
		weapon=me->query_temp("weapon");
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        ||  !living(target))
                return notify_fail("「苍松迎客」只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("huashan-jianfa", 1) < 250 )
                return notify_fail("你的华山剑法功力太浅，使不出华山剑法之「苍松迎客」的功夫!\n");

        if( (int)me->query_skill("sword", 1) < 250 )
                return notify_fail("你的基本剑法太差,使不出「苍松迎客」的功夫!\n");

        if( (int)me->query_skill("huashan-qigong", 1) < 250
	       &&(int)me->query_skill("zixia-gong", 1) < 250)
                return notify_fail("你的特殊内功太差,使不出「苍松迎客」的功夫!\n");

        if(me->query_skill_mapped("force") != "huashan-qigong"
         &&me->query_skill_mapped("force") != "zixia-gong" )
            return notify_fail("你的特殊内功不对，无法使用「苍松迎客」！\n");

        if( (int)me->query("max_neili") <2500 )
               return notify_fail("你的内力修为太浅，使不出「苍松迎客」。\n");

        if( (int)me->query("neili") <1000 )
                return notify_fail("你的真气不够，使不出「苍松迎客」功夫。\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
            || me->query_skill_mapped("sword") != "huashan-jianfa"
	    || me->query_skill_mapped("parry") != "huashan-jianfa")
                return notify_fail("你不使用华山剑法,如何使得了「苍松迎客」?\n");
                 
        me->set_temp("hsjf/cangsong", 1); 
//解密苍松招式
       if(target->query("cs_upgrade") && target->query("cs_kill_id") == me->query("id") && me->query("quest/hsjf/cangsong")!="pass")
	   {
          if(random(me->query("kar"))>26)
		  {
			me->delete_temp("sj_credit/quest/hs/cangsong");
			message_vision(HIG"\n$N突然领会了“苍松迎客”的精要，剑招轻盈灵巧，以巧制拙，当真厉害非常！\n\n"NOR,me);
			log_file("quest/cangsong", sprintf(HIG"苍松迎客Quest记录：%s(%s)成功领会「苍松迎客」。经验%d。"NOR, me->name(1),me->query("id"), me->query("combat_exp")) );
			me->set("quest/hsjf/cangsong","pass");
		  } else{
			message_vision(BLINK HIR"\n$N暗思令狐冲之言，不断体会这「苍松迎客」的精要之处！\n"NOR,me);
			log_file("quest/cangsong", sprintf(HIR"苍松迎客Quest记录：%s(%s)实战未领会「苍松迎客」。经验%d。"NOR, me->name(1),me->query("id"), me->query("combat_exp")) );
		  }
		}

        message_vision(HIG"\n$N手中的"+weapon->query("name")+HIG"突然一晃，满场游走，一身青衫化成了一片青影，一招「"+GRN+"苍"+
           "松迎客"+HIG+"」直刺$n。\n"NOR,me,target);
	   message_vision(HIM"\n只见$N将手中"+weapon->query("name")+HIM+"缓缓刺出,剑身竟丝毫不晃动,可这招对于内力的运用已入化境!\n"NOR,me);

      if( random(me->query_skill("sword",1))>target->query_skill("parry",1)/3 
           || random(me->query("combat_exp")) > target->query("combat_exp")/2
           || target->is_busy() )
	  {
           damage = (int)me->query_skill("huashan-jianfa", 1) + (int)me->query_skill("sword",1);
		   //气宗伤害增加内功
		   if ( me->query("huashan/quest") == "气宗")
		        damage=damage+(int)me->query_skill("force",1);

				damage = damage*2 + random(damage);
           if ( me->query("quest/hsjf/cangsong")=="pass") {
               damage = damage*2;
               message_vision(HIW "$N这招「"+GRN+"苍松迎客"+HIW+"」已得精要,此时使将出来,威力乃今非昔比!\n"NOR,me,target);
           }

           if (wizardp(me))
               write(HIR"damage is; "+damage+" !\n"NOR);
           
		   me->add("neili", -100);
           me->add("jingli",-100);
		   if (damage>3000) damage=damage+(damage-3000)/100;
		 
           target->receive_damage("qi", damage,me);
           target->receive_wound("qi", damage /3,me);

           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           //target->set_temp("last_damage_from", me);
           msg = damage_msg(damage, "刺伤");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           msg = replace_string( msg, "$l", random(2)?"胸口":"腰部" );
           msg = replace_string( msg, "$w", weapon->query("name"));
	       message_vision(msg, me, target);
		   //解开后威力增加
           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
		   if (objectp(target)&&me->query("quest/hsjf/cangsong")=="pass"&&me->is_fighting())
		   {
			   message_vision(HBBLU+HIW"$N将领悟的苍松迎客绝技施展出来，瞬间将平时并不连贯的招式悉数融会贯通，向$n疾功数招。\n"NOR,me,target);
			   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
			   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);

		   }
		   if(userp(me) && me->query("env/damage"))
			   tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR); 
		   
if(userp(target)&& target->query("env/damage"))
			   tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR);
		   } else {
              dodge_skill = target->query_skill_mapped("dodge");
              if( !dodge_skill ) dodge_skill = "dodge";
              if (stringp(msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1)))
		      message_vision(msg, me, target);
              me->add("neili", -100);
              me->start_busy(1); 
              target->add_busy(random(2)+1); 
        }
         //新增苍松打斗。
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
         message_vision(HIB"\n$N竟不给$n有丝毫喘息机会,紧跟着"+weapon->query("name")+HIB"再一次挥出,但听“噌”的一声,"+
           "竟携带无比凌厉的剑气刺向$n!\n"NOR,me,target);

        if( random( me->query_dex(1)) >target->query_dex(1)/2
           || random(me->query("combat_exp")) > target->query("combat_exp")/3
           || target->is_busy() )
		{
           damage =  (int)me->query_skill("huashan-jianfa", 1) + (int)me->query_skill("force",1);
		   
           damage = damage + random(damage*3/2);
           if ( me->query("quest/hsjf/cangsong")=="pass") {
               damage = damage*2;
		       target->add_busy(2+random(2));
               message_vision(HIR "$N早已将此招练得纯熟万分,剑招一出,剑气弥漫，气势便犹如千军万马般,直袭$n破绽之处!\n"NOR,me,target);
           }
           if (wizardp(me))
               write(HIR"damage is; "+damage+" !\n"NOR);
           me->add("neili", -200);
           me->add("jingli",-100);
		   if (damage>5000) damage=damage+(damage-5000)/100;
           target->receive_damage("qi", damage,me);
           target->receive_wound("qi", damage/3,me);

           p = (int)target->query("qi")*100/(int)target->query("max_qi");
          // target->set_temp("last_damage_from", me);
           msg = damage_msg(damage, "刺伤");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           msg = replace_string( msg, "$l", random(2)?"头部":"颈部" );
           msg = replace_string( msg, "$w", weapon->name());
	       message_vision(msg, me, target);
		   if (me->is_fighting(target))
		 		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
		   if (me->is_fighting(target))
		       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
        } 
        else {
              dodge_skill = target->query_skill_mapped("dodge");
              if( !dodge_skill ) dodge_skill = "dodge";
              if (stringp(msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1)))
		      message_vision(msg, me, target);
              me->add("neili", -100);
              me->start_busy(1); 
              target->add_busy(random(2)+1); 
        }
        me->delete_temp("hsjf/cangsong"); 

        me->start_perform(4, "「苍松迎客」");
        return 1;
}

int help(object me)
{
   write(WHT"\n华山剑法「"HIG"苍松迎客"WHT"」："NOR"\n");
   write(@HELP
	五岳剑派乃各有所长，华山剑法更以轻巧、灵活、多变而著称。这招
	「苍松迎客」更是华山首徒令狐冲的得意绝技,招数平平而毫无花俏,
	但若能真正领会其真正剑意,再配合紫霞神功,实乃华山气宗一大杀招!
    
	指令：perform sword.cangsong

要求：
	当前内力 1000 以上；
	最大内力 2500 以上； 
	华山剑法 250 以上；
	基本剑法 250 以上；
	华山气功/紫霞神功 250 以上。
说明：
	若能得到令狐冲指点，领会真正剑意，威力大增！

HELP
   );
   return 1;
}
