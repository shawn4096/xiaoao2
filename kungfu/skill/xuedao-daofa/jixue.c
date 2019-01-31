// jixue.c  血刀经 [祭血诀]
// Edit by sohu@xojh
//增加刀的威力。。
#include <ansi.h>
#include <skill.h>
#include <combat.h>
#include <weapon.h>
inherit F_SSERVER;

string perform_name(){ return RED"祭血诀"NOR; }

void jixue(object me,object target,int times,int now);
 
int perform(object me, object target)
{
	object ob,weapon;
	string msg;
	int lvl,times;
    
	if( !me->is_fighting() )
		return notify_fail("「祭血诀」只能在战斗中使用。\n");

	if (!objectp(weapon = me->query_temp("weapon"))	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");
 
	if((int)me->query_skill("xuedao-jing",1) < 350)
		return notify_fail("你的血刀经修为不够， 目前不能使用「祭血诀」! \n");

	if(me->query_temp("xddf/jixue"))
		return notify_fail("你正在使用「祭血诀」! \n");

	if((int)me->query_skill("blade",1) < 350)
		return notify_fail("你的基本刀法修为不够， 目前不能使用「祭血诀」! \n");

	if( me->query_skill_mapped("blade") != "xuedao-daofa")
		return notify_fail("你必须使用血刀刀法，才能使用「祭血诀」的绝技！\n");
	if ( me->query_skill_mapped("parry") != "xuedao-daofa" && me->query_skill_mapped("parry") != "jingang-liantishu")
             	return notify_fail("你的招架不对，必须激发刀法为血刀刀法或金刚炼体术。\n");
	
	if( me->query_skill("xuedao-daofa",1) < 350)
		return notify_fail("你的血刀刀法等级不够，不能使用「祭血诀」的绝技！\n");

    if( me->query_skill_mapped("force") != "xuedao-jing" && me->query_skill_mapped("force") != "shenzhao-jing")
		return notify_fail("你现在所使用的内功同「血刀大法」向抵触，不能使出「祭血诀」的绝技！\n");

	if( (int)me->query("max_neili") < 2000 )
		return notify_fail("你的内力修为不够！\n");
	if((int)me->query("neili")<800)
		return notify_fail("你的真气不够！\n"); 
	if((int)me->query("jingli")<500)
		return notify_fail("你的精力不够！\n"); 

	ob = me->select_opponent();
	lvl = me->query_skill("xuedao-daofa",1);
	
	me->set_temp("xddf/jixue",1);
	times = me->query("env/血刀祭血");
	
	if(times < 1) times = 1;
	if(times > lvl/40) times = lvl/40;
	if(times > 6) times = 6;

	msg = HIY"\n$N脸色陡然一变，口中念念有词，同时倒转兵刃，不知道要做什么！\n\n"NOR;
	message_vision(msg, me);
	me->add("neili", -200);
	me->add_temp("apply/attack",lvl/3);
	me->add_temp("apply/damage",lvl/4);
	
	msg = BLU"\n$N忽然将自己身上的鲜血涂抹在兵器上，喋喋淫笑道，"HIC"“月圆之夜，杀人之时”"BLU"，来吧小宝贝！\n\n"NOR;
	if (present(target,environment(me)) && me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	
	me->add_temp("apply/attack",-lvl/3);	
	me->add_temp("apply/damage",-lvl/4);

	call_out("jixue",0,me,ob,times,0);


	return 1;
}

void jixue(object me,object target,int times,int now)
{
	string msg,weaname;
	object weapon;
	int lvl,force,damage,attack,qi;

	if( !objectp(me) ) return;
	if( !objectp(target) || !me->is_fighting(target) || (now >= times) || (me->query("neili")<200) || 
	  (!objectp(weapon = me->query_temp("weapon"))) || ((string)weapon->query("skill_type")!="blade") ) {
		me->delete_temp("xddf/jixue");
		me->start_perform(1,"祭血诀");
		if(living(me))
			message_vision(HIC"\n$N慢慢收回内劲，脸上也似乎有了血色。\n"NOR, me);
		return;
	}

	weapon = me->query_temp("weapon");
	weaname = weapon->query("name");
	lvl = me->query_skill("xuedao-jing",1);
	force = me->query_skill("xuedao-dafa",1);

	now++;
	if(now <= 1)
		msg = HIR"\n$N狂啸一声，以兵刃自砍手臂，顿时一飙鲜血飞溅在"NOR+weaname+HIR"之上，"NOR+weaname+HIR"隐隐泛出一层血色。";
	else
	if(now <= 3)
		msg = HIR"\n$N狂啸一声，以兵刃自砍胸膛，顿时一腔鲜血飞溅在"+weaname+HIR"之上，"NOR+weaname+HIR"泛出一层血色！";
	else
		msg = RED"\n$N狂啸一声，当头砍了自己一刀，顿时一股鲜血飞溅在"+weaname+RED"之上，"NOR+weaname+RED"整个变的通红！！！";
	
	attack = 7-now;
	damage = 8-now;
	if(me->query_temp("xuedao/yuxue")) {
		damage--;
		if(damage<2) damage=2;
		msg += "$N更把血刀大法的内劲附于兵刃之上！";
	}
	msg += "\n"NOR;
	message_vision(msg, me);
	
	if(wizardp(me) && me->query("env/test")) tell_object(me,sprintf("damage:%d , attack:%d , qi:%d \n",force/damage,lvl/attack,-50*now));

	me->add_temp("apply/damage", force/damage);
	me->add_temp("apply/attack", lvl/attack);
	me->set_temp("xddf/jixue1",1);
	if (present(target,environment(me)) && me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if (present(target,environment(me)) && me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	me->delete_temp("xddf/jixue1");

	me->add_temp("apply/damage", -force/damage );
	me->add_temp("apply/attack", -lvl/attack);

	if(me->query("qi") < (60*now)) 
		qi = me->query("qi")-10;
	else
		qi = 60*now;
	if(qi<0) qi = 0;

	me->receive_damage("qi", qi,"祭刀失血过多");
	me->receive_wound("qi", qi/2,"祭刀失血过多");

	me->add("neili", -50*now);
	if(me->query("neili") < 0)	me->set("neili",0);

	call_out("jixue",1+random(3),me,target,times,now);
}
int help(object me)

{
        write(RED"\n血刀刀法之「祭血诀」："NOR"\n\n");
        write(@HELP
	血刀经乃是血刀门独门武功，分为内功卷和刀法卷
	血刀刀法以诡异闻名于世，经血刀老祖大雪山雪谷
	中与江南四侠一战，往往都是从不可能之处劈出，
	极端的诡异难测。
	祭血诀乃是先伤几再伤人的绝技，以刀砍自身，以
	血浸刀，以血刺激施展者的战力。循环往复，不
	断出招。

	注意：set 血刀祭血 x (1-6) 有特殊附加效果

	指令：perform blade.jixue

要求：  
	当前内力需求 800 以上；
	最大内力需求 2000 以上；
	当前精力需求 500 以上；
	血刀经等级为 350 以上；
	血刀刀法等级 350 以上；
	激发刀法为血刀刀法；
	激发招架为血刀刀法或金刚护体术；
	激发内功为血刀经。
	手持刀类武器；
HELP
        );
        return 1;
}