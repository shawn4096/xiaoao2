// Modified by Lane@SJ 2005/4/14
// edit by sohu@xojh 2014.1
#include <ansi.h>
int exert(object me)
{
   int cure;
  
   if( !me->is_fighting() )
      return notify_fail("��������ô�У������������˰ɡ�\n");
   if( me->query("class") != "bonze" && me->query("family/generation") > 4 )
		return notify_fail("�㲻�ǳ����ˣ��޷�����ټ�ʮ��ׯ�ġ����ҡ��־���\n");

   if( (int)me->query_skill("linji-zhuang", 1) < 300 )
      return notify_fail("����ڹ���Ϊ��������\n");

   if( (int)me->query_skill("medicine", 1) < 120 )
      return notify_fail("��ı���������Ϊ��������\n");

    if( (int)me->query("neili") < 3000 )
       return notify_fail("�������������\n");

    if( (int)me->query("eff_qi") >= (int)me->query("max_qi") )
        return notify_fail("û���ˣ���ʲô�˰���\n");

    if( (int)me->query("eff_qi") < (int)me->query("max_qi")*3/10 ) // ��Ϊ30%����
        return notify_fail("���Ѿ����˹��أ����ܲ��������𵴣�\n");

    if( me->query_temp("ljz/wuwo") )// �ĳ� ���ܺ� wuwo ͬʱʹ��
       return notify_fail("�����������ټ�ʮ��ׯ�ġ����ҡ��־���\n");
    if (me->query("emjy/pass"))
	{
	   message_vision(HIR"$N�沿����һƬ����֮ɫ�����Ҿ��������������治ͬ���졣\n"NOR,me);
	   cure=(int)me->query_skill("linji-zhuang",1)+(int)me->query_skill("medicine",1)+(int)me->query_skill("jingmai-xue",1);
	 }
    else  cure=(int)me->query_skill("linji-zhuang",1)/2+(int)me->query_skill("medicine",1)/2+(int)me->query_skill("jingmai-xue",1)/2;
   
    message_vision(HIW"$N�����ټ�ׯ���׮���ؾ���ȫ���������������������������ƣ���ɫ�����ö��ˡ�\n"NOR,me);
    me->receive_curing("qi",cure );
    me->add("neili", -100);
    me->start_exert(1,"���");
    if (me->is_busy())
       me->add_busy(1);
	else me->start_busy(1);
    return 1;
}
string exert_name(){ return HIG"����־�"NOR; }

int help(object me)
{
        write(HIW"\n�ټ�ʮ��ׯ������־�����"NOR"\n\n");
        write(@HELP
	�����ټ�ׯ���ǿ�����ʦ����Ů�������˼Ҵ���ѧ�Լ������澭��
	�����������������������ž�ΪŮ�ԣ����Զ����ڹ�������Ȼ��
	���������Ҽ�Ϊʵ�á�
	��ؾ�������ս�����������á��ͱ����Լ�����ѧ�������ڹ��ȼ�
	����Ӱ�졣����Խ������Ч��Խ�ã���ֻ��ս�������ˣ������Ҿ�
	�г�ͻ��450���ɡ�
	
ָ�exert tiandi

Ҫ��  
	��ǰ���� 3000 ���ϣ�
	�ټ�ʮ��ׯ�ȼ� 300 ���ϣ�
	�������� 120 ���ϣ�
	���ܺ͡����ҡ��־�ͬʱʹ�á�
HELP
        );
        return 1;
}
