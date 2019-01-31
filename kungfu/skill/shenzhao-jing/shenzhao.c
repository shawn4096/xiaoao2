// By Spiderii修改 shenzhao.c

#include <ansi.h>
#include <combat_msg.h>
void remove_effect(object me,int skill);

int exert(object me)
{      
       int skill;
	   object weapon;
	   string msg;
       skill = me->query_skill("shenzhao-jing",1);
	   
	   weapon = me->query_temp("weapon");
	if (skill < 450 && !me->is_fighting())
		return notify_fail("你只能在战斗中使用「神照」！\n");

	if( (int)me->query_skill("shenzhao-jing", 1) < 120 )
		return notify_fail("你的神照经修为不够，无法使用「神照」！\n");

	if (me->query_skill_mapped("force") != "shenzhao-jing")
		return notify_fail("其它内功有「神照」吗？\n");

	if( (int)me->query("neili") < 1500 )
		return notify_fail("你目前的内力太少了，无法使用「神照」！\n");

	if( (int)me->query("max_neili") < 2000 )
		return notify_fail("你的内力修为这么差，还想使用「神照」？\n");

	if( me->query_temp("sjz_power"))
		return notify_fail("你正在运用「神照」！\n");

	message_vision(HIW"\n$N深吸一口气，内息缓缓而动，劲力随着增加，顿时感觉精神力气勃然而兴，沛然而至！\n" NOR, me);
	if (skill < 450) me->add_busy(1);

	if (me->query("quest/shenzhao/dingdian"))
	 {
	  message_vision(HIY"$N运起神照经，似乎变了一个人似得，看起来$N的防御能力大幅提升。\n" NOR,me);
	  //msg==HIY"$N运起神照经，似乎变了一个人似得，看起来你的防御能力大幅提升。\n" NOR;
	  me->add_temp("apply/dexerity", skill/10); //略微增加身法躲避
      me->add_temp("apply/parry", skill/5);
	  //me->add_temp("apply/sword",skill/2);
      //me->add_temp("apply/blade",skill/4);
     }  
	if (userp(me) && skill > 449 && me->query("quest/shenzhao/diyun"))
    {
	  message_vision(HBMAG"$N按照狄云所传授的运功法门，神照经随心而起，得心应手，手上的力度似乎增加了。\n" NOR, me);
	
	 // msg==HBMAG"$N按照狄云所传授的运功法门，神照经随心而起，得心应手，手上的力度似乎增加了。\n" NOR;
	  me->add_temp("apply/defense",skill/3);
	  me->add_temp("apply/parry", skill/5);
	  me->add_temp("apply/sword",skill/3);
	  me->add_temp("apply/cuff",skill/3); //为无影拳做准备
      me->add_temp("apply/blade",skill/3);
    }  
	
	if (userp(me) && skill > 549 && (me->query("quest/shenzhao/laozu")|| me->query("quest/szj/pass")==3))
	{  //作为百姓的一门强大内功，设置为阳性，定位为9级
      message_vision(HBRED"$N将神照经融会贯通，面色微微潮红，衣襟缓缓膨起，神照经的威力显然已达化境！\n" NOR, me);
     
	 // msg==HBRED"$N将神照经融会贯通，面色微微潮红，衣襟缓缓膨起，神照经的威力显然已达化境！\n" NOR;
	  //me->add_temp("apply/parry", skill/4);
      me->add_temp("apply/armor", skill/4);
	  me->add_temp("apply/damage", skill/4);
      me->add_temp("apply/strength", skill/9);
	  me->add("neili",-200);
	}
     //message_vision(msg,me);
	 me->add_temp("apply/dodge", me->query_skill("shenzhao-jing", 1)/4);
     me->add_temp("apply/attack", me->query_skill("shenzhao-jing", 1)/4);
	 me->add("neili", -300);
	 me->set_temp("sjz_power",skill);
 	 call_out("remove_effect", 1, me, skill/20);
	 if (!me->query("quest/shenzhao/diyun"))
		 me->start_exert(2, "「神照」");
	 return 1;
}
void remove_effect(object me, int count)
{
	
	 int skill;
	 if (!me) return;
	 skill=me->query_temp("sjz_power");

     if (count>0) {
                        
		call_out("remove_effect", 1, me, count-1);
        return;
         
	 }
	 
	  if (userp(me) && skill > 549 && (me->query("quest/shenzhao/laozu")|| me->query("quest/szj/pass")==3))
	    {
      
          me->add_temp("apply/armor", -skill/4);
	      me->add_temp("apply/damage", -skill/4);
          me->add_temp("apply/strength", -skill/9);
	   }
	   if (userp(me) && skill > 449 && me->query("quest/shenzhao/diyun"))
        {
	       me->add_temp("apply/defense",-skill/3);
	       me->add_temp("apply/sword",-skill/3);
		   me->add_temp("apply/cuff",-skill/3);
           me->add_temp("apply/blade",-skill/3);
		   me->add_temp("apply/parry", -skill/5);
        }  
	   if (me->query("quest/shenzhao/dingdian"))
        {
		  me->add_temp("apply/dexerity", -skill/10); //略微增加身法躲避
          me->add_temp("apply/parry", -skill/5);
        }  
		   
        me->add_temp("apply/dodge", -me->query_skill("shenzhao-jing", 1)/4);
        me->add_temp("apply/attack", -me->query_skill("shenzhao-jing", 1)/4);
      	me->delete_temp("sjz_power");
 
	   message_vision(HIM"$N缓缓地舒了一口气，散去了神照经的运转真气。\n"NOR, me);
	   return;

	
}

string perform_name(){ return HIM"神照功"NOR; }

int help(object me)
{
        write(WHT"\n神照经之「神照功」："NOR"\n");
        write(@HELP
	这是铁骨墨萼梅念笙老先生曾经教丁典的一套内功的秘经
	丁典习得此内功，后又传授狄云，狄云苦心多年，神照经
	已习得第三境界。巧遇机缘得到狄云指点，可更上一层楼
	为了体现神照经作为连城诀中的顶级武功特点，总共分为
	三个阶段，第一段由丁典指点，第二段由狄云指点。第三
	段将因机缘巧合为神照彻底大成，另外因狄云的缘故，神
	照经在和血刀门的武技配合有适当的加成效果，具体经验
	由玩家自行摸索。
	
	指令：exert shenzhao
			        
要求:
	内力 1500 以上；
	神照经 120 级以上；

效果:   
	若解开丁典的神照经，则会大幅提升防御。
	若解开狄云的神照经，则神照威力会彻底释放。
	神照经各段均有不同程度的飞跃，越战越强
	第一段为防御提升
	第二段为攻击提升
	第三段伤害提升        
	450级后大飞。
	550级且解开第三段后神照经的威力将会大幅提高。
			    
        
HELP
        );
        return 1;
}

