// zhanshu.c ����ս�� For hs 9jian quest  by lsxk@hsbbs 2007/7/18
#include <ansi.h>

inherit SPEC; 

void create()
{
    set_name (HIW"����ս��"NOR, ({ "zhanshu"}));
    set("long",HIW"����һ��ս�飬�����˵�������Ȼ�������ˣ������ȴ���������ĸ����֡�����������ܡ���\n"NOR);

    set("unit","��");
	set_weight(100);
	set("value",3000000);
	
    set("no_give",1);
    set("no_drop",1);	
    set("no_get",1);
    set("treasure",1);
    set("degree",1);
    set("flag","spec/zhanshu");
    set("rest",3);
    set("desc","��˵�ǽ�ħ��������µ�ս�飡");
    set("credit",800);
	setup();
}

void init()
{
    add_action("do_yuedu","yuedu");
  
}

int do_yuedu(string arg)
{
	object me=this_player();
	
	    
    if (arg!="zhanshu")
                    return notify_fail("��Ҫ�Ķ�ʲô?\n");
      	
	if (!restrict()&& !me->query("buyvip")) {return notify_fail("�������Ѿ�����ʹ��"+this_object()->query("name")+"�ˡ�\n");}

    me->set_temp("sj_credit/quest/hs/jiujian",1);
    write(HIW"���Ķ��Ŷ���ս�飬�����Ѿ��������ˣ�������ȴ������\n"NOR);
    write(HIR"\n    ���ݺὭ��һ�������޶��֣�����һ�ܶ����ɣ��غ����գ�\n�ѵ�������֮�£�Ī����û������"HIW"���¾Ž�"HIR"�Ķ�����ô��\n\n"NOR);
    write(HIW"�㵱�´󺧣�����������¾Ž������¾Ž����������ѵ�������������˸����Ľ���ô��\n"NOR);
    write(HIW"�漴���㵭ȻһЦ�����룬�����ĸ�����֮����������֮�ƣ����޿��Ŷ��ԣ�˳�ֱ㽫ս��������һ�ԣ�\n"NOR);
	degree();
	return 1;
}	 
