 //wine.c 2009 By fengyue
#include <ansi.h>

 
inherit SPEC; 

void create()
{
        set_name (HIG"�����"NOR, ({ "houer jiu", "jiu" }));
        set("long","����һ̳��ɽ�к������ɽ��Ұ�����Ƶľƣ��׳�"+HIG"�����"NOR"������(he)������������������\n");
        set("unit","С̳");
        set_weight(100);
        set("value",3000000);
        set("no_give",1);
        set("no_drop",1);
        set("no_cun",1);
        set("degree",1);
        set("flag","spec/wine");
        set("desc","����Ѫ����Ѫ��ʢ��");
        //set("credit",2000);
		setup();
} 
 
void init()
{
        add_action("do_he","he");
   
}
 
int do_he(string arg)
{
        object me=this_player();
        
        if (me->query_temp("wine_power"))  return notify_fail("����к����彡�������ε�½���Ѿ������ٶ���ˣ�\n");

		if (arg!="houer jiu" && arg!="jiu")
                 return notify_fail("��Ҫ��ʲô?\n");
        if (!restrict()) return notify_fail("����к����彡�����������Ѿ������ٶ���ˣ�\n");
        
        me->add_temp("apply/force",100);
		//me->add_temp("apply/dodge",100);
        //me->add_temp("apply/parry",100);
        me->add_temp("apply/damage",100);
		//me->add_temp("apply/damage",100);
        me->add_temp("apply/attack",100);
		me->set("neili",me->query("max_neili")*2-1);

		me->set_temp("wine_power",1);
		write(HIY"���ͳ���һС̳"HIG"�����"HIY"�����˹��˵���ͷ������ȥ��\n"NOR); 
		write(HIY"ֻ��һ�ɾ���͸��֫�ٺ�����پ�����������������ӿ������\n"NOR); 
        degree();
        return 1;
}    
