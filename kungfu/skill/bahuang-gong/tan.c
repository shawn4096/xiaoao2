// tan.c creat by sohu@xojh 
// 源自天龙八部天山童姥教授虚竹功法
// 初期必须有暗器在手，后期则转化为生死符，须有盛水的袋子，水中含毒则会中毒附带效果
#include <ansi.h>
inherit F_SSERVER;
inherit F_CLEAN_UP;
#include "/kungfu/skill/eff_msg.h"

string exert_name(){ return HIY"弹字诀"NOR; }

int exert(object me, object target)
{
	int skill,num,damage,p;
	string msg;
	object weapon;
	weapon=me->query_temp("weapon");
	skill =  me->query_skill("bahuang-gong", 1);
    //if(!target) target = offensive_target(me);
    if( !target || !me->is_fighting(target) || !living(target)
            || environment(target)!=environment(me))
                return notify_fail("弹字诀只能在战斗中对对手使用。\n");
	if( me->query("max_neili") < 3000 )
		return notify_fail("你的最大内力不够。\n");
	if( me->query("neili") < 1200 )
		return notify_fail("你的当前内力不够，无法施展弹字诀。\n");
    if( me->query("jingli") < 1000 )
		return notify_fail("你的当前精力不够。\n");

	if( me->query_skill("bahuang-gong", 1) < 350 )
		return notify_fail("你的八荒六合唯我独尊功等级不够。\n");

	if( me->query_skill_mapped("force") != "bahuang-gong" )
		return notify_fail("你的内功不对。\n");
    if ((int)me->query_skill("bahuang-gong",1)<500 || me->query("bhg/biguan",1)<3)
  	  if (!weapon ||weapon->query("skill_type")!="throwing")
        return notify_fail("你八荒六合唯我独尊功尚未大成，尚达不到飞花摘叶之地步，需手持暗器。\n");
	
	if( me->query_temp("bhg/tan") )
		return notify_fail("你已经在运使「八荒六合唯我独尊」弹字诀了。\n");

	if (me->query_skill("bahuang-gong",1)<350) num=3;
	else if (me->query_skill("bahuang-gong",1)<450) num=6;
	else num=12;
	if (me->query("bhg/biguan")<3 && weapon->query_amount() < num)
             return notify_fail("你忽然发现身上的暗器不够，无法使出这弹字诀，只得放下手中暗器。\n");   
	if (userp(target)&&damage>4000) damage=4000+(damage-4000)/100;
	
	me->receive_damage("neili", -random(100)*num);
	me->receive_damage("jingli", -random(50)*num);
	message_vision(HBYEL+HIW "$N将丹田中的真气，先运到肩头巨骨穴，再送到手肘天井穴，然后送到手腕阳池穴，\n"
	                   +"在阳豁、阳谷、阳池三穴中连转三转，然后运到无名指关冲穴！\n" NOR, me);
    message_vision(HIY+chinese_number(num)+"道乌光从$N手上飞掠而出，在八荒功气劲激发之下射向$n。\n"NOR,me,target);
    if (me->query("bhg/biguan")<3 && weapon->query_amount() < num)      
	   weapon->add_amount(-num);
	me->set_temp("bhg/tan",1);
    if (random(me->query("neili"))>target->query("neili")/2||random(me->query_skill("force",1))>target->query_skill("dodge",1)/2)
    {    
	  damage=me->query_skill("bahuang-gong",1)+me->query_skill("force",1);
	  damage=damage*2+random(damage);
	  damage=damage*num;
	  if (damage>target->query("qi",1))
	     damage=target->query("qi")-1;
	  target->receive_damage("qi",damage,me);
	  //target->receive_wound("qi",damage/4);
      p = (int)target->query("qi")*100/(int)target->query("max_qi");
      tell_room(environment(target), HIR + target->name()+"突然顿时为之一滞，显然穴道被打中！\n" NOR, ({ target }));  
           msg = damage_msg(damage, "内伤");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           message_vision(msg, me, target);
      target->start_busy(2+random(1));
	  if (me->query("bhg/biguan")>=2)
	  {
		message_vision(HIY"$N八荒功已然大成，豁然贯通，数股劲气笼罩$n周身，劲气汹涌澎湃,嗤嗤作响。\n"NOR,me,target);
		message_vision(HIC"$n为$N气劲锁住经脉，顿时气血翻涌。\n"NOR,me,target);
		target->apply_condition("no_exert",1+random(1));
		//target->apply_condition();
		target->add_busy(1+random(2));
	  }
	}
	else {
     message_vision(CYN"$n轻轻向旁闪身，躲过了这数道袭击，不由地吓了一身冷汗。\n"NOR,me,target);
	 me->add_busy(1+random(1)); 
	}
	me->delete_temp("bhg/tan");
	//if (me->query_skill("bahuang-gong",1)<450)
	me->start_exert(3, "弹字诀");
	me->start_perform(3, "弹字诀");
	me->start_busy(1);
	return 1;
}



int help(object me)
{
	write(HIW"\n八荒六合唯我独尊功之「弹字诀」："NOR"\n\n");
        write(@HELP
	虚竹子在解救天山童姥的过程中，受童姥指使
	学习了无上内功运使法门。尤其是在打跑外岛
	岛主的追逐过程中，以松球代替暗器，运使八
	荒六合劲打的诸路英豪狼奔豕突。弹字诀的劲
	力运使法门起到关键性作用。
	弹字诀，在小飞前，因技能所限只能弹出三道
	劲气，大飞前能弹出六道劲气，大飞后，能弹
	出十二道劲气。所以这门功法主要是判断双方
	内力强弱，内力或内功越是强大，命中和伤害
	越高。
	注意的是 500级前因功力不到所以需要手持暗
	器，但是当 500级后且功力贯通若解开密室中
	闭关第三段，则可以达到飞花摘叶伤人于无形
	的地步。

	指令；yun tan
	
要求：
	最大内力  3000 以上；
	当前内力  1200  以上；
	当前精力  1000  以上；
	八荒六合唯我独尊功  350  级以上；
HELP
        );
        return 1;
}