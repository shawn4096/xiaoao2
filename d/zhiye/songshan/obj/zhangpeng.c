// OBJECT:  ice.c 玄冰
// Created by Numa 1999-12-09

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIW"嵩山剑派接待帐篷"NOR,({"zhang peng"}));
	set_weight(20000000);
     if (clonep())

        	set_default_object(__FILE__);
     	else
     	{

        	set("unit", "个");
        	set("long", "这是一顶嵩山派专门负责接待临时帐篷，排成一排，气势如虹！弟子们迎来送往，非常热闹。\n");
        	set("value", 1);
        	set("no_get", 1); 
			set("no_steal",1);
        	//set("unique",1);
        	set("location",1);
        	//set_temp("no_return",1);
        }
     	setup();  
}

