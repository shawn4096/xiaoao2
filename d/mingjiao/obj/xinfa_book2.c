// shenghuo-xinfa.c �ڹ��ķ�

inherit ITEM;

void create()
{
	set_name("ʥ���ķ�(��)", ({ "shenghuo xinfa", "xinfa" , "book" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", 
"����һ���ֳ�������ʥ���ķ�(�¾�)�����Ž��������̵�ʥ���񹦺�Ǭ����Ų�ƾ�����������ɡ�\n"
"������������Ļ��˲��ٴ������ŵ����ơ����̵��ӿ��Զ����������ľ���\n"
		);				
		set("value", 1000);
		set("material", "paper");
		set("skill", ([
			"name":	"shenghuo-xinfa",	// name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost":	50,	// jing cost every time study this
			"difficulty":	40,	// the base int to learn this skill
			"max_skill":	200	// the maximum level you can learn
		]) );
	}
}
