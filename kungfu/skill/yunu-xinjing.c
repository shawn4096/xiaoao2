// yunu-xinjing.c ��Ů�ľ�
// Modify By River 10/98

inherit FORCE;
#include <ansi.h>

int valid_enable(string usage) { return usage == "force"; }

#include "force.h"

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("yunu-xinjing", 1);

	if ( me->query("gender") == "����") 
		return notify_fail("���޸����ԣ������������������������Ů�ľ��񹦡�\n");

        if ( lvl < 120)
                return notify_fail("�����ڻ�ֻ��ͨ�����������������Ů�ľ��񹦡�\n");

        if ((int)me->query_skill("yunu-xinjing", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("yunu-xinjing", 1) >= 200 )
               return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

        return valid_public(me);
}

int practice_skill(object me)
{
	if((int)me->query_skill("yunu-xinjing", 1) >= 200 )
	{
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
		{
			me->improve_skill("yunu-xinjing", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("�����ڵ���Ϊ�����������Ů�ľ��ˡ�\n");
	}
	else return notify_fail("�����ڵ���Ů�ľ���Ϊֻ����ѧ(learn)�������������ȡ�\n");

}
void skill_improved(object me)
{
	int i = (int)me->query_skill("yunu-xinjing", 1);   

	if (i == 100)
	{
		 tell_object(me,HIM"��Ů�ľ��İ�������Ѿ��������˵�һ���ˡ�\n");
	     me->set("xinjing/degree",1);
	}
	if (i == 150)
	{
		tell_object(me,HIM"��Ů�ľ��İ�������Ѿ��������˵ڶ����ˡ�\n");
        me->set("xinjing/degree",2);
	}
	if (i == 200) 
	{
		tell_object(me,HIM"��Ů�ľ��İ�������Ѿ��������˵������ˡ�\n");
	    me->set("xinjing/degree",3);
	}
	if (i == 250)
	{
		tell_object(me,HIM"��Ů�ľ��İ�������Ѿ��������˵��Ĳ��ˡ�\n");
	    me->set("xinjing/degree",4);
	}
	if (i == 300)
    {
		tell_object(me,HIM"��Ů�ľ��İ�������Ѿ��������˵�����ˡ�\n");
	     me->set("xinjing/degree",5);
	}
	if (i == 350)
	{
		tell_object(me,HIM"��Ů�ľ��İ�������Ѿ��������˵������ˡ�\n");
	    me->set("xinjing/degree",6);
	}
	if (i == 400)
	{
		tell_object(me,HIM"��Ů�ľ��İ�������Ѿ��������˵��߲��ˡ�\n");
	    me->set("xinjing/degree",7);
	}
	if (i == 450)
    {
		tell_object(me,HIM"��Ů�ľ��İ�������Ѿ��������˵ڰ˲��ˡ�\n");
	     me->set("xinjing/degree",8);
	}
	if (i == 550)
	{
		tell_object(me,HIM"����ǧ����࣬�����ڽ���Ů�ľ��İ�����������˵ھŲ��۷�״̬�ˡ�\n");
	    me->set("xinjing/degree",9);
	}
	
	return ;
	
}

string exert_function_file(string func)
{
	return __DIR__"yunu-xinjing/" + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIB + me->name()+"��̬���ţ���̬����"NOR,
		"start_my_msg" : "���������һ�����������۾���������Ů�ľ�����Ϣ�������п�ʼ��ת��\n",
		"start_other_msg" : me->name()+"��̬ͻȻ��ʼ��������ޱȣ����������ֱ�������쳣��\n",
		"halt_msg" : "$N��Ϣһת��Ѹ��������ֹͣ����Ϣ����ת��\n",
		"end_my_msg" : "���������������뵤������۾������������һ������\n",
		"end_other_msg" : "ֻ��"+me->name()+"�����۾���������³���һ��������̬�ָ���Ȼ��\n"
	]);
}

int hit_ob(object me, object ob, int damage)
{
	object weapon,weap1;
	int i,j,skill;
	string msg;
	if (!me->query("quest/gm/dichuan")) return 0;
	if (!me->query_temp("ynxj/xinjing")) return 0;
	
	skill=me->query_skill("yunu-xinjing",1);
	//damage=skill+me->query_skill("yunu-xinjing",1);
	//damage=damage*2+random(damage);

	if( me->query_int(1) > 40
	 && me->query_dex(1) > 40
	 && me->query_skill_mapped("hand") == "tianluo-diwang"
	 && me->query_skill_mapped("cuff") == "meinu-quanfa"
	 && me->query_skill("hand") > 450
	 && me->query_skill("cuff") > 450
	 && me->query("neili") > 500
	 && me->query("jingli") > 500
	 && me->query("family/family_name") == "��Ĺ��"
	 && me->query("env/��Ů�ľ�") == "�ں�"
	// &&!ob->is_busy()
//	 &&!ob->is_lost()
	 && !random(3))
	{		
         
		if (me->query("quest/jiuyingm/pass") && random(10)>4)
		{            
		  switch (random(5))
		  {
           case 0:
				  //�У�������parry��Ȼ�Ʒ�����Ů����busy
			  if (me->query("gender")=="����")
			  {
				 if (me->query_skill_mapped("parry")=="anran-zhang"&&me->query_skill("anran-zhang",1)>450)
				 {
					 msg=YEL"$N�������������Ȼ�ƹ���Ȼʩչ������������Ȼ�䣬�����ĳ�һ�ơ�\n"NOR;
					 if (random(me->query_str(1))>ob->query_dex(1)/2)
					 {
						 msg+=HIC"�Է�û�����������ʽ���ƻ�����������ȴ̫�ĺܣ�һ��С�ı�$Nһ�ƴ��ڼ粿��\n"NOR;
						 ob->add_busy(2);
					     ob->receive_damage("qi",damage,me);
					     ob->receive_wound("qi",damage/3,me);
					 }
					 else 
					 {
						 msg+=HIC"�Է��������ʽ̫�����ͣ���Ȼ��һ����¿����������������з�����\n"NOR;		
					     me->add_busy(random(1));
					 }
					 message_vision(msg,me,ob);
				 }
			  } else
			  {
				   if (me->query("gender")=="Ů��")
			       {
				     if (me->query_skill_mapped("strike")=="meinu-quanfa"&&me->query_skill("meinu-quanfa",1)>450)
				     {
					    msg=HIC"$N��С��Ů��������Ůȭ������Ȼʩչ�������������䣬��̬���ţ���ЦٻȻ����ζ���\n"NOR;
					    if (random(me->query_dex(1))>ob->query_con(1)/2)
				    	{
						 msg+=HIY"�Է�Ϊ��������Ի�һʱ�����ǳ��У���$Nһ�ƴ��ں󱳡�\n"NOR;
						 ob->add_busy(1);
					     ob->receive_damage("qi",damage/2,me);
					     ob->receive_wound("qi",damage/4,me);
				    	}
					    else 
					    {
						 msg+=HIC"�Է��������ʽ̫�����ͣ���Ȼ��һ����¿����������������з�����\n"NOR;		
					     me->add_busy(random(1));
					    }
					   message_vision(msg,me,ob);
				     }
			       }

			   }
			   break;
		  case 1:
				  //����֮����׷��һ��
                    if (me->query_skill("kongming-quan",1)>450&&me->query("quest/hubo/pass"))
				      {
					    msg=HIR"$N��������ͯ�����򵽵Ŀ���ȭ�ںϵ���ʽ֮�У�˫�ֻ���˳�ƶ�����������������ͬʱ����һ����\n"NOR;
						message_vision(msg,me,ob);
					    COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 3);
					    
						if (ob->query("neili")>2000) ob->add("neili",-random(2000));
					    
					  }
					 break;
		  case 2:
				  //��� ����
		      message_vision(HIM"$N�������澭�еĹ�����������������ͻȻ��ʼ����������ֵı��顣\n"NOR, me, ob);

              if ( random(me->query_int()) > ob->query_int()/2) 
              {        	    
                message_vision(HIW"$n����׼��ȡЦ$N��ȴ��֪������ѧ��$N�ı��顣\n"NOR, me, ob);
	     	    message_vision(HIW"$N��Ȼ�������Լ������Ķ�����$n�������Լ������ƵĹ�������������Խ��Խ�أ�\n"NOR, me, ob);
		        //ob->add_temp("apply/attack",skill/3);
		        ob->add_temp("apply/damage",skill/3);
				ob->add_busy(2);
                ob->set_temp("must_be_hit",1);
                COMBAT_D->do_attack(ob, ob, ob->query_temp("weapon"), 3);
              //  if( me->is_fighting(ob)&& !random(2)) COMBAT_D->do_attack(ob, ob, ob->query_temp("weapon"),random(2)?1:3);
                //if( me->is_fighting(ob)&& !random(4)) COMBAT_D->do_attack(ob, ob, ob->query_temp("weapon"),3);
                if(ob)
                {
					//ob->add_temp("apply/attack",-skill/3);
					ob->add_temp("apply/damage",-skill/3);
					ob->delete_temp("must_be_hit");
				 }
			  }
              else
				   message_vision(HIW"����$N��ô�仯���飬$n����������޶����ԡ�\n"NOR, me, ob); 
				   
		   break;
		  case 3:
				  //����ץ
		      if (me->query_skill_mapped("claw")=="jiuyin-shenzhua" && me->query_skill("jiuyin-shenzhua",1)>450)
			  {	 
				  message_vision(HIR"$N����һ�о�����צ����ʽ�������󣬵������޴�һ��ץ��$n�����ӡ�\n"NOR, me, ob);
				  ob->receive_damage("qi",damage,me);
				  ob->receive_wound("qi",damage/2,me);
			  }else if (me->query_skill_mapped("claw")=="jiuyin-baiguzhua"&&me->query_skill("jiuyin-baiguzhua",1)>450)
			  {

				  message_vision(RED"$N����һЦ����ָ���������������ǳ��������ġ������׹�ץ����\n"NOR,me,ob);
				  ob->receive_damage("qi",damage/2,me);
				  ob->receive_wound("qi",damage/4,me);
			  }
		     break;
          
		 default: 
			 if (objectp(weap1=present("yufeng zhen", me)))
			 {
				message_vision(HIW"\n$N�����������֣���������һ�ӣ�����������һö��������׷ɳ�ֱ��$n�����ȥ��\n"NOR,me,ob);
				if (random(me->query_dex(1))>ob->query_dex(1)/3)
				{
					message_vision(HIY"$n�ۼ�һ��������Լ�������һ��С��Ϊ��������ˡ�\n"NOR,me,ob);
					ob->add_condition("bee_poison",5);
					ob->receive_damage("qi",damage,me);
					ob->receive_wound("qi",damage/3,me);
				}
			 }
			else if (objectp(weap1=present("bingpo yinzhen", me)))
			 {
				message_vision(HIB"\n$N�����������֣���������һ�ӣ�����������һö�����������׷ɳ�ֱ��$n�����ȥ��\n"NOR,me,ob);
				if (random(me->query_dex(1))>ob->query_dex(1)/3)
				{
					message_vision(HIY"$n�ۼ�һ���������Լ�������һ��С��Ϊ�����������ˡ�\n"NOR,me,ob);
					ob->add_condition("bing_poison",7);
					ob->receive_damage("qi",damage,me);
					ob->receive_wound("qi",damage/2,me);
				}

			}
			else message_vision(HIC"$n���һ����ʶ����$N����ͼ������һ�ԡ�\n"NOR,me,ob);	 	
			
		   break;
          }    
		}
		
//����ȫ����书 ���˻��Ե���Ů�ľ�

		//if (objectp(weapon=me->query_temp("weapon")))
			//message_vision(HIC"$N�����е�"+weapon->query("name")+HIC"һ�գ�",me);
		//else
			//message_vision(HIC"$N��ʽ��֮һ�䣬��Ů�ľ��Ĺ������Ķ���\n",me);
        //����taosim,���У������˷��յ�ѹ�ƺͿ���
		//����ȫ�潣��
        
		if (ob->query("family/family_name")=="ȫ���"&&me->query("quest/gumu/ynxj/pass")&&!random(3))
        {
			if (random(me->query("combat_exp")) > ob->query("combat_exp")*2/3 && random(me->query_int())>ob->query_int()/2)
			{
				message_vision("$N�Ѿ�����ʹ��Ů�ľ����һ�µ��书��$nֻ�����Լ��������ƣ��Է�ÿһ���ƺ������Լ�����ʽ�γɿ��ơ�\n",me,ob);
				ob->add_temp("lost_attack",3+random(3));
			}
        }

	   else if(ob->query("class") != "bonze"
		 && ob->query("class") != "huanxi" 
		 && !random(3)
		 && ob->query("class") != "taoism"
		 && me->query("gender") != ob->query("gender")){
			message_vision(HIC"ʩչ����Ĺ�ɵմ���Ůȭ��,��ʽ����������룡\n", me);
			if (random(me->query_per()) > ob->query_per()/2)
			{
				message_vision(HIR"$n����һ�ң���Щ��$N����Ҫ����һ����æ���ң�\n"NOR, me, ob);
				ob->add_busy(2+random(3));
				me->add("jingli",-50);
				me->add("neili",-100);
			}
			else message_vision(HIC"$n����һ�ң���æ������������\n"NOR, me, ob);
		}
		else {
			 message_vision(HIC"��Ȼ��ʩչ����Ĺ�ɵմ����޵����ƣ�˫�ֻӶ����γ�һƬ��Ӱ��\n", me);
			 if (random(me->query_dex(1)) > ob->query_dex(1)/2
				 &&random(10)>5)
			 {
				message_vision(HIR"$n�����ܴ죬�Թ˲�Ͼ���޷�׼ȷ����$N������\n"NOR, me, ob);
				ob->add_temp("lost_attack",1);
				call_out("remove_lost",4,ob);
				me->add("neili",-50);
				me->add("jingli",-100);
			 }
			 else {
				message_vision(HIC"$n�Կ��죬˲���ƽ���$N����Ϯ��\n"NOR, me, ob);
				me->add_busy(1);
			 }
		}
	}
	return 1;
}
int remove_lost(object ob)
{
	if (!ob) return 0;
	ob->delete_temp("lost_attack");
	return 1;
}
/*
mixed ob_hit(object ob, object me, int damage)
{
	    int ap, dp;
        int  lvl,i;
        lvl = me->query_skill("yunu-xinjing", 1);
        if ( lvl < 500
          || me->query("neili") < 2000
		  || random(10)<3 
          || me->query_skill_mapped("force") != "yunu-xinjing")
         	return 0;
        if (!me->query_temp("")) return 0;       
		//if(!me->query("tjg/pass")) return 0;
        if (!me->query("quest/gm/dichuan")) return 0;
		if (!me->query_temp("ynxj/xinjing")) return 0;
	 
        ap = ob->query_skill("force",1);
        dp = me->query_skill("force",1);

        if (random(dp)> ap*2 /3 && random(me->query("neili")) > ob->query("neili")*2/3 )
        {
	        i = -damage;
         

            message_vision(HIC"$N�Ѿ��������澭����Ů�ľ������ںϣ�������ӿ��ѭ��������\n"NOR,me,ob);
			message_vision(HIC"$n�о�һ��������ھ����������಻������ȴ����������\n"NOR,me,ob);

            ob->receive_damage("qi", damage/2,me);
            ob->receive_wound("qi", damage/4, me);
            return i;                              
         }    
        else if (random(dp)> ap /2 && random(me->query_con(1)) > ob->query_con(1)/2 )
         {
	      i = -damage;        //�������������й�����
          message_vision(HIC"$N��Ů�ľ����һ�µ��书ʩչ������������ת����$n�Ĺ�����������\n"NOR,me,ob);
          return i/2;                               
          }     
      
} 
*/