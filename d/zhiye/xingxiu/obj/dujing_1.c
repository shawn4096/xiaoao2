#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("�����޶������ϲ᡽��", ({ "du jing", "jing" }) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
                set("long",
"\n                 �����޶������ϲ᡽��\n\n"
"��������Ϊ���ޱ��䣬���Դ˾�����������ҩ��˽�����ˣ�����Ϊ��ʦ���桢\n"
"����ʦ�š�����ʦ֮ͽ����������أ�����ӱ�����֮�����˳��б����ߣ���\n"
"���Ӽ�һ��ɱһ������ʮ��ɱʮ�����ϲ���˽�ı��ű����߹���������\n\n"
"�����������������������������������������������������������ɡ���\n"
"���ɺ�ҩ��\n"
"���÷�����ҩ�����ˮ�����˺��£�pour yao in <����>����\n"
"��ҩ�ԣ�����������ʹ�˻��ʡ���������ǿ�ߣ�ҩЧ���ԡ�\n\n"
"����ҩ��\n"
"���÷�����ҩ�����ˮ�����˺��£�pour yao in <����>����\n"
"��ҩ�ԣ�������Ů������������٣���Ϊ�����á�\n\n"
"���ϳ�ɢ��\n"
"���÷�����ҩ�����ˮ�����˺��£�pour yao in <����>����\n"
"��ҩ�ԣ���ҩ��γ���϶�����������ǿ�ߣ�ҩЧ���ԡ�\n\n"
"������ɢ��\n"
"���÷����̷���eat san����\n"
"��ҩ�ԣ�Ϊ���Ŷ��Ž�ҩ���ɽ�ϳ�ɢ�����޶���֮����\n"
"    \n");
		set("value", 50);
		set("material", "paper");
		set("unit", "��");
                set("value", 100000);
                set("unique", 1);
                set("treasure",1);
                set("skill", ([
                        "name":"poison",       // name of the skill
                        "exp_required": 3000, // minimum combat experience required
                                              // to learn this skill.
                        "jing_cost": 20,      // jing cost every time study this
                        "difficulty": 20,     // the base int to learn this skill
                                              // modify is jing_cost's (difficulty - int)*5%
                        "max_skill": 50       // the maximum level you can learn
                                              // from this object.
                ]));
	}
	setup();
}
