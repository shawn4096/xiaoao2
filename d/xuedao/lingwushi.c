// nroad6.c
// Modified by Java Apr.27 1998

#include <ansi.h>
inherit ROOM;
int do_yandu(string arg);
void create()
{
        set("short","������");
        set("long",@LONG
Ѫ���ŵĲ�������֮�أ����ϵ������������˲���������ɮ��
���ƹ��죬����̫��Ѩ�����״��������Ȼ���������г�֮��������
���֮����ǽ���ݺύ�������Ŀ̺ۣ���Ȼ�Ǹ����Ե���ǽ�ϵ����
Щ����ͼ��(picture)���ܶ����ŵ����ڴ��ж���
LONG );
        set("exits",([
                "west"   : __DIR__"cave",
                "north" : __DIR__"shufang",
			    "east" : __DIR__"chucangshi",
		]));
//       set("objects",([            
				
       // ]));
	 	set("item_desc", ([
			"picture" : HIR"		Ѫ����---����ƪ"NOR
						+CYN"\n\n\n����һ������ͼ����һ�����ݸɿݵ��������ӣ�һ��ָ�죬һ��ָ��\n"
							+"��Ŀ���ǹ��죬�Ա�ע����������ɫ�Ĺ��֣�������򽣬������\n"
							+"������ͼ�����ӣ�����������Ŀ�������߶�������������\n"
							+"ò���ǹŹ֣�������֮�У������̲���һ������֮�������˲�����\n"
							+"�������ҡ���������ᡣ����������������������������������\n"NOR
							+"\n\n\n\nĩβ����["HIR"Ѫ������"NOR"] �ĸ����֡�\n"NOR,
		]));
        setup();
        //replace_program(ROOM);
}

void init()
{

	add_action("do_yandu","yandu");
}

int do_yandu(string arg)
{
	object me;
	mapping fam;
	me=this_player();

	if (!arg||arg!="ͼ��")
	{
		return notify_fail("��Ҫ�ۿ�ʲô���ݣ�\n");
	}
	if (me->query("class")!="huanxi"&&!me->query("qest/xuedao/shoujie"))
	{
		return notify_fail("�˵�����Ѫ���ž���֮�أ��������������ѵ�Ҫ͵��Ѫ������ѧô��\n");
	}
	
	if (me->query("family/family_name") != "Ѫ����")
		return notify_fail( RANK_D->query_respect(me) + "�����˼�Ѫ���Ų���֮�ܡ�\n");

	if( (string)me->query("gender") == "����" )
		return notify_fail("ʩ�������ȱ����˵�����ն�������������Ѫ������ȫ�������⣬.����\n");

	if (arg == "ͼ��"){		
			if(me->query("potential", 1) < 1)
				return notify_fail("���Ǳ��û�ˣ������ټ�����ϰ��\n");
			if(!(fam = me->query("family")) || fam["family_name"] != "Ѫ����")
				return notify_fail("�㲻��Ѫ���ŵ��ӣ����������Ѫ���ŵĸ����书��\n");
			if(me->query("gender") == "����")
				return notify_fail("���޸����ԣ����������������������Ѫ�����񹦡�\n");
			if(me->is_busy() || me->is_fighting())
				return notify_fail("����æ���ģ�\n");
			if(me->query("jing") < 25 )
				return notify_fail("��ľ���ܲ�, ����ȥ��Ϣһ��. \n");           
			if(me->query_skill("force", 1) < 20)
				return notify_fail("��Ļ����ڹ�̫�ͣ��޷���ϰ���߼����ڹ���\n");        
			//if(me->query_skill("xuedao-jing", 1) < 30)
				//return notify_fail("���Ѫ�����ȼ�̫�ͣ��޷�����ǽ�ϵ����֡�\n");
            if(me->query_skill("xuedao-jing", 1) > 100)
 				return notify_fail("���Ѫ�����񹦾���һ�㣬����ȥ�����и�����̸����书�ˡ�\n");
	
				write("�㿪ʼ��ϰǽ�ϵ����ͼ�Σ������������澭������ܶ����ѡ�\n");
				me->receive_damage("jing",(int) 150/me->query("int"));
                me->improve_skill("xuedao-jing", me->query_int() + random((int)me->query_int() * 5 / 3));

				me->add("potential", -1);
			return 1;

		
		
	}
	return notify_fail("��Ҫ��ϰʲô��\n");


}