// jianqi.c 化血诀, 附带化学辅助效果,by server 2007/7/26

#include <ansi.h>
//#include <combat_msg.h>
#include <combat.h>

inherit F_CLEAN_UP;


void remove_effect(object me,object weapon);

string *name1 = ({
				"胸口",
				"大腿",
				"左上臂",
				"右上臂",
				"后背",
				"小腹",
				"手指",
				"头皮",
				"前额",
				"小腿",
				"臀部",
});
int perform(object me, object target)
{
		object weapon;
		string s_name,t_name,s_long,t_long;
		string msg;
		int skill,damage;
		
		skill=me->query_skill("xuedao-daofa",1);
		weapon= me->query_temp("weapon");
        
		if (!me->is_fighting())
                return notify_fail("你只能在战斗中使用用化血诀。\n");

        if(!weapon || weapon->query("skill_type") != "blade")
                return notify_fail("你手中无刀，如何使用「化血诀」?\n");
        if (!me->query("quest/xd/xddf/huaxue/pass"))
        {
                return notify_fail("化血诀乃是血刀门不传绝学，尚未学会不能使用？\n");
        }
        
        if((int)me->query_skill("xuedao-jing",1)<350)
                return notify_fail("你的血刀经火候还尚浅，无法使用「化血诀」。\n");
        if((int)me->query_skill("xuedao-daofa",1)<350)
                return notify_fail("你的血刀刀法火候还尚浅，无法使用「化血诀」。\n");
		if( me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("你必须使用血刀刀法，才能使用「穿心刀」的绝技！\n");

		if ( me->query_skill_mapped("parry") != "xuedao-daofa" && me->query_skill_mapped("parry") != "jingang-liantishu")
             	return notify_fail("你的招架不对，必须激发刀法为血刀刀法或金刚炼体术。\n");

        if((int)me->query_skill("force",1)<350)
                return notify_fail("你的基本内功火候还尚浅，无法使用「化血诀」。\n");
        if( me->query_skill_mapped("force") != "xuedao-jing" && me->query_skill_mapped("force") != "shenzhao-jing")
                return notify_fail("你现在所使用的内功同「血刀刀法」向抵触，不能使出「化血诀」的绝技！\n");

        if( (int)me->query("neili") < 1200  )
                return notify_fail("你的内力不够。\n");

        if( weapon->query("xddf/huaxue") ) 
                return notify_fail("这把武器已经无法再承受化血诀的叠加威力了。\n");

		if( me->query_temp("xddf/huaxue") ) 
                return notify_fail("你已经在施展化血诀的威力了。\n");

		msg = HBRED+HIW "\n$N运起血刀经中「化血诀」绝技，手中"NOR+weapon->query("name")+HBRED+HIW"闪烁一片暗红色的刀影，向四周依次劈将出去！\n"NOR;
        msg+=weapon->query("name")+RED"上的血槽忽然发出一阵妖邪的暗红之色，极为刺眼,令人胆寒！\n"NOR;
		message_vision(msg, me);
		weapon->set("xddf/huaxue", 1);

//浴血后，且叠加
        if(me->query_temp("xdj/yuxue")&& weapon->query("xddf/huaxue"))
		{
                damage = me->query_skill("xuedao-jing",1)/8;
                me->add_temp("apply/damage", damage);
				me->set_temp("xddf/hxyxadd",damage);
                message_vision(RED"$N更把血刀经的劲气附于兵刃之上，"NOR+weapon->query("name")+RED"闪烁着异样的血红光芒！\n"NOR, me,target);
				call_out("xddf_hxyxadd",1,me,skill/30);
        }

        s_name = weapon->query("name");
        s_long = weapon->query("long");
        t_name = strip(s_name);
        t_long = strip(s_long);

        weapon->set("name",RED+t_name+NOR);
        weapon->set("long",RED+t_long+NOR);
        weapon->set("s_long",s_long);
        weapon->set("s_name",s_name);
        weapon->set("s_rigidity",(int)weapon->query("rigidity"));
        weapon->set("s_sharpness",(int)weapon->query("sharpness"));
        
		weapon->add("rigidity",10);
        weapon->add("sharpness",10);
        

        call_out("remove_effect", 1, me, weapon);
        call_out("xddf_huaxue",1,me,target,weapon);
      //不足500有perform busy  
		if (me->query_skill("xuedao-jing",1)<500&&me->query_skill("xuedao-daofa",1))
           me->start_perform(1, "化血诀");

        return 1;
}
//释放人手上兵器带来的附加伤害
void xddf_hxyxadd(object me,int count)
{
	int damage;
	object weapon;
	if (!me) return;
	damage=me->query_temp("xddf/hxyxadd");
	weapon=me->query_temp("weapon");

	if (!me->is_fighting()
		||!weapon
		||me->query_skill_mapped("blade")!="xuedao-daofa"
		||me->query_skill_mapped("parry")!="xuedao-daofa"
		||weapon->query("skill_type")!="blade"
		||count<0)
	{
		me->add_temp("apply/damage", -damage);
		me->delete_temp("xddf/hxyxadd");
		message_vision(RED"$N奇经八脉一阵松动，附加在兵器上的力道缓缓消退了！\n"NOR,me);
		return;
	}
	call_out("xddf_hxyxadd",1,me,count--);
	
}
//主要判断兵器附加

void remove_effect(object me,object weapon)
{
       string name;
	   if(!objectp(weapon)) return;
		
		
       if (!weapon->query("xddf/huaxue")) return;

       if (weapon->query("broken")) return;
       
	   
	   //如果玩家死了

       if (!me){
           weapon->set("name",weapon->query("s_name"));
           weapon->set("long",weapon->query("s_long"));
//           weapon->set("rigidity",(int)weapon->query("s_rigidity"));
//           weapon->set("sharpness",(int)weapon->query("s_sharpness"));
           weapon->delete("xddf/huaxue");
           return;
       }
		
		//message_vision(HIW"$N脸上紫气一闪，一股若隐若现的剑气豁然而出，刺向$n的"+name+NOR,me,target);
		
       if (me->query_temp("weapon") != weapon
         ||!me->is_fighting()
         ||!living(me)
         ||me->query_skill_mapped("force") != "xuedao-jing"
         ||me->query("neili")<200 )
		{
             message_vision(weapon->query("name")+RED+"上的暗红血色渐渐退去,刀身又恢复了原样!\n"NOR,me);
             weapon->set("name",weapon->query("s_name"));
             weapon->set("long",weapon->query("s_long"));
             weapon->set("rigidity",(int)weapon->query("s_rigidity"));
             weapon->set("sharpness",(int)weapon->query("s_sharpness"));
             weapon->delete("xddf/huaxue");
             return;
         }

         call_out("remove_effect", 1, me, weapon);
		 return;
}

void xddf_huaxue(object me,object target,object weapon)
{
    int ap, dp;
	string name;
    object tweapon;
	name = name1[random(sizeof(name1))];

	if(!weapon) return;
    if(!me) return;
    if(!target) return;
    
	tweapon=target->query_temp("weapon");

	if(!weapon->query("xddf/huaxue")) return;
    
	ap = me->query_skill("blade",1);
    dp = target->query_skill("parry",1);

    if(me->query("env/化血诀")=="放血") {
                message_vision(RED"$N一刀挥出,带起"NOR+weapon->query("name")+RED+"一片暗红血影，削中$n的"+HIY+name+RED",顿时鲜血四溅!\n"NOR,me,target);
                target->receive_damage("qi",ap*3,me);			
                if(random(ap)>dp*2/3) target->add_condition("no_exert",1);

				me->add("neili", -100);	
    }
    if(me->query("env/化血诀")=="眩晕"){
         message_vision(RED"$N手中"+weapon->query("name")+RED"上暗红色刀光一闪,$n为刀光所摄，似乎有些眩晕!\n"NOR,me,target);
         target->add_busy(1+random(2));
		 target->receive_damage("jing",ap,me);
    }
	if(objectp(tweapon) && me->query("env/化血诀")=="斩断")
	{

		if( random(ap + dp) > dp && tweapon->query("imbued") < 4 && weapon->query("sharpness") > 3)
		{
			message_vision(RED"$N潜运血刀经内劲，「咔」地一声轻响，$n手中的"+tweapon->name()+RED"已经被"+weapon->name()+RED"斩断！\n"NOR, me, target );
            tweapon->broken("削断的");
			return ;
        }
		else if (random(ap)>dp/3) {
		
			message_vision(CYN "$N回刀斜引疾撩，$n把捏不住，手中的"+tweapon->name()+CYN"脱手而飞！\n"NOR, me, target );
			target->add_busy(random(2)+1);
			tweapon->move(environment(target));
			target->reset_action();
		}


    }
	call_out("xddf_huaxue",2,me,target,weapon);
	return;
}

string perform_name() {return HBWHT+HIR"化血诀"NOR;}

int help(object me)
{
    write(YEL"\n血刀经「"HIM"化血诀"YEL"」："NOR"\n");
	write(@HELP
	化血诀乃是化血经的刀法总纲，为整个诡异刀法
	的纲要文件，血刀刀法中变幻莫测的刀法绝技均
	由此而来，血刀诀是将平时蕴藏在刀槽中的血气
	精华以内功激发，散发出慑人的杀气和妖艳的红
	光，既能迷惑对手，也同时提高手中兵器的威力
	在战斗中会出现随机削断对方兵器的功效
	
	set 化血诀 斩断 随机削断对方武器
	set 化血诀 放血 随机利用刀上暗槽给对方放血
	set 化血诀 眩晕 随机催动刀上蓄积血气眩晕

	指令: perform blade.huaxue

要求：
	最大内力  1200 以上；
	当前内力  1000  以上；
	血刀大法  450  级以上；
	350级后小飞，
	500后成为起手式。
	激发刀法血刀刀法；
	激发招架为血刀刀法或金刚护体术；
	手持刀类武器；

HELP
   );
   return 1;
}
