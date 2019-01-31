// fojing21.c
#include <ansi.h>

inherit ITEM;

string* titles = ({
//	"������",
//	"άĦ��",
//	"������",
//	"���Ͼ�",
    "СƷ������",
	"�����پ�",
	"�Ӱ�����",
	"��վ�",
	"�����۶��ľ�",
});

void create()
{
	set_name(CYN+titles[random(sizeof(titles))]+NOR, ({ "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��𾭡�\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":	"buddhism",	// name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost":	15,	// jing cost every time study this
			"difficulty":	20,	
			"min_skill":	50, // the base int to learn this skill
			"max_skill":	100// the maximum level you can learn
		]) );
	}
}
/*
void init()
{
	if( this_player() == environment() )
	{
		add_action("do_tear", "tear");
	}
}

int do_tear(string arg)
{
	object me, bible;
	object where;

	if ( !arg )
	{
		return notify_fail("ʲô��\n");
	}

	me = this_player();

	if ( arg == "jing" || arg == "shu" || arg == "book" )
	{
		bible = new(CLASS_D("shaolin")+"/obj/book-jiuyang");
		where = environment(me);
		message_vision("$N����ذ���˺��������ͻȻ�������Ʈ�����ҳ��Ƥֽ��\n",
			this_player());
		bible->move(file_name(where));
		destruct(this_object());
	}

	return 1;
}*/
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


		if ((int)me->query_skill("buddhism", 1) > 100 ){
			write("�Ȿ���������˵�Ѿ�̫��ǳ�ˣ�\n");
			return 1;
			}
                neili_lost = 10;
                me->receive_damage("jing", 15,"����ԭ��");
                me->improve_skill("buddhism", (int)me->query_int()/3);
                write("��������ϰ�����ķ����飬�ƺ��е��ĵá�\n");
                return 1;

}
*/