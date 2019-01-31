// fengyun.c
// Modified by Lane@SJ 2005/4/14

#include <ansi.h>

int exert(object me)
{
	int improve;

	if( me->query("class") != "bonze" && me->query("family/generation") >4)
		return notify_fail("�㲻�ǳ����ˣ��޷�����ټ�ʮ��ׯ�ġ����ơ��־���\n");
        
	if( (int)me->query_skill("linji-zhuang", 1) < 150 )
		return notify_fail("����ټ�ʮ��ׯ��Ϊ��������\n");
    if(me->query("family/family_name")!="������")
		return notify_fail("�㲻�Ƕ����ɣ���ô���ܻ����־�����\n");
	//if(me->query("family/master_name")!="���ʦ̫")
	//	return notify_fail("��û���ܵ�����ʦ��ĵ���ָ������ô���ܻ��������ķ�������\n");
	if((int)me->query("neili") < 500 )
		return notify_fail("�������������\n");
    if((int)me->query("max_neili") < 1500 )
		return notify_fail("����������������\n");
	if((int)me->query("jingli") < 500 )
		return notify_fail("��ľ���������\n");
	if((int)me->query_skill("dodge",1) < 150 )
		return notify_fail("��Ļ����Ṧ������\n");
	if((int)me->query_skill("anying-fuxiang",1) < 150 )
		return notify_fail("��İ�Ӱ���㼼�ܲ�����\n");
	if( me->query_temp("ljz/fengyun") )
		return notify_fail("�����������ټ�ʮ��ׯ�ġ����ơ��־���\n");

	tell_object(me,HIW"�㰵�˷���׮�ķ�����˼����Ʈ��֮���л�����Ĭ���絴��֮Ѹ�ٽ���һ�ɵ���������ע��֫�ٺ�������������������ࡣ\n"NOR, me);
	tell_room(environment(me), HIW"ֻ��"+me->name()+"΢��˫�ۣ���������һȦ����˲Ϣ��һ���������������ָ�������\n"NOR,({ me }));
	improve = (int)me->query("dex")+(int)me->query_skill("linji-zhuang",1)/20;
	if (me->query("class") != "bonze")
	   improve = (int)me->query("dex");
	if (me->query_skill("jiuyin-zhengong",1)>150)
	{
		message_vision(HBBLU+HIW"$N����һ�������������澭�Ĺ�����ټ�ׯ�����ںϣ�������Ʈ�ݣ�\n"NOR,me);
		improve=improve+me->query_skill("jiuyin-zhengong",1)/3;
	}
	me->add_temp("apply/dexerity", improve);
	me->set_temp("ljz/fengyun", improve);  
	me->add("neili", - 150);    
	me->start_exert(1 , "�����ơ��־�");
	call_out("remove_effect", (int)me->query_skill("dodge",1)/3 , me );
	return 1;
}

void remove_effect(object me)
{
	int i;
	if(!me || !me->query_temp("ljz/fengyun")) return;

		i = me->query_temp("ljz/fengyun");
		me->add_temp("apply/dexerity", -i);
		me->delete_temp("ljz/fengyun");
		if ( living(me) && ! me->is_ghost()) 
			tell_object(me, HIW"����ƾ��й��Ѿã��Ծ����ĳ�����һЩ��\n"NOR);
		return;

}

string exert_name(){ return RED"�����־�"NOR; }

int help(object me)
{
    write(HIR"\n�ټ�ʮ��ׯ�������־�����"NOR"\n\n");
    write(@HELP
	�ټ�ʮ��ׯ�˶����������ڹ��ķ����ǿ�ɽ��ʦ�����ں����Լ�һ��
	�������ŵ������ڹ����ķ����ں϶��ɣ����о����񹦵ĸ��ͣ�����
	�����澭��������ᣬ�˵��������ķ���ϵ��
	�������־�����Ҫ��ͨ����ʹ�ټ�ׯ�ķ���ʹ�������������ķ���
	���ҵ�����õ������������ʦ̫���ڡ�Ч�����ѡ���ע�⣬ֻ�а�
	ʦ���ʦ̫����ʹ�á������׼Ҿ���ʹ�ã����׼������ơ�

ָ��: exert fengyun

Ҫ��
	��ǰ������Ҫ�� 500  ���ϣ�
	���������Ҫ�� 1500 ���ϣ�
	�ټ�ʮ��ׯҪ�� 150  ���ϣ�
	�����Ṧ��Ҫ�� 150  ���ϣ�
	��Ӱ�����Ҫ�� 150  ���ϣ�

HELP
        );
        return 1;
}
