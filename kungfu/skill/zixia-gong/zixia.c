// zixia.c yun zixia 可以在战斗中加临时的气
// Update By lsxk@hsbbs 增加set才能有double neili效果,增加功效。
/* update by lsxk@hsbbs 调整为免费增加内力，不需要set, 战斗后，如果当前内力大于
   战斗前内力，则直接调整到战斗前的内力，已防止利用zixia来add max_neili
*/

#include <ansi.h>

//inherit F_CLEAN_UP;
inherit F_SSERVER;

string exert_name() {return HBMAG"紫霞神功"NOR;}

void remove_effect(object me);

int exert(object me, object target)
{
    if( !target ) target = offensive_target(me);

        if (!me->is_fighting())
                return notify_fail("你只能在战斗中使用用紫霞功。\n");
        if(userp(me) && !me->query("quest/huashan/zixia/pass"))
           if(userp(me) && me->query("quest/huashan")!="气宗")
                return notify_fail("紫霞神功乃华山气宗绝学，你非华山气宗弟子，哪里偷学来的紫霞神功？\n");

        if( (int)me->query("neili") < 1000  )
                return notify_fail("你的内力不够。\n");
        if( (int)me->query_temp("zxg/zixia") ) 
                return notify_fail("你已经在运用紫霞神功了。\n");

        me->set_temp("zxg/zixia", me->query("neili"));
        me->add("neili", -500);
        if(me->query("neili")>me->query("max_neili")*2){
                 me->set("neili",me->query("max_neili")*2);
        }
       
        message_vision(MAG "$N暗运华山气宗绝技紫霞神功，脸上紫气时隐时现。\n" NOR, me);
      	me->add_temp("apply/attack",(int)me->query_skill("zixia-gong",1)/5);
        me->add_temp("apply/armor",(int)me->query_skill("zixia-gong",1)/7);
		me->add_temp("apply/damage",(int)me->query_skill("zixia-gong",1)/7);
       	
        call_out("remove_effect", 1, me,me->query_skill("zixia-gong",1)/5);
        call_out("zixia_temp",1,me,target);
        if (me->query_skill("zixia-gong",1)<450) me->start_exert(2+random(2), "紫霞功");
        else if (me->query_skill("zixia-gong",1)<550)  me->start_exert(1, "紫霞功");

        return 1;
}

void remove_effect(object me)
{
        if (objectp(me)) {
                if (me->is_fighting() && (int)me->query("neili")>800) {
                        call_out("remove_effect", 1, me);
                        return;
                }
               // if((int)me->query("neili")>(int)me->query_temp("zxg/zixia"))
                
				me->add_temp("apply/attack",-(int)me->query_skill("zixia-gong",1)/5);
                me->add_temp("apply/armor",-(int)me->query_skill("zixia-gong",1)/7);
		        me->add_temp("apply/damage",-(int)me->query_skill("zixia-gong",1)/7);
				me->set("neili",(int)me->query_temp("zxg/zixia"));
                me->delete_temp("zxg/zixia");
                tell_object(me, MAG"你的紫霞神功运行完毕，周身紫气渐渐消退。\n"NOR);
        }
}

void zixia_temp(object me,object target)
{
    int lvl;
    if(!me) return;
    if(!target) return;

    lvl = (int)me->query_skill("zixia-gong",1)*2/3 + (int)me->query_skill("force",1)/3;
    if (me->query_temp("zxg/zixia") && me->is_fighting(target) )
     {
          if (random(lvl) > ( (int)target->query_skill("parry") )*3/4 ){
              message_vision(HIM "$N潜运紫霞神功，趁$n防备不周时连攻两招！\n" NOR, me,target);
              COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 1);
              COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 1);
          }
          else if (random(lvl) > ( (int)target->query_skill("parry") )/2 ){
              message_vision(MAG "$N潜运紫霞神功，趁$n防备不周时狠攻一招！\n" NOR, me,target);
              COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 1);
          }
          call_out("zixia_temp",1,me,target);
      }
}

int help(object me)
{
   write(YEL"\n紫霞神功「"MAG"紫霞神功"YEL"」："NOR"\n");
	write(@HELP
	“华山九功，首功紫霞”，这紫霞神功不愧为当世奇功。对阵中往往
	由于自己内力耗尽而不得不败下阵来，而此绝迹却能令自己在对阵时
	聚集以往两倍的内力，并且时刻寻找机会进行反攻。使得对阵杀敌易
	如反掌。另，紫霞神功大成者，亦有护体奇效！
	450级后小飞，550级后大飞，取消busy。
	指令：exert zixia
	要求：当前内力 1000 以上。	
	说明：
		当紫霞神功大于300级时，可以通过【set 紫霞神功 护体】
		来使用紫霞神功的特殊防御效果。每出现一次护体效果，都
		会消耗部分当前内力。请谨慎使用！
HELP
	);
	return 1;
}
