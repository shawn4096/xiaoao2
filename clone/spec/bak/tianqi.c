//flowray 2005.6.20
#include <ansi.h>


inherit SPEC; 

void create()
{
	set_name (HIC"田七鲨胆散"NOR, ({"tianqi","san"}));
	
	set("long",HIW"采集田七鲨胆精心练制的疗伤秘药。\n"NOR);

	set("unit","份");
	set_weight(100);
	set("value",3000000);
//  set("no_give",1);
  set("no_drop",1);  
  set("no_get",1);
        set("degree",1);
	set("flag","spec/tianqi");
	set("desc","可以治疗各种顽固的杂症。");
        set("credit",20);       
	setup();
}

void init()
{
	add_action("do_eat","eat");
  
}

int do_eat(string arg)
{
        object me = this_player();
        if (!id(arg))
              return notify_fail("你要吃什么？\n");
        me->clear_conditions_by_type("poison");
        me->clear_condition("no_perform");
        me->clear_condition("no_exert");
        me->clear_condition("no_force");
        me->clear_condition("neishang");
        me->clear_condition("yyz_hurt");
        me->clear_condition("yzc_qiankun");
        me->clear_condition("fx_busy");
        me->clear_condition("hunyuan_hurt");
        me->clear_condition("no_enforce");
        me->clear_conditions_by_type("hurt");
	      me->clear_conditions_by_type("wound");
        message_vision(HIR"$N服下一份田七鲨胆散，一股清凉的气息自丹田涌上来。\n"NOR, this_player());
//        destruct(this_object());
       degree();
	     return 1;
}	 
