#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY"ͭ��"NOR, ({ "tong gang","tonggang","gang"}) );
        set_weight(30000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
				set("value", 250000);
                set("material", "iron");
				set("armor_prop/armor", 6);
			   // set("weight",10000);
				set("water",100);

        }
        setup();
}
int init()
{
	add_action("do_ju","ju");

}

int do_ju(string arg)
{
	object me,gang;
	me=this_player();

	if (!arg||arg!="ͭ��")
	{
		return notify_fail("��Ҫ��ʲô��\n");
	}
	
	gang=present("tong gang",environment(this_object()));
	if (!gang) return notify_fail("�˵�û��ͭ��,��Ҫ����ʲô����\n");
	
	message_vision(HIR"$N����������ŭ��һ�����˾��ڱۣ����Ǹ�ʢ��ˮ�Ĵ�ͭ�׾�����!\nȻ��Хһ���������˾�㵵������У�ƮȻ��ȥ��\n"NOR,me);

	gang->move(me);

	me->set_temp("quest/���Ӣ�۴�/�����߹�/jugang",1);
	return 1;
}