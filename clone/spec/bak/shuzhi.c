// shuzhi.c С��֦ For hubo quest by lsxk@hsbbs 2007/7/20
#include <ansi.h>

inherit SPEC; 

void create()
{
    set_name (HIC"С��֦"NOR, ({ "xiao shuzhi"}));
    set("long",HIY"����һ����ͨ��С��֦,С�����Ƕ�ϲ���������ڵ��ϻ���(hua).\n"NOR);

    set("unit","��");
	set_weight(100);
	set("value",3000000);
	
    set("no_give",1);
    set("no_drop",1);	
    set("no_get",1);
    set("treasure",1);
    set("degree",1);
    set("flag","spec/shuzhi");
    set("rest",3);
    set("desc","��˵������ͯ�Դ��书ʱ�ù��Ķ���!");
    set("credit",300);
	setup();
}

void init()
{
    add_action("do_hua","hua");
  
}

int do_hua(string arg)
{
	object me=this_player();
	
	    
    if (arg!="fangyuan" && arg!="��Բ"){
              message_vision(HIW"$N��С����һ��"HIC"С��֦"HIW"�ڵ��ϻ��Ų��.���ļ���....\n"NOR,me);
              return 1;
    }
      	
	if (!restrict()&& !me->query("buyvip")) {return notify_fail("�������Ѿ�����ʹ��"+this_object()->query("name")+"�ˡ�\n");}

    me->set_temp("sj_credit/quest/public/hubo",1);
    message_vision(HIR"$N��Ѫ����,��"HIC"С��֦"HIR"�۳���֦,������һ֦����,������һ֦��Բ,��Ȼ������һ��������һ����Բ!\n"+
    HIY"��Ȼ,������$N�����ֻ�������,��Բȴ��$N�����ֻ�������......\n"NOR,me);
    message_vision(HIG"$N�����ؾ��˾���,һ�Ѿͽ�С��֦ԶԶ�����˳�ȥ!\n"NOR,me);
	degree();
	return 1;
}	 
