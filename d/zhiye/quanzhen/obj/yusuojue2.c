// jinguan-yusuo
// ���������ʮ�ľ�
// by sohu
inherit ITEM;
#include <ansi.h>
void create()
{
	set_name(HIW"���������ʮ�ľ����²᡿"NOR, ({ "jinguan yusuo", "jinguan" , "yusuo", "book" }));
	set_weight(600);
	if( clonep() )
	set_default_object(__FILE__);
	else
	{
		set("unit", "��");
		set("long", "����һ����װ�飬���顶���������ʮ�ľ����²ᣩ��\n");
		set("value", 5000);
		set("treasure", 1);
		set("unique",1);
		set("no_give",1);
		set("no_drop",1);
		set("no_steal",1);
		set("material", "paper");
		set("skill", ([
			"name":			"jinguan-yusuojue",	// name of the skill
			"exp_required":	0,			// minimum combat experience required
			"jing_cost":	50,			// jing cost every time study this
			"difficulty":	45,			// the base int to learn this skill
			"min_skill":	100,	
			"max_skill":	200,			// the maximum level you can learn
			]) );
	}
}
