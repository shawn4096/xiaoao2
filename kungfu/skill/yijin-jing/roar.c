// roar.c for xixin-dafa by sohu@xojh

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;
		skill = me->query_skill("yijin-jing",1);
        if( me->query("yjj/powerup") !="pass" )
             return notify_fail("你只是听说过易筋经,但无法运使佛门狮子吼神功。\n");
        if (me->query_skill_mapped("force") != "yijin-jing" )
             return notify_fail("你所使用的特殊内功不对，无法实现易筋经神功之【狮子吼】。\n");  
		if( (int)me->query_skill("yijin-jing",1) < 500 )
                return notify_fail("你的易筋经功力不够。\n");
		if( (int)me->query_skill("force",1) < 500 )
                return notify_fail("你的基本内功不够。\n");
		if( (int)me->query("max_neili") < 10000 )
                return notify_fail("你的最大内力不够。\n");
		if( (int)me->query("neili") < 5000 )
                return notify_fail("你的当前内力不够。\n");
		if( (int)me->query("jingli") < 2000 )
                return notify_fail("你的精力不够。\n");     
	    if( environment(me)->query("no_fight") )
                return notify_fail("在这里不能攻击他人。\n");

        me->add("neili", -1000);
        me->receive_damage("qi", 190);

        me->start_busy(1+random(4));
        message_vision(HBRED+HIY "$N深深地吸一口气，运起佛门狮子吼对着长空发出一声惊天动地的长吼，宛如狮啸密林。\n空气中顿时传来惊天动地的嗡嗡回声.........\n" NOR, me);

        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++) {
                if( !living(ob[i]) || ob[i]==me ||ob[i]->query("no_pk")) continue;
                if( skill/2 + random(skill/2) < (int)ob[i]->query("con") * 2 ) continue;
                                
				damage = (me->query("neili")-ob[i]->query("neili"))*skill/5;
                if( damage > 0 ) {
					    ob[i]->start_busy(2+random(4));
						ob[i]->apply_condition("no_perform",1+random(2));
						ob[i]->apply_condition("no_exert",1+random(2));
						if (damage>8000) damage=8000+(damage-7000)/10;
					
                        ob[i]->receive_damage("qi", damage);
						ob[i]->receive_damage("jing", damage/3);
                        if( (int)ob[i]->query("neili") < skill * 2 )
                                ob[i]->receive_wound("qi", damage/2,me);
                        tell_object(ob[i],HIR "你觉得眼前一阵金星乱冒，耳朵痛得像是要裂开一样！\n"NOR);
                }
                
                if( userp(ob[i]) ) ob[i]->fight_ob(me);
                else if( !ob[i]->is_killing(me) ) ob[i]->kill_ob(me);
        }
		me->start_exert(4+random(2));
        return 1;
}

string exert_name(){ return HIR"佛门狮子吼"NOR; }
int help(object me)
{
        write(HIR"\n易筋经神功"+HIY+"「佛门狮子吼」"NOR"\n");
        write(@HELP
		佛门狮子吼,乃是少林寺秘传稀释奇功之一,此功为人体丹田内气外发,发声吐气
		之功法,功成之后遇敌交手,发功呼啸,则犹如讯雷疾泻传出数里之外,令敌肝胆剧
		烈,心惊胆战,毛骨悚然,往往一声长啸即使对手不战而败。
		【佛门狮子吼】此功法源于<<狮子经>>,原喻本师释迦佛文说法如狮吼。有震慑人心
		的不可思议之威力.后经少林寺祖师们的不断研练,遂成一门克敌绝技。
		要求：
			基本内功等级 500 以上；
			易筋经功等级 500 以上；
			最大内力     10000 以上。
			当前内力     5000 以上。
			当前精力     3000 以上。
HELP
        );
        return 1;
}
