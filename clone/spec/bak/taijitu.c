// taijitu.c ̫��ͼ For wd taiji quest by lsxk@hsbbs 2007/7/18
#include <ansi.h>

inherit SPEC; 

void create()
{
    set_name (WHT"̫��ͼ"NOR, ({ "taiji tu"}));
    set("long",WHT"����һ��̫��ͼ�����������̫���ھ�Ҫ�죬����̫��ȭ��̫������������ƺ����Դ�������ʲô��\n"NOR);

    set("unit","��");
	set_weight(100);
	set("value",3000000);
	
    set("no_give",1);
    set("no_drop",1);	
    set("no_get",1);
    set("treasure",1);
    set("degree",1);
    set("flag","spec/taijitu");
    set("rest",3);
    set("desc","�ƺ����䵱�ɿ�ɽ��ʦ������֮��!");
    set("credit",800);
	setup();
}

void init()
{
    add_action("do_yanjiu","yanjiu");
  
}

int do_yanjiu(string arg)
{
	object me=this_player();
	
	    
    if (arg!="taiji tu")
                    return notify_fail("��Ҫ�о�ʲô?\n");
      	
   	if (!restrict()&& !me->query("buyvip")) {return notify_fail("�������Ѿ�����ʹ��"+this_object()->query("name")+"�ˡ�\n");}

    me->set_temp("sj_credit/quest/wd/taiji",1);
    write(HIG"�㾲���о���"WHT"̫��ͼ"HIG"ͻȻ�����Լ������˲���̫������!\n"NOR);
	degree();
	return 1;
}	 
