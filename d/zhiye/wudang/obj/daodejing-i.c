// daodejing-i.c
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name( CYN"���¾����Ͼ�"NOR, ({ "daode jing","jing"  }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ����¾����Ͼ����������һʼ��ȥ�õ���ʮֹ��\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":	"taoism",	// name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost": 20, 	// jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
			"max_skill":	100,	// the maximum level you can learn
		]) );
	}
}
/*
void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
}    
int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        int dzlevel; 
        int neili_lost;
        if (!(arg=="jing" ||arg=="daode jing" ))
        return 0;

        if (where->query("pigging")){
                write("�㻹��ר�Ĺ���ɣ�\n");
                return 1;
        }
        if (me->is_busy()) {
                write("��������æ���ء�\n");
                return 1;
        }

        if( me->is_fighting() ) {
                write("���޷���ս����ר�������ж���֪��\n");
                return 1;
        }

        if (!id(arg)) { 
                write("��Ҫ��ʲô��\n");
                return 1;
        }
	
        if( !me->query_skill("literate", 1) ){
                write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
                return 1;
        }

        if( (int)me->query("jing") < 15 ) {
                write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
                return 1;
        }
        
        if( (int)me->query("neili") < neili_lost) {
                write("�������������޷�������ô������书��\n");
                return 1;
        }


		if ((int)me->query_skill("taoism", 1) > 100 ){
			write("�Ȿ���������˵�Ѿ�̫��ǳ�ˣ�\n");
			return 1;
			}
                neili_lost = 10;
                me->receive_damage("jing", 15,"����ԭ��");
                me->improve_skill("taoism", (int)me->query_int()/3);
                write("��������ϰ���ӵ��¾������ڵ����ķ��ƺ��е��ĵá�\n");
                return 1;

}
*/