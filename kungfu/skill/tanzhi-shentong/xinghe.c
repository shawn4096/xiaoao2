// xinghe Modify By River@SJ 2001.12.13
inherit F_SSERVER;
#include <ansi.h>
#include <combat.h>
void check_xinghe(object me, object target, int count);
void xinghe_effct(object me);

mapping valid_types = 
([
	"finger":	"指法",
	"hand":		"手法",
	"cuff":		"拳法",
	"claw":		"爪法",
	"strike":	"掌法",
	"leg":		"腿法",
]);

int perform(object me, object target)
{
	string *skill, basic1, msg, sk;
	int i,lvl;
	mapping smap, pmap;
    lvl=me->query_skill("tanzhi-shentong",1)+me->query_skill("bihai-chaosheng",1)/5;
	if( !target ) target = offensive_target(me);

        if( !objectp(target)
	 ||  !target->is_character()
	 ||  !me->is_fighting(target) )
		return notify_fail("「星河千帆舞」只能对战斗中的对手使用。\n");
  
	if ( me->query_skill("bihai-chaosheng", 1) < 350 )
		return notify_fail("你的碧海潮生功不够，无法使出星河千帆舞。\n");

	if ( me->query_skill("suibo-zhuliu", 1) < 350 )
		return notify_fail("你的随波逐流修为未到，无法使出星河千帆舞。\n");

	if ( me->query_skill("tanzhi-shentong", 1) < 350 )
		return notify_fail("你的弹指神通修为未到，无法使出星河千帆舞。\n");

	if ( me->query_skill_mapped("parry") != "tanzhi-shentong"
	 || me->query_skill_mapped("finger") != "tanzhi-shentong"
	 || me->query_skill_prepared("finger") != "tanzhi-shentong")
	 	return notify_fail("你现在无法使用星河千帆舞。\n");

	if ( me->query_temp("weapon"))
		return notify_fail("你现在无法使用星河千帆舞,必须空手。\n");

	if ( me->query_skill("finger",1) < 350 )
		return notify_fail("你的指法修为不足，使不出星河千帆舞。\n");

	if( me->query("max_neili") < 3500 )
		return notify_fail("你内力太弱，不能出星河千帆舞。\n");

	if( me->query("neili") < 1200 )
		return notify_fail("你真气太弱，不能出星河千帆舞。\n");

	if( me->query("jingli") < 1000 )
		return notify_fail("你精力太弱，不能出星河千帆舞。\n");
    if (me->is_busy()
	  ||me->query_temp("no_prepare")
	  ||me->is_perform()
	  ||me->query_condition("no_perform")){	  
	  return notify_fail("你气血不匀，无法使用星河千帆舞。\n");
    }
		
	if (me->query_temp("thd/xinghe"))
		//|| me->query_temp("xinghe")
		return notify_fail("你正在使用星河千帆舞。\n");

	sk = me->query("env/xinghe");

	if (!sk || sk == "tanzhi-shentong") 
		return notify_fail("你必须选择一个技巧来配合！\n");

	if (me->query_skill(sk,1) < 350)
		return notify_fail("你的组合技巧还没纯熟。\n");
	//所有map的武技
	smap = me->query_skill_map();
	//所有prepare的武技
	pmap = me->query_skill_prepare();
	//获得设置星河的基本武技basic1
	skill = keys(valid_types);
	for (i=0; i<sizeof(skill); i++) {
		if( smap[skill[i]] == sk ) basic1 = skill[i];
	}
	if ( !basic1 )
		return notify_fail("这种技能尚未激发或目前不能准备。\n");
	//此时清理所有prepare 技能，

	skill = keys(pmap);
	for (i=0; i<sizeof(skill); i++) {
		me->prepare_skill(skill[i]);
	}
	//重新准备新技能
	me->prepare_skill(basic1, sk);
	//重置行为
	me->reset_action();

	if (me->query_skill("tanzhi-shentong",1)<400)
	   me->start_perform(2, "星河千帆舞");
	
	message_vision(HIW"\n$N长啸一声，身形加快，施展出桃花岛绝技「星河千帆舞」，招数一变，不时抽空施展弹指神通！\n"NOR,me,target);
	me->add("neili",-400);
	me->add_temp("apply/attack", lvl/4);
	me->add_temp("apply/damage", lvl/6);
	me->add("jingli", - 200);
	me->set_temp("thd/xinghe",lvl);
	//message_vision(msg, me, target);
	if ( me->is_fighting(target) )
        COMBAT_D->do_attack(me, target, 0, 3);
  /*  if ( me->is_fighting(target) )
                 COMBAT_D->do_attack(me, target, 0, 3);*/
	//if ( me->is_fighting(target) ){
		//remove_call_out("check_xinghe");
		//改为直接调用，以免出错
	call_out("check_xinghe", 1, me, target, (int)me->query_skill("tanzhi-shentong",1));
	//}
	return 1;
}

string *xue_name = ({ 
"劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
"幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴","清灵穴","至阳穴",
"涌泉穴","大锥穴","风府穴",
}); 

void check_xinghe(object me, object target, int count)
{
	int p, lvl, dam,i, x=1;
	int ap, dp;
	string msg, *skill, dodge_skill, name, *limbs;
	mapping pmap;
    object weapon;
	
 
	if ( !me ) return; //死掉则退出
	//if( !target ) target = offensive_target(me);
	weapon=me->query_temp("weapon");

    lvl=me->query_temp("thd/xinghe");

	dam = (me->query_skill("finger",1)+me->query_skill("tanzhi-shentong",1)+me->query_skill("bihai-chaosheng",1))* 2;
	dam += me->query("jiali");
	dam += random(dam);

	pmap = me->query_skill_prepare();	

	if (count < 1 || !me->is_fighting() || !objectp(target)|| objectp(weapon))
	{
		me->delete_temp("thd/xinghe");
		if (weapon)
		{
			message_vision(HIC"$N拿起了武器，星河顿时连贯不起来。\n"NOR,me);
		}
		
		skill = keys(pmap);
		for (i=0; i<sizeof(skill); i++) {
			me->prepare_skill(skill[i]);
		}
		me->prepare_skill("finger", "tanzhi-shentong");		
		//me->delete_temp("xinghe");
		me->add_temp("apply/attack", -lvl/4);
		me->add_temp("apply/damage", -lvl/6);
		if (me->query_skill("tanzhi-shentong",1)<400)
			me->start_perform(1, "星河千帆舞");
		if (living(me) && !me->is_ghost())
			message_vision(HIW"\n$N招数一变，又转回了弹指神通。\n"NOR, me);
		return;
	}

		if (!sizeof(pmap)) msg = "unarmed";
		else msg = keys(pmap)[0];

		limbs = target->query("limbs");
		name = xue_name[random(sizeof(xue_name))];
		
		message_vision(HBGRN+HIW+"\n$N将弹指神通挟在招数之中，弹出一道指风，直指向$n的「"NOR+HIR+name+HBGRN+HIW"」！\n"NOR, me, target);
		message_vision(replace_string(SKILL_D("tanzhi-shentong")->query_action(me, 0)["action"],"$l", limbs[random(sizeof(limbs))]) + "！\n"NOR, me, target);
        
		
	   
		if ( me->is_fighting(target)&&objectp(target) )
                 COMBAT_D->do_attack(me, target, 0, 3);
		switch (random(3)) 
		{
			case 0:
				if (objectp(target) && me->is_fighting(target) )
				{	
					target->receive_damage("qi", dam, me);
					target->receive_wound("qi", dam/4, me);
					if (!random(3)) target->add_condition("no_exert", 2);
				//msg = COMBAT_D->damage_msg(lvl, "刺伤");
					message_vision(HIC"$N将劲气运于食指，弹指神通劲力澎湃，当真神鬼莫测,指风凌冽，嗤嗤有声。\n"NOR,me,target);
					//if(userp(me) && me->query("env/damage"))
						//tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ dam+ WHT"点攻击伤害。\n"NOR);
				
					//if(userp(target)&& target->query("env/damage"))
						//tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ dam+ WHT"点伤害。\n"NOR);
					if (random(2) && target->query("qi") >=0 || target->query("eff_qi")+target->query_temp("apply/qi") < 0) 
					{
						p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100
							/(target->query("max_qi")+target->query_temp("apply/qi"));
						msg = "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
					}
					else {
						p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
						msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
					}
					msg = replace_string( msg, "$w", "弹指剑气");
				//	msg = replace_string( msg, "$l", name);
					//me->delete_temp("xinghe/"+target->query("id"));
					//message_vision(msg,me,target);  //这里msg会出现strike的信息，暂时屏蔽 by renlai
 					message_vision(HIG"$N趁$n的招式一阵迷茫之际，弹指神通连出数招！\n"NOR, me, target);
					COMBAT_D->do_attack(me, target, 0, 3);
					//COMBAT_D->do_attack(me, target, 0, 3);
				}
				break;
			case 1:
				if (objectp(target) && me->is_fighting(target) )
				{
 					message_vision(HIY"$N弹指神通绝技已经出神入化，劲风凛冽，弹向$n的"+HIR+name+HIC"！。\n"NOR, me, target);
					if (userp(target)) target->add_busy(2);
					else target->add_busy(4);
				}
				break;
		    case 2:
				if (objectp(target) && me->is_fighting(target) )
				{
				 message_vision(HIG"$n稍微露出破绽，$N运起弹指神通绝技，戳向$n的"+HIR+name+HIG"！嗤嗤有声。\n"NOR, me, target);
                 
				 target->receive_damage("jing",random(500),me);
				 
				 me->add_temp("apply/finger",(int)me->query_skill("finger",1)/3);
				 COMBAT_D->do_attack(me, target, 0, 3);
				 COMBAT_D->do_attack(me, target, 0, 3);
				 me->add_temp("apply/finger",-(int)me->query_skill("finger",1)/3);
			    }
				break;			
			//default: call_out("xinghe_effct",2,me);
			
		}
		 //remove_call_out("check_xinghe");
		call_out("check_xinghe", 2, me, target, count -1);
	return;	

}

string perform_name(){ return HIW"星河千帆舞"NOR; }

int help(object me)
{
        write(HIW"\n弹指神通之「星河千帆舞」："NOR"\n\n");
        write(@HELP
	东邪黄药师喜欢诗词歌赋，尤其喜欢李清照的《渔家傲》
	天接云涛连晓雾，星河欲转千帆舞。仿佛梦魂归帝所，闻
	天语，殷勤问我归何处，我道路长嗟日暮，学诗漫有惊人
	语。九万里风鹏正举，风休住，蓬舟吹取三山去。后来黄
	药师将此意境融入到自己平生得意绝技之中。
	
	perform finger.xinghe
	
要求：
	最大内力要求 3500 以上；
	当前内力要求 1200 以上；
	当前精力要求 1000 以上；
	碧海潮生等级 350 以上；
	随波逐流等级 350 以上；
	弹指神通等级 350 以上；
	基本指法等级 350 以上；
	激发指法为弹指神通；
	激发招架为弹指神通；
	空手且备指法为弹指神通。
	注明：400级后飞跃
使用说明：
	set xinghe <空手特殊武功>
	例：set xinghe luoying-zhang

HELP
        );
        return 1;
}
