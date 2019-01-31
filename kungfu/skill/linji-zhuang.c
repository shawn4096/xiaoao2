// linji-zhuang.c ����  �ټ�ʮ��ׯ
// Modified by Lane@SJ 2005/4/14
// By Spiderii�޸�Ч��

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

#include "/kungfu/skill/force.h"

int valid_learn(object me)
{
        int nb, nf, nh;
        nb = (int)me->query_skill("dacheng-fofa", 1);
        nf = (int)me->query_skill("force", 1);
        nh = (int)me->query_skill("linji-zhuang", 1);

        if ( nb < 150 && nb <= nh )
                return notify_fail("��Ĵ�˷���Ϊ�������޷�����������ټ�ʮ��ׯ��\n");

        if ( nf < 15)
                return notify_fail("��Ļ����ڹ���򻹲������޷�����ټ�ʮ��ׯ��\n");

        if ( me->query("gender") == "����" )
                return notify_fail("���޸����ԣ�������ϰ�ټ�ʮ��ׯ�ڹ���\n");

        if ((int)me->query_skill("linji-zhuang", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("linji-zhuang", 1) >= 200 )
               return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

        return valid_public(me);
}


int practice_skill(object me)
{
       if((int)me->query_skill("linji-zhuang", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("linji-zhuang", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("�����ڵ���Ϊ����������ټ�ʮ��ׯ�ˡ�\n");
       }
        else return notify_fail("�����ڵ��ټ�ʮ��ׯ��Ϊֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"linji-zhuang/" + func;
}

mapping exercise_msg(object me)
{
        return ([
                "status_msg" : HIR + me->name()+"���Ϻ�����֣�˫�ִ�����ϥ����" NOR,
                "start_my_msg" : HIR"��ϯ�ض������������죬���Ϻ��ʱ��ʱ�֣���Ϣ˳��������������\n"NOR,
                "start_other_msg" : MAG + me->name() +"ϯ�ض������������죬���Ϻ��ʱ��ʱ�֡�\n"NOR,
                "halt_msg" : HIW"$N����һ����������Ϣ�������˻�ȥ��վ��������\n"NOR,
                "end_my_msg" : HIC"�㽫��Ϣ���˸�С���죬���ص���չ�վ��������\n"NOR,
                "end_other_msg" : HIR"��һ���"+me->name()+"��������ĵ�վ��������\n"NOR
        ]);
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int i=0, j=0, sk,count;
        object weapon;
        count=me->query_skill("linji-zhuang",1)/5;
        if( ( sk = me->query_skill("linji-zhuang", 1) ) < 350 ) return 1;
        
		if (!me->query_temp("emjy/powerup")&&me->query("emjy/pass"))
		{
			message_vision(HBRED"$Nƽ�ľ��������˶��Ҿ�������ȫ�������ž���죬����������Ȼ��ͬС�ɡ�\n"NOR,me,victim);
		    me->add_temp("apply/attack",sk/4);
			me->add_temp("apply/damage",sk/5);
			me->add_temp("apply/strength",sk/30);
			me->add("neili",-100-random(100));
			
			me->set_temp("emjy/powerup",count);
			me->set_temp("emjy/start",1);
			call_out("emjy_remove",1,me,count);
		}
        // Ů�����ӽ�������
        if( me->query_skill_mapped("sword") == "huifeng-jian"
         && me->query("jiali") > 0
         && me->query("gender") == "Ů��" 
         && me->query_skill("huifeng-jian", 1) >= 100
         && objectp(weapon = me->query_temp("weapon"))
         && weapon->query("skill_type") == "sword" ) {
                i += ( me->query_skill("huifeng-jian", 1)/100 ) * sk/10;        // 100 level Ϊһ����Ծ
                if( me->query_temp("apply/damage") < 100 ) i = i + random(i/3);
                else i += random(i/5);
                if( wizardp(me) ) tell_object(me, "��Ľ�������������"+i+"��\n"NOR);
        }

        // �������ӽ�������
        if( me->query_skill_mapped("sword") == "huifeng-jian"
         && me->query("jiali") > 0
         && me->query("gender") == "����" 
         && me->query_skill("huifeng-jian", 1) >= 120
         && objectp(weapon = me->query_temp("weapon"))
         && weapon->query("skill_type") == "sword" ) {
                i += ( me->query_skill("huifeng-jian", 1)/120 ) * sk/10;        // 120 level Ϊһ����Ծ
                if( me->query_temp("apply/damage") < 120 ) i = i + random(i/3);
                else i += random(i/5);
                if( wizardp(me) ) tell_object(me, "��Ľ�������������"+i+"��\n"NOR);
        }


        // ���ӱ�������Ч��
        if( victim->is_perform() || victim->is_exert() ) {
                j = me->query_str() * me->query_con() / 20;
                j = j + random(j/4);
                if( wizardp(me) ) tell_object(me, "�����ڱ�������״̬���������� "+j+"��\n"NOR);
        }

        i = i + j;

        if( !userp(me) ) i = i/3;

        return i;
}
void emjy_remove(object me,int count)
{
   int sk;
   if (!me||!living(me)) return;
   sk=me->query_skill("linji-zhuang",1);
   //if (!me->is_fighting()) count=0;
   
  // if (objectp(me)&&me->query_temp("emjy/powerup"))
   if (objectp(me) && me->query_temp("emjy/start"))
   {
	   if( count <= 0 || !me->is_fighting() ) {
			
		
		message_vision(HIY"$N������Ҿ����������걸���������û�����㣬һ���������˳�����\n"NOR,me);
		me->add_temp("apply/attack",-sk/4);
		me->add_temp("apply/damage",-sk/5);
		me->add_temp("apply/strength",-sk/30);

		me->delete_temp("emjy/powerup");
		me->delete_temp("emjy/start");
		return;
	   }
	   call_out("emjy_remove", 1, me, count--);
	   return;
   }   

}

mixed ob_hit(object ob, object me, int damage)
{
	 int ap, dp;
        int  lvl,i;
        lvl = me->query_skill("linji-zhuang", 1);
        if ( lvl < 450
          || me->query("neili") < 2000
          || me->query_skill_mapped("force") != "linji-zhuang")
         	return 0;
		if(!me->query("emjy/pass")) return 0;
         	
        ap = ob->query_skill("force",1);
        dp = me->query_skill("force",1);

        if (random(dp)> ap*2 /3 && random(me->query("neili")) > ob->query("neili")*2/3 )
        {
	        i = -damage/3;
            //ob->receive_damage("qi", damage,me);
           // ob->receive_wound("qi", damage/3, me);

            message_vision(HIY"$N��"HIG"���Ҿ�����"HIC"���Ķ�������ӿ��һ�����εľ�����$nֻ���Լ�����ʽ�ܵ�һ�ɺ�ǿ�ķ���֮����\n"NOR,me,ob);
            ob->add_busy(1+random(1));
			ob->receive_damage("qi", damage/2,me);
            ob->receive_wound("qi", damage/4,me);
            //COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), userp(ob)?1:3); //�����֧��Ŷ
            return i;                              
         }    
        else if (random(dp)> ap /2 && random(me->query_con(1)) > ob->query_con(1)/2 )
         {
	      i = -damage/5;        //�������������й�����
          ob->receive_damage("qi", damage/4,me);
          ob->receive_wound("qi", damage/6,me);
          message_vision(HIY"$N�Ķ��Ҿ�������ת����,������$n�Ĳ��ֹ��ơ�\n"NOR,me,ob);
          return i;                               
          }           
 
         return 0;  

} 
