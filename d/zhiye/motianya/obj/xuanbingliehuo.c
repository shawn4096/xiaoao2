// xuebingliehuo.c �����һ��
// ����ʹ��

//by sohu@xojh ������ϵ��

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW"����"HIR"�һ�"HIC"��"NOR, ({ "xuanbing liehuojiu","xuanbing" ,"jiu"}) );
        set("long",HIC"����ƿ�����һ�ƣ����ֺ�������������ʹ�ߺͷ���ʹ�������ơ�\n"
						+"���˺��ܵ����������������ں���һ��Ȼ����������\n"NOR);
        set("unit", "ƿ");
        set("weight", 90);
        set("no_sell",1);
        set("no_give",1);
        set("no_get",1);
        set("value", 0);
		set("remain", 20);//�ܺȶ�ʮ��

}

void init()
{
	add_action("do_drink","drink");
}

int do_sa(string arg)
{
	object me=this_player() , ob , bb;

	if (!arg) return notify_fail("��Ҫ��˭��\n");

	ob = present(arg, environment(me));
	if (!ob || !living(ob)) return notify_fail("��Ҫ��˭��\n");

	if (!wizardp(me) && ob->query("gender")!="����" )
		return notify_fail("��û�и��ѽ����ô���Ķ���Ҫ�õ��ؼ��ĵط���\n");
	
	if ((userp(ob) || ob->query("id")!="xie yanke"))
		return notify_fail("�㲻�����ʹ�������\n");
	
	if (ob->query("id")=="xie yanke")
		ob->kill_ob(me);
             // ob->unconcious();
              me->add("������/jiejiu3", 1);
	message_vision(HIM"$N"HIM"��л�̿����˹�ȥ������Ľе���л����~�����ӽ�ʱ���䲻����ָ����$n���ᵯ�˵��ĭ��\n"
			MAG"л�̿�������һ�л���һ�����������˭����������ʶ����Ȼ$n�Ų�����ҡҡ��׹��\n"NOR,me, ob);
         CHANNEL_D->do_channel(ob, "chat", "ǿ��һ������,�ƿڴ��������!"+ me->name(1)+ "���С������Ȼ�����������ֶ�ı�����ң�����ҵ���~~��\n");  
	       message_vision("\n˵�գ�л�̿�ƾ����ǿ��������һ��������ʩչ�����ṦһԾ������Զ����ȥ��\n", ob);

	destruct(ob);
	return 1;
}
