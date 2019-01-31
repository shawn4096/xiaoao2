// roar.c for xixin-dafa by sohu@xojh

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;
		skill = me->query_skill("xixing-dafa",1);
        if( me->query("quest/xxdf/pass") <2 )
              return notify_fail("你当前的功力无法运使狮子吼内力，须得获得任我行亲自传授方可。\n");
        if (me->query_skill_mapped("force") != "xixing-dafa" )
             return notify_fail("你所使用的特殊内功不对，无法实现吸星大法之【狮子吼】。\n");  
		if( (int)me->query("max_neili") < 10000 )
                return notify_fail("你的最大内力不够。\n");
		if( (int)me->query("jingli") < 2000 )
                return notify_fail("你的精力不够。\n");     
        if( environment(me)->query("no_fight") )
                return notify_fail("在这里不能攻击他人。\n");

        me->add("neili", -300);
        me->receive_damage("qi", 190);

        me->start_busy(5+random(2));
        message_vision(HIY "$N深深地吸一口气，运起吸星大法对着$n狂吼一声。\n顿时一阵惊天动地的巨吼传来，$n感觉心神受到极大刺激。\n" NOR, me,target);

        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++) {
                if( !living(ob[i]) || ob[i]==me ||ob[i]->query("no_pk")) continue;
                if( skill/2 + random(skill/2) < (int)ob[i]->query_con(1) * 2 ) continue;
                                
				damage = (me->query("neili")-ob[i]->query("neili"))*skill/10;
                if( damage > 0 ) {
					    ob[i]->start_busy(1+random(2));
						if (damage>4000) damage=4000+(damage-4000)/100;
					
                        ob[i]->receive_damage("qi", damage,me);
                        if( (int)ob[i]->query("neili")*3/2 < (int)me->query("neili")  )
                             ob[i]->receive_wound("jing", damage/8,me);
                        tell_object(ob[i],HIR "你觉得眼前一阵金星乱冒，耳朵痛得像是要裂开一样！\n"NOR);
                }
                
                if( userp(ob[i]) ) 
			    {
					ob[i]->fight_ob(me);
					me->kill_ob(ob[i]);
				}
                else if( !userp(ob[i])&&!ob[i]->is_killing(me) ) ob[i]->kill_ob(me);

        }
        return 1;
}

string exert_name(){ return HIY"「狮子吼」"NOR; }
int help(object me)
{
        write(HIR"\n吸星大法"+HIY+"「狮子吼」"NOR"\n");
        write(@HELP
		吸星大法乃是日月神教前教主任我行的秘传武技，想当初日月神教有两大神技，
		其一为葵花宝典，其二为吸星大法，前教主任我行在位时选择修习吸星大法。
		固然有其陷害东方不败的嫌疑，但吸星大法的诡异和强横也是他选择的主要原因
		以至于，江湖中为之谈虎色变。后来任我行在少林一战，以吸星大法重出江湖
		可见其威力无铸。
		【狮子吼】绝技，乃是源自任我行在梅庄地牢中凭借一身功力全力一吼，以音波
		震晕令狐冲等人的武技。非功力深厚者不能使用。
		要求：
			基本内功等级 450 以上；
			吸星大法等级 450 以上；
			最大内力     8000 以上。
			当前内力     10000 以上。
			最大精力     5000 以上。
			当前精力     3000 以上。
HELP
        );
        return 1;
}
