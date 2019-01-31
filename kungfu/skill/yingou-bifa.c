//yingou-bifa.c 银钩笔法
//by sohu@xojh
#include <ansi.h>

inherit SKILL;

string  *msg = ({
"$N一招曹衣带水，长啸一声，手中$w自左向右斜直划下来，顺畅无比，笔笔凌空，顾盼生姿，",
"$N顺手使出「房玄龄碑」如「天女散花」，书法刚健婀娜，极尽仰扬控纵之妙，$w向$n的$l扫出",
"$N转身吐气，$w送出，笔锋在空中横书斜钓，似乎写字一般，然笔锋所指，却处处是人身大穴，向$n后心点去",
"$N一个左拗步，抢到了西首，$w自左向右平平横扫，打向$n的太阳穴，而雄伟中又蕴有一股秀逸的书卷气",
"$N手中$w自右上角斜挥左下角，扫向$n的腰肋。书法之中有点穴，点穴之中有书法，当真是银钓铁划，劲峭凌厉，",
"$N左手直钩，右手中的$w砰的一点，以笔代指，也是招招法度严谨，宛如楷书般的一笔不苟，点向$n胸中膻中穴",
"$N伸左掌在$n肩上一按，一借力，轻轻巧巧的在空中一个翻身，落在远处，长袖飞舞，狂奔疾走，出招全然不依章法",
"但见$N如疯如癫、如酒醉、如中邪，笔意淋漓，指走龙蛇手中$w下掠，左掌带住$n的一记攻势，$w的一撇在$n$l一点，身子借势窜起",
"$N吟道“张旭三杯草圣传，脱帽露顶王公前，挥毫落纸如云烟”，挥洒自如，蓦地里右手倏出，戳向$n的$l，",
"但见$N所写的每一字都是盘绕纠缠，倒像是一幅幅的小画，一个字也不识得。陡然间将$w在半空中疾挥下来，击向$n的太阳穴",
"$N一个字一个字篆将出来，文字固然古奥，而作为书法之基的一阳指也相应加强劲力，手中的$w嗤嗤作响，劲力强劲",
"$N大喝一声，手中$w抖动，已在$n的面上上题了一个大篆，正是一个「尔」字",
"$N轻笑一声，默念口诀，$w向左虚引，右前方豁然疾书，却是一个「乃」字",
"$N身子急速转动，瞻之在前忽然在后，手中的$w神出鬼没，突然间在$n的$l和$l上写上「蛮」和「夷」",
});

int valid_enable(string usage)
{
    return usage == "brush" || usage == "parry";
}

mapping query_action(object me, object weapon)
{         
        return ([
                "action":msg[random(sizeof(msg))],
                "damage":150+random(100),
                "damage_type":random(2)?"刺伤":"割伤",
                "dodge":random(40)-random(20),
                "force":random(200)+100,
               ]); 
}

int practice_skill(object me)
{    
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "brush")
                return notify_fail("你使用的武器不对。\n");
       if ((int)me->query("jingli") < 30)
               return notify_fail("你的体力不够练判官笔法。\n");         
       if ((int)me->query("neili") < 50)
               return notify_fail("你的内力不够练判官笔法。\n");
       me->receive_damage("jingli", 30);
       me->add("neili", -10);
       return 1;
}

int valid_learn(object me)
{
       int skill = me->query_skill("yingou-bifa", 1);
       if ((int)me->query("max_neili") < 500)
               return notify_fail("你的内力不够。\n");
       if ((int)me->query_skill("qiantian-yiyang", 1) < (skill-60))
               return notify_fail("你的乾天一阳功火候太浅。\n");
       if (me->query_skill("yingou-bifa",1)<300)
     	   if ((int)me->query_skill("literate", 1) < (skill-60))
               return notify_fail("你的读书写字级别太低，无法领会书法的意念。\n");      
       return 1;
}

string perform_action_file(string action)
{
      return __DIR__"yingou-bifa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{                
    object weapon=me->query_temp("weapon");
	if (me->query_skill_mapped("force")!="qiantian-yiyang")
		return;
    if (me->query_skill("qiantian-yiyang",1)<250)
        return;
	if (!me->query("quest/tls/yiyangshu/pass")) return;

	if( me->query_temp("qtyy/yiyang") 
		&& me->query("neili")>1000
		&& !random(4)) 
	{
        message_vision(HIY"$N头顶蒸汽氤氲，已然将一阳指的功力运用到这一路银钩笔法的招式中，凌厉刚猛。\n"NOR,me,victim);
		switch (random(2))
		{
		   case 0:
               if (random(me->query_int(1))>victim->query_int()/4)
               {
			     message_vision(HIR"$n从没学过这一路书法，眼花缭乱之际为$N以一阳指力封住了穴道。\n"NOR,me,victim);
				 victim->add_busy(3+random(2));
				 victim->apply_condition("no_exert",1);
               }else {
				 message_vision(HIC"$n对于$N所写的这路书法了然若胸，顺势化解了$N的攻势。\n"NOR,me,victim);
				 me->add_busy(1);
			   }
			   break;
			case 1:
			  if (random(me->query_skill("brush",1))>victim->query_skill("parry",1)/3)
               {
			     message_vision(MAG"$N手中"+weapon->query("name")+MAG"已然变得滚烫，隐隐变红，$n被烫的哇哇大叫,神情疲敝至极。\n"NOR,me,victim);
				 victim->receive_damage("qi",random(3000),me);
				 victim->receive_damage("jing",random(1000),me);
               }else {
				 message_vision(HIC"$n对于$N所写的这路书法了然若胸，顺势化解了$N的攻势。\n"NOR,me,victim);
				 me->add_busy(1);
			   }
			   break;		   
		
		}
        
    }
	return;
}
