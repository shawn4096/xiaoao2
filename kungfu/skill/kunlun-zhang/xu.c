//���ص���֮�
// By truekk

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HBWHT+HIY"�"NOR; }

void checking(int i,int j,object me);

int perform(object me, object target)
{
        int i,j;

        if( !target ) target = offensive_target(me);
        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("�����ֻ����ս����ʹ�á�\n");       
        if( (int)me->query_skill("strike", 1) < 500 )
                return notify_fail("��Ļ���ȭ��������죬�޷�ʹ�����ص���֮���\n");  
        //��ζ��550�����������������
		
		if( objectp(me->query_temp("weapon")) 
			&& (int)me->query_skill("xuantian-wuji", 1) < 550
			&& !me->query("quest/kl/klz/xu/pass"))
                return notify_fail("��������޼�����Ϊ���㣬��δ�ڻ��ͨ���޷���ʹ�ñ�����ʱ��������\n");  
        
		if((int)me->query_skill("kunlun-zhang", 1) < 500 )
                return notify_fail("������ص��ƻ�������죬����ʹ�����ص���֮���\n");
        if (me->query_skill_prepared("strike") != "kunlun-zhang"
           || me->query_skill_mapped("strike") != "kunlun-zhang")
                return notify_fail("�㲻ʹ�����ص��ƣ�������ʹ�����\n");   
        
		if( (int)me->query("max_neili", 1) < 15000 )
                return notify_fail("��������Ϊ̫ǳ���޷����\n");                
        if( (int)me->query("neili", 1) < 10000 )
                return notify_fail("�����������������޷����\n");
        if( (int)me->query_skill("xuantian-wuji", 1) < 500 )
                return notify_fail("��������޼�����Ϊ�����Խ�������š�\n");
        if( me->query_skill_mapped("force") != "xuantian-wuji")
                return notify_fail("����ڹ��ķ����ԣ����Ӳ����֮����\n");   
        
		if( me->query_temp("kunlun_xu") )
                return notify_fail("���ϴ�������û�������뱬������𣡣�\n");

	
        if( me->query_str(1) < 80 )
                return notify_fail("��ĺ����������80���޷�ʹ�����ص���֮�������\n");  
		
		i=me->query_skill("kunlun-zhang",1)/40;
        j=me->query("env/���ص����");
        
		if( j<1) j=1;
		j=(int)me->query_skill("kunlun-zhang",1)/6;
		
        if( j>10) j=10;

        if( !userp(me))  i = i / 5;    //npc ����
		
        if( objectp(me->query_temp("weapon")) ) i=i / 2;//��������
		
		if (me->query("gender")!="����")
		{
			j=j/3;
		}

        message_vision(WHT"\n$N���������޼�������ɫ������������������˫�֣�������Ϣ�����Ͼ���Խ��Խǿ�����ƴ�����\n" NOR, me);
        me->delete_temp("kl_xu");
       //�趨������
		me->set_temp("kl_xu",1);
        
		me->set_temp("kunlun_xu",1);
        me->add("neili", -100); 
        call_out("checking",1,i,j,me);
        return 1;
}
/*
void checking(int i,int j,object me)
{
        object weapon,target;
      //  int i;
        if( !me )  return;	
		
	//	i=me->query_skill("kunlun-zhang",1)/15;

        if( !target ) target = offensive_target(me);
        if( !target || !(target->is_character()) || !(me->is_fighting(target)) ) 
		{
			call_out("xu_end", 1,i,j, me);
			return; 
		}


        if ( (int)me->query("neili") < 900  ) {
             message_vision(HIR"$N���ھ�������������ò�ֹͣ������\n" NOR, me,target);
             call_out("xu_end", 1,i,j, me);
			 return;
        }
        else if ( me->query_skill_mapped("strike") != "kunlun-zhang"
				||me->query_skill_prepared("strike") != "kunlun-zhang" ) {
             tell_object(me, HIR "\n��δʩչ���ص��ƣ��޷��ٽ��С������\n\n" NOR);
             call_out("xu_end", 1,i,j, me);
             return;
        }
        else if ( me->is_busy() ) {
             tell_object(me, HIR "\n�����ڶ����������޷�����ά��������\n\n" NOR);
             call_out("xu_end", 1,i,j, me);
             return;
        }
        else if (!me->is_fighting()) {
             tell_object(me,  "\n������û�к��˹��У������ջ��ˡ����!��\n" NOR);
             call_out("xu_end", 1,i,j, me);
             return;
        }
        else if( environment(target) != environment(me) ) {
             tell_object(me, "����Է��Ѿ������������ֹͣ��������\n");
             call_out("xu_end", 1,i,j, me);
             return;
        }
        else {
			
			if ( me->query_temp("kl_xu") ==10 )
			{        
				 message_vision(HBRED+HIW"\n$N�ĵ�ʮ�������޼���������˫�֣����ƴ�����\n" NOR, me);
				 me->add_temp("apply/damage", i);
				 me->add("neili", -900);
			}
			else if ( me->query_temp("kl_xu") ==9 ) {        
				 message_vision(HBYEL+"\n$N�ĵھŲ������޼���������˫�֣����ƴ�����\n" NOR, me);
				 me->add_temp("apply/damage", i);
				 me->add("neili", -800);
			}
			else if ( me->query_temp("kl_xu") ==8 ) {        
				 message_vision(HIR"\n$N�ĵڰ˲������޼���������˫�֣����ƴ�����\n" NOR, me);
				 me->add_temp("apply/damage", i);
				 me->add("neili", -700);
			}
			else if ( me->query_temp("kl_xu") ==7 ) {        
				 message_vision(WHT"\n$N�ĵ��߲������޼���������˫�֣����ƴ�����\n" NOR, me);
				 me->add_temp("apply/damage", i);
				 me->add("neili", -600);
			}
			else if ( me->query_temp("kl_xu") ==6 ) {        
				 message_vision(RED"\n$N�ĵ����������޼���������˫�֣����ƴ�����\n" NOR, me);
				 me->add_temp("apply/damage", i);
				 me->add("neili", -500);
			}
			else if ( me->query_temp("kl_xu") ==5 ) {        
				 message_vision(BLU"\n$N�ĵ���������޼���������˫�֣����ƴ�����\n" NOR, me);
				 me->add_temp("apply/damage", i);
				 me->add("neili", -400);
			}
			else if ( me->query_temp("kl_xu") ==4 ) {        
				 message_vision(HIG"\n$N�ĵ��Ĳ������޼���������˫�֣����ƴ�����\n" NOR, me);
				 me->add_temp("apply/damage", i);
				 me->add("neili", -300);
			}
			else if ( me->query_temp("kl_xu") ==3 ) {        
				 message_vision(MAG"\n$N�ĵ����������޼���������˫�֣����ƴ�����\n" NOR, me);
				 me->add_temp("apply/damage", i);
				 me->add("neili", -200);
			}
			else if ( me->query_temp("kl_xu") ==2 ) {        
				 message_vision(YEL"\n$N�ĵڶ��������޼���������˫�֣����ƴ�����\n" NOR, me);
				 me->add_temp("apply/damage", i);
				// me->add_temp("apply/attack", i*2);
				 me->add("neili", -100);
			}
			else if ( me->query_temp("kl_xu") ==1 ) {        
				 message_vision(CYN"\n$N�ĵ�һ�������޼���������˫�֣����ƴ�����\n" NOR, me);
				 me->add_temp("apply/damage", i);
				// me->add_temp("apply/attack", i*2);
				 me->add("neili", -100);
			}
			else if ( me->query_temp("kl_xu") == j ) {
				 message_vision(HIW "\n$N������ɣ���Хһ����˫����ҫ���ɫ�Ĺ�ԣ���Ȼ�Ѿ��������޼���������������\n" NOR, me, target);      	
				 call_out("xu_end", (int)me->query_skill("kunlun-zhang",1)/60,i,j, me);        		
			}
			else {
				 me->set_temp("kl_xu", me->query_temp("kl_xu")+1);
				 call_out("checking", 1,i,j, me);
			}  
        }
}  */

void checking(int i,int j,object me)
{
		object weapon,target;
		int klz;
		if( !me )  return;	
		
		klz= me->query_temp("kl_xu");
		
		     
		message_vision(HIW"\n$N�����޼�����תһȦ������"HIY+chinese_number(klz)+HIW"�������޼���������˫�֣�\n" NOR, me);
		me->add_temp("apply/damage", i);
		//���˼��10��
		if (me->query_temp("kl_xu") == j )
		{
			message_vision(HIR "\n$N��Хһ���������Ѿ��ﵽƿ����˫����ҫ���ɫ�Ĺ�ԣ���Ȼ�Ѿ��������޼���������������\n" NOR, me, target); 
			call_out("xu_end", (int)me->query_skill("kunlun-zhang",1)/60,i,j, me);
			return;
		}


        if ( (int)me->query("neili") < 900  )
		{
             message_vision(HIR"$N���ھ�������������ò�ֹͣ������\n" NOR, me,target);
             call_out("xu_end", 1,i,j, me);
			 return;
        }
        if ( me->query_skill_mapped("strike") != "kunlun-zhang"
				||me->query_skill_prepared("strike") != "kunlun-zhang" ) 
		{
             tell_object(me, HIR "\n��δʩչ���ص��ƣ��޷��ٽ��С������\n\n" NOR);
             call_out("xu_end", 1,i,j, me);
             return;
        }
        if ( me->is_busy() ) {
             tell_object(me, HIR "\n�����ڶ����������޷�����ά��������\n\n" NOR);
             call_out("xu_end", 1,i,j, me);
             return;
        }
        if (!me->is_fighting()) {
             tell_object(me,  "\n������û�к��˹��У������ջ��ˡ����!��\n" NOR);
             call_out("xu_end", 1,i,j, me);
             return;
        }
        if( environment(target) != environment(me) ) {
             tell_object(me, "����Է��Ѿ������������ֹͣ��������\n");
             call_out("xu_end", 1,i,j, me);
             return;
        }
		me->set_temp(me->query_temp("kl_xu")+1);
		me->add("neili", -900-random(100));

	    call_out("checking", 1,i,j, me);
}

void xu_end(int i,int j,object me)
{
	if (!me) return;
	
  
  
  //  me->add_temp("apply/attack", -i*2);   
    me->add_temp("apply/damage", -i*j);   
    me->delete_temp("kl_xu");
    me->delete_temp("kunlun_xu");
    me->start_busy(2+random(2));
    tell_object(me, HIW "\n�㰵�Ե�Ϣ�������ͷ������˫�ָ��ŵ������޼�������\n\n" NOR);

   return;
}

int help(object me)
{
	write(WHT"\n���ص���֮��"HBWHT+HIY"�"WHT"����"NOR"\n");
	write(@HELP
	���ص����������ɿ�����ʦ������ĸ߼����ֹ���
	�������ս������ʱ����������Ӳ����ս������Ҳ
	�������Ʒ��������Կ��������Ʒ�������ã�����
	�ޱ���Ȼ��������ʮ���Ƹ��ͣ���Ҳ�������֮����
	���ص��������ǽ��Լ�ƽ�������������ھ���ʹ˫
	��֮�У��������������Խ������Խ��
	���ص���������550�����ܿ�س���ָ���,�ھ���
	ʹԲת���⣬���в��������Ƿ��б��������ơ���
	�����������״̬��һ�롣
	���м�Ϊ�����������������������ã�����������
	���á�
	ע�⣺set ���ص���� xx��1-10�����ִ������
	�ľ���������Ĭ��ֵΪһ���ھ���
	
	ָ�perform strike.xu

Ҫ��     
	��ǰ���� 2000 ���ϣ�
	������� 15000 ���ϡ�
	�����Ʒ� 500  ���ϣ�
	���ص��� 500  ���ϣ�
	�����޼� 500  ���ϣ�
	������� 80   ���ϣ�
	�����ڹ�Ϊ�����޼�����
	�����Ʒ��ұ�Ϊ���ص���
	���ܺ��������ʹ��
HELP
	);
	return 1;
}
