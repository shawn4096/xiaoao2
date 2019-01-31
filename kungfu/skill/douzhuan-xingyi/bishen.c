// bishen.c 以彼之道还施彼身
// by tiantian@sj
// By Spiderii@ty更新
#include <ansi.h>
#include <weapon.h>
#include <combat.h>
string perform_name(){ return HIG"以彼之道还施彼身"NOR; }
inherit F_SSERVER;
string query_pfm(object me,object target);
string query_sk(object me);

mapping tested=([
	    "claw":"爪法",
	    "cuff":"拳法",
	    "finger":"指法",
	    "strike":"掌法",
	    "hand":"手法",
	    "leg":"腿法",
      ]);
mapping tested2=([
	    "sword":"剑法",
	    "blade":"刀法",
	    "dagger":"匕法",
	    "brush":"笔法",
	    "spear":"枪法",
	    "hook":"钩法",
	    "stick":"棒法",
	    "staff":"杖法",
	    "club":"棍法",
	    "throwing":"暗器",
	    "whip":"鞭法",
	    "axe":"斧法",
	    "hammer":"锤法"
      ]);
 
int perform(object me, object target)
{
	int i,j;
	object weapon,weapon2;
	//string perform,perform_file;
	string skill,kungfu1,kungfu2;

	if( !target )
		target = offensive_target(me);
	if( !target || !me->is_fighting(target) ) 
		return notify_fail("以彼之道还施彼身只能在战斗中使用!。\n");
//by spiderii@ty
    if(target->query("race") != ("人类"))
		return notify_fail("不会吧，你对动物用的着这样？\n");
	if(me->query_temp("bishen_target") || me->query_temp("dzxy/bishen") )
		return notify_fail("你正在使用以彼之道还施彼身！\n");               
	if(me->query_temp("bishen_target"))
		return notify_fail("你正在使用以彼之道还施彼身。\n");
	if(me->query_temp("douzhuan_target")|| me->query_temp("douzhuan_target"))
		return notify_fail("你正在使用斗转星移。\n");
    
//	if(me->query("quest/mr/dzxy/bishen/pass"))
 
		//return notify_fail("以彼之道还施彼身乃是慕容氏绝学，你尚未融汇贯通！\n");
	
	weapon=me->query_temp("weapon");
	weapon2=target->query_temp("weapon");
    if( !me->query("quest/bishen/pass"))
       if ((!weapon&&weapon2) || (weapon&&!weapon2))
         return notify_fail("你和对方的兵器不同，不能使用以彼之道还施彼身。\n");
	if( target->query("family/family_name")=="姑苏慕容"
		|| target->query_skill("douzhuan-xingyi",1)>0
		|| target->query_temp("bishen_target") )
		return notify_fail("对方身负斗转星移绝技，你无法向对方使用以彼之道还施彼身。\n");
    if(me->query_skill_mapped("force") != "shenyuan-gong")
         return notify_fail("你的内功不是神元功，无法使用以彼之道还施彼身！\n");      
    if(me->query_skill_mapped("parry") != "douzhuan-xingyi")
         return notify_fail("你招架功夫不对,无法使用以彼之道还施彼身！\n");     
    if( (int)me->query("max_neili") < 15000 )
		return notify_fail("你的内力还不够高！\n");
	if( (int)me->query("neili") < 5000 )
		return notify_fail("你当前的内力不够！\n");
	if(me->query_skill("douzhuan-xingyi",1)<500 )
		return notify_fail("你的斗转星移不够熟练，还不能以彼之道还施彼身。\n");
	if(me->query_skill("shenyuan-gong",1)<500 )
		return notify_fail("你的神元功不够熟练，还不能以彼之道还施彼身。\n");
	
	if( me->query("combat_exp")<target->query("combat_exp")/3)
		return notify_fail("你的武功修为跟对方相差太远，强行运用以彼之道还施彼身反而会伤了自己。\n");

	me->set_temp("bishen_target",target);
    me->set_temp("bishen_start",1);
	skill=query_pfm(me,target);
	if (weapon && weapon2) 
      {
		kungfu1=tested2[weapon->query("skill_type")];
		kungfu2=tested2[weapon2->query("skill_type")];
	 }
	if (!weapon && weapon2) 
       {
		kungfu1=tested[query_sk(me)];
		kungfu2=tested2[weapon2->query("skill_type")];
	   }
	if (weapon && !weapon2) 
       {
		kungfu1=tested2[weapon->query("skill_type")];
		kungfu2=tested[query_sk(target)];
	     }
 	if (!weapon && !weapon2) 
       {
		kungfu1=tested[query_sk(me)];
		kungfu2=tested[query_sk(target)];
	   }
	   j = me->query_skill("douzhuan-xingyi", 1);
       i = me->query_skill("douzhuan-xingyi", 1)+me->query_skill("shengyuan-gong", 1)/2;
	if (kungfu1 != kungfu2 )
	   message_vision(HIG"$N仰天狂笑，喝道：今天就教你见识『以彼之道，还施彼身』，化"+kungfu1+"为"+kungfu2+"，使出$n的成名绝技『"+to_chinese(skill)+"』。\n"NOR,me,target);
	else
	   message_vision(HIG"$N仰天狂笑，喝道：今天就教你见识『以彼之道，还施彼身』，使出$n的成名绝技『"+to_chinese(skill)+"』。\n"NOR,me,target);
         me->add_temp("apply/attack", i/3); 
         me->add_temp("apply/damage",i/4);
		 
		 if (!userp(target)) {
		   if (target->is_busy()) target->add_busy(j/100);
		   else target->start_busy(j/100);
		 }
         else 
         { 
			 if (target->is_busy()) target->add_busy(1+random(1));
		     else target->add_busy(1+random(1));
         }
		 
		 message_vision(MAG"$n见到$N忽然施展出自己的成名招式攻来，一时间不禁亡魂皆冒！\n"NOR,me,target);

         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
         if(objectp(target) && me->is_fighting(target)&&me->query_skill("douzhuan-xingyi",1)>350)
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
         if(objectp(target) && me->is_fighting(target)&&me->query_skill("douzhuan-xingyi",1)>450)
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
         if(objectp(target) && me->is_fighting(target)&&me->query_skill("douzhuan-xingyi",1)>550)
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		 
	

         me->add_temp("apply/attack", -i/3); 
         me->add_temp("apply/damage",-i/4);
 	   
	   message_vision(HIG"$N使完一套「"+to_chinese(skill)+"」，左脚后退一步，闪至一边，嘴角露出一丝轻蔑的笑意。\n"NOR,me,target);
       
	   if( me->query("quest/bishen/pass") && me->query_skill("douzhuan-xingyi",1) > 450 ){
                tell_object(me, HIY"\n紧接着你暗暗催动内息,顺势使出“星移斗转”绝技……\n"NOR);
                me->start_call_out( (: call_other, __DIR__"xingyi","xingyi_hit", me,target, 1 :), 1 );
        }
    	me->delete_temp("bishen_target",target);
        me->delete_temp("bishen_start",1);
    	me->start_perform(4,"以彼之道还施彼身"); 
    return 1;
}

string query_pfm(object me, object target)
{
	object weapon=target->query_temp("weapon");
	//string skill,perform;
	string skill;
	int i;
	string *base_skill=({ "cuff","strike","hand","leg","claw","finger" });
    skill="none";
	if(weapon)
	{
		skill=target->query_skill_mapped(weapon->query("skill_type"));
	}
	else
	{
		for(i=0;i<6;i++)
		{
			if( (skill=target->query_skill_prepared(base_skill[i]) ) ) break;
				
		}
	}
	return skill;
}

string query_sk(object me)
{
	//string skill;
	mapping pmap;
	int i;
	string *base_skill=({ "cuff","strike","hand","leg","claw","finger" });
  
  pmap = me->query_skill_prepare();
  
  if (!pmap) pmap = ([]);
  
  if (!sizeof(pmap))
      return "none";

		for(i=0;i<6;i++)
		{
			if( me->query_skill_prepared(base_skill[i]) ) return base_skill[i];				
		}
		return "none";
}



int help(object me)
{
    write(WHT"\n斗转星移之「"HIG"以彼之道，还施彼身"WHT"」："NOR"\n");
         write(@HELP
	「以彼之道，还施彼身」是为慕容世家家传绝学。用对手
	的成名绝技反攻，斗转星移达到一定等级时可顺势使出另
	一绝技「星移斗转」。此武功乃慕容氏斗转星移至高绝学
	需要身具有深厚的功力方可施展，机缘巧合之下，通过解
	密方可修习。

指令：perform parry.bishen

要求：
	最大内力 15000 以上；      
	当前内力 5000  以上；
	斗转星移 500   级以上
	神元功法 500   级以上
	激发内功为神元功；
	激发招架为斗转星移；
	未解其精要时，必须与对方同时空手或同持武器；
	武学修为与对方相差不能小于对方1/3。
	不能对慕容弟子使用。       
HELP
    );
        return 1;
}

