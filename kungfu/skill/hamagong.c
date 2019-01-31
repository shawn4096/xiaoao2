// hamagong.c ��󡹦
// reModified by fengyue


inherit FORCE;

int get_bouns(int damage,int t,int level,int flag);
int valid_enable(string usage) { return usage == "force"; }

#include "/kungfu/skill/force.h"
#include <ansi.h>


int valid_learn(object me)
{
	if( me->query_skill("hamagong", 1) < 100 )
		return notify_fail("��󡹦�������ʲô�ط���������ϰ�ġ�\n");
	return 1;
}


int practice_skill(object me)
{
	if((int)me->query_skill("hamagong", 1) >= 100 ){
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200){
			me->improve_skill("hamagong", (int)me->query_int());
			me->add("neili", -150);
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("�����ڵ���Ϊ��������߸�󡹦�ˡ�\n");
	}
	else return notify_fail("��󡹦���������ϰ��\n");
}


string exert_function_file(string func)
{
	return __DIR__"hamagong/" + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIW + me->name()+"����ڵ��ϣ���ð����" NOR,
		"heal_msg" : HIW"$Nȫ����ɣ�����ڵ��Ͽ�ʼ�˹����ˡ���\n"NOR,
		"heal_finish_msg" : HIW"$N���ۣ����Ĵ��һ����ȫ��İ���������ɢ��\n"NOR,
		"heal_unfinish_msg" : "$N���ۣ����Ĵ��һ����վ������������ɫ�԰ף���������������\n",
		"heal_halt_msg" : "$N��ð���������ۣ����Ĵ��һ����վ��������\n",
	]);
}


string* msgs =
({
        HBRED"$NͻȻ����һ�ã�΢΢��ͷ��һ����ĭ�³���ȥ�����ң�\n"NOR,
        HBWHT"$N��Ȼ�ſڼ�ҧ�������ƺ������������ſڿ�ݣ��������Զ�����\n"NOR,
        HBMAG"$N����һ����ĭ���£�����̵����ĭҲ�����˹�������������ȭ��֮��ʹ�ã�\n"NOR, 
        HBWHT"$N��󡹦��ת���ã�������֮��������֮��һ���Ļأ�\n"NOR,
        HBCYN"$N���˾���������������һ���Է�����������°�ĭ����ͷ��ײ��\n"NOR, 

});

int ob_hit(object ob, object me, int damage)
{
    int t;
    t = random(10);        
	if(!environment(me)) return 0;
	if( me->query("env/��󡹦")=="��ת" && t> 6)		
		{
			message_vision(msgs[random(sizeof(msgs))]+"$n��Ȼ�䱻$N����һ���������в��ɵ����˼��֣�\n"NOR,me,ob);
			return -get_bouns(damage,t,me->query_skill("hamagong",1),1);
		}
	
    if( (me->query("qi")-damage) >= 3000 ) return 0;
	
    if ( t >= 5 && me->query("env/��󡹦")=="��ת" )
      {       
	       message_vision(HIY"$N"HIY"$N�ۼ�����Σ�����������Լ�������ץһ�ѣ��ַ������Լ�ƨ���Ϻ���һ�ţ�������ȫ��������ȴ�������������һ����\n" NOR, me);
	       return -damage;
      }
}

int hit_ob(object me,object victim,int damage)
{
	if(!me) return 0;
	if(!environment(me)) return 0;
	
	if (me->query_temp("hmg/powerup")
		&&random(10)>5
		&&me->query("env/��󡹦ɢ��"))
	{
		//message_vision(msgs[random(sizeof(msgs))]+"\n$N��󡹦������������������ѾõĶ������������\n"NOR,me);
	//	write("1111111111");
		message_vision(HIB"$N��󡹦������������������ѾõĶ������������\n"NOR,me);
		if (!random(2)
		&&me->query("baituo/poison/gsdu")	
		&&!me->query_condition("snake_poison"))
		{
			victim->apply_condition("snake_poison",2);
		}else if (!me->query_condition("hama_poison")
				  && random(10)>6
				  && me->query("baituo/poison/chanchu"))
		{
			victim->apply_condition("hama_poison",2);

		}
	}

	if( me->query("env/��󡹦")=="��ת" &&me->query_temp("hmg_nizhuan"))
	{
		int t;
        t = random(10);
		
        if( t > 6 )
		{
            message_vision(msgs[random(sizeof(msgs))],me);
			
           // message_vision(msgs[random(sizeof(msgs))]+"$N�������ˣ����ǲ��壬����ȴ��Խ��������\n"NOR,me);
			return get_bouns(damage,t,me->query_skill("hamagong",1),1);
		}
        if (t>7)
        {
            message_vision(HBRED"$N�������ˣ����ǲ��壬����ȴ��Խ��������\n"NOR,me);
            return get_bouns(damage,t,me->query_skill("hamagong",1),2);
        }
		if (me->query_temp("hmg_nizhuan") && me->query("oyf/hamagong",1)==3 && random(10)>6)
	    {
		  if (me->is_busy()){		
			message_vision(HIR "\n$N��Ȼ�������澭�����ɹ���ȫ������ת����������ȫ������ת����Ѱ����ѧ�ľ�����Ϊ��ͬ��\n"
				  +"����ת���������£�һ·��Ѩ�ƹأ�����ס��Ѩλ���´�ͨ,$N�ָֻ����ж���\n" NOR, me,victim);
            me->start_busy(-1);
		  }
		  if( me->query_condition("no_exert") ){
               message_vision(HIY"$NĬ�˸�󡹦������������ת֮�£�ѹ���˷��ڲ��ѵ���Ѫ��\n"NOR,me);
               me->clear_condition("no_exert");
           }
	    }
	}
	return 0;
}

int get_bouns(int damage,int t,int level,int flag)
{
	int dm;
	dm= (damage*flag*(t+level/20))/(t+level/20+10);
	if(flag && level>350) dm += dm/2;
	if(flag && level>450) dm += dm/2;
	return dm;
}
