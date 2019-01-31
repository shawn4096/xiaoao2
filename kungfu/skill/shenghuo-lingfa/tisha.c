// tisha.c 踢沙
// Update By lsxk@hsbbs 2007/6/11 

#include <ansi.h>
inherit F_SSERVER;
int nuoyi_ob(object me,object victim,int damage);
int perform(object me, object target)
{
	object weapon=me->query_temp("weapon");
	int j, f, flag;
    flag=0;

	if( !target ) target = offensive_target(me);

    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
		return notify_fail("「圣火绝学」只能对战斗中的对手使用。\n");

   if(me->query_skill("shenghuo-lingfa", 1) < 450 )
		return notify_fail("你的圣火令法功力太浅，不能使用。\n");

   if(!me->query_skill("jiuyang-shengong", 1)||(int)me->query_skill("jiuyang-shengong",1)<450)
   if(me->query_skill("shenghuo-shengong", 1) < 450 )
           return notify_fail("你的特殊内功功力太浅，不能使用。\n");


   if(me->query_skill("dagger", 1) < 450 )
		return notify_fail("你的基本匕法功力太浅，不能使用。\n");

   if(me->query_skill("cuff", 1) < 450)
		return notify_fail("你的基本拳法功力太浅，不能使用。\n");

   if(me->query_skill("qiankun-danuoyi", 1) < 450 )
		return notify_fail("你的乾坤大挪移功力太浅，不能使用。\n");

   if(me->query("max_neili") < 3000 )
		return notify_fail("你的内力太浅，不能使用。\n");

	if(me->query("neili") < 1000 )
		return notify_fail("你的真气不够，不能使用。\n");

	if(me->query("jingli") < 1000)
		return notify_fail("你的精力不够，不能使用。\n");

	if( me->query_temp("tisha") )
		return notify_fail("你正在施展踢沙绝技呢！\n");

	/*if( me->query_temp("qkdny/hua") )
		return notify_fail("你正在施展乾坤大挪移「化」字诀呢！\n");*/

    if( me->query_skill_mapped("parry") != "shenghuo-lingfa" 
        && me->query_skill_mapped("parry") != "qiankun-danuoyi" )
                return notify_fail("你需要激发招架为圣火令法，方能使用此绝技。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	 || weapon->query("skill_type") != "dagger"
	 || me->query_skill_prepared("cuff") != "shenghuo-lingfa"
	 || me->query_skill_mapped("dagger") != "shenghuo-lingfa"
    || me->query_skill_mapped("cuff") != "shenghuo-lingfa" 
    || (me->query_skill_mapped("force") != "shenghuo-shengong" && me->query_skill_mapped("force") != "jiuyang-shengong") )
		return notify_fail("你不能使用这个绝招！\n");


    if ( !me->query_skill("jiuyang-shengong", 1)&&me->query_skill("qiankun-danuoyi", 1)<350||(!userp(me) && userp(target)))
	  {
	   flag = 3;
	   f = (int)me->query_skill("shenghuo-lingfa", 1)+ (int)me->query_skill("shenghuo-shengong", 1)/3;
	   }
	 else
	   {
		flag = 4;
        f = (int)me->query_skill("shenghuo-lingfa", 1) + (int)me->query_skill("force", 1)/3+(int)me->query_skill("jiuyang-shengong", 1)/3;
		}
    if (me->query("mjqkdny/pass")||me->query("quest/jiuyang/pass"))
	    {
		 flag=5;  		 
         f = (int)me->query_skill("shenghuo-lingfa", 1) + (int)me->query_skill("qiankun-danuoyi", 1)/5+(int)me->query_skill("jiuyang-shengong", 1)/5;
		}
  
     j = f / (8-flag);//由原来的调整8，防止溢出
/*
	if ( f > 500 )
		j = to_int(f/（7-flag） * f/ 250.0);
*/

	message_vision(HBBLU+HIY"\n$N突然横腿疾扫，卷起地下大片沙石，身子一分为"+chinese_number(flag)+"，前后夹击、连攻"+chinese_number(flag)+"招！\n" NOR, me);
    //手持圣火令，威力增加
	if (weapon->query("id")=="shenghuo ling")
         me->add_temp("apply/damage", j/5);
	     me->set_temp("tisha", 5);
   if(userp(me))
      me->add_temp("apply/damage", j);
      me->add_temp("apply/attack", j);
      //target->set_temp("must_be_hit",1);

	  weapon->unequip();
	  me->set_temp("type", 1);
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"),(flag>=4)?3:1);          //第一招空手
	  me->delete_temp("type");
      //target->delete_temp("must_be_hit",1);

	  weapon->wield();
	if (present(target,environment(me)) && me->is_fighting(target))
           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (flag>=4)?3:1); //第2招兵器
//空手且为普通攻击；
	   weapon->unequip();
	  me->set_temp("type", 1);
	if (present(target,environment(me)) && me->is_fighting(target))
           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (flag>=4)?3:1);//第3招空手
	   weapon->wield();
	   me->delete_temp("type");
        
	if (present(target,environment(me)) && me->is_fighting(target) && flag >=4 )   //第4招兵器
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
       
  
   // call_out("nuoyi_ob",0,me,target);
	if (present(target,environment(me)) && me->is_fighting(target) && me->query("mjqkdny/pass"))
	  { 
	   //me->add_temp("apply/damage",j);
	   message_vision(HBRED"\n$N左脚向地上斜踩，溅起地上的泥沙，在霎时之间，$n但觉飞沙扑面，双眼不能见物，茫然不知所措，\n"NOR+HIR"$N趁势从背后一跃而起，向$n的后颈插去。\n"NOR,me,target);
       target->add_busy(2);
	   target->set_temp("must_be_hit",1);
	   COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 3);
	   //me->add_temp("apply/damage",-j);
	   target->delete_temp("must_be_hit");
	 }
	if(userp(me))
      me->add_temp("apply/damage", -j);
      me->add_temp("apply/attack", -j);
	  me->delete_temp("tisha");
   if (weapon->query("id")=="shenghuo ling")
         me->add_temp("apply/damage", -j/5);
   me->add("neili", -600);
   me->add("jingli", -300);
   me->start_perform(4, "踢沙");
   me->start_busy(2);
   return 1;
}

string perform_name(){ return HBRED+HIW"踢沙"NOR; }

int help(object me)
{
	write(YEL"\n圣火令法之「踢沙」："NOR"\n\n");
	write(@HELP
	圣火令法乃是明教两大镇教神功之一。据说传自波斯霍山老人
	后经拜火教传入中原，自波斯三使在灵蛇岛和张无忌一战，纵
	横天下无敌手的张教主连连受挫，吃了不少苦头，根本原因就
	在于其诡异难挡。忽东忽西，南北难辨，防不上防。
	「踢沙」绝技乃是通过功力运转，将路边的沙子飞溅，阻挡敌
	人的视线并同时趁敌人迷惑之际，猛然连出数招。当然，若解
	开乾坤大挪移神功谜题，则此招将再次飞跃。实乃圣火令法最
	为厉害的一大杀技。
	
指令；perform dagger.tisha

要求：
	当前内力的需求 5000 以上；
	最大内力的需求 9000 以上；
	当前精力的需求 2000 以上；
	圣火令法的等级 450 以上；
	乾坤大挪移等级 450 以上：
	圣火神功的等级 450 以上 或者 明教九阳功等级 450 以上；
	基本令法的等级 450 以上；
	基本拳法的等级 450 以上；
	激发令法为圣火令法；
	激发拳法为圣火令法；
	激发招架为圣火令法；
	备拳法为圣火令法；
	且手持兵器,若手持圣火令，武技威力倍增。

HELP
        );
        return 1;
}
