// daodejing.c
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name( HIC"���¾�"NOR, ({ "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��ȫ�����¾���������������ļ�¼�˸���ע�⣬ֽ�ʷ��ƣ�һ�����������Զ֮�\n");
		set("value", 500);
		set("treasure",1);
		set("unique",1);
		set("material", "paper");
		set("skill", ([
			"name":	"taoism",	// name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost": 20+random(20),// jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
			
			"max_skill":	200	// the maximum level you can learn
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
        if (!(arg=="shu" ||arg=="book" ))
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


		if ((int)me->query_skill("taoism", 1) > 200 ){
			write("�Ȿ���������˵�Ѿ�̫��ǳ�ˣ�\n");
			return 1;
			}
                neili_lost = 10;
                me->receive_damage("jing", 35,"����ԭ��");
                me->improve_skill("taoism", (int)me->query_int()/3);
                write("��������ϰ���ӵ��¾������ڵ����ķ��ƺ��е��ĵá�\n");
                return 1;

}
*/